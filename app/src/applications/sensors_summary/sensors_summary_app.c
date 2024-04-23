#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/device.h>
#include <zephyr/zbus/zbus.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

#include "sensors/zsw_pressure_sensor.h"
#include "sensors/zsw_light_sensor.h"
#include "sensors/zsw_environment_sensor.h"
#include "managers/zsw_app_manager.h"
#include "ui/utils/zsw_ui_utils.h"
#include "ui/sensors_summary_ui.h"

static void on_close_sensors_summary(void);
static void on_ref_set(void);
static void zbus_environment_sample_callback(const struct zbus_channel *chan);
static void zbus_light_sample_callback(const struct zbus_channel *chan);
static void zbus_pressure_sample_callback(const struct zbus_channel *chan);

static void timer_callback(lv_timer_t *timer);

LOG_MODULE_REGISTER(sensors_summary, LOG_LEVEL_DBG);

ZSW_LV_IMG_DECLARE(move);

ZBUS_CHAN_DECLARE(environment_data_chan);
ZBUS_CHAN_DECLARE(light_data_chan);
ZBUS_CHAN_DECLARE(pressure_data_chan);
ZBUS_LISTENER_DEFINE(environment_observer, zbus_environment_sample_callback);
ZBUS_LISTENER_DEFINE(light_observer, zbus_light_sample_callback);
ZBUS_LISTENER_DEFINE(pressure_observer, zbus_pressure_sample_callback);

void zbus_environment_sample_callback(const struct zbus_channel *chan)
{
    printf("Environment\n\r");
}

static void zbus_light_sample_callback(const struct zbus_channel *chan)
{
    printf("Light\n\r");
}

static void zbus_pressure_sample_callback(const struct zbus_channel *chan)
{
    printf("Pressure\n\r");
}

static void sensors_summary_app_start(lv_obj_t *root, lv_group_t *group)
{
    Sensors_Summary_UI_Init(root);
    zbus_chan_add_obs(&environment_data_chan, &environment_observer, K_NO_WAIT);
    zbus_chan_add_obs(&light_data_chan, &light_observer, K_NO_WAIT);
    zbus_chan_add_obs(&pressure_data_chan, &pressure_observer, K_NO_WAIT);
}

static void sensors_summary_app_stop(void)
{
    // Cleanup after ourselves
    // TODO need mechanism so that multiple user can request ODR without
    // breaking for another when changed.
    //zsw_pressure_sensor_set_odr(BOSCH_BMP581_ODR_DEFAULT);
    //lv_timer_del(refresh_timer);
    //sensors_summary_ui_remove();

    zbus_chan_rm_obs(&environment_data_chan, &environment_observer, K_NO_WAIT);
    zbus_chan_rm_obs(&light_data_chan, &light_observer, K_NO_WAIT);
    zbus_chan_rm_obs(&pressure_data_chan, &pressure_observer, K_NO_WAIT);
    Sensors_Summary_UI_Deinit();
}

static bool sensors_summary_app_back(void)
{
    if (Sensors_Summary_UI_GetCurrentScreen() == SENSORS_SUMMARY_SCREEN_TEMPERATURE) {
        Sensors_Summary_UI_ChangeScreen(SENSORS_SUMMARY_SCREEN_HOME);

        return false;
    }
    else if (Sensors_Summary_UI_GetCurrentScreen() == SENSORS_SUMMARY_SCREEN_HUMIDITY) {
        Sensors_Summary_UI_ChangeScreen(SENSORS_SUMMARY_SCREEN_HOME);

        return false;
    }
    else if (Sensors_Summary_UI_GetCurrentScreen() == SENSORS_SUMMARY_SCREEN_PRESSURE) {
        Sensors_Summary_UI_ChangeScreen(SENSORS_SUMMARY_SCREEN_HOME);

        return false;
    }
    else if (Sensors_Summary_UI_GetCurrentScreen() == SENSORS_SUMMARY_SCREEN_HOME) {
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