idf_component_register(
    SRCS "app_main.c"
         "app_settings.c"
         "app_illuminator.c"
         "app_camera.c"
         "app_wifi.c"
         "app_fonts.c"
         "app_httpd.c"
         "app_lcd.c"
         "app_sntp.c"
    REQUIRES esp32-camera
             mdns
             nvs_flash
             esp_http_server
    INCLUDE_DIRS "include"
                 "fonts"
)
