////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 1, 2022
//
////////////////////////////////////////////////////////////
#include "header.h"
#include "main.h"


///////////////////////////
// WinMain
///////////////////////////
#ifdef LS_PLATFORM_WINDOWS
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
  LRESULT Result = 0;
  
  g_main_args.hInstance = hInstance;
  g_main_args.hPrevInstance = hPrevInstance;
  g_main_args.lpCmdLine = lpCmdLine;
  g_main_args.nCmdShow = nCmdShow;
  
  UNREFERENCED_PARAMETER(hInstance);
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);
  UNREFERENCED_PARAMETER(nCmdShow);
  
  MessageBoxA(NULL, "Engine is running WinMain!", "Error!", MB_ICONEXCLAMATION | MB_OK);
  
  return Result;
}
#else // LS_PLATFORM_WINDOWS
int main(int argc, char** argv)
{
  MessageBoxA(NULL, "Engine is running standard main!", "Error!", MB_ICONEXCLAMATION | MB_OK);
  
  return 0;
}
#endif // LS_PLATFORM_WINDOWS


///////////////////////////
// EOF
///////////////////////////
