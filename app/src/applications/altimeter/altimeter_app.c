#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "ui_export/altimeter_ui.h"
#include "managers/zsw_app_manager.h"
#include "sensors/zsw_pressure_sensor.h"
#include "sensors/zsw_environment_sensor.h"

LOG_MODULE_REGISTER(altimeter_app, CONFIG_ZSW_ALTIMETER_APP_LOG_LEVEL);

static void altimeter_app_start(lv_obj_t *root, lv_group_t *group);
static void altimeter_app_stop(void);
static void on_Timer_Callback(lv_timer_t *timer);

LV_IMG_DECLARE(move);

static application_t app = {
    .name = "Altimeter",
    .icon = &move,
    .start_func = altimeter_app_start,
    .stop_func = altimeter_app_stop
};

static lv_timer_t *refresh_timer;
static float relative_pressure;

static void on_Timer_Callback(lv_timer_t *timer)
{
    float temperature;
    float pressure;
    float height;

    zsw_environment_sensor_get_temperature(&temperature);
    zsw_pressure_sensor_get_pressure(&pressure);
    height = zsw_pressure_get_relative_height_m(relative_pressure, pressure, temperature);

    LOG_DBG("Relative height: %f", height);

    altimeter_ui_add_data(height);
}

static void altimeter_app_start(lv_obj_t *root, lv_group_t *group)
{
    altimeter_ui_show(root);
    zsw_pressure_sensor_get_pressure(&relative_pressure);
    refresh_timer = lv_timer_create(on_Timer_Callback, 1000, NULL);
}

static void altimeter_app_stop(void)
{
    lv_timer_del(refresh_timer);
    altimeter_ui_remove();
}

static int altimeter_app_add(void)
{
    zsw_app_manager_add_application(&app);

    return 0;
}

SYS_INIT(altimeter_app_add, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);