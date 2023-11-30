#pragma once

#include "lvgl.h"

void altimeter_ui_show(lv_obj_t *root);

void altimeter_ui_remove(void);

void altimeter_ui_add_data(lv_coord_t datapoint);