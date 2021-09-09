public class PoleGroup extends ButtonGroup {
  protected int value = -1;
  PoleGroup(ControlP5 cp5) {
   super(cp5,
         new String[] {"Pole 1", "Pole 2", "Pole 3", "Pole 4", "Pole 5", "Pole 6"},
         new int[][] {{115+270,400+300},{0+270,200+300},{115+270,0+300},{345+270,0+300},{460+270,200+300},{345+270,400+300}});
   getButton(0).setOn();
   value = 1;
  }

  protected int getValue() {
    
    int oldValue = value;
    value = 0;
    for (int i=0; i<6; i++) {
      if(getButton(i).isOn()) {
        value |= 1 << i;
      }
    }
    
    //Always keep one pole on
    /*if(value == 0) {
      for (int i=0; i<6; i++) {
        if(oldValue == 1 << i) {
           Button lastButtonOn = getButton(i);
           lastButtonOn.setOn();
        }
      }
      value = oldValue; 
    }  */
    
    return value;
  }
}
