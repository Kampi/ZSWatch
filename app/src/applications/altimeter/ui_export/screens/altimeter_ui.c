#include "../altimeter_ui.h"

static lv_obj_t *ui_root_page = NULL;
static lv_obj_t *ui_ChartAltitude;
static lv_obj_t *ui_ButtonReference;
static lv_obj_t *ui_LabelButtonReference;
static lv_chart_series_t *ui_ChartAltitude_series;

static void on_ButtonReference_Click(lv_event_t *e)
{
}

void altimeter_ui_show(lv_obj_t *p_parent)
{
    assert(ui_root_page == NULL);

    ui_root_page = lv_obj_create(p_parent);
    lv_obj_set_style_border_width(ui_root_page, 0, LV_PART_MAIN);
    lv_obj_set_size(ui_root_page, LV_PCT(100), LV_PCT(100));

    lv_obj_clear_flag(ui_root_page, LV_OBJ_FLAG_SCROLLABLE);

    ui_ChartAltitude = lv_chart_create(ui_root_page);
    lv_obj_set_width(ui_ChartAltitude, 160);
    lv_obj_set_height(ui_ChartAltitude, 100);
    lv_obj_set_align(ui_ChartAltitude, LV_ALIGN_CENTER);
    lv_chart_set_update_mode(ui_ChartAltitude, LV_CHART_UPDATE_MODE_SHIFT);
    lv_chart_set_type(ui_ChartAltitude, LV_CHART_TYPE_LINE);
    lv_chart_set_range(ui_ChartAltitude, LV_CHART_AXIS_PRIMARY_Y, -1, 10);
    lv_chart_set_axis_tick(ui_ChartAltitude, LV_CHART_AXIS_PRIMARY_X, 10, 5, 5, 2, true, 50);
    lv_chart_set_axis_tick(ui_ChartAltitude, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 5, 2, true, 50);
    ui_ChartAltitude_series = lv_chart_add_series(ui_ChartAltitude, lv_color_hex(0x808080), LV_CHART_AXIS_PRIMARY_Y);

    ui_ButtonReference = lv_btn_create(ui_root_page);
    lv_obj_set_width(ui_ButtonReference, 100);
    lv_obj_set_height(ui_ButtonReference, 25);
    lv_obj_set_x(ui_ButtonReference, 0);
    lv_obj_set_y(ui_ButtonReference, -80);
    lv_obj_set_align(ui_ButtonReference, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonReference, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_ButtonReference, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_event_cb(ui_ButtonReference, on_ButtonReference_Click, LV_EVENT_CLICKED, NULL);

    ui_LabelButtonReference = lv_label_create(ui_ButtonReference);
    lv_obj_set_width(ui_LabelButtonReference, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelButtonReference, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_LabelButtonReference, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelButtonReference, "Set ref");
    lv_obj_set_style_text_font(ui_LabelButtonReference, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void altimeter_ui_remove(void)
{
    lv_obj_del(ui_root_page);
    ui_root_page = NULL;
}

void altimeter_ui_add_data(lv_coord_t data)
{
    lv_chart_series_t *ser = lv_chart_get_series_next(ui_ChartAltitude, NULL);

    lv_chart_set_next_value(ui_ChartAltitude, ser, data);

    uint16_t p = lv_chart_get_point_count(ui_ChartAltitude);
    uint16_t s = lv_chart_get_x_start_point(ui_ChartAltitude, ser);
    lv_coord_t *a = lv_chart_get_y_array(ui_ChartAltitude, ser);

    a[(s + 1) % p] = LV_CHART_POINT_NONE;
    a[(s + 2) % p] = LV_CHART_POINT_NONE;
    a[(s + 2) % p] = LV_CHART_POINT_NONE;

    lv_chart_refresh(ui_ChartAltitude);
}