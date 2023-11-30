#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/kernel_version.h>

#include <string.h>

#include "about_ui.h"
#include "app_version.h"
#include "managers/zsw_app_manager.h"

static void about_app_start(lv_obj_t *root, lv_group_t *group);
static void about_app_stop(void);

LV_IMG_DECLARE(templates);

static application_t app = {
    .name = "About",
    .icon = &templates,
    .start_func = about_app_start,
    .stop_func = about_app_stop
};

static void about_app_start(lv_obj_t *root, lv_group_t *group)
{
    char version_string[16];
    char app_string[16];
    uint32_t version = sys_kernel_version_get();

    sprintf(version_string, "Kernel:\t%u.%u.%u", SYS_KERNEL_VER_MAJOR(version), SYS_KERNEL_VER_MINOR(version),
            SYS_KERNEL_VER_PATCHLEVEL(version));
    sprintf(app_string, "App:\t%s", APP_VERSION_STRING);

    about_ui_show(root, version_string, app_string);
}

static void about_app_stop(void)
{
    about_ui_remove();
}

static int about_app_add(void)
{
    zsw_app_manager_add_application(&app);

    return 0;
}

SYS_INIT(about_app_add, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);