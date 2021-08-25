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
   
  MagicPoleButtons poles = new MagicPoleButtons(cp5, "p");
  MagicMovementButtons poleMovement = new MagicMovementButtons(cp5, "m");
  
  MagicSlider bpm = new MagicSlider(cp5, "b", "BPM", 60, 180);
  bpm.getControl().setPosition(700, 100);
  bpm.getControl().setHeight(200);
 
  MagicButtons setBeat= new MagicButtons(cp5, "a", "Set Beat");
  setBeat.getControl().setPosition(750, 120);
  setBeat.getControl().setHeight(60);
  setBeat.getControl().setWidth(60);
 
  MagicButtons pause = new MagicButtons(cp5, "u", "Pause");
  pause.getControl().setPosition(750, 220);
  pause.getControl().setHeight(60);
  pause.getControl().setWidth(60);
  
  
  MagicSlider movementSpeed = new MagicSlider(cp5, "s", "Movement Speed", 1, 4);
  movementSpeed.getControl().setPosition(500, 100);
  MagicSlider pollHueShift = new MagicSlider(cp5, "h", "Pole Hue Shift", 0, 127);
  pollHueShift.getControl().setPosition(400, 100);
  
  MagicButtons colorBalance= new MagicButtons(cp5, "l", "Balance Color");
  colorBalance.getControl().setPosition(300, 100);
  
  
  /* Grid stuff */

  MagicModeButtons gridMode = new MagicModeButtons(cp5, "g");
  
  MagicButtons gridSmoothColor = new MagicButtons(cp5, "o", "Grid Smooth Color");
  gridSmoothColor.getControl().setPosition(420, 600);
  MagicButtons gridReverse= new MagicButtons(cp5, "r", "Grid Reverse");
  gridReverse.getControl().setPosition(520, 350);
  MagicButtons gridBackForth= new MagicButtons(cp5, "f", "Grid Back Forth");
  gridBackForth.getControl().setPosition(430, 350);
  
  MagicSlider gridLightCount = new MagicSlider(cp5, "c", "Grid Light Count", 1, 4); 
  gridLightCount.getControl().setPosition(350, 350);
  gridLightCount.getControl().setNumberOfTickMarks(4);
  gridLightCount.getControl().snapToTickMarks(true);
  
  MagicSlider gridSpeed = new MagicSlider(cp5, "e", "Grid Speed", 1, 4);
  gridSpeed.getControl().setPosition(620, 350);
  
  MagicSlider gridHueShift = new MagicSlider(cp5, "i", "Grid Hue Shift", 0, 127);
  gridHueShift.getControl().setPosition(350, 580);
  MagicSlider gridHueDistance = new MagicSlider(cp5, "d", "Grid Hue Distance", 0, 127);
  gridHueDistance.getControl().setPosition(620, 580);

}

void draw() {
  background(128);
}
