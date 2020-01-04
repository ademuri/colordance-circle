public class MagicSlider extends MagicControl<Slider> {

  MagicSlider(ControlP5 cp5, String paramIdentifier, String name) {
    super(paramIdentifier, cp5.addSlider(name)
      .setRange(0, 255)
      .setWidth(50)
      .setHeight(255)
      .setHandleSize(50)
      .setSliderMode(Slider.FLEXIBLE));
  }
}
