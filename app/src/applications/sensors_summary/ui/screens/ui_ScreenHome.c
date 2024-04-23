#include <lvgl.h>

#include "../sensors_summary_ui.h"

LV_IMG_DECLARE(ui_img_925774327);
LV_IMG_DECLARE(ui_img_1463213690);
LV_IMG_DECLARE(ui_img_1479496048);

static lv_obj_t *ui_ButtonTemperature;
static lv_obj_t *ui_ButtonPressure;
static lv_obj_t *ui_ButtonHumidity;
static lv_obj_t *root_page = NULL;

static void on_ButtonTemperature_Clicked(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED) {
        Sensors_Summary_UI_ChangeScreen(SENSORS_SUMMARY_SCREEN_TEMPERATURE);
    }
}

static void on_ButtonPressure_Clicked(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED) {
        Sensors_Summary_UI_ChangeScreen(SENSORS_SUMMARY_SCREEN_PRESSURE);
    }
}

static void on_ButtonHumidity_Clicked(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED) {
        Sensors_Summary_UI_ChangeScreen(SENSORS_SUMMARY_SCREEN_HUMIDITY);
    }
}

lv_obj_t *Sensors_Summary_HomeScreen_Init(void)
{
    root_page = lv_obj_create(NULL);

    lv_obj_clear_flag(root_page, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_width(root_page, 0, LV_PART_MAIN);
    lv_obj_set_size(root_page, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(root_page, lv_color_hex(0x30343F), LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonTemperature = lv_btn_create(root_page);
    lv_obj_set_width(ui_ButtonTemperature, 50);
    lv_obj_set_height(ui_ButtonTemperature, 50);
    lv_obj_set_x(ui_ButtonTemperature, -40);
    lv_obj_set_y(ui_ButtonTemperature, -40);
    lv_obj_set_align(ui_ButtonTemperature, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonTemperature, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_ButtonTemperature, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_ButtonTemperature, lv_color_hex(0x9EC8F6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_ButtonTemperature, &ui_img_925774327, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonPressure = lv_btn_create(root_page);
    lv_obj_set_width(ui_ButtonPressure, 50);
    lv_obj_set_height(ui_ButtonPressure, 50);
    lv_obj_set_x(ui_ButtonPressure, 40);
    lv_obj_set_y(ui_ButtonPressure, -40);
    lv_obj_set_align(ui_ButtonPressure, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonPressure, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_ButtonPressure, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_ButtonPressure, lv_color_hex(0x9EC8F6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_ButtonPressure, &ui_img_1463213690, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonHumidity = lv_btn_create(root_page);
    lv_obj_set_width(ui_ButtonHumidity, 50);
    lv_obj_set_height(ui_ButtonHumidity, 50);
    lv_obj_set_x(ui_ButtonHumidity, -40);
    lv_obj_set_y(ui_ButtonHumidity, 40);
    lv_obj_set_align(ui_ButtonHumidity, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonHumidity, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_ButtonHumidity, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_ButtonHumidity, lv_color_hex(0x9EC8F6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_ButtonHumidity, &ui_img_1479496048, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_ButtonTemperature, on_ButtonTemperature_Clicked, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_ButtonPressure, on_ButtonPressure_Clicked, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_ButtonHumidity, on_ButtonHumidity_Clicked, LV_EVENT_CLICKED, NULL);

    return root_page;
}

void Sensors_Summary_HomeScreen_Remove(void)
{
    lv_obj_del(root_page);
    root_page = NULL;
}