#ifndef EZI_DS_SLIST_H
#define EZI_DS_SLIST_H

#include <stddef.h>

/* Iterates the list item-by-item starting from head */
#define SLIST_ITERATE(sl, ptr) for (ptr = (sl)->head; ptr; ptr = ptr->next)

/* Iterates the list item-by-item starting a specific node */
#define SLIST_ITERATE_NODE(node, ptr) for (ptr = node; ptr; ptr = ptr->next)

/* Gets the value of the first node (head) */
#define SLIST_FIRST(sl, type) ((sl)->head ? ((type)(sl)->head->data) : NULL)

/* Gets the value of the last node (tail) */
#define SLIST_LAST(sl, type) ((sl)->tail ? ((type)(sl)->tail->data) : NULL)

#define SLIST_VALID(sl)                                                        \
    (!(!(sl)->head ^ !(sl)->tail) &&                                           \
     !(!(sl)->head && !(sl)->tail && (sl)->count > 0))

/* Gets the current length of the linked list */
#define SLIST_COUNT(sl) ((sl)->count)

typedef void (*free_func_t)(void *);
typedef int (*ezi_slist_data_cmp_t)(const void *, const void *, const void *);

struct ezi_slist_node
{
    void *                 data;
    struct ezi_slist_node *next;
};

struct ezi_slist
{
    size_t count;
    size_t element_size;

    struct ezi_slist_node *head;
    struct ezi_slist_node *tail;
    free_func_t            free_func;
};

/*!
 * \brief Initializes a generic singly-linked-list with a specific element size
 *
 * \param [in,out] sl            A pointer to the list to initialize
 * \param [in]     element_size  The element size to use
 * \param [in]     free_func     A pointer to the function which to use when
 *                               freeing the list
 *
 * \return 0 on success, -1 otherwise with errno set
 */
int
init_ezi_slist_free(struct ezi_slist *sl,
                    size_t            element_size,
                    free_func_t       free_func);

/*!
 * \brief Initializes a generic singly-linked-list with a specific element size
 *
 * \param [in,out] sl            A pointer to the list to initialize
 * \param [in]     element_size  The element size to use
 *
 * \return 0 on success, -1 otherwise with errno set
 */
int
init_ezi_slist(struct ezi_slist *sl, size_t element_size);

/*!
 * \biref Pushes an item to the end (tail) of the list
 *
 * \param [in] sl    The list to push this item onto
 * \param [in] data  The item to push
 *
 * \return 0 on success, -1 otherwise with errno set
 */
int
ezi_slist_push_no_alloc(struct ezi_slist *sl, void *data);

/*!
 * \brief Pushes an item to the end (tail) of the list
 *
 * this function is the same as \see ezi_slist_push_no_alloc, but the data
 * gets copied into a malloced buffer
 *
 * \param [in] sl    The list to push this item onto
 * \param [in] data  The item to push
 *
 * \return 0 on success, -1 otherwise with errno set
 */
int
ezi_slist_push(struct ezi_slist *sl, const void *data);

/*!
 * \brief Pops the last item from the end of the list, and remove it afterwards.
 *        The returned item MUST be freed manually along with its data.
 *
 * \param [in] sl  The list to pop the item from
 *
 * \return The poped item, NULL if the list is empty
 */
void *
ezi_slist_pop(struct ezi_slist *sl);

/*!
 * \brief Inserts an item to the begining (head) of the list
 *
 * \param [in] sl    The list to insert this item into
 * \param [in] data  The item to insert
 *
 * \return 0 on success, -1 otherwise with errno set
 */
int
ezi_slist_shift_no_alloc(struct ezi_slist *sl, void *data);

/*!
 * \brief Inserts an item to the begining (head) of the list
 *
 * this function is the same as \see ezi_slist_shift_no_alloc, but the data
 * gets copied into a malloced buffer
 *
 * \param [in] sl    The list to insert this item into
 * \param [in] data  The item to insert
 * \return 0 on success, -1 otherwise with errno set
 */
int
ezi_slist_shift(struct ezi_slist *sl, const void *data);

/*!
 * \brief Removes the last item from the begining of the list, and remove it
 *        afterwards. The returned item MUST be freed manually along with
 *        its data.
 *
 * \param [in] sl  The list to remove the item from
 *
 * \return The removed item, NULL if the list is empty
 */
void *
ezi_slist_unshift(struct ezi_slist *sl);

void *
ezi_slist_remove(struct ezi_slist * sl,
                 const void *       data,
                 const void *       ctx,
                 ezi_slist_data_cmp_t cmp);

/*!
 * \breif Clears a singly linked-list pointed to by \see sl items
 *
 * \param [in,out]  sl  A pointer to the singly linked list to to be cleared
 */
void
ezi_slist_clear(struct ezi_slist *sl);

/*!
 * \brief Frees an list node
 *
 * \param [in]  The node to free
 */
void
free_ezi_slist_node(struct ezi_slist_node *node);

/*!
 * \brief Frees all resources used by the list
 *
 * \param [in] sl  The list to free
 */
void
free_ezi_slist(struct ezi_slist *sl);

#endif /* EZI_DS_SLIST_H */
