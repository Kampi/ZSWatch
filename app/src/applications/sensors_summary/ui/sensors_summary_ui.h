#pragma once

#include <lvgl.h>

typedef enum {
    SENSORS_SUMMARY_SCREEN_HOME = 0,
    SENSORS_SUMMARY_SCREEN_TEMPERATURE,
    SENSORS_SUMMARY_SCREEN_HUMIDITY,
    SENSORS_SUMMARY_SCREEN_PRESSURE
} Sensors_Summary_Screen_t;

/** @brief
 *  @param entry
*/
void Sensors_Summary_UI_Init(lv_obj_t *entry);

/** @brief
*/
void Sensors_Summary_UI_Deinit(void);

/** @brief
 *  @param Screen
*/
void Sensors_Summary_UI_ChangeScreen(Sensors_Summary_Screen_t Screen);

/** @brief
 *  @return
*/
Sensors_Summary_Screen_t Sensors_Summary_UI_GetCurrentScreen(void);

/** @brief
 *  @return
*/
lv_obj_t* Sensors_Summary_HomeScreen_Init(void);

/** @brief
*/
void Sensors_Summary_HomeScreen_Remove(void);

/** @brief
 *  @return
*/
lv_obj_t* Sensors_Summary_TemperatureScreen_Init(void);

/** @brief
*/
void Sensors_Summary_TemperatureScreen_Remove(void);

/** @brief
 *  @param Temperature
*/
void Sensors_Summary_TemperatureScreen_Add(int8_t Temperature);

/** @brief
 *  @return
*/
lv_obj_t* Sensors_Summary_PressureScreen_Init(void);

/** @brief
*/
void Sensors_Summary_HumidityScreen_Remove(void);

/** @brief
 *  @return
*/
lv_obj_t* Sensors_Summary_HumidityScreen_Init(void);

/** @brief
*/
void Sensors_Summary_PressureScreen_Remove(void);