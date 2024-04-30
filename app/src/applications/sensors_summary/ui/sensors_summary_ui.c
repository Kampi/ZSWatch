#include "sensors_summary_ui.h"

static lv_obj_t *entry_screen;
static lv_obj_t *root_page_home;
static lv_obj_t *root_page_temperature;
static lv_obj_t *root_page_humidity;
static lv_obj_t *root_page_pressure;
static Sensors_Summary_Screen_t CurrentScreen;

void Sensors_Summary_UI_Init(lv_obj_t *entry)
{
    entry_screen = entry;
    root_page_home = Sensors_Summary_HomeScreen_Init();
    root_page_temperature = Sensors_Summary_TemperatureScreen_Init();
    root_page_humidity = Sensors_Summary_HumidityScreen_Init();
    root_page_pressure = Sensors_Summary_PressureScreen_Init();
    lv_disp_load_scr(root_page_home);
    CurrentScreen = SENSORS_SUMMARY_SCREEN_HOME;
}

void Sensors_Summary_UI_Deinit(void)
{
    lv_disp_load_scr(entry_screen);
    Sensors_Summary_HomeScreen_Remove();
    Sensors_Summary_TemperatureScreen_Remove();
    Sensors_Summary_HumidityScreen_Remove();
    Sensors_Summary_PressureScreen_Remove();
}

void Sensors_Summary_UI_ChangeScreen(Sensors_Summary_Screen_t Screen)
{
    lv_obj_t *page;

    if(CurrentScreen == Screen)
    {
        return;
    }

    CurrentScreen = Screen;

    switch(CurrentScreen)
    {
    case SENSORS_SUMMARY_SCREEN_TEMPERATURE: {
        page = root_page_temperature;
        break;
    }
    case SENSORS_SUMMARY_SCREEN_HUMIDITY: {
        page = root_page_humidity;
        break;
    }
    case SENSORS_SUMMARY_SCREEN_PRESSURE: {
        page = root_page_pressure;
        break;
    }
    default: {
        page = root_page_home;
        break;
    }
    }

    lv_scr_load_anim(page, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false);
}

Sensors_Summary_Screen_t Sensors_Summary_UI_GetCurrentScreen(void)
{
    return CurrentScreen;
}