if(CONFIG_APPLICATIONS_USE_SENSORS_SUMMARY)
    FILE(GLOB app_sources *.c)
    target_sources(app PRIVATE ${app_sources} 
                                ui/sensors_summary_ui.c
                                ui/screens/ui_ScreenHome.c
                                ui/screens/ui_ScreenTemperature.c
                                ui/screens/ui_ScreenPressure.c
                                ui/screens/ui_ScreenHumidity.c
                                ui/images/ui_img_925774327.c
                                ui/images/ui_img_1463213690.c
                                ui/images/ui_img_1479496048.c)
endif()