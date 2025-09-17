
auto OverrideSettings::construct() -> void {
  overrideTable.setHeadered();
  overrideTable.append(TableViewColumn().setText("Setting"));
  overrideTable.append(TableViewColumn().setText("Value"));
  addButton.setText("Add").onActivate([&] {
    overrideDialog.show();
  });
  removeButton.setText("Remove");
}

OverrideDialog::OverrideDialog() {
  layout.setPadding(5);
  acceptButton.setText("Accept").onActivate([&] { accept(); });
  cancelButton.setText("Cancel").onActivate([&] { cancel(); });
  for(auto overrideSetting : overrides) {
    settingSelector.append(ComboButtonItem().setText(overrideSetting.settingName));
  }

  onClose([&] { cancel(); });

  setSize({320, layout.minimumSize().height()});
  setDismissable();
}

auto OverrideDialog::show() -> Override {
  setVisible();
  return {};
}

auto OverrideDialog::accept() -> void {

}

auto OverrideDialog::cancel() -> void {

}
