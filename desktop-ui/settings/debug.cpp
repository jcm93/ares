auto DebugSettings::construct() -> void {
  setCollapsible();
  setVisible(false);

  debugLabel.setText("GDB Server:");
  debugOption.setText("Enable remote debugging via the GDB protocol over the local network");
  portLabel.setText("Port:");

  port.setText(integer(settings.debugServer.port));
  port.setEditable(true);
  port.onChange([&](){
    settings.debugServer.port = port.text().integer();
    string portStr = integer(settings.debugServer.port);

    if(portStr != port.text()) {
      port.setText(settings.debugServer.port == 0 ? string{""} : portStr);
    }

    infoRefresh();
  });

  portHint.setText("Safe range: 1024 - 32767").setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);
  connectInfo.setFont(Font().setSize(7.0)).setForegroundColor(SystemColor::Sublabel);

  ipv4Label.setText("Use IPv4:");

  ipv4.setEnabled(true);
  ipv4.setChecked(settings.debugServer.useIPv4);
  ipv4.onToggle([&](){
    settings.debugServer.useIPv4 = ipv4.checked();
    serverRefresh();
    infoRefresh();
  });

  debugOption.setChecked(settings.debugServer.enabled);
  debugOption.onToggle([&](){
    settings.debugServer.enabled = debugOption.checked();
    ipv4.setEnabled(debugOption.checked());
    port.setEnabled(debugOption.checked());
    serverRefresh();
    infoRefresh();
  });

  debugServerTableLayout.setSize(Size{2, 5});
  debugServerTableLayout.column(0).setAlignment(1.0);

  infoRefresh();
  ipv4.setEnabled(debugOption.checked());
  port.setEnabled(debugOption.checked());
}

auto DebugSettings::infoRefresh() -> void {
  connectInfo.setText(settings.debugServer.useIPv4
    ? "Note: IPv4 mode binds to any device, enabling anyone on your network to access this server"
    : "Note: localhost only (for Windows/WSL: please use IPv4 instead)"
  );
}

auto DebugSettings::serverRefresh() -> void {
  nall::GDB::server.close();

  if(settings.debugServer.enabled) {
    nall::GDB::server.open(settings.debugServer.port, settings.debugServer.useIPv4);
  }
}
