idf_component_register(
    SRCS "app_main.c"
         "app_settings.c"
         "app_illuminator.c"
         "app_camera.c"
         "app_wifi.c"
         "app_fonts.c"
         "app_httpd.c"
         "app_sntp.c"
    REQUIRES esp32-camera
             mdns
             nvs_flash
             esp_http_client
             esp_http_server
             esp_https_ota
    INCLUDE_DIRS "include"
                 "fonts"
    EMBED_FILES "www/index.html.gz"
                "www/style.css.gz"
                "www/script.js.gz"
)
