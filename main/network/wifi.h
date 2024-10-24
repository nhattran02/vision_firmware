
#ifndef _APP_WIFI_H_
#define _APP_WIFI_H_

#ifdef __cplusplus
extern "C" {
#endif


	void update_wifi_status(bool connect_status);
	extern volatile bool wifi_connected;
	void app_wifi_main();
	void app_wifi_stop();

#ifdef __cplusplus
}
#endif

#endif
