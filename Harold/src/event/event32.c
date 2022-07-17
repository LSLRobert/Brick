////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 5, 2022
//
////////////////////////////////////////////////////////////
#include "header.h"
#include "event32_int.h"


// PollEvent
LS_HAROLD_API bool LS_PollEvent(LS_Event *event)
{
  // loop
  MSG Message = { 0 };
  
  while (PeekMessageA(&Message, gWindowData.window, 0, 0, PM_REMOVE))
  {
    switch (Message.message)
    {
      // TODO::TODO::TODO::TODO::TODO::TODO::TODO::TODO::TODO::
      /* setup - Key, Mouse, Controller ... EVENTS
      */
      case WM_KEYDOWN: // TEMP shutdown with Escape Key
        if (Message.wParam == VK_ESCAPE) gWindowData.isRunning = false;
        break;
      
      case WM_CLOSE:
        // the CLOSE should never come through this queue
        puts("WM_CLOSE - PeekMessage\n");
        break;
      
      case WM_QUIT:
        // this is inconsistent don't use it
        puts("WM_QUIT  - PeekMessage\n");
        break;
      
      default:
        TranslateMessage(&Message);
        DispatchMessageA(&Message);
        break;
    }
  }
  
  return false;
}

//    puts("MSG Message\n");
//    printf("Message.hwnd    : %d\n", Message.hwnd);     // HWND
//    printf("Message.message : %d\n", Message.message);  // UINT
//    printf("Message.wParam  : %d\n", Message.wParam);   // WPARAM
//    printf("Message.lParam  : %d\n", Message.lParam);   // LPARAM
//    printf("Message.time    : %d\n", Message.time);     // DWORD
//    printf("Message.pt:   %d, %d\n", Message.pt.x, Message.pt.y); // POINT
//    printf("Message.lPrivate: %d\n", Message.lPrivate); // DWORD
//    puts("\n");


///////////////////////////
// EOF
///////////////////////////
