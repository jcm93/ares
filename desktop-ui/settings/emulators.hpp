// MARK: Default Settings
struct DefaultSettings: VerticalLayout {
  auto construct() -> void;
  Label commonSettingsLabel{this, Size{~0, 0}, 5};
    HorizontalLayout rewindLayout{this, Size{~0, 0}, 5};
      CheckLabel rewind{&rewindLayout, Size{0, 0}, 5};
      Label rewindHint{&rewindLayout, Size{~0, 0}};
    HorizontalLayout runAheadLayout{this, Size{~0, 0}, 5};
      CheckLabel runAhead{&runAheadLayout, Size{0, 0}, 5};
      Label runAheadHint{&runAheadLayout, Size{~0, 0}};
    HorizontalLayout autoSaveMemoryLayout{this, Size{~0, 0}, 5};
      CheckLabel autoSaveMemory{&autoSaveMemoryLayout, Size{0, 0}, 5};
      Label autoSaveMemoryHint{&autoSaveMemoryLayout, Size{~0, 0}};
    HorizontalLayout homebrewModeLayout{this, Size{~0, 0}, 5};
      CheckLabel homebrewMode{&homebrewModeLayout, Size{0, 0}, 5};
      Label homebrewModeHint{&homebrewModeLayout, Size{~0, 0}};
    HorizontalLayout forceInterpreterLayout{this, Size{~0, 0}, 5};
      CheckLabel forceInterpreter{&forceInterpreterLayout, Size{0, 0}, 5};
      Label forceInterpreterHint{&forceInterpreterLayout, Size{0, 0}};
  
  Label emulatorSettingsLabel{this, Size{~0, 0}, 5};
    HorizontalLayout colorBleedLayout{this, Size{~0, 0}, 5};
      CheckLabel colorBleedOption{&colorBleedLayout, Size{0, 0}, 5};
      Label colorBleedHint{&colorBleedLayout, Size{~0, 0}};
    HorizontalLayout colorEmulationLayout{this, Size{~0, 0}, 5};
      CheckLabel colorEmulationOption{&colorEmulationLayout, Size{0, 0}, 5};
      Label colorEmulationHint{&colorEmulationLayout, Size{~0, 0}};
    HorizontalLayout deepBlackBoostLayout{this, Size{~0, 0}, 5};
      CheckLabel deepBlackBoostOption{&deepBlackBoostLayout, Size{0, 0}, 5};
      Label deepBlackBoostHint{&deepBlackBoostLayout, Size{~0, 0}};
    HorizontalLayout interframeBlendingLayout{this, Size{~0, 0}, 5};
      CheckLabel interframeBlendingOption{&interframeBlendingLayout, Size{0, 0}, 5};
      Label interframeBlendingHint{&interframeBlendingLayout, Size{~0, 0}};
    HorizontalLayout overscanLayout{this, Size{~0, 0}};
      CheckLabel overscanOption{&overscanLayout, Size{0, 0}, 5};
      Label overscanHint{&overscanLayout, Size{~0, 0}};
    HorizontalLayout pixelAccuracyLayout{this, Size{~0, 0}};
      CheckLabel pixelAccuracyOption{&pixelAccuracyLayout, Size{0, 0}, 5};
      Label pixelAccuracyHint{&pixelAccuracyLayout, Size{~0, 0}};
};

// MARK: Arcade Settings
struct ArcadeSettings : VerticalLayout {
  auto construct() -> void;
};

// MARK: A2600 Settings
struct A2600Settings : VerticalLayout {
  auto construct() -> void;
};

// MARK: ColecoVision Settings
struct ColecoVisionSettings : VerticalLayout {
  auto construct() -> void;
};

// MARK: Famicom Settings
struct FamicomSettings : VerticalLayout {
  auto construct() -> void;
};

// MARK: GameBoyAdvance Settings
struct GameBoyAdvanceSettings : VerticalLayout {
  auto construct() -> void;
};

// MARK: GameBoyGameBoyColor Settings
struct GameBoyGameBoyColorSettings : VerticalLayout {
  auto construct() -> void;
};

// MARK: GameGear Settings
struct GameGearSettings : VerticalLayout {
  auto construct() -> void;
};

// MARK: MasterSystem Settings
struct MasterSystemSettings : VerticalLayout {
  auto construct() -> void;
};

// MARK: Mega32XMegaCD32XMegaCDMegaDrive Settings
struct Mega32XMegaCD32XMegaCDMegaDriveSettings : VerticalLayout {
  auto construct() -> void;
  Label megaDriveSettingsLabel{this, Size{~0, 0}, 5};
    HorizontalLayout megaDriveTmssLayout{this, Size{~0, 0}, 5};
      CheckLabel megaDriveTmssOption{&megaDriveTmssLayout, Size{0, 0}, 5};
      Label megaDriveTmssHint{&megaDriveTmssLayout, Size{0, 0}};
};

// MARK: MSX Settings
struct MSXSettings : VerticalLayout {
  auto construct() -> void;
};

// MARK: MSX2 Settings
struct MSX2Settings : VerticalLayout {
  auto construct() -> void;
};

// MARK: MyVision Settings
struct MyVisionSettings : VerticalLayout {
  auto construct() -> void;
};

// MARK: NeoGeo Settings
struct NeoGeoSettings : VerticalLayout {
  auto construct() -> void;
};

// MARK: N64 Settings
struct N64Settings : VerticalLayout {
  auto construct(shared_pointer<Emulator> n64Instance) -> void;
  shared_pointer<Emulator> instance;
  Label commonSettingsLabel{this, Size{~0, 0}, 5};
    HorizontalLayout homebrewModeLayout{this, Size{~0, 0}, 5};
      CheckLabel homebrewMode{&homebrewModeLayout, Size{0, 0}, 5};
      Label homebrewModeHint{&homebrewModeLayout, Size{~0, 0}};
    HorizontalLayout forceInterpreterLayout{this, Size{~0, 0}, 5};
      CheckLabel forceInterpreter{&forceInterpreterLayout, Size{0, 0}, 5};
      Label forceInterpreterHint{&forceInterpreterLayout, Size{0, 0}};
  Label emulatorSettingsLabel{this, Size{~0, 0}, 5};
    HorizontalLayout overscanLayout{this, Size{~0, 0}};
      CheckLabel overscanOption{&overscanLayout, Size{0, 0}, 5};
      Label overscanHint{&overscanLayout, Size{~0, 0}};
  Label nintendo64SettingsLabel{this, Size{~0, 0}, 5};
    HorizontalLayout nintendo64ExpansionPakLayout{this, Size{~0, 0}, 5};
      CheckLabel nintendo64ExpansionPakOption{&nintendo64ExpansionPakLayout, Size{0, 0}, 5};
      Label nintendo64ExpansionPakHint{&nintendo64ExpansionPakLayout, Size{0, 0}};
    HorizontalLayout nintendo64ControllerPakBankLayout{this, Size{~0, 0}, 5};
      Label nintendo64ControllerPakBankLabel{&nintendo64ControllerPakBankLayout, Size{0, 0}};
      ComboButton nintendo64ControllerPakBankOption{&nintendo64ControllerPakBankLayout, Size{0, 0}};
      // LineEdit nintendo64ControllerPakBankOption{&nintendo64ControllerPakBankLayout, Size{40, 0}};
      Label nintendo64ControllerPakBankHint{&nintendo64ControllerPakBankLayout, Size{0, 0}};
  
  Label renderSettingsLabel{this, Size{~0, 0}, 5};
  HorizontalLayout disableVideoInterfaceProcessingLayout{this, Size{~0, 0}, 5};
    CheckLabel disableVideoInterfaceProcessingOption{&disableVideoInterfaceProcessingLayout, Size{0, 0}, 5};
    Label disableVideoInterfaceProcessingHint{&disableVideoInterfaceProcessingLayout, Size{0, 0}};
  HorizontalLayout weaveDeinterlacingLayout{this, Size{~0, 0}, 5};
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

// MARK: PCEngine Settings
struct PCEngineSettings : VerticalLayout {
  auto construct() -> void;
};

// MARK: Playstation Settings
struct PlaystationSettings : VerticalLayout {
  auto construct() -> void;
};

// MARK: PocketChallengeV2 Settings
struct PocketChallengeV2Settings : VerticalLayout {
  auto construct() -> void;
};

// MARK: Saturn Settings
struct SaturnSettings : VerticalLayout {
  auto construct() -> void;
};

// MARK: SG1000 Settings
struct SG1000Settings : VerticalLayout {
  auto construct() -> void;
};

// MARK: SuperFamicom Settings
struct SuperFamicomSettings : VerticalLayout {
  auto construct() -> void;
};

// MARK: SuperGrafx Settings
struct SuperGrafxSettings : VerticalLayout {
  auto construct() -> void;
};

// MARK: WonderSwan Settings
struct WonderSwanSettings : VerticalLayout {
  auto construct() -> void;
};

// MARK: ZXSpectrum Settings
struct ZXSpectrumSettings : VerticalLayout {
  auto construct() -> void;
};

