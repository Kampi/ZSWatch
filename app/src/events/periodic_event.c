#include <zephyr/kernel.h>
#include <zephyr/zbus/zbus.h>

#include "events/periodic_event.h"

static struct k_work_delayable periodic_60s_work;
static struct k_work_delayable periodic_10s_work;
static struct k_work_delayable periodic_1s_work;
static struct k_work_delayable periodic_100ms_work;

ZBUS_CHAN_DEFINE(periodic_event_60s_chan,
                 struct periodic_event,
                 NULL,
                 &periodic_60s_work,
                 ZBUS_OBSERVERS_EMPTY,
                 ZBUS_MSG_INIT()
                );

ZBUS_CHAN_DEFINE(periodic_event_10s_chan,
                 struct periodic_event,
                 NULL,
                 &periodic_10s_work,
                 ZBUS_OBSERVERS_EMPTY,
                 ZBUS_MSG_INIT()
                );

ZBUS_CHAN_DEFINE(periodic_event_100ms_chan,
                 struct periodic_event,
                 NULL,
                 &periodic_100ms_work,
                 ZBUS_OBSERVERS_EMPTY,
                 ZBUS_MSG_INIT()
                );

ZBUS_CHAN_DEFINE(periodic_event_1s_chan,
                 struct periodic_event,
                 NULL,
                 &periodic_1s_work,
                 ZBUS_OBSERVERS_EMPTY,
                 ZBUS_MSG_INIT()
                );