struct Emulator;

// MARK: Arcade Settings
struct ArcadeSettings : VerticalLayout {
  auto construct() -> void;
  shared_pointer<Emulator> system;
};

// MARK: A2600 Settings
struct A2600Settings : VerticalLayout {
  auto construct() -> void;
  shared_pointer<Emulator> system;
};

// MARK: ColecoVision Settings
struct ColecoVisionSettings : VerticalLayout {
  auto construct() -> void;
  shared_pointer<Emulator> system;
};

// MARK: Famicom Settings
struct FamicomSettings : VerticalLayout {
  auto construct() -> void;
  shared_pointer<Emulator> system;
};

// MARK: GameBoyAdvance Settings
struct GameBoyAdvanceSettings : VerticalLayout {
  auto construct() -> void;
  shared_pointer<Emulator> system;
};

// MARK: GameBoyGameBoyColor Settings
struct GameBoyGameBoyColorSettings : VerticalLayout {
  auto construct() -> void;
  shared_pointer<Emulator> system;
};

// MARK: GameGear Settings
struct GameGearSettings : VerticalLayout {
  auto construct() -> void;
  shared_pointer<Emulator> system;
};

// MARK: MasterSystem Settings
struct MasterSystemSettings : VerticalLayout {
  auto construct() -> void;
  shared_pointer<Emulator> system;
};

// MARK: Mega32XMegaCD32XMegaCDMegaDrive Settings
struct Mega32XMegaCD32XMegaCDMegaDriveSettings : VerticalLayout {
  auto construct() -> void;
  auto eventChange() -> void;
  shared_pointer<Emulator> system;
  Label megaDriveSettingsLabel{this, Size{~0, 0}, 5};
    HorizontalLayout megaDriveTmssLayout{this, Size{~0, 0}, 5};
      CheckLabel megaDriveTmssOption{&megaDriveTmssLayout, Size{0, 0}, 5};
      Label megaDriveTmssHint{&megaDriveTmssLayout, Size{0, 0}};
};

// MARK: MSX Settings
struct MSXSettings : VerticalLayout {
  auto construct() -> void;
  shared_pointer<Emulator> system;
};

// MARK: MSX2 Settings
struct MSX2Settings : VerticalLayout {
  auto construct() -> void;
  shared_pointer<Emulator> system;
};

// MARK: MyVision Settings
struct MyVisionSettings : VerticalLayout {
  auto construct() -> void;
  shared_pointer<Emulator> system;
};

// MARK: NeoGeo Settings
struct NeoGeoSettings : VerticalLayout {
  auto construct() -> void;
  shared_pointer<Emulator> system;
};

// MARK: N64 Settings
struct N64SettingsLayout : VerticalLayout {
  auto construct() -> void;
  shared_pointer<Emulator> system;
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
  shared_pointer<Emulator> system;
};

// MARK: Playstation Settings
struct PlaystationSettings : VerticalLayout {
  auto construct() -> void;
  shared_pointer<Emulator> system;
};

// MARK: PocketChallengeV2 Settings
struct PocketChallengeV2Settings : VerticalLayout {
  auto construct() -> void;
  shared_pointer<Emulator> system;
};

// MARK: Saturn Settings
struct SaturnSettings : VerticalLayout {
  auto construct() -> void;
  shared_pointer<Emulator> system;
};

// MARK: SG1000 Settings
struct SG1000Settings : VerticalLayout {
  auto construct() -> void;
  shared_pointer<Emulator> system;
};

// MARK: SuperFamicom Settings
struct SuperFamicomSettings : VerticalLayout {
  auto construct() -> void;
  shared_pointer<Emulator> system;
};

// MARK: SuperGrafx Settings
struct SuperGrafxSettings : VerticalLayout {
  auto construct() -> void;
  shared_pointer<Emulator> system;
};

// MARK: WonderSwan Settings
struct WonderSwanSettings : VerticalLayout {
  auto construct() -> void;
  shared_pointer<Emulator> system;
};

// MARK: ZXSpectrum Settings
struct ZXSpectrumSettings : VerticalLayout {
  auto construct() -> void;
  shared_pointer<Emulator> system;
};

