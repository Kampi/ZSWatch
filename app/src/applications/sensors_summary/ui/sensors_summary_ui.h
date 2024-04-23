#pragma once

#include <lvgl.h>

typedef enum {
    SENSORS_SUMMARY_SCREEN_HOME = 0,
    SENSORS_SUMMARY_SCREEN_TEMPERATURE,
    SENSORS_SUMMARY_SCREEN_HUMIDITY,
    SENSORS_SUMMARY_SCREEN_PRESSURE
} Sensors_Summary_Screen_t;

void Sensors_Summary_UI_Init(lv_obj_t *entry);
void Sensors_Summary_UI_Deinit(void);
void Sensors_Summary_UI_ChangeScreen(Sensors_Summary_Screen_t Screen);
Sensors_Summary_Screen_t Sensors_Summary_UI_GetCurrentScreen(void);

lv_obj_t* Sensors_Summary_HomeScreen_Init(void);
lv_obj_t* Sensors_Summary_TemperatureScreen_Init(void);
lv_obj_t* Sensors_Summary_PressureScreen_Init(void);
lv_obj_t* Sensors_Summary_HumidityScreen_Init(void);

void Sensors_Summary_HomeScreen_Remove(void);
void Sensors_Summary_TemperatureScreen_Remove(void);
void Sensors_Summary_HumidityScreen_Remove(void);
void Sensors_Summary_PressureScreen_Remove(void);