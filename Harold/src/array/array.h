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
typedef struct LS_List_
{
  int count;
  int max;
  size_t isize;
  void* items;
} LS_List_, *LS_List;

// Declaration
LS_HAROLD_API LS_List LS_ListNew_n(uSize size);
LS_HAROLD_API void LS_ListFree_n(LS_List list);

LS_HAROLD_API LS_List LS_ListNew(void* memory, uSize size);
LS_HAROLD_API void LS_ListFree(void* memory, LS_List list);

LS_HAROLD_API void* LS_ListAdd(LS_List list, void* item);
LS_HAROLD_API void LS_ListRm(LS_List list, void* item);
LS_HAROLD_API void LS_ListRemove(LS_List list, void* item);

LS_HAROLD_API void* LS_ListGet(LS_List list, i32 num);
LS_HAROLD_API void* LS_ListSet(LS_List list, i32 num, void* item);


#endif // LS_ARRAY_H


///////////////////////////
// EOF
///////////////////////////
