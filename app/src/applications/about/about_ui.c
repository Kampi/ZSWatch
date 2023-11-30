#include "about_ui.h"

static lv_obj_t *ui_root_page = NULL;
static lv_obj_t *ui_LabelKernelVersion;
static lv_obj_t *ui_LabelAppVersion;
static lv_obj_t *ui_LabelBuildDate;
static lv_obj_t *ui_LabelBuildTime;
static lv_obj_t *ui_LabelHeader;

void about_ui_show(lv_obj_t *p_parent, char *kernel, char *app)
{
    assert(ui_root_page == NULL);

    ui_root_page = lv_obj_create(p_parent);
    lv_obj_set_style_border_width(ui_root_page, 0, LV_PART_MAIN);
    lv_obj_set_size(ui_root_page, LV_PCT(100), LV_PCT(100));
    lv_obj_set_scrollbar_mode(ui_root_page, LV_SCROLLBAR_MODE_OFF);

    ui_LabelHeader = lv_label_create(ui_root_page);
    lv_obj_set_width(ui_LabelHeader, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelHeader, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelHeader, 45);
    lv_obj_set_y(ui_LabelHeader, -85);
    lv_obj_set_align(ui_LabelHeader, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_LabelHeader, "About ZSWatch");

    ui_LabelKernelVersion = lv_label_create(ui_root_page);
    lv_obj_set_width(ui_LabelKernelVersion, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelKernelVersion, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_LabelKernelVersion, LV_ALIGN_LEFT_MID);
    lv_obj_set_x(ui_LabelKernelVersion, 30);
    lv_obj_set_y(ui_LabelKernelVersion, -45);
    lv_label_set_text(ui_LabelKernelVersion, kernel);

    ui_LabelAppVersion = lv_label_create(ui_root_page);
    lv_obj_set_width(ui_LabelAppVersion, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelAppVersion, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelAppVersion, 30);
    lv_obj_set_y(ui_LabelAppVersion, -25);
    lv_obj_set_align(ui_LabelAppVersion, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_LabelAppVersion, app);

    ui_LabelBuildDate = lv_label_create(ui_root_page);
    lv_obj_set_width(ui_LabelBuildDate, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelBuildDate, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelBuildDate, 30);
    lv_obj_set_y(ui_LabelBuildDate, -5);
    lv_obj_set_align(ui_LabelBuildDate, LV_ALIGN_LEFT_MID);
    lv_label_set_text_fmt(ui_LabelBuildDate, "Build date:\t%s", __DATE__);

    ui_LabelBuildTime = lv_label_create(ui_root_page);
    lv_obj_set_width(ui_LabelBuildTime, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelBuildTime, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelBuildTime, 30);
    lv_obj_set_y(ui_LabelBuildTime, 15);
    lv_obj_set_align(ui_LabelBuildTime, LV_ALIGN_LEFT_MID);
    lv_label_set_text_fmt(ui_LabelBuildTime, "Build time:\t%s", __TIME__);
}

void about_ui_remove(void)
{
    lv_obj_del(ui_root_page);
    ui_root_page = NULL;
}