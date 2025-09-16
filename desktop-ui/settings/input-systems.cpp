
auto SystemInputSettings::construct() -> void {
  setCollapsible();
  setVisible(false);

  portList.onChange([&] { portChange(); });
  deviceList.onChange([&] { deviceChange(); });
  inputList.setBatchable();
  inputList.setHeadered();
  inputList.onContext([&](auto cell) { eventContext(cell); });
  inputList.onChange([&] { eventChange(); });
  inputList.onActivate([&](auto cell) { eventAssign(cell); });

  veryBadFunction();
}

auto SystemInputSettings::systemChange(std::shared_ptr<Emulator> emulatorIn) -> void {
  emulator = emulatorIn;
  portList.reset();
  auto& ports = Emulator::enumeratePorts(emulator->name);
  for(auto& port : ports) {
    portList.append(ComboButtonItem().setText(port.name));
  }
  portChange();
}

auto SystemInputSettings::portChange() -> void {
  deviceList.reset();
  auto& ports = Emulator::enumeratePorts(emulator->name);
  auto& port = ports[portList.selected().offset()];
  for(auto& device : port.devices) {
    deviceList.append(ComboButtonItem().setText(device.name));
  }
  deviceChange();
}

auto SystemInputSettings::deviceChange() -> void {
  inputList.reset();
  inputList.append(TableViewColumn().setText("Name"));
  inputList.append(TableViewColumn().setText({"Mapping"}).setExpandable());

  auto& ports = Emulator::enumeratePorts(emulator->name);
  auto& port = ports[portList.selected().offset()];
  auto& device = port.devices[deviceList.selected().offset()];
  for(auto& input : device.inputs) {
    TableViewItem item{&inputList};
    item.setAttribute<u32>("type", (u32)input.type);
    item.append(TableViewCell().setText(input.name).setFont(Font().setBold()));
    item.append(TableViewCell());
  }

  refresh();
  eventChange();
  Application::processEvents();
  inputList.resizeColumns();
}

auto SystemInputSettings::refresh() -> void {
  u32 index = 0;
  auto& ports = Emulator::enumeratePorts(emulator->name);
  auto& port = ports[portList.selected().offset()];
  auto& device = port.devices[deviceList.selected().offset()];
  for(auto& input : device.inputs) {
    if(input.name == "L-Up") {
      print(string{"l up value is ", input.mapping, " on refresh, input address is ", &input, "\n"});
    }
    auto cell = inputList.item(index).cell(1);
    cell.setIcon(input.mapping->bindings[1].icon());
    cell.setText(input.mapping);
    index++;
  }
}

auto SystemInputSettings::eventContext(TableViewCell cell) -> void {
  if(!cell) return;
  if(cell.offset() == 0) return;  //ignore label cell
  if(cell.offset() >= BindingLimit) return;  //should never occur

  auto item = cell->parentTableViewItem();
  auto type = (InputNode::Type)item->attribute<u32>("type");
  //menu.setVisible(false);
  //menu.reset();
  auto& ports = Emulator::enumeratePorts(emulator->name);
  auto& port = ports[portList.selected().offset()];
  InputDevice& device = port.devices[deviceList.selected().offset()];
  auto poop = device.inputs[item->offset()];
  if(poop.name == "L-Up") {
    print(string{"l up value is ", poop.mapping, " on context define, input address is ", &poop, "\n"});
  }
  if(type == InputNode::Type::Analog) {
    for(int x : range(5)) {
      for(auto analogInputName : analogInputs) {
        MenuItem menuItem{&menu};
        mappingsMenuItemsGroup.append(menuItem);
        menuItem.setText(string{"VirtualPad", x + 1, "/", analogInputName}).onActivate([&, this] {
          auto mappingKey = menuItem.text();
          InputAnalog *mapping = cursedAnalogMap.find(mappingKey).data();
          InputNode element = device.inputs[item->offset()];
          std::vector<InputNode> listOfInputs = device.inputs;
          std::erase(listOfInputs, element);
          InputMapping& ref = *mapping;
          device.analog(element.name, ref);
          refresh();
        });
      }
    }
  } else if(type == InputNode::Type::Digital) {
    for(int x : range(5)) {
      for(auto digitalInputName : digitalInputs) {
        menu.append(MenuItem().setText(string{"VirtualPad", x + 1, "", digitalInputName}));
      }
    }
  } else if(type == InputNode::Type::Relative) {
    for(int x : range(5)) {
      for(auto relativeInputName : relativeInputs) {
        menu.append(MenuItem().setText(string{"VirtualPad", x + 1, "", relativeInputName}));
      }
    }
  }
  if(menu.actionCount()) menu.setVisible(true);
}

auto SystemInputSettings::eventChange() -> void {

}

auto SystemInputSettings::eventClear() -> void {
  auto& ports = Emulator::enumeratePorts(emulator->name);
  auto& port = ports[portList.selected().offset()];
  auto& device = port.devices[deviceList.selected().offset()];
  for(auto& item : inputList.batched()) {
    auto& mapping = *device.inputs[item.offset()].mapping;
    mapping.unbind();
  }
  refresh();
}

auto SystemInputSettings::eventAssign(TableViewCell cell, string binding) -> void {
  if(ruby::input.driver() == "None") return (void)MessageDialog().setText(
    "Bindings cannot be set when no input driver has been loaded.\n"
    "Please go to driver settings and activate an input driver first."
  ).setAlignment(settingsWindow).error();

  auto& ports = Emulator::enumeratePorts(emulator->name);
  auto& port = ports[portList.selected().offset()];
  auto& device = port.devices[deviceList.selected().offset()];
  if(auto item = inputList.selected()) {
    if(activeMapping) refresh();  //clear any previous assign arrow prompts
    activeMapping = device.inputs[item.offset()];
    activeBinding = max(0, (s32)cell.offset() - 1);

    for(auto device : inputManager.devices) {
      if(device->isMouse()) {
        for(auto& group : *device) {
          if(auto inputID = group.find(binding)) {
            auto groupID = (binding == "X" || binding == "Y") ? HID::Mouse::GroupID::Axis : HID::Mouse::GroupID::Button;
            activeMapping->mapping->bind(activeBinding, device, groupID, inputID(), 0, 1);
          }
        }
      }
    }

    activeMapping.reset();
    refresh();
  }
}

auto SystemInputSettings::eventAssign(TableViewCell cell) -> void {
  Program::Guard guard;
  inputManager.poll(true);  //clear any pending events first

  if(ruby::input.driver() == "None") return (void)MessageDialog().setText(
    "Bindings cannot be set when no input driver has been loaded.\n"
    "Please go to driver settings and activate an input driver first."
  ).setAlignment(settingsWindow).error();

  auto& ports = Emulator::enumeratePorts(emulator->name);
  auto& port = ports[portList.selected().offset()];
  auto& device = port.devices[deviceList.selected().offset()];
  if(auto item = inputList.selected()) {
    if(activeMapping) refresh();  //clear any previous assign arrow prompts
    activeMapping = device.inputs[item.offset()];
    activeBinding = max(0, (s32)cell.offset() - 1);

    item.cell(1 + activeBinding).setIcon(Icon::Go::Right).setText("(assign ...)");
    refresh();
    settingsWindow.setDismissable(false);
    Application::processEvents();
  }
}

auto SystemInputSettings::eventInput(std::shared_ptr<HID::Device> device, u32 groupID, u32 inputID, s16 oldValue, s16 newValue) -> void {
  if(!activeMapping) return;
  if(!settingsWindow.focused()) return;
  if(device->isMouse()) return;

  if(activeMapping->mapping->bind(activeBinding, device, groupID, inputID, oldValue, newValue)) {
    activeMapping.reset();
    refresh();
    timer.onActivate([&] {
      timer.setEnabled(false);
      inputList.setFocused();
      settingsWindow.setDismissable(true);
    }).setInterval(200).setEnabled();
  }
}

auto SystemInputSettings::setVisible(bool visible) -> SystemInputSettings& {
  if(visible == 0) activeMapping.reset(), settingsWindow.setDismissable(true);
  VerticalLayout::setVisible(visible);
  return *this;
}

auto SystemInputSettings::inputDriverUpdate() -> bool {
  if(emulator && settings.input.driver != "None" && MessageDialog(
    "Warning: incompatible drivers may cause this software to crash.\n"
    "Are you sure you want to change this driver while a game is loaded?"
  ).setAlignment(settingsWindow).question() != "Yes") return false;
  program.inputDriverUpdate();
  inputRefresh();
  return true;
}
