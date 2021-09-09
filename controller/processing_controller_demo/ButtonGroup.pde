public abstract class ButtonGroup {
  // This is the token that identifies the param for this control - this is used to communicate this param to the Colordance program. Probably a single character.
 protected ArrayList<Button> buttons;
 ButtonGroup(ControlP5 cp5, String[] names, int[][] positions) {
    buttons = new ArrayList();
    for (int i=0; i<positions.length; i++) {
      buttons.add(cp5.addButton(names[i])
      .setSize(50, 50)
      .setSwitch(true)
      .setPosition(positions[i][0]-25, positions[i][1]-25));
    }
  }
  
  protected Button getButton(int index) {
    return buttons.get(index);
  }
  
  protected int getValue() {
    return -1;
  }
  
  protected void setOnChange(CallbackListener listener) {
    for (Button button : buttons) {
      button.onRelease(listener);
    }
  }
}
