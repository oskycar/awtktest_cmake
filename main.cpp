//
//  main.cpp
//  awtktest
//
//  Created by cbav on 2019/7/1.
//  Copyright © 2019 cbav. All rights reserved.
//

#include "awtk.h"
#include "demos/assets.h"
static ret_t on_click(void* ctx, event_t* e) {
    log_debug("on_click\n");
    return RET_OK;
}

static ret_t on_long_press(void* ctx, event_t* e) {
    log_debug("on_long_press\n");
    return RET_OK;
}

void application_init() {
    widget_t* win = window_create(NULL, 0, 0, 0, 0);
    widget_t* ok = button_create(win, 0, 0, 0, 0);

    widget_set_text(ok, L"ok");
    widget_set_self_layout_params(ok, "center", "middle", "50%", "30");
    widget_on(ok, EVT_CLICK, on_click, NULL);
    widget_on(ok, EVT_LONG_PRESS, on_long_press, NULL);

    widget_layout(win);
}


#ifdef USE_GUI_MAIN
int gui_app_start(int lcd_w, int lcd_h) {
    tk_init(lcd_w, lcd_h, APP_MOBILE, NULL, NULL);
#elif defined(WIN32)
#include <windows.h>
    int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow) {
        tk_init(320, 480, APP_SIMULATOR, NULL, RES_ROOT);
#else
int main(void) {
    tk_init(320, 480, APP_SIMULATOR, NULL, RES_ROOT);
#endif

    //#define WITH_LCD_PORTRAIT 1
#if defined(USE_GUI_MAIN) && defined(WITH_LCD_PORTRAIT)
    if (lcd_w > lcd_h) {
                tk_set_lcd_orientation(LCD_ORIENTATION_90);
            }
#endif /*WITH_LCD_PORTRAIT*/

#ifdef WITH_LCD_LANDSCAPE
    if (lcd_w < lcd_h) {
                tk_set_lcd_orientation(LCD_ORIENTATION_90);
            }
#endif /*WITH_LCD_PORTRAIT*/

    assets_init();
    application_init();
    tk_ext_widgets_init();

    tk_run();

    return 0;
}
