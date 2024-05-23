#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <math.h>

#include "sensors/zsw_pressure_sensor.h"
#include "sensors/zsw_light_sensor.h"
#include "sensors/zsw_environment_sensor.h"
#include "managers/zsw_app_manager.h"
#include "ui/utils/zsw_ui_utils.h"
#include "ui/sensors_summary_ui.h"

static void on_close_sensors_summary(void);
static void on_ref_set(void);

static void timer_callback(lv_timer_t *timer);

ZSW_LV_IMG_DECLARE(move);

static void sensors_summary_app_start(lv_obj_t *root, lv_group_t *group)
{
    Sensors_Summary_UI_Init(root);
}

static void sensors_summary_app_stop(void)
{
    // Cleanup after ourselves
    // TODO need mechanism so that multiple user can request ODR without
    // breaking for another when changed.
    zsw_pressure_sensor_set_odr(BOSCH_BMP581_ODR_DEFAULT);
    //lv_timer_del(refresh_timer);
    //sensors_summary_ui_remove();
    SensorsSummary_HomeScreen_Remove();
}

static bool sensors_summary_app_back(void)
{
    if (sensors_summary_screenTemperature != NULL) {
        Sensors_Summary_UI_ChangeScreen();

        return false;
    }

    else if (sensors_summary_screenHome != NULL) {
        return true;
    }
}

static double get_relative_height_m(double relative_pressure, double new_pressure, double temperature)
{
}

static void timer_callback(lv_timer_t *timer)
{

}

static void on_ref_set(void)
{
    //zsw_pressure_sensor_get_pressure(&relative_pressure);
}

static application_t app = {
    .name = "Sensors",
    .icon = ZSW_LV_IMG_USE(move),
    .start_func = sensors_summary_app_start,
    .stop_func = sensors_summary_app_stop,
    .back_func = sensors_summary_app_back
};

static int sensors_summary_app_add(void)
{
    zsw_app_manager_add_application(&app);
    return 0;
}

SYS_INIT(sensors_summary_app_add, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);