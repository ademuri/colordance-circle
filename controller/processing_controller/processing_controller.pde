import processing.serial.*;
import controlP5.*;  

SerialPortHandler serialPortHandler;
ControlP5 cp5;
DropdownList serialPortSelector;

void setup() {
  size(1000, 1000);
  cp5 = new ControlP5(this);
  serialPortHandler = new SerialPortHandler(this);
  serialPortSelector = cp5.addDropdownList("serialPortSelector")
    .setPosition(0, 0)
    .onChange(serialPortHandler)
    .addItem("none", null)
    .addItems(Serial.list())
    .close();
  
   /* Poll stuff */
   
  MagicEffectButtons effect = new MagicEffectButtons(cp5, "e");
  
  MagicSlider s1 = new MagicSlider(cp5, "v", "S1", 0, 255);
  s1.getControl().setPosition(333, 530);
  
  MagicSlider s2 = new MagicSlider(cp5, "w", "S2", 0, 255);
  s2.getControl().setPosition(533, 530);
  
  MagicButtons b1 = new MagicButtons(cp5, "x", "Option 1");
  b1.getControl().setPosition(205, 517);
  b1.getControl().setHeight(75);
  b1.getControl().setWidth(75);
  
  MagicButtons b2 = new MagicButtons(cp5, "y", "Option 2");
  b2.getControl().setPosition(720, 517);
  b2.getControl().setHeight(75);
  b2.getControl().setWidth(75);
  

  
  MagicButtons reverse = new MagicButtons(cp5, "s", "Shift");
  reverse.getControl().setPosition(279, 650);
  reverse.getControl().setHeight(83);
  reverse.getControl().setWidth(83);
  
  MagicButtons shiftLoop = new MagicButtons(cp5, "l", "Shift Loop");
  shiftLoop.getControl().setPosition(221, 629);
  shiftLoop.getControl().setHeight(33);
  shiftLoop.getControl().setWidth(33);
  
  MagicButtons beat = new MagicButtons(cp5, "b", "BEAT");
  beat.getControl().setPosition(409, 621);
  beat.getControl().setHeight(141);
  beat.getControl().setWidth(182);
  
  MagicButtons pause = new MagicButtons(cp5, "p", "Pause");
  pause.getControl().setPosition(637, 650);
  pause.getControl().setHeight(83);
  pause.getControl().setWidth(83);
  
}

void draw() {
  background(128);
}
