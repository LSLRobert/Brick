////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 17, 2022
//
////////////////////////////////////////////////////////////
#ifndef LS_ARRAY_H
#define LS_ARRAY_H


// Structure
typedef struct ls_list_
{
  int count;
  int max;
  usize isize;
  ls_memory arena;
  void* items;
} ls_list_, *ls_list;

// Declaration
LS_HAROLD_API ls_list ls_list_new(ls_memory arena, usize size);
LS_HAROLD_API void  ls_list_free(ls_list list);
LS_HAROLD_API void* ls_list_add(ls_list list, void* item);
LS_HAROLD_API void  ls_list_rm(ls_list list, void* item);
LS_HAROLD_API void  ls_list_remove(ls_list list, void* item);
LS_HAROLD_API void* ls_list_get(ls_list list, i32 num);
LS_HAROLD_API void* ls_list_set(ls_list list, i32 num, void* item);


#endif /* LS_ARRAY_H */


///////////////////////////
// EOF
///////////////////////////
