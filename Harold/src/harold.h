////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 1, 2022
//
// include "harold.h"
////////////////////////////////////////////////////////////
#ifndef LS_HAROLD_H
#define LS_HAROLD_H

/* defines */
#define false   0
#define true    1

#define ls_assert(expression) \
  if(!expression) { \
    printf("Assert: %d, %s, %s\n", __LINE__, __FILE__, __func__);\
    *(int*)0=0; }
#define UNIMPLEMENTED printf("UNIMPLEMENTED: %d, %s, %s\n", __LINE__, __FILE__, __func__);

/* c includes */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* c types */
typedef uint64_t  u64;
typedef int64_t   i64;
typedef uint32_t  u32;
typedef int32_t   i32;
typedef uint16_t  u16;
typedef int16_t   i16;
typedef uint8_t   u8;
typedef int8_t    i8;
typedef double    f64;
typedef float     f32;
typedef uint8_t*  ls_string;
typedef int32_t   bool;
typedef size_t    usize;

/* current platform */
#define LS_PLATFORM_WINDOWS

#ifdef LS_PLATFORM_WINDOWS
  #ifdef LS_HAROLD_BUILD
    #define LS_HAROLD_API __declspec( dllexport )
  #else
    #define LS_HAROLD_API __declspec( dllimport )
  #endif
#else
  #error LS Harold currently only support Windows!
  // #elseif future platforms
#endif


///////////////////////////
// Window - win32_x64
///////////////////////////
#include "win32/window/window.h"

/* Declaration */
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


///////////////////////////
// Event - win32_x64
///////////////////////////
#include "event/event.h"

/* Declaration */
LS_HAROLD_API bool ls_poll_event(ls_event* event);


///////////////////////////
// Render
///////////////////////////
#include "render/rendergl.h"

/* Declaration */
LS_HAROLD_API void ls_render_frame_graphics(void);


///////////////////////////
// Memory Manager - win32_x64
///////////////////////////
#include "memory/memory.h"

/* Declaration */
LS_HAROLD_API ls_memory ls_memory_new(usize size_bytes);
LS_HAROLD_API void  ls_memory_free(ls_memory arena);
LS_HAROLD_API void* ls_malloc(ls_memory arena, usize size);
LS_HAROLD_API void* ls_calloc(ls_memory arena, usize num_items, usize size_items);
LS_HAROLD_API void* ls_realloc(ls_memory arena, void* memory, usize size_new);
LS_HAROLD_API void  ls_free(ls_memory arena, void* memory);
LS_HAROLD_API void  ls_memory_display(ls_memory arena);
LS_HAROLD_API void  ls_memory_print(ls_memory arena);


///////////////////////////
// Array and ArrayList - NON_Platform
///////////////////////////
#include "array/array.h"

/* Declaration */
LS_HAROLD_API ls_list ls_list_new(ls_memory arena, usize size);
LS_HAROLD_API void  ls_list_free(ls_list list);
LS_HAROLD_API void* ls_list_add(ls_list list, void* item);
LS_HAROLD_API void  ls_list_rm(ls_list list, void* item);
LS_HAROLD_API void  ls_list_remove(ls_list list, void* item);
LS_HAROLD_API void* ls_list_get(ls_list list, i32 num);
LS_HAROLD_API void* ls_list_set(ls_list list, i32 num, void* item);


#endif /* LS_HAROLD_H */

///////////////////////////
// EOF
///////////////////////////
