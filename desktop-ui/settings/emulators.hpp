struct Emulator;

// MARK: Arcade Settings
struct ArcadeSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: A2600 Settings
struct A2600Settings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: ColecoVision Settings
struct ColecoVisionSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: Famicom Settings
struct FamicomSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: Famicom Disk System Settings
struct FamicomDiskSystemSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: Game Boy Settings
struct GameBoySettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: Game Boy Color Settings
struct GameBoyColorSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: Game Boy Advance Settings
struct GameBoyAdvanceSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: Game Gear Settings
struct GameGearSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: MegaLD Settings
struct MegaLDSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: MasterSystem Settings
struct MasterSystemSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: MegaDrive Settings
struct MegaDriveSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  auto eventChange() -> void;
  shared_pointer<Emulator> system;
  Label megaDriveSettingsLabel{this, Size{~0, 0}, 5};
    HorizontalLayout megaDriveTmssLayout{this, Size{~0, 0}, 5};
      CheckLabel megaDriveTmssOption{&megaDriveTmssLayout, Size{0, 0}, 5};
      Label megaDriveTmssHint{&megaDriveTmssLayout, Size{0, 0}};
};

// MARK: Mega 32X Settings
struct Mega32XSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  auto eventChange() -> void;
  shared_pointer<Emulator> system;
  Label forceInterpreterLabel{this, Size{~0, 0}};
  CheckLabel forceInterpreterCheck{this, Size{0, 0}, 5};
};

// MARK: Mega CD Settings
struct MegaCDSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  auto eventChange() -> void;
  shared_pointer<Emulator> system;
};

// MARK: Mega CD 32X Settings
struct MegaCD32XSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  auto eventChange() -> void;
  shared_pointer<Emulator> system;
  Label forceInterpreterLabel{this, Size{~0, 0}};
  CheckLabel forceInterpreterCheck{this, Size{0, 0}, 5};
};

// MARK: MSX Settings
struct MSXSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: MSX2 Settings
struct MSX2Settings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: MyVision Settings
struct MyVisionSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: Neo Geo Settings
struct NeoGeoSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: Neo Geo Pocket Settings
struct NeoGeoPocketSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: Neo Geo Pocket Color Settings
struct NeoGeoPocketColorSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: N64 Settings
struct N64SettingsLayout : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;

  TableLayout nintendo64SettingsLayout{this, Size{~0, 0}};
    Label placeholder{&nintendo64SettingsLayout, Size{sx((settingsWidth / 2) - 400), 0}};
    Label nintendo64SettingsLabel{&nintendo64SettingsLayout, Size{0, 25_sy}};

    Label forceInterpreterLabel{&nintendo64SettingsLayout, Size{0, 0}};
    CheckLabel forceInterpreterCheck{&nintendo64SettingsLayout, Size{0, 0}};

    Label homebrewLabel{&nintendo64SettingsLayout, Size{0, 0}};
    CheckLabel homebrewCheck{&nintendo64SettingsLayout, Size{0, 0}};

    Label expansionPakLabel{&nintendo64SettingsLayout, Size{0, 0}};
    CheckLabel expansionPakCheck{&nintendo64SettingsLayout, Size{0, 0}};

    Label controllerPakBankLabel{&nintendo64SettingsLayout, Size{0, 0}};
    ComboButton controllerPakBankOption{&nintendo64SettingsLayout, Size{0, 0}};

    Label placeholder2{&nintendo64SettingsLayout, Size{sx((settingsWidth / 2) - 400), 0}};
    Label controllerPakBankHint{&nintendo64SettingsLayout, Size{0, 25_sy}};

    Label placeholder2{&nintendo64SettingsLayout, Size{sx((settingsWidth / 2) - 400), 0}};
    Label renderSettingsLabel{this, Size{~0, 0}, 5};

    CheckLabel disableVideoInterfaceProcessingOption{&disableVideoInterfaceProcessingLayout, Size{0, 0}, 5};
    Label disableVideoInterfaceProcessingHint{&disableVideoInterfaceProcessingLayout, Size{0, 0}};

    CheckLabel weaveDeinterlacingOption{&weaveDeinterlacingLayout, Size{0, 0}, 5};
    Label weaveDeinterlacingHint{&weaveDeinterlacingLayout, Size{0, 0}};
  HorizontalLayout renderQualityLayout{this, Size{~0, 0}, 5};
    RadioLabel renderQualitySD{&renderQualityLayout, Size{0, 0}};
    RadioLabel renderQualityHD{&renderQualityLayout, Size{0, 0}};
    RadioLabel renderQualityUHD{&renderQualityLayout, Size{0, 0}};
    Group renderQualityGroup{&renderQualitySD, &renderQualityHD, &renderQualityUHD};
  HorizontalLayout renderSupersamplingLayout{this, Size{~0, 0}, 5};
    CheckLabel renderSupersamplingOption{&renderSupersamplingLayout, Size{0, 0}, 5};
    Label renderSupersamplingHint{&renderSupersamplingLayout, Size{0, 0}};
  HorizontalLayout renderSettingsLayout{this, Size{~0, 0}};
      Label renderSettingsHint{&renderSettingsLayout, Size{0, 0}};
};

// MARK: N64DD Settings
struct N64DDSettingsLayout : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: PCEngine Settings
struct PCEngineSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: PCEngine CD Settings
struct PCEngineCDSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: NEC PAC Settings
struct NECPACSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: PlayStation Settings
struct PlayStationSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: PocketChallengeV2 Settings
struct PocketChallengeV2Settings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: Saturn Settings
struct SaturnSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: SG1000 Settings
struct SG1000Settings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: SC3000 Settings
struct SC3000Settings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: SuperFamicom Settings
struct SuperFamicomSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: SuperGrafx Settings
struct SuperGrafxSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: SuperGrafx CD Settings
struct SuperGrafxCDSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: WonderSwan Settings
struct WonderSwanSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: WonderSwan Color Settings
struct WonderSwanColorSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: ZXSpectrum Settings
struct ZXSpectrumSettings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

// MARK: ZX Spectrum 128 Settings
struct ZXSpectrum128Settings : VerticalLayout {
  auto construct(shared_pointer<Emulator>) -> void;
  shared_pointer<Emulator> system;
};

