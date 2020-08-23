void ClockScreenBuild() {
  clockScreen = lv_obj_create(NULL, NULL);
  lv_obj_add_style(clockScreen, LV_OBJ_PART_MAIN, &global_style);

  clockScreenClockLabel = lv_label_create(clockScreen, NULL);
  lv_obj_add_style(clockScreenClockLabel, LV_OBJ_PART_MAIN, &clock_label_style);
  lv_obj_align_origo(clockScreenClockLabel, NULL, LV_ALIGN_CENTER, 0, 0);

  lv_obj_t * clockScreenNotificationsButton = lv_btn_create(clockScreen, NULL);
  lv_obj_add_style(clockScreenNotificationsButton, LV_BTN_PART_MAIN, &global_style);
  lv_obj_set_event_cb(clockScreenNotificationsButton, ClockScreenEventCallback);
  lv_obj_align(clockScreenNotificationsButton, NULL, LV_ALIGN_CENTER, 0, 60);

  lv_obj_t * clockScreenNotificationsButtonLabel = lv_label_create(clockScreenNotificationsButton, NULL);
  lv_label_set_text(clockScreenNotificationsButtonLabel, "Notifications");

  updateClockScreenClockLabel();
  
  clockScreenTask = lv_task_create(ClockScreenTask, 500, LV_TASK_PRIO_MID, NULL);
}

void ClockScreenEventCallback(lv_obj_t * obj, lv_event_t event) {
  switch(event) {
    case LV_EVENT_CLICKED:
      NotificationScreenBuild();
      lv_scr_load(notificationScreen);
      ClockScreenDestroy();
      break;

    default:
      
      break;
  }
}

void ClockScreenTask(lv_task_t * _task) {
  updateClockScreenClockLabel();
}

void updateClockScreenClockLabel() {
  RTC_Date now_datetime = rtc->getDateTime();
  String now_string = zeroPad(now_datetime.hour) + ':' + zeroPad(now_datetime.minute) + ':' + zeroPad(now_datetime.second);
  lv_label_set_text(clockScreenClockLabel, now_string.c_str());
  lv_obj_realign(clockScreenClockLabel);
}

void ClockScreenDestroy() {
  lv_task_del(clockScreenTask);
  lv_obj_del(clockScreen);
}

String zeroPad(int value) {
  if (value < 10) {
    return '0' + String(value);
  } else {
    return String(value);
  }
}
