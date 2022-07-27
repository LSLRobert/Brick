////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 17, 2022
//
////////////////////////////////////////////////////////////
#include "header.h"
#include "memory32_int.h"


// LS_MemoryNew
LS_HAROLD_API LS_Memory LS_MemoryNew(uSize sizeBytes)
{
  // LPVOID VirtualAlloc(lpAddress, dwSize, flAllocationType, flProtect);
  LS_Memory arena = malloc(sizeof(LS_Memory_));
  arena->address = VirtualAlloc(NULL, sizeBytes, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
  if(arena->address == NULL)
  {
    puts("VirtualAlloc failed!");
    exit(EXIT_FAILURE);
  }
  arena->size = sizeBytes;
  return arena;
}


// LS_MemoryFree
LS_HAROLD_API void LS_MemoryFree(LS_Memory arena)
{
  VirtualFree(arena->address, 0, MEM_RELEASE);
  free(arena);
}


// LS_Malloc
LS_HAROLD_API void* LS_Malloc(LS_Memory arena, uSize size)
{
  // void* malloc(uSize size)
  UNIMPLEMENTED
  return malloc(size);
}


// LS_Calloc
LS_HAROLD_API void* LS_Calloc(LS_Memory arena, uSize numItems, uSize sizeItems)
{
  // void* calloc(uSize nmemb, uSize size)
  UNIMPLEMENTED
  return calloc(numItems, sizeItems);
}


// LS_Realloc
LS_HAROLD_API void* LS_Realloc(LS_Memory arena, void* memory, uSize sizeNew)
{
  // void realloc(void* ptr, uSize size)
  UNIMPLEMENTED
  return realloc(memory, sizeNew);
}


// LS_Free
LS_HAROLD_API void LS_Free(LS_Memory arena, void* memory)
{
  // void free(void* ptr)
  UNIMPLEMENTED
  free(memory);
}


// LS_MemoryDisplay
LS_HAROLD_API void LS_MemoryDisplay(LS_Memory arena)
{
  UNIMPLEMENTED
}


// LS_MemoryPrint
LS_HAROLD_API void LS_MemoryPrint(LS_Memory arena)
{
  UNIMPLEMENTED
}


///////////////////////////
// EOF
///////////////////////////
