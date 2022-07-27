////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 17, 2022
//
////////////////////////////////////////////////////////////
#ifndef MEMORY32_H
#define MEMORY32_H

// Type def
typedef struct LS_Memory_
{
  void* address;
  uSize size;
  
} LS_Memory_, *LS_Memory;

// Declaration
LS_HAROLD_API LS_Memory LS_MemoryNew(uSize sizeBytes);
LS_HAROLD_API void  LS_MemoryFree(LS_Memory arena);
LS_HAROLD_API void* LS_Malloc(LS_Memory arena, uSize size);
LS_HAROLD_API void* LS_Calloc(LS_Memory arena, uSize numItems, uSize sizeItems);
LS_HAROLD_API void* LS_Realloc(LS_Memory arena, void* memory, uSize sizeNew);
LS_HAROLD_API void  LS_Free(LS_Memory arena, void* memory);
LS_HAROLD_API void  LS_MemoryDisplay(LS_Memory arena);
LS_HAROLD_API void  LS_MemoryPrint(LS_Memory arena);


#endif // MEMORY32_H


///////////////////////////
// EOF
///////////////////////////
