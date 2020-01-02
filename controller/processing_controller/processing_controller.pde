import processing.serial.*;
import controlP5.*;  

SerialPortHandler serialPortHandler;
ControlP5 cp5;
DropdownList serialPortSelector;
Slider slider;

void setup() {
  size(400, 400);
  cp5 = new ControlP5(this);
  serialPortHandler = new SerialPortHandler(this);
  serialPortSelector = cp5.addDropdownList("serialPortSelector")
    .setPosition(0, 0)
    .onChange(serialPortHandler);

  serialPortSelector.addItem("none", null)
    .addItems(Serial.list())
    .close();


  MagicSlider slider = new MagicSlider(cp5, "m");
  slider.getControl().setPosition(100, 100);
}

void draw() {
  background(128);
}
