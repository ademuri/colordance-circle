public abstract class MagicControl<T extends Controller> implements CallbackListener {
  // This is the token that identifies the param for this control - this is used to communicate this param to the Colordance program. Probably a single character.
  protected final String paramIdentifier;
  protected final T control;

  MagicControl(String paramIdentifier, T control) {
    this.paramIdentifier = paramIdentifier;
    this.control = control;

    control.onChange(this);
  }

  protected int getValue() {
    return (int) control.getValue();
  }

  void controlEvent(CallbackEvent theEvent) {
    String output = String.format("%s: %d\n", paramIdentifier, getValue()); 
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
