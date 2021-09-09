public class MagicModeButtons extends MagicButtonGroupControl<ModeGroup> {
  MagicModeButtons(ControlP5 cp5, String paramIdentifier) {
    super(paramIdentifier, new ModeGroup(cp5));
  }
}
