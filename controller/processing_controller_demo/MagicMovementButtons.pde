public class MagicMovementButtons extends MagicButtonGroupControl<MovementGroup> {
  MagicMovementButtons(ControlP5 cp5, String paramIdentifier) {
    super(paramIdentifier, new MovementGroup(cp5));
  }
}
