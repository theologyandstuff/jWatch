void setupPower() {
  pinMode(AXP202_INT, INPUT_PULLUP);
  attachInterrupt(AXP202_INT, IRQISR, FALLING);

  ttgo->power->enableIRQ(AXP202_PEK_SHORTPRESS_IRQ, true);

  ttgo->power->clearIRQ();
  
  powerTask = lv_task_create(PowerTask, 250, LV_TASK_PRIO_MID, NULL);
}

void IRQISR() {
  IRQHasMessage = true;
//  lv_task_once(powerTask);
//  powerTask = lv_task_create_basic();
//  lv_task_set_cb(powerTask, IRQTask);
}

void PowerTask(lv_task_t * _task) {
  if (IRQHasMessage) {
    ttgo->power->readIRQ();
    
    if (ttgo->power->isPEKShortPressIRQ()) {
      Serial.println("Button Pressed!");

      if (lv_scr_act() == clockScreen) {
        toggleBacklight();
      } else if (lv_scr_act() == notificationScreen) {
        NotificationScreenBuild();
        lv_scr_load(notificationScreen);
        ClockScreenDestroy();
      } else {
        toggleBacklight();
      }
    }
  
    ttgo->power->clearIRQ();
    IRQHasMessage = false;
  }
}

void toggleBacklight() {
  if (backlightStatus) {
    backlightFadeOut();
  } else {
    backlightFadeIn();
  }
}
