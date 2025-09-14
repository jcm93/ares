
auto OverrideSettings::construct() -> void {
  overrideTable.setHeadered();
  overrideTable.append(TableViewColumn().setText("Setting"));
  overrideTable.append(TableViewColumn().setText("Value"));
  addButton.setText("Add").onActivate([&] {
    if(auto newOverride = OverrideDialog()) {
      
    }
  });
  removeButton.setText("Remove");
}
