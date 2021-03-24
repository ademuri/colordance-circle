public class MagicButtons extends MagicControl<Button> {
  MagicButtons(ControlP5 cp5, String paramIdentifier, String name) {
    super(paramIdentifier, cp5.addButton(name)
      .setWidth(50)
      .setHeight(50)
      .setSwitch(true)
      );
  }

  protected int getValue() {
    return control.isOn() ? 1 : 0;
  }
}
