#define LILYGO_WATCH_2020_V1
#define LILYGO_WATCH_LVGL
#include <LilyGoWatch.h>

#include "esp32notifications.h"
#include "ancs_notification_queue.h"
#include <map>
#include <vector>
#include <stack>

#define DEVICE_NAME "jWatch"
#define BACKLIGHT_TRANSITION_TIME 500

BLENotifications  notifications;
uint32_t          incomingCallNotificationUUID;
bool              bluetoothConnected              = false;
bool              lvglIsRunning                   = true;
TTGOClass *       ttgo;
PCF8563_Class *   rtc;

lv_task_t *       powerTask;
bool              IRQHasMessage;

uint8_t           maxBrightness                   = 255;
uint8_t           normalBrightness                = 127;
uint8_t           currentBrightness               = 127;
uint8_t           currentBrightnessCache          = 127;
uint8_t           minBrightness                   = 0;
uint32_t          backlightTransitionStart        = 0;
bool              backlightStatus                 = true;
lv_task_t *       backlightTask;

lv_obj_t *        clockScreen;
lv_task_t *       clockScreenTask;
lv_obj_t *        clockScreenClockLabel;

lv_obj_t *        notificationScreen;
lv_obj_t *        notificationScreenPage;
lv_task_t *       notificationScreenTask;
bool              notificationUpdateState         = false;
uint8_t           notificationUpdateCounter       = 0;

lv_style_t        global_style;
lv_style_t        clock_label_style;
lv_style_t        notification_page_style;
lv_style_t        notification_container_style;
lv_style_t        notification_element_from_style;
lv_style_t        notification_element_subject_style;
lv_style_t        notification_element_message_style;

void setup() {
  Serial.begin(115200);
  ttgo = TTGOClass::getWatch();
  ttgo->begin();
  ttgo->openBL();
  ttgo->bl->adjust(normalBrightness);
  ttgo->lvgl_begin();
  rtc = ttgo->rtc;
  rtc->check();

  setupPower();

  notifications.begin(DEVICE_NAME);
  notifications.setConnectionStateChangedCallback(onBLEStateChanged);
  notifications.setNotificationCallback(onNotificationArrived);
  notifications.setRemovedCallback(onNotificationRemoved);

  setupStyles();
//  NotificationScreenBuild();
//  lv_scr_load(notificationScreen);
  ClockScreenBuild();
  lv_scr_load(clockScreen);
  
  delay(2000);
}

void loop() {
  if (lvglIsRunning) {
    lv_task_handler();
  }
}
