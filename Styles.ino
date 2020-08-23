void setupStyles() {
  lv_style_init(&global_style);
  lv_style_set_bg_color(&global_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
  lv_style_set_text_font(&global_style, LV_STATE_DEFAULT, &lv_font_montserrat_16);
  lv_style_set_text_color(&global_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);

  lv_style_init(&clock_label_style);
  lv_style_set_text_font(&clock_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_48);

  lv_style_init(&notification_page_style);
  lv_style_set_bg_opa(&notification_page_style, LV_STATE_DEFAULT, LV_OPA_TRANSP);
  lv_style_set_border_width(&notification_page_style, LV_STATE_DEFAULT, 0);
  lv_style_set_text_font(&notification_page_style, LV_STATE_DEFAULT, &lv_font_montserrat_12);

  lv_style_init(&notification_container_style);
  lv_style_set_bg_color(&notification_container_style, LV_STATE_DEFAULT, lv_color_hex(0x202020));
  lv_style_set_bg_opa(&notification_container_style, LV_STATE_DEFAULT, LV_OPA_COVER);
  lv_style_set_radius(&notification_container_style, LV_STATE_DEFAULT, 10);
  lv_style_set_border_width(&notification_container_style, LV_STATE_DEFAULT, 0);
  lv_style_set_pad_inner(&notification_container_style, LV_STATE_DEFAULT, 0);
  lv_style_set_pad_top(&notification_container_style, LV_STATE_DEFAULT, 10);
  lv_style_set_pad_bottom(&notification_container_style, LV_STATE_DEFAULT, 10);
  lv_style_set_pad_left(&notification_container_style, LV_STATE_DEFAULT, 10);
  lv_style_set_pad_right(&notification_container_style, LV_STATE_DEFAULT, 10);
  lv_style_set_text_font(&notification_container_style, LV_STATE_DEFAULT, &lv_font_montserrat_12);

  lv_style_init(&notification_element_from_style);
  lv_style_set_text_color(&notification_element_from_style, LV_STATE_DEFAULT, LV_COLOR_RED);

  lv_style_init(&notification_element_subject_style);
  lv_style_set_text_color(&notification_element_subject_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);

  lv_style_init(&notification_element_message_style);
  lv_style_set_text_color(&notification_element_message_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
}
