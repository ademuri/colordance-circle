import processing.serial.*;
import controlP5.*;  
import http.*;

SerialPortHandler serialPortHandler;
ControlP5 cp5;
DropdownList serialPortSelector;

// To get this library, download this zip, and extract it into ~/sketchbook/libraries
// https://diskordier.net/simpleHTTPServer/download/SimpleHTTPServer-6.zip
SimpleHTTPServer server;

void setup() {
  size(1000, 1000);
  
  // This creates an HTTP server listening on http://localhost:8000/
  server = new SimpleHTTPServer(this); 
  DynamicResponseHandler responder = new DynamicResponseHandler(new JsonHandler(), "application/json");
  server.createContext("set", responder);
  
  cp5 = new ControlP5(this);
  serialPortHandler = new SerialPortHandler(this);
  serialPortSelector = cp5.addDropdownList("serialPortSelector")
    .setPosition(0, 0)
    .onChange(serialPortHandler)
    .addItem("none", null)
    .addItems(Serial.list())
    .close();
  
   /* Pole stuff */
   
  MagicPoleButtons poles = new MagicPoleButtons(cp5, "p");
  MagicMovementButtons poleMovement = new MagicMovementButtons(cp5, "m");
  
  MagicSlider movementSpeed = new MagicSlider(cp5, "s", "Movement Speed", 0, 4);
  movementSpeed.getControl().setPosition(400, 100);
  MagicSlider pollHueShift = new MagicSlider(cp5, "h", "Pole Hue Shift", 0, 127);
  pollHueShift.getControl().setPosition(500, 100);
  
  MagicButtons colorBalance= new MagicButtons(cp5, "l", "Balance Color");
  colorBalance.getControl().setPosition(550, 100);
  
  
  /* Grid stuff */

  MagicModeButtons gridMode = new MagicModeButtons(cp5, "g");
  
  MagicButtons gridSmoothColor = new MagicButtons(cp5, "o", "Grid Smooth Color");
  gridSmoothColor.getControl().setPosition(420, 600);
  MagicButtons gridReverse= new MagicButtons(cp5, "r", "Grid Reverse");
  gridReverse.getControl().setPosition(520, 350);
  MagicButtons gridBackForth= new MagicButtons(cp5, "b", "Grid Back Forth");
  gridBackForth.getControl().setPosition(430, 350);
  
  MagicSlider gridLightCount = new MagicSlider(cp5, "c", "Grid Light Count", 1, 4); 
  gridLightCount.getControl().setPosition(350, 350);
  gridLightCount.getControl().setNumberOfTickMarks(4);
  gridLightCount.getControl().snapToTickMarks(true);
  
  MagicSlider gridSpeed = new MagicSlider(cp5, "e", "Grid Speed", 0, 12);
  gridSpeed.getControl().setPosition(620, 350);
  
  MagicSlider gridHueShift = new MagicSlider(cp5, "i", "Grid Hue Shift", 0, 255);
  gridHueShift.getControl().setPosition(350, 580);
  MagicSlider gridHueDistance = new MagicSlider(cp5, "d", "Grid Hue Distance", 0, 127);
  gridHueDistance.getControl().setPosition(620, 580);

}

void draw() {
  background(128);
}

class JsonHandler extends ResponseBuilder {
  public String getResponse(String requestBody) {
    JSONObject json = parseJSONObject(requestBody);
    String name = json.getString("name");
    String value = json.getString("value");
    System.out.format("(%s, %s)\n", name, value);
    return "{'error': false}";
  }
}
