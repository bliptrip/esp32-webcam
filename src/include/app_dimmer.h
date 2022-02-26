#ifndef _APP_DIMMER_H_
#define _APP_DIMMER_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_DIMMER_ENABLED
    
void app_dimmer_startup();
void app_dimmer_shutdown();
void app_dimmer_set_intensity(float duty);

#endif

#ifdef __cplusplus
}
#endif

#endif