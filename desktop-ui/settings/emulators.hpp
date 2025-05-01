struct ArcadeSettings : VerticalLayout {
  auto construct() -> void;
};

struct A2600Settings : VerticalLayout {
  auto construct() -> void;
};

struct ColecoVisionSettings : VerticalLayout {
  auto construct() -> void;
};

struct FamicomSettings : VerticalLayout {
  auto construct() -> void;
};

struct GameBoyAdvanceSettings : VerticalLayout {
  auto construct() -> void;
};

struct GameBoyGameBoyColorSettings : VerticalLayout {
  auto construct() -> void;
};

struct GameGearSettings : VerticalLayout {
  auto construct() -> void;
};

struct MasterSystemSettings : VerticalLayout {
  auto construct() -> void;
};

struct Mega32XMegaCD32XMegaCDMegaDriveSettings : VerticalLayout {
  auto construct() -> void;
  Label megaDriveSettingsLabel{this, Size{~0, 0}, 5};
    HorizontalLayout megaDriveTmssLayout{this, Size{~0, 0}, 5};
      CheckLabel megaDriveTmssOption{&megaDriveTmssLayout, Size{0, 0}, 5};
      Label megaDriveTmssHint{&megaDriveTmssLayout, Size{0, 0}};
};

struct MSXSettings : VerticalLayout {
  auto construct() -> void;
};

struct MSX2Settings : VerticalLayout {
  auto construct() -> void;
};

struct MyVisionSettings : VerticalLayout {
  auto construct() -> void;
};

struct NeoGeoSettings : VerticalLayout {
  auto construct() -> void;
};

struct N64Settings : VerticalLayout {
  auto construct() -> void;
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

struct PCEngineSettings : VerticalLayout {
  auto construct() -> void;
};

struct PlaystationSettings : VerticalLayout {
  auto construct() -> void;
};

struct PocketChallengeV2Settings : VerticalLayout {
  auto construct() -> void;
};

struct SaturnSettings : VerticalLayout {
  auto construct() -> void;
};

struct SG1000Settings : VerticalLayout {
  auto construct() -> void;
};

struct SuperFamicomSettings : VerticalLayout {
  auto construct() -> void;
};

struct SuperGrafxSettings : VerticalLayout {
  auto construct() -> void;
};

struct WonderSwanSettings : VerticalLayout {
  auto construct() -> void;
};

struct ZXSpectrumSettings : VerticalLayout {
  auto construct() -> void;
};

