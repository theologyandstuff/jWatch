void backlightFadeIn() {
  backlightTransitionStart = millis();
  currentBrightnessCache = currentBrightness;
  Serial.println("Beginning backlight fade in");
  backlightTask = lv_task_create(BacklightFadeInTask, 50, LV_TASK_PRIO_HIGH, NULL);

//  lv_tick_inc(LV_DISP_DEF_REFR_PERIOD);
//  timer_start();
//  lv_task_handler();
//  lvglIsRunning = true;
}

void backlightFadeOut() {
  backlightTransitionStart = millis();
  currentBrightnessCache = currentBrightness;
  Serial.println("Beginning backlight fade out");
  backlightTask = lv_task_create(BacklightFadeOutTask, 50, LV_TASK_PRIO_HIGH, NULL);
  
//  timer_stop();
//  lvglIsRunning = false;
}

void BacklightFadeOutTask(lv_task_t * _task) {
  if (currentBrightness > minBrightness) {
    currentBrightness = 
      max(
        (int)map(
          (int)(millis() - backlightTransitionStart),
          0, 
          BACKLIGHT_TRANSITION_TIME, 
          currentBrightnessCache, 
          minBrightness
          ), 
        0
      );
    
    ttgo->bl->adjust(currentBrightness);
  } else {
    Serial.println("Backlight fade out finished.");
    currentBrightnessCache = currentBrightness;
    backlightStatus = false;
    lv_task_del(_task);
  }
}

void BacklightFadeInTask(lv_task_t * _task) {
  if (currentBrightness < normalBrightness) {
    currentBrightness = 
      min(
        (int)map(
          (int)(millis() - backlightTransitionStart),
          0, 
          BACKLIGHT_TRANSITION_TIME, 
          currentBrightnessCache, 
          normalBrightness
          ), 
        (int)normalBrightness
      );
    
    ttgo->bl->adjust(currentBrightness);
  } else {
    Serial.println("Backlight fade in finished.");
    currentBrightnessCache = currentBrightness;
    backlightStatus = true;
    lv_task_del(_task);
  }
}
