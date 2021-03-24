public class MovementGroup extends ButtonGroup {
  protected int value = -1;
  MovementGroup(ControlP5 cp5) {
   super(cp5,
         new String[] {"Stable", "Rotate Selection", "Rotate In", "Across Flash", "Side Flash"},
         new int[][] {{100,800},{200,800},{300,800},{400,800},{500,800}});
   getButton(0).setOn();
   value = 0;
  }

  protected int getValue() {
    Button currentButton = getButton(value);
    if (currentButton.isOn()) {
      currentButton.setOff();
      for(int i=0; i<5; i++) {
        if(getButton(i).isOn()) {
          value = i;
          return value;
        }
      }
    } else {
      currentButton.setOn();
    }
    
    return value;
  }
}
