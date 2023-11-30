#pragma once

#include <inttypes.h>
#include <lvgl.h>

void about_ui_show(lv_obj_t *p_parent, char *kernel, char *app);

void about_ui_remove(void);