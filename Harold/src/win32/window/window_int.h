////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 4, 2022
//
////////////////////////////////////////////////////////////
#ifndef LS_WINDOW_INT_H
#define LS_WINDOW_INT_H
#include "window.h"

/* Structures */
typedef struct main_args
{
  HINSTANCE hInstance;
  HINSTANCE hPrevInstance;
  PSTR lpCmdLine;
  INT nCmdShow;
  
} main_args;

/* non Platform */
typedef struct window_data
{
  ls_window window;
  ls_window device_context;
  ls_window resource_gl;
  ls_string title;
  i32 width;
  i32 height;
  i32 major;
  i32 minor;
  i32 viewport_width;
  i32 viewport_height;
  i32 monitor_width;
  i32 monitor_height;
  bool fullscreen;
  bool is_running;
  bool multi_run;
  bool window_set;
  ls_string vendor_gl;
  ls_string render_gl;
  ls_string version_gl;
  
} window_data;

/* Global Variables */
main_args g_main_args;
window_data g_window_data;
MONITORINFO g_monitor_info;

/* Internal */
void window_set_data(void);
void c_gl_get_string(void);
i32 create_main_window(void);
i32 create_window_gl_context(void);
bool is_already_running(void);
LSTATUS get_reg_key_value(u8* buffer_data, HKEY hkey, u8* reg_key, u8* Key);
LRESULT CALLBACK main_window_procedures(HWND window_handle, UINT message, WPARAM wparam, LPARAM lparam);
HDC get_device_context(void);

#endif /* LS_WINDOW_INT_H */

///////////////////////////
// EOF
///////////////////////////
