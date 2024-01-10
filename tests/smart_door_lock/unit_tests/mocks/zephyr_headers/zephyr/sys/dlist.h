#ifndef DLIST_H_
#define DLIST_H_

#ifdef __cplusplus
extern "C"
{
#endif

    struct _dnode
    {
        union
        {
            struct _dnode *head; /* ptr to head of list (sys_dlist_t) */
            struct _dnode *next; /* ptr to next node    (sys_dnode_t) */
        };
        union
        {
            struct _dnode *tail; /* ptr to tail of list (sys_dlist_t) */
            struct _dnode *prev; /* ptr to previous node (sys_dnode_t) */
        };
    };

    typedef struct _dnode sys_dlist_t;
    typedef struct _dnode sys_dnode_t;

#ifdef __cplusplus
}
#endif

#endif