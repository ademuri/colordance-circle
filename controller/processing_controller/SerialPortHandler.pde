public static class SerialPortHandler implements CallbackListener {
  public static boolean controlsModified = false;

  private final PApplet papplet;
  private static Serial port = null;

  SerialPortHandler(PApplet papplet) {
    this.papplet = papplet;
  }

  void controlEvent(CallbackEvent theEvent) {
    if (port != null) {
      port.stop();
    }

    String selectedPort = (String) ((DropdownList) theEvent.getController()).getItem((int) theEvent.getController().getValue()).get("text");
    print("Selected serial port: " + selectedPort + "\n");

    if (selectedPort.equals("none")) {
      port = null;
    } else {
      port = new Serial(papplet, selectedPort);
    }
  }

  static Serial getPort() {
    return port;
  }
}
