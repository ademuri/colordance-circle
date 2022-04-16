public class EffectGroup extends ButtonGroup {
  protected int buttonIndex = -1;
  
  EffectGroup(ControlP5 cp5) {
   super(cp5,
         new String[] {"Effect 1", "Effect 2", "Effect 3", "Effect 4", "Effect 5", "Effect 6", "Effect 7"},
         new int[][] {{300,250},{450,250},{600,250},{225,375},{375,375},{525,375},{675,375}});
   getButton(0).setOn();
   buttonIndex = 0;
  }

    protected int getValue() {
    Button currentButton = getButton(buttonIndex);
    if (currentButton.isOn()) {
      currentButton.setOff();
      for(int i=0; i<7; i++) {
        if(getButton(i).isOn()) {
          buttonIndex = i;
          return buttonIndex;
        }
      }
    } else {
      currentButton.setOn();
    }
    
    return buttonIndex;
  }
}
