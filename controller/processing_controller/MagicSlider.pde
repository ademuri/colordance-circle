public class MagicSlider extends MagicControl<Slider> {

  MagicSlider(ControlP5 cp5, String paramIdentifier, String name, int minValue, int maxValue) {
    super(paramIdentifier, cp5.addSlider(name)
      .setRange(minValue, maxValue)
      .setWidth(20)
      .setHeight(60)
      .setHandleSize(20)
      .setSliderMode(Slider.FLEXIBLE));
  }
}
