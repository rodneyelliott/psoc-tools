/****************************************************************************
 *
 *  File:           dllist.h
 *  Module:         Doubly Linked List Library
 *  Project:        Code Vault
 *  Workspace:      PSoC Tools
 *
 *  Author:         Rodney B. Elliott
 *  Date:           20 August 2013
 *
 ****************************************************************************
 *
 *  Copyright:      2000 Richard Heathfield
 *                  Eton Computer Systems Ltd
 *                  Macmillan Computer Publishing
 *
 *                  2013 Rodney B. Elliott
 *
 *  This file is part of PSoC Tools.
 *
 *  PSoC Tools is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PSoC Tools is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with PSoC Tools. If not, see <http://www.gnu.org/licenses/>.
 *
 ****************************************************************************/
#ifndef DLLIST_H
#define DLLIST_H
/**
 *  @file dllist.h
 *  @brief Doubly linked list library interface.
 *
 *  <H3> Introduction </H3>
 *
 *  The doubly linked list library is a collection of functions that enable
 *  the programmer to make use of the abstract data structure known as the
 *  doubly linked list (DLL) within their project.
 *
 *  A typical library DLL consists of one or more @em nodes, with each node
 *  containing a pointer to a single @em object. By abstracting the structure
 *  of the DLL away from its content, the library is able to provide a single
 *  set of functions that are able to manipulate @em all DLLs, regardless of
 *  their content. This includes heterogeneous DLLs in which the type of
 *  object stored within the DLL varies from node to node. In order to
 *  accomplish this however, the structure of the nodes that comprise the
 *  DLL must be made as generic as possible.
 *
 *  The nodes of a library DLL thus contain the following fields:
 *
 *  -# Tag. A tag used to identify this node's object type.
 *  -# Previous. A pointer to the previous node in the DLL.
 *  -# Next. A pointer to the next node in the DLL.
 *  -# Object. A pointer to this node's object.
 *
 *  The library uses several terms to describe the relationship between nodes
 *  in a DLL. These include 'previous', 'next', 'first' and 'last', as well as
 *  'before' and 'after'. The precise meaning of these terms is illustrated
 *  below.
 *
 *  Consider a three node DLL whose nodes were added from left to right, and
 *  whose object pointers are represented by a capital letter.
 *
 *  @image html dllist_abc.jpg
 *
 *  Note that the previous and next pointers of each node are represented by
 *  arrows, and that a crossed out square represents a pointer to NULL. Given
 *  that nodes were added from left to right, node A is clearly the oldest
 *  node in the DLL (being the first to be added), whilst node C is clearly
 *  the newest node (being the last to be added). If a new node D were to be
 *  added to the right hand end of the DLL, then it would replace node C as
 *  the newest node. This may be accomplished using the library function
 *  dl_add_last().
 *
 *  @image html dllist_abcd.jpg
 *
 *  If on the other hand, node D needed to be added between nodes B and C,
 *  this could be accomplished using either dl_add_after() with node B as
 *  an argument, or dl_add_before() with node C as an argument.
 *
 *  @image html dllist_abdc.jpg
 *
 *  <H3> Use </H3>
 *
 *  In order to use the library, the programmer must start by declaring a
 *  pointer to a DL_LIST structure with scope appropriate to the intended
 *  application. This pointer must be initialised to NULL, ie:
 *
 *  @code DL_LIST *dl_list = NULL; @endcode
 *
 *  It is important that a pointer to a DL_LIST structure is declared, rather
 *  than an instance of the structure itself. This is because the library has
 *  been built around creating and destroying nodes on the heap, and declaring
 *  an actual instance of the DL_LIST structure will break this functionality.
 *
 *  With the pointer declared, the first node may be added to the empty DLL
 *  using any one of the following library functions:
 *
 *  - dl_create()
 *  - dl_add_before()
 *  - dl_add_after()
 *  - dl_add_first()
 *  - dl_add_last()
 *
 *  Additional nodes may be added to the DLL using the same set of functions,
 *  with the exception of dl_create(). If instead of adding a newly created
 *  node to a DLL, an existing node needs to be inserted into a DLL, either
 *  dl_insert_before() or dl_insert_after() may be used.
 *
 *  The library also provides a number of functions to manipulate existing
 *  nodes and DLLs. The function dl_exchange() enables the position of two
 *  nodes within a DLL to be exchanged, whilst dl_join() enables two DLLs to
 *  be joined together.
 *
 *  Finally, a single node may be deleted using the function dl_delete(),
 *  whilst dl_destroy() deletes all nodes from a DLL.
 *
 *  For further information about these and other library functions, please
 *  refer to the individual function documentation.
 *
 *  <H3> Hardware </H3>
 *
 *  The DLL library has no hardware requirements.
 */

/****************************************************************************
 *  Modules
 ****************************************************************************/

/****************************************************************************
 *  Definitions and Macros
 ****************************************************************************/
/**
 *  @brief Generic success.
 */
#define DL_SUCCESS                      0

/**
 *  @brief Generic failure.
 */
#define DL_FAILURE                      1

/**
 *  @brief Memory was unable to be allocated from the heap.
 *
 *  Any function returning this value will free any memory that was
 *  successfully allocated from the heap prior to the allocation failure.
 */
#define DL_NO_MEMORY                    2

/**
 *  @brief A bad argument was passed to a function.
 */
#define DL_BAD_ARGUMENT                 3

/****************************************************************************
 *  Typedefs and Structures
 ****************************************************************************/
/**
 *  @brief A doubly linked list (DLL) node.
 */
typedef struct DL_LIST
{
    /**
     *  @brief A tag used to identify this node's object type.
     */
    uint16 tag;
    
    /**
     *  @brief A pointer to the previous node in the DLL.
     */
    struct DL_LIST *previous;
    
    /**
     *  @brief A pointer to the next node in the DLL.
     */
    struct DL_LIST *next;
    
    /**
     *  @brief A pointer to this node's object.
     */
    void *object;
} DL_LIST;

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
/**
 *  @brief Create a new DLL node.
 *  @param[out] node A pointer to a pointer to the newly created node.
 *  @param[in] tag A tag used to identify the new node's object type.
 *  @param[in] object A pointer to the new node's object.
 *  @return #DL_SUCCESS if successful, otherwise #DL_BAD_ARGUMENT or
 *      #DL_NO_MEMORY.
 */
uint8 dl_create(DL_LIST **node, uint16 tag, void *object);

/**
 *  @brief Insert a node into a DLL before another node.
 *  @param[in] node A pointer to the DLL node to insert before.
 *  @param[in] new_node A pointer to the DLL node to insert.
 *  @return #DL_SUCCESS if successful, otherwise #DL_BAD_ARGUMENT.
 *  @warning It is up to the caller to ensure that both arguments
 *      point to actual nodes. Passing pointers to uninitialised
 *      nodes would be a <B> very bad thing. </B>
 */
uint8 dl_insert_before(DL_LIST *node, DL_LIST *new_node);

/**
 *  @brief Insert a node into a DLL after another node.
 *  @param[in] node A pointer to the DLL node to insert after.
 *  @param[in] new_node A pointer to the DLL node to insert.
 *  @return #DL_SUCCESS if successful, otherwise #DL_BAD_ARGUMENT.
 *  @warning It is up to the caller to ensure that both arguments
 *      point to actual nodes. Passing pointers to uninitialised
 *      nodes would be a <B> very bad thing. </B>
 */
uint8 dl_insert_after(DL_LIST *node, DL_LIST *new_node);

/**
 *  @brief Get the first node of a DLL.
 *  @param[in] list A pointer to a DLL.
 *  @return A pointer to the first node of the DLL.
 *  @remark If the DLL is empty, a NULL pointer will be returned.
 *  @warning It is up to the caller to ensure that the list argument
 *      points to an actual list. Passing a pointer to an uninitialised
 *      list would be a <B> very bad thing. </B>
 */
DL_LIST *dl_get_first(DL_LIST *list);

/**
 *  @brief Insert a new node into a DLL in first place.
 *  @param[out] list A pointer to a pointer to the DLL in which to insert.
 *  @param[in] tag A tag used to identify the new node's object type.
 *  @param[in] object A pointer to the new node's object.
 *  @return #DL_SUCCESS if successful, otherwise #DL_BAD_ARGUMENT or
 *      #DL_NO_MEMORY.
 *  @remark If the DLL is empty, the list pointer will be modified from
 *      pointing to NULL to pointing to the newly created node. If the
 *      DLL is not empty, the list pointer will remain unchanged.
 *  @warning It is up to the caller to ensure that the list argument
 *      points to an actual list. Passing a pointer to an uninitialised
 *      list pointer would be a <B> very bad thing. </B>
 */
uint8 dl_add_first(DL_LIST **list, uint16 tag, void *object);

/**
 *  @brief Get the last node of a DLL.
 *  @param[in] list A pointer to a DLL.
 *  @return A pointer to the last node of the DLL.
 *  @remark If the DLL is empty, a NULL pointer will be returned.
 *  @warning It is up to the caller to ensure that the list argument
 *      points to an actual list. Passing a pointer to an uninitialised
 *      list would be a <B> very bad thing. </B>
 */
DL_LIST *dl_get_last(DL_LIST *list);

/**
 *  @brief Insert a new node into a DLL in last place.
 *  @param[out] list A pointer to a pointer to the DLL in which to insert.
 *  @param[in] tag A tag used to identify the new node's object type.
 *  @param[in] object A pointer to the new node's object.
 *  @return #DL_SUCCESS if successful, otherwise #DL_BAD_ARGUMENT or
 *      #DL_NO_MEMORY.
 *  @remark If the DLL is empty, the list pointer will be modified from
 *      pointing to NULL to pointing to the newly created node. If the
 *      DLL is not empty, the list pointer will remain unchanged.
 *  @warning It is up to the caller to ensure that the list argument
 *      points to an actual list. Passing a pointer to an uninitialised
 *      list pointer would be a <B> very bad thing. </B>
 */
uint8 dl_add_last(DL_LIST **list, uint16 tag, void *object);

/**
 *  @brief Get the previous node of a DLL.
 *  @param[in] node A pointer to a DLL node.
 *  @return A pointer to the previous node of the DLL.
 *  @remark If the DLL is empty, or if the DLL contains a single
 *      node, a NULL pointer will be returned.
 *  @warning It is up to the caller to ensure that the node argument
 *      points to an actual node. Passing a pointer to an uninitialised
 *      node would be a <B> very bad thing. </B>
 */
DL_LIST *dl_get_previous(DL_LIST *node);

/**
 *  @brief Insert a new node into a DLL before another node.
 *  @param[out] node A pointer to a pointer to the DLL node to insert before.
 *  @param[in] tag A tag used to identify the new node's object type.
 *  @param[in] object A pointer to the new node's object.
 *  @return #DL_SUCCESS if successful, otherwise #DL_BAD_ARGUMENT or
 *      #DL_NO_MEMORY.
 *  @remark If the DLL is empty, the list pointer will be modified from
 *      pointing to NULL to pointing to the newly created node. If the
 *      DLL is not empty, the list pointer will remain unchanged.
 *  @warning It is up to the caller to ensure that the node argument
 *      points to an actual node. Passing a pointer to an uninitialised
 *      node pointer would be a <B> very bad thing. </B>
 */
uint8 dl_add_before(DL_LIST **node, uint16 tag, void *object);

/**
 *  @brief Get the next node of a DLL.
 *  @param[in] node A pointer to a DLL node.
 *  @return A pointer to the next node of the DLL.
 *  @remark If the DLL is empty, or if the DLL contains a single
 *      node, a NULL pointer will be returned.
 *  @warning It is up to the caller to ensure that the node argument
 *      points to an actual node. Passing a pointer to an uninitialised
 *      node would be a <B> very bad thing. </B>
 */
DL_LIST *dl_get_next(DL_LIST *node);

/**
 *  @brief Insert a new node into a DLL after another node.
 *  @param[out] node A pointer to a pointer to the DLL node to insert after.
 *  @param[in] tag A tag used to identify the new node's object type.
 *  @param[in] object A pointer to the new node's object.
 *  @return #DL_SUCCESS if successful, otherwise #DL_BAD_ARGUMENT or
 *      #DL_NO_MEMORY.
 *  @remark If the DLL is empty, the list pointer will be modified from
 *      pointing to NULL to pointing to the newly created node. If the
 *      DLL is not empty, the list pointer will remain unchanged.
 *  @warning It is up to the caller to ensure that the node argument
 *      points to an actual node. Passing a pointer to an uninitialised
 *      node pointer would be a <B> very bad thing. </B>
 */
uint8 dl_add_after(DL_LIST **node, uint16 tag, void *object);

/**
 *  @brief Get the node count of a DLL.
 *  @param[in] list A pointer to a DLL.
 *  @return The number of nodes in the DLL.
 *  @remark If the DLL is empty, a count of zero will be returned.
 *  @warning It is up to the caller to ensure that the list argument
 *      points to an actual list. Passing a pointer to an uninitialised
 *      list would be a <B> very bad thing. </B>
 */
uint32 dl_get_count(DL_LIST *list);

/**
 *  @brief Get the object of a DLL node.
 *  @param[in] node A pointer to a DLL node.
 *  @param[out] tag A pointer to the returned object's tag.
 *  @param[out] object A pointer to a pointer to the returned object.
 *  @return #DL_SUCCESS if successful, otherwise #DL_BAD_ARGUMENT.
 *  @remark This function does not remove the object from the node,
 *      nor does it remove the node from the DLL.
 *  @remark The tag parameter is optional, and may be set to NULL if
 *      the object's tag is not required.
 *  @warning It is up to the caller to ensure that the node argument
 *      points to an actual node. Passing a pointer to an uninitialised
 *      node would be a <B> very bad thing. </B>
 */
uint8 dl_get_object(DL_LIST *node, uint16 *tag, void **object);

/**
 *  @brief Extract a node from a DLL.
 *  @param[in] node A pointer to a DLL node.
 *  @return #DL_SUCCESS if successful, otherwise #DL_BAD_ARGUMENT.
 *  @remark The node is extracted from the structure of the DLL, but
 *      otherwise remains intact.
 *  @warning If the node pointer is the only means of addressing a DLL,
 *      the DLL will be lost.
 *  @warning It is up to the caller to ensure that the node argument
 *      points to an actual node. Passing a pointer to an uninitialised
 *      node would be a <B> very bad thing. </B>
 */
uint8 dl_extract(DL_LIST *node);

/**
 *  @brief Delete a DLL node.
 *  @param[in] node A pointer to a DLL node.
 *  @return #DL_SUCCESS if successful, otherwise #DL_BAD_ARGUMENT.
 *  @warning If the node pointer is the only means of addressing a DLL,
 *      the DLL will be lost.
 *  @warning It is up to the caller to ensure that the node argument
 *      points to an actual node. Passing a pointer to an uninitialised
 *      node would be a <B> very bad thing. </B>
 */
uint8 dl_delete(DL_LIST *node);

/**
 *  @brief Destroy a DLL.
 *  @param[in] list A pointer to a pointer to a DLL.
 *  @return #DL_SUCCESS if successful, otherwise #DL_BAD_ARGUMENT.
 *  @remark Deletes all nodes from the DLL, and modifies the list
 *      pointer to point to NULL.
 *  @warning It is up to the caller to ensure that the list argument
 *      points to an actual list. Passing a pointer to an uninitialised
 *      list pointer would be a <B> very bad thing. </B>
 */
uint8 dl_destroy(DL_LIST **list);

/**
 *  @brief Join two DLLs.
 *  @param[in] list_a A pointer to a DLL.
 *  @param[in] list_b A pointer to a DLL.
 *  @return #DL_SUCCESS if successful, otherwise #DL_BAD_ARGUMENT.
 *  @remark After joining, the last node of list_a will point to
 *      the first node of list_b.
 *  @warning It is up to the caller to ensure that both arguments
 *      point to actual lists. Passing pointers to uninitialised
 *      lists would be a <B> very bad thing. </B>
 */
uint8 dl_join(DL_LIST *list_a, DL_LIST *list_b);

/**
 *  @brief Exchange two nodes in a DLL.
 *  @param[in] node_a A pointer to a DLL node.
 *  @param[in] node_b A pointer to a DLL node.
 *  @return #DL_SUCCESS if successful, otherwise #DL_BAD_ARGUMENT.
 *  @warning It is up to the caller to ensure that both arguments
 *      point to actual lists. Passing pointers to uninitialised
 *      lists would be a <B> very bad thing. </B>
 */
uint8 dl_exchange(DL_LIST *node_a, DL_LIST *node_b);

/**
 *  @brief Update a DLL node's object.
 *  @param[in] node A pointer to a pointer to the DLL node to update.
 *  @param[in] new_tag A tag used to identify the node's new object type.
 *  @param[in] new_object A pointer to the node's new object.
 *  @return #DL_SUCCESS if successful, otherwise #DL_BAD_ARGUMENT or
 *      #DL_NO_MEMORY.
 *  @remark If the node fails to update, its old tag and object will
 *      be retained.
 *  @warning It is up to the caller to ensure that the node argument
 *      points to an actual node. Passing a pointer to an uninitialised
 *      node pointer would be a <B> very bad thing. </B>
 */
uint8 dl_update(DL_LIST **node, uint16 new_tag, void *new_object);

#endif

/****************************************************************************
 *  End of File
 ****************************************************************************/
