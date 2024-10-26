
#ifndef _APP_WIFI_H_
#define _APP_WIFI_H_

#ifdef __cplusplus
extern "C" {
#endif

	#include "gui_logic_utils.h"

	void update_wifi_status(bool connect_status, ui_state_t current_screen);

	extern volatile bool wifi_connected;
	void app_wifi_main();
	void app_wifi_stop();

#ifdef __cplusplus
}
#endif

#endif
