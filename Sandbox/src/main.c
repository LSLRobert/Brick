////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 1, 2022
//
////////////////////////////////////////////////////////////
#include <harold.h>
#include "main.h"


///////////////////////////
// Testing
///////////////////////////

/* testing includes */
#include "test_memory.c"
 #include "test_array.c"

/* test_init */
void test_init()
{
  /*  */
  test_init_memory();
  test_init_array();
}

/* test_loop */
void test_loop()
{
  /*  */
  test_loop_memory();
  test_loop_array();
}

/* test_exit */
void test_exit()
{
  /*  */
  test_exit_memory();
  test_exit_array();
}

///////////////////////////
// main
///////////////////////////
int main(int argc, char** argv)
{
  printf("Welcome to the Sandbox\n");
  
  /* window */
  ls_window_set_version_gl(3, 3);
  ls_window_set_viewport(400, 300);
  ls_window window = ls_window_create_gl("App Name", 800, 600, false);
  if (!window) 
  {
    // TODO: LOG ERROR
    printf("Window Init Failed\n");
    goto Exit;
  }
  
  /* Log */
  ls_log_current_windows_version();
  
  /* Event Queue */
  ls_event event;
  
  /* test init before loop */
  test_init();
  
  /* game loop */
  while (ls_is_application_running())
  {
    while (ls_poll_event(&event))
    {
      switch (event.type)
      {
//        case MSG_CLOSE:
//        case MSG_QUIT:
//        {
//          ls_set_application_running(false);
//          break;
//        }
        
        default:
        {
          break;
        }
        
      }
    } /* PollEvent */
    
    /* testing in loop */
    test_loop();

    ls_render_frame_graphics();
    
    
    /* temp solution */
//    Sleep(1);
  }
  
Exit:
  
  /* testing at exit */
  test_exit();
  
  return 0;
}


///////////////////////////
// EOF
///////////////////////////
