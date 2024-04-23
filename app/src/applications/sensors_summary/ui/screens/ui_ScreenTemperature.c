#include <lvgl.h>

#include "../sensors_summary_ui.h"

static lv_obj_t *root_page = NULL;
static lv_obj_t *box;
static lv_timer_t* timer;
static int Counter;

void my_timer(lv_timer_t* timer)
{
    lv_label_set_text_fmt(box, "%d", Counter++);
}

lv_obj_t* Sensors_Summary_TemperatureScreen_Init(void)
{
    Counter = 0;
    root_page = lv_obj_create(NULL);

    lv_obj_clear_flag(root_page, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_width(root_page, 0, LV_PART_MAIN);
    lv_obj_set_size(root_page, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(root_page, lv_color_hex(0x30343F), LV_PART_MAIN | LV_STATE_DEFAULT);

    box = lv_label_create(root_page);
    lv_obj_set_width(box, 150);

    timer = lv_timer_create(my_timer, 500, NULL);

    return root_page;
}

void Sensors_Summary_TemperatureScreen_Remove(void)
{
    lv_timer_del(timer);
    lv_obj_del(root_page);
    root_page = NULL;
}