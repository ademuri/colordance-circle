public class MagicPoleButtons extends MagicButtonGroupControl<PoleGroup> {
  MagicPoleButtons(ControlP5 cp5, String paramIdentifier) {
    super(paramIdentifier, new PoleGroup(cp5));
  }
}
