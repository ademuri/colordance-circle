public abstract class MagicControl<T extends Controller> implements CallbackListener {
  private final String paramIdentifier;
  private final T control;

  MagicControl(String paramIdentifier, T control) {
    this.paramIdentifier = paramIdentifier;
    this.control = control;

    control.onChange(this);
  }

  void controlEvent(CallbackEvent theEvent) {
    String output = String.format("%s: %d\n", paramIdentifier, (int)control.getValue()); 
    if (SerialPortHandler.getPort() == null) {
      print(output);
    } else {
      SerialPortHandler.getPort().write(output);
    }
  }

  T getControl() {
    return control;
  }
}