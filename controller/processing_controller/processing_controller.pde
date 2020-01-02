import processing.serial.*;
import controlP5.*;


Serial port;       

ControlP5 cp5;
DropdownList serialPortSelector;
Slider slider;

void setup() {
  size(400, 400);
  cp5 = new ControlP5(this);
  serialPortSelector = cp5.addDropdownList("serialPortSelector")
    .setPosition(0, 0)
    .onChange(new SerialPortUpdater(this));

  serialPortSelector.addItem("none", null)
    .addItems(Serial.list())
    .close();

  slider = cp5.addSlider("slider1")
    .setPosition(100, 100)
    .setRange(0, 255)
    .setWidth(50)
    .setHeight(255)
    .setHandleSize(50)
    .setSliderMode(Slider.FLEXIBLE)
    .onChange(new ParamUpdater());
}

void draw() {
  background(128);
}

private class SerialPortUpdater implements CallbackListener {
  PApplet papplet;

  SerialPortUpdater(PApplet papplet) {
    this.papplet = papplet;
  }

  void controlEvent(CallbackEvent theEvent) {
    if (port != null) {
      port.stop();
    }

    String selectedPort = (String) serialPortSelector.getItem((int)serialPortSelector.getValue()).get("text");
    print("Selected serial port: " + selectedPort + "\n");

    if (selectedPort.equals("none")) {
      port = null;
    } else {
      port = new Serial(papplet, selectedPort);
    }
  }
}

private class ParamUpdater implements CallbackListener {
  void controlEvent(CallbackEvent theEvent) {
    String output = String.format("m: %d\n", (int)slider.getValue()); 
    if (port == null) {
      print(output);
    } else {
      port.write(output);
    }
  }
}
