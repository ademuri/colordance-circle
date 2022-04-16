public class MagicEffectButtons extends MagicButtonGroupControl<EffectGroup> {
  MagicEffectButtons(ControlP5 cp5, String paramIdentifier) {
    super(paramIdentifier, new EffectGroup(cp5));
  }
}
