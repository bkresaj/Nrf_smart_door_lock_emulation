#ifndef SLIST_H_
#define SLIST_H_

#ifdef __cplusplus
extern "C"
{
#endif

    /** @cond INTERNAL_HIDDEN */
    struct _snode
    {
        struct _snode *next;
    };
    /** @endcond */

    /** Single-linked list node structure. */
    typedef struct _snode sys_snode_t;

    /** @cond INTERNAL_HIDDEN */
    struct _slist
    {
        sys_snode_t *head;
        sys_snode_t *tail;
    };
    /** @endcond */

    /** Single-linked list structure. */
    typedef struct _slist sys_slist_t;

#ifdef __cplusplus
}
#endif

#endif