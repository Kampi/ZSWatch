#include <lvgl.h>

#include "../sensors_summary_ui.h"

static lv_obj_t *root_page = NULL;
static lv_obj_t *chart;
static lv_chart_series_t *series_list;
static lv_timer_t *timer;

static void draw_event_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);

    // Add the faded area before the lines are drawn.
    lv_obj_draw_part_dsc_t *dsc = lv_event_get_draw_part_dsc(e);
    if (dsc->part == LV_PART_ITEMS) {
        if (!dsc->p1 || !dsc->p2) {
            return;
        }

        // Add a line mask that keeps the area below the line.
        lv_draw_mask_line_param_t line_mask_param;
        lv_draw_mask_line_points_init(&line_mask_param, dsc->p1->x, dsc->p1->y, dsc->p2->x, dsc->p2->y,
                                      LV_DRAW_MASK_LINE_SIDE_BOTTOM);
        int16_t line_mask_id = lv_draw_mask_add(&line_mask_param, NULL);

        // Draw a rectangle that will be affected by the mask.
        lv_draw_rect_dsc_t draw_rect_dsc;

        lv_draw_rect_dsc_init(&draw_rect_dsc);
        draw_rect_dsc.bg_opa = LV_OPA_50;
        draw_rect_dsc.bg_color = lv_color_hex(0x30343F);

        lv_area_t a;
        a.x1 = dsc->p1->x;
        a.x2 = dsc->p2->x - 1;
        a.y1 = LV_MIN(dsc->p1->y, dsc->p2->y);
        // -13 cuts off where the rectangle draws over the chart margin. Without this an area of 0 doesn't look like 0.
        a.y2 = obj->coords.y2 - 13;
        lv_draw_rect(dsc->draw_ctx, &draw_rect_dsc, &a);

        // Remove the mask.
        lv_draw_mask_free_param(&line_mask_param);
        lv_draw_mask_remove_id(line_mask_id);
    }
}

static void add_data(lv_timer_t *timer)
{
    LV_UNUSED(timer);
    lv_chart_set_next_value(chart, series_list, lv_rand(-20, 60));
}

lv_obj_t *Sensors_Summary_TemperatureScreen_Init(void)
{
    root_page = lv_obj_create(NULL);

    lv_obj_clear_flag(root_page, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_width(root_page, 0, LV_PART_MAIN);
    lv_obj_set_size(root_page, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(root_page, lv_color_hex(0x30343F), LV_PART_MAIN | LV_STATE_DEFAULT);

    chart = lv_chart_create(root_page);
    lv_obj_set_size(chart, 250, 110);
    lv_obj_set_pos(chart, 0, 120);
    lv_obj_set_style_line_width(chart, 0, LV_PART_ITEMS);
    lv_obj_set_style_size(chart, 0, LV_PART_INDICATOR);

    lv_obj_set_style_bg_color(chart, lv_color_hex(0x9EC8F6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(chart, lv_color_hex(0x9EC8F6), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(chart, draw_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);

    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
    lv_chart_set_range(chart, LV_CHART_AXIS_SECONDARY_Y, -20, 60);
    lv_chart_set_update_mode(chart, LV_CHART_UPDATE_MODE_CIRCULAR);
    lv_chart_set_div_line_count(chart, 0, 0);
    lv_chart_set_point_count(chart, 50);

    lv_chart_set_axis_tick(chart, LV_CHART_AXIS_SECONDARY_Y, 0, 0, 5, 5, true, 50);

    series_list = lv_chart_add_series(chart, lv_color_hex(0x30343F), LV_CHART_AXIS_SECONDARY_Y);

    timer = lv_timer_create(add_data, 100, NULL);

    return root_page;
}

void Sensors_Summary_TemperatureScreen_Remove(void)
{
    lv_timer_del(timer);
    lv_obj_del(root_page);
    root_page = NULL;
}