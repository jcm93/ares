//NEC uPD75006 (G-631)
//4-bit MCU HLE

auto MCD::CDD::load(Node::Object parent) -> void {
  dac.load(parent);
}

auto MCD::CDD::unload(Node::Object parent) -> void {
  dac.unload(parent);
}

auto MCD::CDD::clock() -> void {
  if(++counter < 434) return;
  counter = 0;

  //75hz
  if(!hostClockEnable) return;

  if(statusPending) {
    statusPending = 0;
    irq.raise();
  }

  switch(io.status) {

  case Status::Stopped: {
    io.status = mcd.fd ? Status::ReadingTOC : Status::NoDisc;
    io.sector = 0;
    io.sample = 0;
    io.track  = 0;
  } break;

  case Status::ReadingTOC: {
    io.sector++;
    if(!session.inLeadIn(io.sector)) {
      io.status = Status::Paused;
      if(auto track = session.inTrack(io.sector)) io.track = track();
      io.tocRead = 1;
    }
  } break;

  case Status::Playing: {
    readSubcode();
    if(session.tracks[io.track].isAudio()) break;
    mcd.cdc.decode(io.sector);
    advance();
  } break;

  case Status::Tracking: [[fallthrough]]; // TODO: implement tracking logic
  case Status::Seeking: {
    if(io.latency && --io.latency) break;
    io.status = io.seeking;
    if(auto track = session.inTrack(io.sector)) io.track = track();
  } break;

  }
}

auto MCD::CDD::advance() -> void {
  // Calculate the sector advance amount based on the MegaLD playback modes, if applicable.
  i32 sectorAdvanceOffset = 1;
  if (MegaLD()) {
    switch (mcd.ld.currentPlaybackMode) {
    case 0x00:
      // Normal playback. Nothing to do.
      sectorAdvanceOffset = 1;
      io.sectorRepeatCount = 0;
      break;
    case 0x01:
      // Frame skipping. This only affects the analog video update rate.
      //##TODO##
    case 0x02:
      // Frame stepping.
      switch (mcd.ld.currentPlaybackSpeed) {
      case 0x00:
        //-0x0: 0 frames. This pauses playback in frame stepping mode, and performs a normal playback in frame skipping mode.
        sectorAdvanceOffset = 0;
        io.sectorRepeatCount = 0;
        break;
      case 0x01:
        //-0x1: 1 frame only. The image will not update after the initial frame. Note that under frame step mode, output register
        // 0x07 will report this step speed as 0x1 only until the single frame step has been performed, after which, the output
        // register will now state a value of 0x0.
        if (io.sectorRepeatCount == 0) {
          sectorAdvanceOffset = 1;
          io.sectorRepeatCount = 1;
        } else {
          sectorAdvanceOffset = 0;
        }
        break;
      case 0x02:
        //-0x2: 1 frame every 0.0625 seconds (100 frames every 16 seconds) (1.875 times slower)
        //##FIX## Rounded to 2
        sectorAdvanceOffset = (++io.sectorRepeatCount >= 30 ? 2 : 0);
        break;
      case 0x03:
        //-0x3: 1 frame every 0.133r seconds (4 frames every 3 seconds) (4 times slower)
        sectorAdvanceOffset = (++io.sectorRepeatCount >= 4 ? 1 : 0);
        break;
      case 0x04:
        //-0x4: 1 frame every 0.25 seconds (7.5 times slower)
        //##FIX## Rounded to 8
        sectorAdvanceOffset = (++io.sectorRepeatCount >= 8 ? 1 : 0);
        break;
      case 0x05:
        //-0x5: 1 frame every 0.5 seconds (15 times slower)
        sectorAdvanceOffset = (++io.sectorRepeatCount >= 15 ? 1 : 0);
        break;
      case 0x06:
        //-0x6: 1 frame per second (30 times slower)
        sectorAdvanceOffset = (++io.sectorRepeatCount >= 30 ? 1 : 0);
        break;
      case 0x07:
        //-0x7: 1 frame every 3 seconds (90 times slower)
        sectorAdvanceOffset = (++io.sectorRepeatCount >= 90 ? 1 : 0);
        break;
      }
      sectorAdvanceOffset = (mcd.ld.currentPlaybackDirection ? (i32)(-sectorAdvanceOffset) : sectorAdvanceOffset);
      io.sectorRepeatCount = (sectorAdvanceOffset != 0 ? (i32)0 : io.sectorRepeatCount);
      break;
    case 0x03:
      // Fast forward.
      switch (mcd.ld.currentPlaybackSpeed) {
      case 0x00:
        sectorAdvanceOffset = 1;
        break;
      case 0x01:
        sectorAdvanceOffset = 2;
        break;
      case 0x02:
        sectorAdvanceOffset = 3;
        break;
      case 0x03:
        sectorAdvanceOffset = 8;
        break;
      case 0x04:
        sectorAdvanceOffset = 14;
        break;
      case 0x05:
        sectorAdvanceOffset = 20;
        break;
      case 0x06:
      case 0x07:
        //##TODO## Unimplemented
        //       -0x7/0x06: Search mode. Plays 0.75 seconds of footage forwards in time, with audio, then jumps either forward or back
        //        4 seconds from the resulting point. Note that setting this register to 0x07 is the same as 0x06, but 0x06 is the value
        //        that is reported back as the current mode in either case by output register 0x07.
        break;
      }
      sectorAdvanceOffset = (mcd.ld.currentPlaybackDirection ? (i32)(-sectorAdvanceOffset) : sectorAdvanceOffset);
      io.sectorRepeatCount = 0;
      break;
    }
  }

  if(auto track = session.inTrack(io.sector + sectorAdvanceOffset)) {
    io.track = track();
    io.sector += sectorAdvanceOffset;
    io.sample = 0;

    if (MegaLD()) {
      // Only update the displayed video frame if the image hold bit isn't set
      if (!mcd.ld.inputRegs[0x0C].bit(5)) {
        mcd.ld.updateCurrentVideoFrameNumber(io.sector);
      }
    }

    if (stopPointEnabled && (io.sector == targetStopPoint)) {
      reachedStopPoint = true;
      io.status = Status::Paused;
    }
    return;
  }

  if ((io.sector + sectorAdvanceOffset) < 0) {
    io.status = Status::LeadIn;
    io.track = 0xa00;
  } else {
    io.status = Status::LeadOut;
    io.track = 0xaa;
  }
}

auto MCD::CDD::sample() -> void {
  i16 digitalSampleLeft  = 0;
  i16 digitalSampleRight = 0;
  if(io.status == Status::Playing) {
    if(session.tracks[io.track].isAudio()) {
      mcd.fd->seek((abs(session.leadIn.lba) + io.sector) * 2448 + io.sample);
      digitalSampleLeft  = mcd.fd->readl(2);
      digitalSampleRight = mcd.fd->readl(2);
      io.sample += 4;
      if(io.sample >= 2352) advance();
    }
  }

  if (MegaLD()) {
    // Disable digital audio if it is turned off
    //if (!mcd.ld.inputRegs[0x01].bit(7)) {
    //  digitalSampleLeft = 0;
    //  digitalSampleRight = 0;
    //}
    // Attenuate the digital audio using the digital audio fader
    //##TODO## Fully reverse enginner input reg 0x0D and take bits 4-7 into account for digital audio
    float digitalAudioFader = (float)mcd.ld.inputRegs[0x0F] / (float)((1 << 8) - 1);
    digitalSampleLeft = (int16_t)((float)digitalSampleLeft * digitalAudioFader);
    digitalSampleRight = (int16_t)((float)digitalSampleLeft * digitalAudioFader);
    // Take digital left/right exclusive register state into account
    if (mcd.ld.inputRegs[0x0D].bit(0) && mcd.ld.inputRegs[0x0D].bit(1)) {
      digitalSampleLeft /= 2;
      digitalSampleRight /= 2;
    } else if (mcd.ld.inputRegs[0x0D].bit(0)) {
      digitalSampleRight = digitalSampleLeft;
    } else if (mcd.ld.inputRegs[0x0D].bit(1)) {
      digitalSampleLeft = digitalSampleRight;
    }
    // Retrieve the next analog audio sample
    i16 analogSampleLeft = 0;
    i16 analogSampleRight = 0;
    auto analogAudioSamplePos = (io.sector * 2352) + io.sample + (mcd.ld.analogAudioLeadingAudioSamples * 4);
    if ((analogAudioSamplePos + 3) < mcd.ld.analogAudioRawDataView.size()) {
      analogSampleLeft = (i16)((u16)mcd.ld.analogAudioRawDataView[analogAudioSamplePos + 0] | (u16)(mcd.ld.analogAudioRawDataView[analogAudioSamplePos + 1] << 8));
      analogSampleRight = (i16)((u16)mcd.ld.analogAudioRawDataView[analogAudioSamplePos + 2] | (u16)(mcd.ld.analogAudioRawDataView[analogAudioSamplePos + 3] << 8));
    }
    // Disable analog audio if it is turned off
    if (!mcd.ld.inputRegs[0x01].bit(7) && !mcd.ld.inputRegs[0x0D].bit(4)) {
      analogSampleLeft = 0;
      analogSampleRight = 0;
    }
    // Take analog mute and left/right exclusive register state into account
    if (mcd.ld.inputRegs[0x0E].bit(7) || (mcd.ld.inputRegs[0x0E].bit(0) && mcd.ld.inputRegs[0x0E].bit(1))) {
      analogSampleLeft = 0;
      analogSampleRight = 0;
    } else if (mcd.ld.inputRegs[0x0E].bit(0)) {
      analogSampleRight = analogSampleLeft;
    } else if (mcd.ld.inputRegs[0x0E].bit(1)) {
      analogSampleLeft = analogSampleRight;
    }
    // Audio is disabled in frame stepping mode
    if (mcd.ld.currentPlaybackMode == 0x02) {
      digitalSampleLeft = 0;
      digitalSampleRight = 0;
      analogSampleLeft = 0;
      analogSampleRight = 0;
    }
    // Attenuate the analog audio
    //##TODO## Fully reverse engineer input regs 0x1E and 0x1F to provide analog audio attenuation
    // Mix analog and digital audio together
    i16 combinedSampleLeft = (int16_t)std::clamp((int)digitalSampleLeft + (int)analogSampleLeft, (int)std::numeric_limits<int16_t>::min(), (int)std::numeric_limits<int16_t>::max());
    i16 combinedSampleRight = (int16_t)std::clamp((int)digitalSampleRight + (int)analogSampleRight, (int)std::numeric_limits<int16_t>::min(), (int)std::numeric_limits<int16_t>::max());
    // Output the combined sample
    dac.sample(combinedSampleLeft, combinedSampleRight);
  } else {
    dac.sample(digitalSampleLeft, digitalSampleRight);
  }
}

//convert sector# to normalized sector position on the CD-ROM surface for seek latency calculation
auto MCD::CDD::position(s32 sector) -> double {
  static const f64 sectors = 7500.0 + 330000.0 + 6750.0;
  static const f64 radius = 0.058 - 0.024;
  static const f64 innerRadius = 0.024 * 0.024;  //in mm
  static const f64 outerRadius = 0.058 * 0.058;  //in mm

  sector += session.leadIn.lba;  //convert to natural
  return sqrt(sector / sectors * (outerRadius - innerRadius) + innerRadius) / radius;
}

auto MCD::CDD::readSubcode() -> void {
  if(!mcd.fd) return;

  mcd.fd->seek(((abs(mcd.cdd.session.leadIn.lba) + io.sector) * 2448) + 2352);
  vector<u8> subchannel;
  subchannel.resize(96);
  mcd.fd->read({subchannel.data(), 96});

  io.subcodePosition += 49;
  n6 index = io.subcodePosition;

  //subchannel data is stored by ares as 12x8 for each channel (PQRSTUVW)
  //we need to convert this back to the raw subchannel encoding as per EMCA-130
  for(int i = 0; i < 96; i+= 2) {
    n16 data = 0;
    for(auto channel : range(8)) {
      n8 input = subchannel[(channel * 12) + (i / 8)];
      n2 bits = input >> (6 - (i & 6));
      data.bit( 7 - channel) = bits.bit(0);
      data.bit(15 - channel) = bits.bit(1);
    }

    subcode[index++] = data;
  }

  mcd.irq.subcode.raise();
}

auto MCD::CDD::process() -> void {
//if(command[0]) print("CDD ", command[0], ":", command[3], "\n");

  if(!valid()) {
    //unverified
    debug(unusual, "[MCD::CDD::process] CDD checksum error");
    io.status = Status::ChecksumError;
  }

  else
  switch(command[0]) {

  case Command::Idle: {
    //fixes Lunar: The Silver Star
    if(!io.latency && status[1] == 0xf) {
      status[1] = 0x2;
      status[2] = io.track / 10; status[3] = io.track % 10;
    }
  } break;

  case Command::Stop: {
    stop();
    status[1] = 0x0;
    status[2] = 0x0; status[3] = 0x0;
    status[4] = 0x0; status[5] = 0x0;
    status[6] = 0x0; status[7] = 0x0;
    status[8] = 0x0;
  } break;

  case Command::Request: {
    switch(command[3]) {

    case Request::AbsoluteTime: {
      auto [minute, second, frame] = CD::MSF(io.sector);
      status[1] = command[3];
      status[2] = minute / 10; status[3] = minute % 10;
      status[4] = second / 10; status[5] = second % 10;
      status[6] = frame  / 10; status[7] = frame  % 10;
      status[8] = session.tracks[io.track].isData() << 2;
    } break;

    case Request::RelativeTime: {
      auto [minute, second, frame] = CD::MSF(io.sector - session.tracks[io.track].indices[1].lba);
      status[1] = command[3];
      status[2] = minute / 10; status[3] = minute % 10;
      status[4] = second / 10; status[5] = second % 10;
      status[6] = frame  / 10; status[7] = frame  % 10;
      status[8] = session.tracks[io.track].isData() << 2;
    } break;

    case Request::TrackInformation: {
      status[1] = command[3];
      status[2] = io.track / 10; status[3] = io.track % 10;
      status[4] = 0x0; status[5] = 0x0;
      status[6] = 0x0; status[7] = 0x0;
      status[8] = 0x0;
      if(session.inLeadIn (io.sector)) { status[2] = 0x0; status[3] = 0x0; }
      if(session.inLeadOut(io.sector)) { status[2] = 0xa; status[3] = 0xa; }
    } break;

    case Request::DiscCompletionTime: {  //time in mm:ss:ff
      auto [minute, second, frame] = CD::MSF(session.leadOut.lba);
      status[1] = command[3];
      status[2] = minute / 10; status[3] = minute % 10;
      status[4] = second / 10; status[5] = second % 10;
      status[6] = frame  / 10; status[7] = frame  % 10;
      status[8] = 0x0;
    } break;

    case Request::DiscTracks: {  //first and last track numbers
      auto firstTrack = session.firstTrack;
      auto lastTrack  = session.lastTrack;
      status[1] = command[3];
      status[2] = firstTrack / 10; status[3] = firstTrack % 10;
      status[4] = lastTrack  / 10; status[5] = lastTrack  % 10;
      status[6] = 0x0; status[7] = 0x0;
      status[8] = 0x0;
    } break;

    case Request::TrackStartTime: {
      if(command[4] > 9 || command[5] > 9) break;
      u32 track  = command[4] * 10 + command[5];
      auto [minute, second, frame] = CD::MSF(session.tracks[track].indices[1].lba);
      status[1] = command[3];
      status[2] = minute / 10; status[3] = minute % 10;
      status[4] = second / 10; status[5] = second % 10;
      status[6] = frame  / 10; status[7] = frame  % 10;
      status[6].bit(3) = session.tracks[track].isData();
      status[8] = track % 10;
    } break;

    case Request::ErrorInformation: {
      //always report no errors
      status[1] = command[3];
      status[2] = 0x0; status[3] = 0x0;
      status[4] = 0x0; status[5] = 0x0;
      status[6] = 0x0; status[7] = 0x0;
      status[8] = 0x0;
    } break;

    }
  } break;

  case Command::SeekPlay: {
    u32 minute = command[2] * 10 + command[3];
    u32 second = command[4] * 10 + command[5];
    u32 frame  = command[6] * 10 + command[7];
    s32 lba    = minute * 60 * 75 + second * 75 + frame - 3;

    counter    = 0;
    io.status  = Status::Seeking;
    io.seeking = Status::Playing;
    io.latency = 11 + 112.5 * abs(position(io.sector) - position(lba));
    io.sector  = lba;
    io.sample  = 0;

    status[1] = 0xf;
    status[2] = 0x0; status[3] = 0x0;
    status[4] = 0x0; status[5] = 0x0;
    status[6] = 0x0; status[7] = 0x0;
    status[8] = 0x0;
  } break;

  case Command::SeekPause: {
    u32 minute = command[2] * 10 + command[3];
    u32 second = command[4] * 10 + command[5];
    u32 frame  = command[6] * 10 + command[7];
    s32 lba    = minute * 60 * 75 + second * 75 + frame - 3;

    counter    = 0;
    io.status  = Status::Seeking;
    io.seeking = Status::Paused;
    io.latency = 11 + 112.5 * abs(position(io.sector) - position(lba));
    io.sector  = lba;
    io.sample  = 0;

    status[1] = 0xf;
    status[2] = 0x0; status[3] = 0x0;
    status[4] = 0x0; status[5] = 0x0;
    status[6] = 0x0; status[7] = 0x0;
    status[8] = 0x0;
  } break;

  case Command::Pause: {
    pause();
  } break;

  case Command::Play: {
    play();
  } break;

  // TrackSkip command directs movement of the laser/sled by a specified radial track count.
  // Certain versions of the Mega-CD BIOS will issue this tracking command followed by a
  // Seek command (buffered). Therefore, it is not critical to handle the operation explicitly.
  // Actual seek algorithms (implemented in the MCU program) are currently unknown.
  case Command::TrackSkip: {
    // cmd[2..3] : Direction (flag)
    //   non-zero == inward movement (i.e., backtracking); zero == outward movement
    // cmd[4..7] : Magnitude (in hexadecimal -- not BCD)
    //   number of radial tracks to traverse

    //u8  direction = command[2] << 4 | command[3];
    //s16 magnitude = command[4] << 12 | command[5] << 8 | command[6] << 4 | command[7];
    //magnitude = direction ? -magnitude : magnitude;

    // TODO: Implement this properly. For now, it is treated as a null seek operation.

    counter    = 0;
    io.status  = Status::Tracking;
    io.seeking = Status::Paused;
    io.latency = 0;
    //io.sector  = lba;
    io.sample  = 0;

    status[1] = 0xf;
    status[2] = 0x0; status[3] = 0x0;
    status[4] = 0x0; status[5] = 0x0;
    status[6] = 0x0; status[7] = 0x0;
    status[8] = 0x0;
  } break;

  // TrackCue command directs movement of the laser/sled to find a target track index number.
  // It is not known to be used by the CD BIOS, so it remains unsupported.
  //case Command::TrackCue: {
  //} break;

  default:
    io.status = Status::CommandError;
  }

  status[0] = io.status;
  checksum();
  statusPending = 1;
}

auto MCD::CDD::valid() -> bool {
  n4 checksum;
  for(u32 index : range(9)) checksum += command[index];
  checksum = ~checksum;
  return checksum == command[9];
}

auto MCD::CDD::checksum() -> void {
  n4 checksum;
  for(u32 index : range(9)) checksum += status[index];
  checksum = ~checksum;
  status[9] = checksum;
}

auto MCD::CDD::insert() -> void {
  if(!mcd.disc || !mcd.fd) {
    io.status = Status::NoDisc;
    return;
  }

  //read TOC (table of contents) from disc lead-in
  u32 sectors = mcd.fd->size() / 2448;
  vector<u8> subchannel;
  subchannel.resize(sectors * 96);
  for(u32 sector : range(sectors)) {
    mcd.fd->seek(sector * 2448 + 2352);
    mcd.fd->read({subchannel.data() + sector * 96, 96});
  }
  session.decode(subchannel, 96);

  io.status  = Status::ReadingTOC;
  io.sector  = session.leadIn.lba;
  io.sample  = 0;
  io.track   = 0;

  // Check if this is a MegaLD Laserdisc. We currently do this by looking at magic bytes in the first data sector.
  static auto constexpr matchString = "LICENCED BY PIONEER & SEGA";
  static auto constexpr matchStringLength = std::string::traits_type::length(matchString);
  mcd.fd->seek(((abs(session.leadIn.lba) + session.tracks[session.firstTrack].indices[1].lba) * 2448) + 0x23E);
  isDiscMegaLd = false;
  if ((mcd.fd->size() - mcd.fd->offset()) >= matchStringLength) {
    isDiscMegaLd = (std::strncmp((const char*)(mcd.fd->data() + mcd.fd->offset()), matchString, matchStringLength) == 0);
  }
}

auto MCD::CDD::eject() -> void {
  session = {};

  io.status  = Status::NoDisc;
  io.sector  = 0;
  io.sample  = 0;
  io.track   = 0;
}

auto MCD::CDD::stop() -> void {
  io.status = mcd.fd ? Status::Stopped : Status::NoDisc;
}

auto MCD::CDD::play() -> void {
  io.status = Status::Playing;
}

auto MCD::CDD::pause() -> void {
  io.status = Status::Paused;
}

auto MCD::CDD::seekToTime(u8 minute, u8 second, u8 frame, bool startPaused) -> void {
  s32 lba = lbaFromTime(minute, second, frame) - 3;
  seekToSector(lba, startPaused);
}

auto MCD::CDD::seekToRelativeTime(n7 track, u8 minute, u8 second, u8 frame, bool startPaused) -> void {
  auto firstTrack = session.firstTrack;
  auto lastTrack = session.lastTrack;
  if ((track < firstTrack) || (track > lastTrack)) {
    return;
  }

  auto targetTrackLba = session.tracks[track].indices[1].lba;
  s32 lba = targetTrackLba + ((s32)minute * 60 * 75 + (s32)second * 75 + (s32)frame - 3);
  seekToSector(lba, startPaused);
}

auto MCD::CDD::seekToSector(s32 lba, bool startPaused) -> void {
  counter = 0;
  io.status = Status::Seeking;
  io.seeking = (startPaused ? Status::Paused : Status::Playing);
  io.latency = 11 + 112.5 * abs(position(io.sector) - position(lba));
  io.sector = lba;
  io.sample = 0;
  if (auto track = session.inTrack(io.sector)) io.track = track();
}

auto MCD::CDD::seekToTrack(n7 track, bool startPaused) -> void {
  auto lba = session.tracks[track].indices[1].lba;
  seekToSector(lba, startPaused);
}

auto MCD::CDD::getTrackCount() -> n7 {
  return session.lastTrack - session.firstTrack;
}

auto MCD::CDD::getFirstTrack() -> n7 {
  return session.firstTrack;
}

auto MCD::CDD::getLastTrack() -> n7 {
  return session.lastTrack;
}

auto MCD::CDD::getCurrentTrack() -> n7 {
  return io.track;
}

auto MCD::CDD::getCurrentSector() -> s32 {
  return io.sector;
}

auto MCD::CDD::getCurrentTimecode(u8& minute, u8& second, u8& frame) -> void {
  auto [lminute, lsecond, lframe] = CD::MSF(io.sector);
  minute = lminute;
  second = lsecond;
  frame = lframe;
}

auto MCD::CDD::getCurrentTrackRelativeTimecode(u8& minute, u8& second, u8& frame) -> void {
  auto [lminute, lsecond, lframe] = CD::MSF(io.sector - session.tracks[io.track].indices[1].lba);
  minute = lminute;
  second = lsecond;
  frame = lframe;
}

auto MCD::CDD::getLeadOutTimecode(u8& minute, u8& second, u8& frame) -> void {
  auto [lminute, lsecond, lframe] = CD::MSF(session.leadOut.lba);
  minute = lminute;
  second = lsecond;
  frame = lframe;
}

auto MCD::CDD::getTrackTocData(n7 track, u8& flags, u8& minute, u8& second, u8& frame) -> void {
  auto [lminute, lsecond, lframe] = CD::MSF(session.tracks[track].indices[1].lba);
  minute = lminute;
  second = lsecond;
  frame = lframe;
  flags = session.tracks[track].control;
}

auto MCD::CDD::lbaFromTime(u8 minute, u8 second, u8 frame) -> s32 {
  s32 lba = ((s32)minute * 60 * 75) + ((s32)second * 75) + (s32)frame;
  return lba;
}

auto MCD::CDD::isTrackAudio(n7 track) -> bool {
  return session.tracks[track].isAudio();
}

auto MCD::CDD::isDiscLoaded() -> bool {
  return (mcd.disc && mcd.fd);
}

auto MCD::CDD::isDiscLaserdisc() -> bool {
  if (!isDiscLoaded()) {
    return false;
  }

  // We don't have mechanical state here to tell us if a physical Laserdisc or CD was inserted. Since the only kind of
  // laserdiscs we care about right now are valid MegaLD titles, we just return true if a MegaLD disc image has been
  // detected. This won't get the bios "CD player" working for Laserdisc video however. If in the future we want to be
  // able to, for example, load a file which represents just an analog laserdisc, this will need to be amended.
  return isDiscMegaLd;
}

auto MCD::CDD::isLaserdiscClv() -> bool {
  //##TODO## Forced to false right now. Some MegaLD games do use CAV format. Once we determine how we're going to bundle
  //things all together for MegaLD games, plumb the necessary metadata here so we can set this properly.
  return false;
}

auto MCD::CDD::isLaserdiscDigitalAudioPresent() -> bool {
  //##TODO## Forced to true right now. Not actually required to be anything other than true for MegaLD games, but if we
  //wanted to support loading raw Laserdisc video in the future, this could be set to handle the different hardware
  //behaviour.
  return true;
}

auto MCD::CDD::power(bool reset) -> void {
  irq = {};
  counter = 0;
  dac.power(reset);
  io = {};
  hostClockEnable = 0;
  statusPending = 0;
  for(auto& data : status) data = 0x0;
  for(auto& data : command) data = 0x0;
  insert();
  checksum();
  isDiscMegaLd = false;
  stopPointEnabled = false;
  reachedStopPoint = false;
  targetStopPoint = 0;
}
