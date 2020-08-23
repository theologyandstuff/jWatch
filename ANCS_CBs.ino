void onBLEStateChanged(BLENotifications::State state) {
  switch(state) {
    case BLENotifications::StateConnected:
      bluetoothConnected = true;
      break;

    case BLENotifications::StateDisconnected:
      bluetoothConnected = false;
      notifications.startAdvertising(); 
      break; 
  }
}

void onNotificationArrived(const ArduinoNotification * notification, const Notification * rawNotificationData) {
  Serial.println("Added Notification: #" + String(notification->uuid));
  if (lv_scr_act() == notificationScreen) {
    NotificationScreenCreateNotificationElement(notification->uuid, notification->type, notification->title, notification->message);
    NotificationScreenSetNotificationUpdateState(true);
  }
}

void onNotificationRemoved(const ArduinoNotification * notification, const Notification * rawNotificationData) {
  Serial.println("Removed Notification: #" + String(notification->uuid));
  if (lv_scr_act() == notificationScreen) {
    NotificationScreenSetNotificationUpdateState(true);
  }
}
