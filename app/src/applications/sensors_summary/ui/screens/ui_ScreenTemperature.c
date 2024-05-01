#include <lvgl.h>

#include "../sensors_summary_ui.h"

static lv_obj_t *root_page = NULL;
static lv_obj_t *chart_temp_history;
static lv_obj_t *arc_temp;
static lv_obj_t *arc_temp;
static lv_obj_t *label_current_temp;
static lv_obj_t *label_max_temp;
static lv_obj_t *label_min_temp;
static lv_chart_series_t *series;
static float max_temperature;
static float min_temperature;

static void on_TemperatureScreen_Draw(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);

    // Add the faded area before the lines are drawn.
    lv_obj_draw_part_dsc_t *dsc = lv_event_get_draw_part_dsc(e);
    if (dsc->part == LV_PART_ITEMS) {
        lv_area_t a;
        lv_draw_rect_dsc_t draw_rect_dsc;
        lv_draw_mask_line_param_t line_mask_param;
        int16_t line_mask_id;

        if (!dsc->p1 || !dsc->p2) {
            return;
        }

        // Add a line mask that keeps the area below the line.
        lv_draw_mask_line_points_init(&line_mask_param, dsc->p1->x, dsc->p1->y, dsc->p2->x, dsc->p2->y,
                                      LV_DRAW_MASK_LINE_SIDE_BOTTOM);
        line_mask_id = lv_draw_mask_add(&line_mask_param, NULL);

        // Draw a rectangle that will be affected by the mask.
        lv_draw_rect_dsc_init(&draw_rect_dsc);
        draw_rect_dsc.bg_opa = LV_OPA_50;
        draw_rect_dsc.bg_color = lv_color_hex(0x9EC8F6);

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

lv_obj_t *Sensors_Summary_TemperatureScreen_Init(float InitTemp)
{
    max_temperature = InitTemp;
    min_temperature = InitTemp;

    root_page = lv_obj_create(NULL);

    lv_obj_clear_flag(root_page, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_width(root_page, 0, LV_PART_MAIN);
    lv_obj_set_size(root_page, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(root_page, lv_color_hex(0x30343F), LV_PART_MAIN | LV_STATE_DEFAULT);

    arc_temp = lv_arc_create(root_page);
    lv_obj_set_width(arc_temp, 220);
    lv_obj_set_height(arc_temp, 220);
    lv_obj_set_align(arc_temp, LV_ALIGN_CENTER);
    lv_arc_set_range(arc_temp, -25, 60);
    lv_arc_set_value(arc_temp, 0);
    lv_arc_set_bg_angles(arc_temp, 185, 355);
    lv_obj_remove_style(arc_temp, NULL, LV_PART_KNOB);

    chart_temp_history = lv_chart_create(root_page);
    lv_obj_set_width(chart_temp_history, 240);
    lv_obj_set_height(chart_temp_history, 130);
    lv_obj_set_x(chart_temp_history, 0);
    lv_obj_set_y(chart_temp_history, 70);
    lv_obj_set_align(chart_temp_history, LV_ALIGN_CENTER);
    lv_obj_set_style_line_width(chart_temp_history, 0, LV_PART_ITEMS);
    lv_obj_set_style_size(chart_temp_history, 0, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(chart_temp_history, lv_obj_get_style_bg_color(root_page, LV_PART_MAIN | LV_STATE_DEFAULT),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(chart_temp_history, lv_obj_get_style_bg_color(root_page, LV_PART_MAIN | LV_STATE_DEFAULT),
                                  LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(chart_temp_history, on_TemperatureScreen_Draw, LV_EVENT_DRAW_PART_BEGIN, NULL);

    label_current_temp = lv_label_create(root_page);
    lv_obj_set_width(label_current_temp, LV_SIZE_CONTENT);
    lv_obj_set_height(label_current_temp, LV_SIZE_CONTENT);
    lv_obj_set_x(label_current_temp, 0);
    lv_obj_set_y(label_current_temp, -50);
    lv_obj_set_align(label_current_temp, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(label_current_temp, lv_color_hex(0xFFBAAF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(label_current_temp, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label_current_temp, &lv_font_montserrat_42, LV_PART_MAIN | LV_STATE_DEFAULT);

    label_min_temp = lv_label_create(root_page);
    lv_obj_set_width(label_min_temp, LV_SIZE_CONTENT);
    lv_obj_set_height(label_min_temp, LV_SIZE_CONTENT);
    lv_obj_set_x(label_min_temp, -30);
    lv_obj_set_y(label_min_temp, -15);
    lv_obj_set_align(label_min_temp, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(label_min_temp, lv_color_hex(0xFFBAAF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(label_min_temp, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    label_max_temp = lv_label_create(root_page);
    lv_obj_set_width(label_max_temp, LV_SIZE_CONTENT);
    lv_obj_set_height(label_max_temp, LV_SIZE_CONTENT);
    lv_obj_set_x(label_max_temp, 30);
    lv_obj_set_y(label_max_temp, -15);
    lv_obj_set_align(label_max_temp, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(label_max_temp, lv_color_hex(0xFFBAAF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(label_max_temp, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_chart_set_type(chart_temp_history, LV_CHART_TYPE_LINE);
    lv_chart_set_range(chart_temp_history, LV_CHART_AXIS_PRIMARY_Y, -25, 60);
    lv_chart_set_update_mode(chart_temp_history, LV_CHART_UPDATE_MODE_CIRCULAR);
    lv_chart_set_div_line_count(chart_temp_history, 0, 0);
    lv_chart_set_point_count(chart_temp_history, 60 * 24);
    lv_chart_set_axis_tick(chart_temp_history, LV_CHART_AXIS_PRIMARY_X, 0, 0, 0, 0, false, 50);
    lv_chart_set_axis_tick(chart_temp_history, LV_CHART_AXIS_PRIMARY_Y, 0, 5, 0, 5, false, 50);
    lv_chart_set_axis_tick(chart_temp_history, LV_CHART_AXIS_SECONDARY_Y, 0, 5, 0, 5, false, 25);

    series = lv_chart_add_series(chart_temp_history, lv_color_hex(0x9EC8F6), LV_CHART_AXIS_PRIMARY_Y);

    Sensors_Summary_TemperatureScreen_Add(InitTemp);

    return root_page;
}

void Sensors_Summary_TemperatureScreen_Remove(void)
{
    lv_obj_del(root_page);
    root_page = NULL;
}

void Sensors_Summary_TemperatureScreen_Add(float Temperature)
{
    if (Temperature > max_temperature) {
        max_temperature = Temperature;
    }

    if (Temperature < min_temperature) {
        min_temperature = Temperature;
    }

    lv_label_set_text_fmt(label_current_temp, "%.1f°", Temperature);
    lv_label_set_text_fmt(label_max_temp, "%.1f°", max_temperature);
    lv_label_set_text_fmt(label_min_temp, "%.1f°", min_temperature);
    lv_arc_set_value(arc_temp, Temperature);
    lv_chart_set_next_value(chart_temp_history, series, Temperature);
}