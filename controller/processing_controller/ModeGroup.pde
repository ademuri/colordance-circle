public class ModeGroup extends ButtonGroup {
  protected int buttonIndex = -1;
  protected int value = -1;
  protected int lineValue = -1;
  protected int crossValue = -1;
  protected int circleValue = -1;
  
  ModeGroup(ControlP5 cp5) {
   super(cp5,
         new String[] {"Line", "Cross", "Circle", "Breathe", "Twinke"},
         new int[][] {{420,450},{490,450},{560,450},{420,550},{490,550}});
   getButton(0).setOn();
   buttonIndex = 0;
   value = 0;
   lineValue = 0;    //max 8
   crossValue = 0;   //max 4
   circleValue = 0;  //max 2
  }

  protected int getValue() {
    Button currentButton = getButton(buttonIndex); //button from old value
    if (currentButton.isOn()) {
      currentButton.setOff();
      for(int i=0; i<5; i++) {
        if(getButton(i).isOn()) {
          buttonIndex = i;
        }
      }
    } else {
      currentButton.setOn();
      if(buttonIndex == 0) {
        lineValue = (++lineValue)%4;
      } else if(buttonIndex == 1) {
        crossValue = (++crossValue)%2;
      } else if(buttonIndex == 2) {
        circleValue = (++circleValue)%4;
      }
        
    }
    updateValue();
    return value;
  }
  
  private void updateValue() {
    if(buttonIndex == 0) {
        value = lineValue;
      } else if(buttonIndex == 1) {
        value = 4 + crossValue;
      } else if(buttonIndex == 2) {
        value = 6 + circleValue;
      } else if(buttonIndex == 3) {
        value = 10;
      } else {
        value = 11;
      }
  }
}
