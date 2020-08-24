void NotificationScreenBuild() {
  notificationScreen = lv_obj_create(NULL, NULL);

  lv_obj_add_style(notificationScreen, LV_OBJ_PART_MAIN, &global_style);
  
  notificationScreenPage = lv_page_create(notificationScreen, NULL);
  lv_obj_add_style(notificationScreenPage, LV_OBJ_PART_MAIN, &global_style);
  lv_obj_add_style(notificationScreenPage, LV_OBJ_PART_MAIN, &notification_page_style);
  lv_obj_set_size(notificationScreenPage, 240, 240);
  lv_obj_align(notificationScreenPage, NULL, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_event_cb(notificationScreenPage, NotificationScreenEventCallback);
  lv_page_set_scrl_width(notificationScreenPage, 200);
  lv_page_set_scrl_layout(notificationScreenPage, LV_LAYOUT_COLUMN_LEFT);

  lv_page_clean(notificationScreenPage);

  if (bluetoothConnected) {
    ANCSBLEClient * BLEclient = notifications.getANCSBLEClient();
    ANCSNotificationQueue * queue;
    std::map<uint32_t, Notification> * notificationList;
    
    if (BLEclient != nullptr) {
      queue = BLEclient->getANCSNotificationQueue();
    } else {
      Serial.println("BLE Client object not initialized! Possibly connection is dead?");
      return;
    }
    if (queue != nullptr) {
      notificationList = queue->getNotificationList();
    } else {
      Serial.println("Notification queue parent object not initialized!");
      return;
    }
    
    std::map<uint32_t, Notification>::iterator itr;
    uint8_t notificationListSize = notificationList->size();
    
    if (notificationListSize) {
      itr = notificationList->begin();
      for (int i = 0; i < notificationListSize; i++) {
        if ((String(itr->second.message.c_str()) != "") && (String(itr->second.title.c_str()) != "")) {
//          contents = contents + "#ff0000 " + String(itr->second.title.c_str()) + "# " + String(itr->second.message.c_str()).substring(0, 100) + "\n";
          String _from = itr->second.type.c_str();
          String _subject = itr->second.title.c_str();
          String _message = itr->second.message.c_str();
          NotificationScreenCreateNotificationElement(itr->second.uuid, _from, _subject, _message);
        }
        itr++;
      }
    } else {
      Serial.println("You have no notifications.");
    }
  } else {
    Serial.println("Please connect your " + String(DEVICE_NAME) + " to your phone to recieve notifications.");
  }
}

void NotificationScreenEventCallback(lv_obj_t * obj, lv_event_t event) {
  switch(event) {
    case LV_EVENT_CLICKED:
      break;

    default:
      break;
  }
}

void NotificationScreenSetNotificationUpdateState(bool temp) {
  notificationUpdateState = temp;
}

void NotificationScreenCreateNotificationElement(uint32_t _uuid, String _from, String _subject, String _message) {
  lv_obj_t * cont = lv_cont_create(notificationScreenPage, NULL);
  lv_obj_add_style(cont, LV_OBJ_PART_MAIN, &notification_container_style);
  lv_obj_set_click(cont, false);
  lv_obj_set_user_data(cont, _uuid);
  lv_cont_set_fit2(cont, LV_FIT_PARENT, LV_FIT_TIGHT);
  lv_cont_set_layout(cont, LV_LAYOUT_COLUMN_LEFT);

  lv_obj_t * from_label = lv_label_create(cont, NULL);
  lv_obj_add_style(from_label, LV_OBJ_PART_MAIN, &notification_element_from_style);
  lv_label_set_long_mode(from_label, LV_LABEL_LONG_DOT);
  lv_obj_set_width(from_label, lv_obj_get_width(cont) - 20);
  lv_label_set_text(from_label, _from.c_str());

  lv_obj_t * subject_label = lv_label_create(cont, NULL);
  lv_obj_add_style(subject_label, LV_OBJ_PART_MAIN, &notification_element_subject_style);
  lv_label_set_long_mode(subject_label, LV_LABEL_LONG_DOT);
  lv_obj_set_width(subject_label, lv_obj_get_width(cont) - 20);
  lv_label_set_text(subject_label, _subject.c_str());

  lv_obj_t * message_label = lv_label_create(cont, NULL);
  lv_obj_add_style(message_label, LV_OBJ_PART_MAIN, &notification_element_message_style);
  lv_label_set_long_mode(message_label, LV_LABEL_LONG_BREAK);
  lv_obj_set_width(message_label, lv_obj_get_width(cont) - 20);
  lv_label_set_text(message_label, _message.c_str());
}

void NotificationScreenTask(lv_task_t * _task) {
  
}

void NotificationScreenDestroy() {
  if (notificationScreenTask != nullptr) {
    lv_task_del(notificationScreenTask);
  }
  if (notificationScreen != nullptr) {
    lv_obj_del(notificationScreen);
  }
}
