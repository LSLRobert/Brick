////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 17, 2022
//
////////////////////////////////////////////////////////////
#ifndef MEMORY_H
#define MEMORY_H

// Type def
typedef void* LS_Memory;

// Declaration
LS_HAROLD_API LS_Memory LS_MemoryNew(uSize sizeBytes);
LS_HAROLD_API void LS_MemoryFree(LS_Memory address);

LS_HAROLD_API void* LS_Malloc(LS_Memory address, uSize size);
LS_HAROLD_API void* LS_Calloc(LS_Memory address, uSize  numItems, uSize sizeItems);
LS_HAROLD_API void* LS_Realloc(LS_Memory address, void* memory, uSize sizeNew);
LS_HAROLD_API void LS_Free(LS_Memory address, void* memory);

LS_HAROLD_API void LS_MemoryDisplay(LS_Memory address);
LS_HAROLD_API void LS_MemoryPrint(LS_Memory address);


#endif // MEMORY_H


///////////////////////////
// EOF
///////////////////////////
