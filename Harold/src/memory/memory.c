////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 17, 2022
//
////////////////////////////////////////////////////////////
#include "header.h"
#include "memory_int.h"

////////////////////////////////////////////////////////////
//
// https://gist.github.com/apsun/caa3c5552dce7b13b898b70569b1f239
//
////////////////////////////////////////////////////////////

//  typedef struct ls_chunk_
//  {
//    void* address;
//    uSize size;
//    uSize used;
//    void* prev;
//    void* next;
//    
//  } ls_chunk_, *ls_chunk;

/* ls_memory_new */
LS_HAROLD_API ls_memory ls_memory_new(usize size_bytes)
{
  // LPVOID VirtualAlloc(lpAddress, dwSize, flAllocationType, flProtect);
  UNIMPLEMENTED
  void* address = VirtualAlloc(NULL, size_bytes, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
  if(address == NULL) exit(EXIT_FAILURE);
  ls_memory arena = (ls_memory)address;
  arena->address = address;
  arena->size = size_bytes;
  arena->used = sizeof(ls_memory_);
  return arena;
}


/* ls_memory_free */
LS_HAROLD_API void ls_memory_free(ls_memory arena)
{
  // BOOL VirtualFree(lpAddress, dwSize, dwFreeType);
  UNIMPLEMENTED
  VirtualFree(arena->address, 0, MEM_RELEASE);
}


/* ls_malloc */
LS_HAROLD_API void* ls_malloc(ls_memory arena, usize size)
{
  // void* malloc(uSize size)
  UNIMPLEMENTED
//    // TODO:: Allocate based on a chunk struct that holds 
//    //      the address and size.. Like the arena
//    // -------
//    // first 8 bytes is the size, followed by the memory space
//    // we can get the size with
//    //      (LS_Chunk)chunk = (address - sizeof(LS_Chunk_));
//    //      size = chunk->size;
//    
//    ls_assert(arena->size >= arena->used + size);
//    void* ptr = arena->address + arena->used;
//    arena->used += size;
//    return ptr;
  return malloc(size);
}


/* ls_calloc */
LS_HAROLD_API void* ls_calloc(ls_memory arena, usize num_items, usize size_items)
{
  // void* calloc(uSize nmemb, uSize size)
  UNIMPLEMENTED
  return calloc(num_items, size_items);
}


/* ls_realloc */
LS_HAROLD_API void* ls_realloc(ls_memory arena, void* memory, usize size_new)
{
  // void realloc(void* ptr, uSize size)
  UNIMPLEMENTED
  return realloc(memory, size_new);
}


/* ls_free */
LS_HAROLD_API void ls_free(ls_memory arena, void* memory)
{
  // void free(void* ptr)
  UNIMPLEMENTED
  free(memory);
}


/* ls_memory_display */
LS_HAROLD_API void ls_memory_display(ls_memory arena)
{
  UNIMPLEMENTED
}


/* ls_memory_print */
LS_HAROLD_API void ls_memory_print(ls_memory arena)
{
  UNIMPLEMENTED
}


///////////////////////////
// EOF
///////////////////////////
