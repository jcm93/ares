// MARK: Settings struct

struct N64Settings;

#define settingsWidth 875
#define settingsHeight 465

struct Settings : Markup::Node {
  using string = nall::string;

  auto load() -> void;
  auto save() -> void;
  auto process(bool load) -> void;

  struct Video {
    string driver;
    string monitor;
    string format;
    bool exclusive = false;
    bool blocking = false;
    bool forceSRGB = false;
    bool threadedRenderer = true;
    bool nativeFullScreen = false;
    bool flush = false;
    string shader = "None";
    u32 multiplier = 2;
    string output = "Scale";
    string aspectCorrection = "Standard";
    bool adaptiveSizing = true;
    bool autoCentering = false;

    f64 luminance = 1.0;
    f64 saturation = 1.0;
    f64 gamma = 1.0;
    bool colorBleed = false;
    bool colorEmulation = true;
    bool deepBlackBoost = false;
    bool interframeBlending = true;
    bool overscan = false;
    bool pixelAccuracy = false;
  } video;

  struct Audio {
    string driver;
    string device;
    u32 frequency = 0;
    u32 latency = 0;
    bool exclusive = false;
    bool blocking = true;
    bool dynamic = false;
    bool mute = false;

    f64 volume = 1.0;
    f64 balance = 0.0;
  } audio;

  struct Input {
    string driver;
    string defocus = "Pause";
  } input;

  struct Boot {
    bool fast = false;
    bool debugger = false;
    string prefer = "NTSC-U";
  } boot;

  struct General {
    bool showStatusBar = true;
    bool rewind = false;
    bool runAhead = false;
    bool autoSaveMemory = true;
    bool homebrewMode = false;
    bool forceInterpreter = false;
  } general;

  struct Rewind {
    u32 length = 100;
    u32 frequency = 10;
  } rewind;

  struct Paths {
    string home;
    string firmware;
    string saves;
    string screenshots;
    string debugging;
    string arcadeRoms;
  } paths;

  struct Recent {
    string game[9];
  } recent;

  struct DebugServer {
    u32 port = 9123;
    bool enabled = false; // if enabled, server starts with ares
    bool useIPv4 = false; // forces IPv4 over IPv6
  } debugServer;

  N64Settings *nintendo64 = {};

  GBASettings *gameBoyAdvance = {};

  MDSettings *megaDrive = {};

  SFCSettings *superFamicom = {};

private:
  auto processBasic(bool load, string prefix, nall::shared_pointer<Emulator> emulator) -> void;
};

// MARK: emulators.hpp

#include "emulators.hpp"

// MARK: Video

struct VideoSettings : VerticalLayout {
  auto construct() -> void;
  auto videoRefresh() -> void;
  auto videoDriverUpdate() -> bool;

  TableLayout videoDriverLayout{this, Size{~0, 0}};
    Label placeholder{&videoDriverLayout, Size{(settingsWidth / 2) - 138, 0}};
    Label videoLabel{&videoDriverLayout, Size{~0, 25}};

    Label videoDriverLabel{&videoDriverLayout, Size{0, 0}};
    ComboButton videoDriverList{&videoDriverLayout, Size{150, 0}};

    Label videoMonitorLabel{&videoDriverLayout, Size{0, 0}};
    ComboButton videoMonitorList{&videoDriverLayout, Size{200, 0}};

    Label videoFormatLabel{&videoDriverLayout, Size{0, 0}};
    ComboButton videoFormatList{&videoDriverLayout, Size{100, 0}};

#if defined(PLATFORM_MACOS)
    Label videoColorSpaceToggleName{&videoDriverLayout, Size{0, 20}};
    CheckLabel videoColorSpaceToggle{&videoDriverLayout, Size{0, 0}};

    Label videoThreadedRendererToggleName{&videoDriverLayout, Size{0, 20}};
    CheckLabel videoThreadedRendererToggle{&videoDriverLayout, Size{0, 0}};

    Label videoNativeFullScreenToggleName{&videoDriverLayout, Size{0, 20}};
    CheckLabel videoNativeFullScreenToggle{&videoDriverLayout, Size{0, 0}};
#endif
  HorizontalLayout videoToggleLayout{this, Size{~0, 0}};
#if !defined(PLATFORM_MACOS)
    Label videoExclusiveToggleName{&videoDriverLayout, Size{0, 20}};
    CheckLabel videoExclusiveToggle{&videoToggleLayout, Size{0, 0}};
#endif


  TableLayout colorAdjustmentLayout{this, Size{~0, 0}};
    Label placeholderOne{&colorAdjustmentLayout, Size{(settingsWidth / 2) - 138 - 57, 0}};
    Label placeholderThree{&colorAdjustmentLayout, Size{0, 0}};
    Label colorAdjustmentLabel{&colorAdjustmentLayout, Size{0, 25}};

    Label luminanceLabel{&colorAdjustmentLayout, Size{0, 0}};
    Label luminanceValue{&colorAdjustmentLayout, Size{50_sx, 0}};
    HorizontalSlider luminanceSlider{&colorAdjustmentLayout, Size{400, 0}};
  //
    Label saturationLabel{&colorAdjustmentLayout, Size{0, 0}};
    Label saturationValue{&colorAdjustmentLayout, Size{50_sx, 0}};
    HorizontalSlider saturationSlider{&colorAdjustmentLayout, Size{400, 0}};
  //
    Label gammaLabel{&colorAdjustmentLayout, Size{0, 0}};
    Label gammaValue{&colorAdjustmentLayout, Size{50_sx, 0}};
    HorizontalSlider gammaSlider{&colorAdjustmentLayout, Size{400, 0}};
  //
};

// MARK: Audio

struct AudioSettings : VerticalLayout {
  auto construct() -> void;
  auto audioRefresh() -> void;
  auto audioDriverUpdate() -> bool;
  
  //
  TableLayout audioDriverLayout{this, Size{~0, 0}};
    Label placeholder{&audioDriverLayout, Size{(settingsWidth / 2) - 138, 0}};
    Label audioLabel{&audioDriverLayout, Size{~0, 25}};

    Label audioDriverLabel{&audioDriverLayout, Size{0, 0}};
    ComboButton audioDriverList{&audioDriverLayout, Size{125, 0}};

    Label audioDeviceLabel{&audioDriverLayout, Size{0, 0}};
    ComboButton audioDeviceList{&audioDriverLayout, Size{0, 0}};

    Label audioFrequencyLabel{&audioDriverLayout, Size{0, 0}};
    ComboButton audioFrequencyList{&audioDriverLayout, Size{125, 0}};

    Label audioLatencyLabel{&audioDriverLayout, Size{0, 0}};
    ComboButton audioLatencyList{&audioDriverLayout, Size{125, 0}};

    Label audioExclusiveToggleName{&audioDriverLayout, Size{0, 0}};
    CheckLabel audioExclusiveToggle{&audioDriverLayout, Size{0, 0}};

  TableLayout effectsLayout{this, Size{~0, 0}};
    Label placeholderOne{&effectsLayout, Size{(settingsWidth / 2) - 138 - 57, 0}};
    Label placeholderThree{&effectsLayout, Size{0, 0}};
    Label effectsLabel{&effectsLayout, Size{~0, 25}};

    Label volumeLabel{&effectsLayout, Size{0, 0}};
    Label volumeValue{&effectsLayout, Size{50_sx, 0}};
    HorizontalSlider volumeSlider{&effectsLayout, Size{400, 0}};
  //
    Label balanceLabel{&effectsLayout, Size{0, 0}};
    Label balanceValue{&effectsLayout, Size{50_sx, 0}};
    HorizontalSlider balanceSlider{&effectsLayout, Size{400, 0}};
};

// MARK: Sync

struct SyncSettings : VerticalLayout {
  auto construct() -> void;
  auto refresh() -> void;
  
  TableLayout syncAdjustmentLayout{this, Size{~0, 0}};
    Label placeholder{&syncAdjustmentLayout, Size{(settingsWidth / 2) - 138, 0}};
    Label syncLabel{&syncAdjustmentLayout, Size{0, 25}};
  //
    Label syncDescriptionLabel{&syncAdjustmentLayout, Size{0, 0}};
    ComboButton syncOptionList{&syncAdjustmentLayout, Size{0, 0}};
  //
    Label placeholder2{&syncAdjustmentLayout, Size{0, 0}};
    Label syncDescriptionHint{&syncAdjustmentLayout, Size{~0, 30}};
  //
    Label gpuSyncDescription{&syncAdjustmentLayout, Size{0, 0}};
    CheckLabel gpuSyncCheckLabel{&syncAdjustmentLayout, Size{0, 0}};
  //
    Label dynamicRateDescription{&syncAdjustmentLayout, Size{0, 0}};
    CheckLabel dynamicRateCheckLabel{&syncAdjustmentLayout, Size{0, 0}};
  
  HorizontalLayout syncDescriptionHintLayout{this, Size{~0, 0}};
};

// MARK: Input

struct InputSettings : VerticalLayout {
  auto construct() -> void;
  auto systemChange() -> void;
  auto portChange() -> void;
  auto deviceChange() -> void;
  auto refresh() -> void;
  auto eventContext(TableViewCell) -> void;
  auto eventChange() -> void;
  auto eventClear() -> void;
  auto eventAssign(TableViewCell, string binding) -> void;
  auto eventAssign(TableViewCell) -> void;
  auto eventInput(shared_pointer<HID::Device>, u32 groupID, u32 inputID, s16 oldValue, s16 newValue) -> void;
  auto setVisible(bool visible = true) -> InputSettings&;
  auto inputRefresh() -> void;
  auto inputDriverUpdate() -> bool;
  
  //

  HorizontalLayout indexLayout{this, Size{~0, 0}};
    ComboButton systemList{&indexLayout, Size{~0, 0}};
    ComboButton portList{&indexLayout, Size{~0, 0}};
    ComboButton deviceList{&indexLayout, Size{~0, 0}};
  TableView inputList{this, Size{~0, ~0}};
  HorizontalLayout controlLayout{this, Size{~0, 0}};
    Label inputDriverLabel{&controlLayout, Size{0, 0}};
    ComboButton inputDriverList{&controlLayout, Size{0, 0}};
    Label inputDefocusLabel{&controlLayout, Size{0, 0}};
    RadioLabel inputDefocusPause{&controlLayout, Size{0, 0}};
    RadioLabel inputDefocusBlock{&controlLayout, Size{0, 0}};
    RadioLabel inputDefocusAllow{&controlLayout, Size{0, 0}};
    Label assignLabel{&controlLayout, Size{~0, 0}};
    Canvas spacer{&controlLayout, Size{1, 0}};
    Button assignButton{&controlLayout, Size{80, 0}};
    Button clearButton{&controlLayout, Size{80, 0}};

  Group inputDefocusGroup{&inputDefocusPause, &inputDefocusBlock, &inputDefocusAllow};

  maybe<InputNode&> activeMapping;
  u32 activeBinding = 0;
  Timer timer;
  PopupMenu menu;
};

// MARK: Hotkeys

struct HotkeySettings : VerticalLayout {
  auto construct() -> void;
  auto reload() -> void;
  auto refresh() -> void;
  auto eventChange() -> void;
  auto eventClear() -> void;
  auto eventAssign(TableViewCell) -> void;
  auto eventInput(shared_pointer<HID::Device>, u32 groupID, u32 inputID, s16 oldValue, s16 newValue) -> void;
  auto setVisible(bool visible = true) -> HotkeySettings&;

  TableView inputList{this, Size{~0, ~0}};
  HorizontalLayout controlLayout{this, Size{~0, 0}};
    Label assignLabel{&controlLayout, Size{~0, 0}};
    Canvas spacer{&controlLayout, Size{1, 0}};
    Button assignButton{&controlLayout, Size{80, 0}};
    Button clearButton{&controlLayout, Size{80, 0}};

  maybe<InputHotkey&> activeMapping;
  u32 activeBinding = 0;
  Timer timer;
};

// MARK: Emulators

struct EmulatorSettings : VerticalLayout {
  auto construct() -> void;
  auto eventToggle(TableViewCell cell) -> void;
  auto eventChange() -> void;

  HorizontalLayout layout{this, Size{700_sx, ~0}};
    TableView emulatorList{&layout, Size{200_sx, ~0}};
    VerticalLayout emulatorPanelContainer{&layout, Size{575_sx, ~0}};
      DefaultSettings defaultSettings;
      ArcadeSettings arcadeSettings;
      A2600Settings a2600Settings;
      ColecoVisionSettings colecoVisionSettings;
      FamicomSettings famicomSettings;
      GameBoyAdvanceSettings gameBoyAdvanceSettings;
      GameBoyGameBoyColorSettings gameBoyGameBoyColorSettings;
      GameGearSettings gameGearSettings;
      MasterSystemSettings masterSystemSettings;
      Mega32XMegaCD32XMegaCDMegaDriveSettings mega32XMegaCD32XMegaCDMegaDriveSettings;
      MSXSettings msxSettings;
      MSX2Settings msx2Settings;
      MyVisionSettings myVisionSettings;
      NeoGeoSettings neoGeoSettings;
      N64SettingsLayout n64Settings;
      PCEngineSettings pcEngineSettings;
      PlaystationSettings playstationSettings;
      PocketChallengeV2Settings pocketChallengeV2Settings;
      SaturnSettings saturnSettings;
      SG1000Settings sg1000Settings;
      SuperFamicomSettings superFamicomSettings;
      SuperGrafxSettings superGrafxSettings;
      WonderSwanSettings wonderSwanSettings;
      ZXSpectrumSettings zxSpectrumSettings;
};

// MARK: Firmware

struct FirmwareSettings : VerticalLayout {
  auto construct() -> void;
  auto refresh() -> void;
  auto select(const string& emulator, const string& type, const string& region) -> bool;
  auto eventChange() -> void;
  auto eventAssign() -> void;
  auto eventClear() -> void;
  auto eventScan() -> void;
  auto findFirmware(string sha256) -> string;

  Label firmwareLabel{this, Size{~0, 0}, 5};
  TableView firmwareList{this, Size{~0, ~0}};
  HorizontalLayout controlLayout{this, Size{~0, 0}};
    Button scanButton{&controlLayout, Size{80, 0}};
    Canvas spacer{&controlLayout, Size{~0, 0}};
    Button assignButton{&controlLayout, Size{80, 0}};
    Button clearButton{&controlLayout, Size{80, 0}};

  map<string, string> fileHashes;
};

// MARK: Paths

struct PathSettings : VerticalLayout {
  auto construct() -> void;
  auto refresh() -> void;

  Label homeLabel{this, Size{~0, 0}, 5};
  HorizontalLayout homeLayout{this, Size{~0, 0}};
    LineEdit homePath{&homeLayout, Size{~0, 0}};
    Button homeAssign{&homeLayout, Size{80, 0}};
    Button homeReset{&homeLayout, Size{80, 0}};
  Label firmwareLabel{this, Size{~0, 0}, 5};
    HorizontalLayout firmwareLayout{this, Size{~0, 0}};
    LineEdit firmwarePath{&firmwareLayout, Size{~0, 0}};
    Button firmwareAssign{&firmwareLayout, Size{80, 0}};
    Button firmwareReset{&firmwareLayout, Size{80, 0}};
  Label savesLabel{this, Size{~0, 0}, 5};
  HorizontalLayout savesLayout{this, Size{~0, 0}};
    LineEdit savesPath{&savesLayout, Size{~0, 0}};
    Button savesAssign{&savesLayout, Size{80, 0}};
    Button savesReset{&savesLayout, Size{80, 0}};
  Label screenshotsLabel{this, Size{~0, 0}, 5};
  HorizontalLayout screenshotsLayout{this, Size{~0, 0}};
    LineEdit screenshotsPath{&screenshotsLayout, Size{~0, 0}};
    Button screenshotsAssign{&screenshotsLayout, Size{80, 0}};
    Button screenshotsReset{&screenshotsLayout, Size{80, 0}};
  Label debuggingLabel{this, Size{~0, 0}, 5};
  HorizontalLayout debuggingLayout{this, Size{~0, 0}};
    LineEdit debuggingPath{&debuggingLayout, Size{~0, 0}};
    Button debuggingAssign{&debuggingLayout, Size{80, 0}};
    Button debuggingReset{&debuggingLayout, Size{80, 0}};
  Label arcadeRomsLabel{this, Size{~0, 0}, 5};
  HorizontalLayout arcadeRomsLayout{this, Size{~0, 0}};
    LineEdit arcadeRomsPath{&arcadeRomsLayout, Size{~0, 0}};
    Button arcadeRomsAssign{&arcadeRomsLayout, Size{80, 0}};
    Button arcadeRomsReset{&arcadeRomsLayout, Size{80, 0}};
};

// MARK: Debug

struct DebugSettings : VerticalLayout {
  auto construct() -> void;
  auto infoRefresh() -> void;
  auto serverRefresh() -> void;

  Label debugLabel{this, Size{~0, 0}, 5};

  HorizontalLayout portLayout{this, Size{~0, 0}};
    Label portLabel{&portLayout, Size{48, 20}};
    LineEdit port{&portLayout, Size{~0, 0}};
    Label portHint{&portLayout, Size{~0, 0}};

  HorizontalLayout ipv4Layout{this, Size{~0, 0}};
    Label ipv4Label{&ipv4Layout, Size{48, 20}};
    CheckLabel ipv4{&ipv4Layout, Size{~0, 0}};

  HorizontalLayout enabledLayout{this, Size{~0, 0}};
    Label enabledLabel{&enabledLayout, Size{48, 20}};
    CheckLabel enabled{&enabledLayout, Size{~0, 0}};

  Label connectInfo{this, Size{~0, 30}, 5};
};

// MARK: Home

struct HomePanel : VerticalLayout {
  auto construct() -> void;

  Canvas canvas{this, Size{~0, ~0}};
};

// MARK: Settings Window

struct SettingsWindow : Window {
  auto show(const string& panel) -> void;
  auto eventChange() -> void;

  VerticalLayout layout{this};
#if defined(PLATFORM_MACOS)
    Toolbar panelList{&layout, Size{~0, -5_sy}};
#else
    TabFrame panelList{&layout, Size{~0, 20_sy}};
#endif
    VerticalLayout panelContainer{&layout, Size{~0, ~0}};
      VideoSettings videoSettings;
      AudioSettings audioSettings;
      SyncSettings syncSettings;
      InputSettings inputSettings;
      HotkeySettings hotkeySettings;
      EmulatorSettings emulatorSettings;
      FirmwareSettings firmwareSettings;
      PathSettings pathSettings;
      DebugSettings debugSettings;
      HomePanel homePanel;
  
  bool initialized = false;
  
private:
  auto initialize() -> void;
};

extern Settings settings;
namespace Instances { extern Instance<SettingsWindow> settingsWindow; }
extern SettingsWindow& settingsWindow;
extern VideoSettings& videoSettings;
extern AudioSettings& audioSettings;
extern SyncSettings& syncSettings;
extern InputSettings& inputSettings;
extern HotkeySettings& hotkeySettings;
extern EmulatorSettings& emulatorSettings;
extern FirmwareSettings& firmwareSettings;
extern PathSettings& pathSettings;
extern DebugSettings& debugSettings;
