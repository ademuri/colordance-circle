public abstract class MagicButtonGroupControl<T extends ButtonGroup> implements CallbackListener {
  // This is the token that identifies the param for this control - this is used to communicate this param to the Colordance program. Probably a single character.
  protected final String paramIdentifier;
  protected final T buttons;

  MagicButtonGroupControl(String paramIdentifier, T buttons) {
    this.paramIdentifier = paramIdentifier;
    this.buttons = buttons;

    buttons.setOnChange(this);
  }

  protected int getValue() {
    return buttons.getValue();
  }
  
  void controlEvent(CallbackEvent theEvent) {
    String output = String.format("%s: %d\n", paramIdentifier, getValue()); 
    if (SerialPortHandler.getPort() == null) {
      print(output);
    } else {
      SerialPortHandler.getPort().write(output);
    }
  }
}
