////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 17, 2022
//
////////////////////////////////////////////////////////////
#ifndef MEMORY_H
#define MEMORY_H

#define Kilobyte(Value) (Value * 1024LL)
#define Megabyte(Value) (Value * 1024LL * 1024)
#define Gigabyte(Value) (Value * 1024LL * 1024 * 1024)

/* Type def */
typedef struct ls_memory_
{
  void* address;
  usize size;
  usize used;
  
} ls_memory_, *ls_memory;

/* Declaration */
LS_HAROLD_API ls_memory ls_memory_new(usize size_bytes);
LS_HAROLD_API void  ls_memory_free(ls_memory arena);
LS_HAROLD_API void* ls_malloc(ls_memory arena, usize size);
LS_HAROLD_API void* ls_calloc(ls_memory arena, usize num_items, usize size_items);
LS_HAROLD_API void* ls_realloc(ls_memory arena, void* memory, usize size_new);
LS_HAROLD_API void  ls_free(ls_memory arena, void* memory);
LS_HAROLD_API void  ls_memory_display(ls_memory arena);
LS_HAROLD_API void  ls_memory_print(ls_memory arena);


#endif /* MEMORY_H */


///////////////////////////
// EOF
///////////////////////////
