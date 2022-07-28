////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 5, 2022
//
////////////////////////////////////////////////////////////
#ifndef LS_EVENT_H
#define LS_EVENT_H


/* Structures */
typedef struct ls_event
{
  i32 type;
  
} ls_event;


/* Declaration */
LS_HAROLD_API bool ls_poll_event(ls_event* event);


#endif /* LS_EVENT_H */

///////////////////////////
// EOF
///////////////////////////
