import processing.serial.*;
import controlP5.*;  

SerialPortHandler serialPortHandler;
ControlP5 cp5;
DropdownList serialPortSelector;

void setup() {
  size(450, 250);
  cp5 = new ControlP5(this);
  serialPortHandler = new SerialPortHandler(this);
  serialPortSelector = cp5.addDropdownList("serialPortSelector")
    .setPosition(0, 0)
    .onChange(serialPortHandler)
    .addItem("none", null)
    .addItems(Serial.list())
    .close();
  
   /* Poll stuff */
 
  MagicButtons prev = new MagicButtons(cp5, "p", "Previous");
  prev.getControl().setPosition(100, 120);
  prev.getControl().setHeight(60);
  prev.getControl().setWidth(60);
 
  MagicButtons rand = new MagicButtons(cp5, "r", "Random");
  rand.getControl().setPosition(200, 120);
  rand.getControl().setHeight(60);
  rand.getControl().setWidth(60);
  
  MagicButtons next = new MagicButtons(cp5, "n", "Next");
  next.getControl().setPosition(300, 120);
  next.getControl().setHeight(60);
  next.getControl().setWidth(60);
 
}

void draw() {
  background(128);
}
