#include <lvgl.h>

#include "../sensors_summary_ui.h"

static lv_obj_t *root_page = NULL;

lv_obj_t* Sensors_Summary_PressureScreen_Init(void)
{
    root_page = lv_obj_create(NULL);

    lv_obj_clear_flag(root_page, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_width(root_page, 0, LV_PART_MAIN);
    lv_obj_set_size(root_page, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(root_page, lv_color_hex(0x30343F), LV_PART_MAIN | LV_STATE_DEFAULT);

    return root_page;
}

void Sensors_Summary_PressureScreen_Remove(void)
{
    lv_obj_del(root_page);
    root_page = NULL;
}