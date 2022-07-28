////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 4, 2022
//
////////////////////////////////////////////////////////////
#ifndef LS_WINDOW_H
#define LS_WINDOW_H

/* fields */
typedef void* ls_window;

LS_HAROLD_API void ls_window_set_viewport(i32 width, i32 height);
LS_HAROLD_API i32  ls_window_get_viewport_width(void);
LS_HAROLD_API i32  ls_window_get_viewport_height(void);
LS_HAROLD_API ls_window ls_window_create_gl(ls_string title, i32 width, i32 height, bool fullscreen);
LS_HAROLD_API void ls_window_set_version_gl(i32 major, i32 minor);
LS_HAROLD_API i32  ls_window_get_version_gl_major(void);
LS_HAROLD_API i32  ls_window_get_version_gl_minor(void);
LS_HAROLD_API      ls_string ls_window_get_vendor_gl(void);
LS_HAROLD_API      ls_string ls_window_get_render_gl(void);
LS_HAROLD_API      ls_string ls_window_get_version_gl(void);
LS_HAROLD_API bool ls_is_application_running(void);
LS_HAROLD_API void ls_set_application_running(bool running);
LS_HAROLD_API void ls_log_current_windows_version(void);

#endif /* LS_WINDOW_H */

///////////////////////////
// EOF
///////////////////////////
