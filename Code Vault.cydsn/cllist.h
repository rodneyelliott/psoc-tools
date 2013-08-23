/****************************************************************************
 *
 *  File:           cllist.h
 *  Module:         Circular Linked List Library
 *  Project:        Code Vault
 *  Workspace:      PSoC Tools
 *
 *  Author:         Rodney B. Elliott
 *  Date:           22 August 2013
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
#ifndef CLLIST_H
#define CLLIST_H
/**
 *  @file cllist.h
 *  @brief Circular linked list library interface.
 *
 *  <H3> Introduction </H3>
 *
 *  The circular linked list library is a collection of functions that enable
 *  the programmer to make use of the abstract data structure known as the
 *  circular linked list (CLL) within their project.
 *
 *  A typical library CLL consists of one or more @em nodes, with each node
 *  containing a pointer to a single @em object. By abstracting the structure
 *  of the CLL away from its content, the library is able to provide a single
 *  set of functions that are able to manipulate @em all CLLs, regardless of
 *  their content. This includes heterogeneous CLLs in which the type of
 *  object stored within the CLL varies from node to node. In order to
 *  accomplish this however, the structure of the nodes that comprise the
 *  CLL must be made as generic as possible.
 *
 *  The nodes of a library CLL thus contain the following fields:
 *
 *  -# Tag. A tag used to identify this node's object type.
 *  -# Previous. A pointer to the previous node in the CLL.
 *  -# Next. A pointer to the next node in the CLL.
 *  -# Object. A pointer to this node's object.
 *
 *  The library uses several terms to describe the relationship between nodes
 *  in a CLL. These include 'previous', 'next', 'before' and 'after'. The
 *  precise meaning of these terms is illustrated below.
 *
 *  Consider a CLL containing a single node whose object pointer is
 *  represented by a capital letter.
 *
 *  @image html cllist_a.jpg
 *
 *  Note that the previous and next pointers of the node are represented by
 *  arrows. Unlike a linear doubly linked list (DLL), a CLL has no 'first'
 *  or 'last' node to serve as a position reference. Instead, operations on a
 *  CLL are performed relative to the 'current' node. This initially points to
 *  the first node to be added to a CLL, but may be repositioned by moving it
 *  'forward' or 'backward' relative to its current location. These directions
 *  are defined by the library as follows: forward is in the direction of the
 *  current node's next pointer; backward is in the direction of the current
 *  node's previous pointer.
 *
 *  The position of the current node is not changed when a new node is added
 *  to an existing CLL. Using the library function cl_add_after() to add a
 *  further three nodes to the single node CLL shown above will result in the
 *  following.
 *
 *  @image html cllist_adcb.jpg
 *
 *  As can be seen, each new node has been added after the current node A. If
 *  the function cl_add_before() were to be used instead, the result would be
 *  as follows.
 *
 *  @image html cllist_bcda.jpg
 *
 *  Whilst a new node may be added to a CLL either side of the current node,
 *  only the current node may be removed from a CLL. Whenever this is done,
 *  the previous node becomes the new current node. If node A were to be
 *  removed from the CLL above, node D would become the new current node.
 *
 *  @image html cllist_bcd.jpg
 *
 *  <H3> Use </H3>
 *
 *  In order to use the library, the programmer must start by declaring an
 *  instance of a CL_LIST structure with scope appropriate to the intended
 *  application. This instance must be initialised to zero, ie:
 *
 *  @code CL_LIST cl_list = {0}; @endcode
 *
 *  With the instance declared, nodes may be added to the empty CLL using
 *  the library functions cl_add_before() and cl_add_after(). Nodes may be
 *  removed from the CLL using the function cl_remove_current().
 *
 *  The functions cl_move_forward() and cl_move backward() may be used to
 *  move the current node forward or backward, whilst cl_get_current_object()
 *  may be used to examine an object without removing its node from the CLL.
 *
 *  The library function cl_get_count() returns the number of nodes in the
 *  CLL, and cl_destroy() deletes all nodes from a CLL.
 *
 *  For further information about these library functions, please refer to the
 *  individual function documentation.
 *
 *  <H3> Hardware </H3>
 *
 *  The CLL library has no hardware requirements.
 *
 */
 
/****************************************************************************
 *  Modules
 ****************************************************************************/
#include "dllist.h"

/****************************************************************************
 *  Definitions and Macros
 ****************************************************************************/
/**
 *  @brief Generic success.
 */
#define CL_SUCCESS                      0

/**
 *  @brief Generic failure.
 */
#define CL_FAILURE                      1

/**
 *  @brief Memory was unable to be allocated from the heap.
 *
 *  Any function returning this value will free any memory that was
 *  successfully allocated from the heap prior to the allocation failure.
 */
#define CL_NO_MEMORY                    2

/**
 *  @brief A bad argument was passed to a function.
 */
#define CL_BAD_ARGUMENT                 3

/**
 *  @brief The CLL is empty.
 */
#define CL_EMPTY                        4

/****************************************************************************
 *  Typedefs and Structures
 ****************************************************************************/
/**
 *  @brief A CLL based upon a doubly linked list (DLL).
 */
typedef struct CL_LIST
{
    /**
     *  @brief A pointer to a DLL.
     */
    DL_LIST *list;
    
    /**
     *  @brief The number of nodes in the DLL.
     */
    uint32 count;
} CL_LIST;

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
/**
 *  @brief Insert a new node into a CLL after the current node.
 *  @param[in] list A pointer to the CLL in which to insert.
 *  @param[in] tag A tag used to identify the new node's object type.
 *  @param[in] object A pointer to the new node's object.
 *  @return #CL_SUCCESS if successful, otherwise #CL_BAD_ARGUMENT or
 *      #CL_NO_MEMORY.
 *  @remark If the CLL is empty, the new node will become the current
 *      node. If the CLL is not empty, the position of the current
 *      node will remain unchanged.
 *  @warning It is up to the caller to ensure that the list argument
 *      points to an actual list. Passing a pointer to an uninitialised
 *      list would be a <B> very bad thing. </B>
 */
uint8 cl_add_after(CL_LIST *list, uint16 tag, void *object);

/**
 *  @brief Insert a new node into a CLL before the current node.
 *  @param[in] list A pointer to the CLL in which to insert.
 *  @param[in] tag A tag used to identify the new node's object type.
 *  @param[in] object A pointer to the new node's object.
 *  @return #CL_SUCCESS if successful, otherwise #CL_BAD_ARGUMENT or
 *      #CL_NO_MEMORY.
 *  @remark If the CLL is empty, the new node will become the current
 *      node. If the CLL is not empty, the position of the current
 *      node will remain unchanged.
 *  @warning It is up to the caller to ensure that the list argument
 *      points to an actual list. Passing a pointer to an uninitialised
 *      list would be a <B> very bad thing. </B>
 */
uint8 cl_add_before(CL_LIST *list, uint16 tag, void *object);

/**
 *  @brief Remove the current node from a CLL.
 *  @param[in] list a pointer to a CLL.
 *  @param[out] object A pointer to a pointer to the returned object.
 *  @return #CL_SUCCESS if successful, otherwise #CL_BAD_ARGUMENT or
 *      #CL_EMPTY.
 *  @remark The object parameter is optional, and may be set to NULL if the
 *      object is not required.
 *  @remark The previous node becomes the new current node.
 *  @warning It is up to the caller to ensure that the list argument
 *      points to an actual list. Passing a pointer to an uninitialised
 *      list would be a <B> very bad thing. </B>
 */
uint8 cl_remove_current(CL_LIST *list, void **object);

/**
 *  @brief Move the current node forward.
 *  @param[in] list A pointer to a CLL.
 *  @param[in] places The number of places to move forward.
 *  @return #CL_SUCCESS if successful, otherwise #CL_BAD_ARGUMENT or
 *      #CL_EMPTY.
 *  @warning It is up to the caller to ensure that the list argument
 *      points to an actual list. Passing a pointer to an uninitialised
 *      list would be a <B> very bad thing. </B>
 */
uint8 cl_move_forward(CL_LIST *list, uint32 places);

/**
 *  @brief Move the current node backward.
 *  @param[in] list A pointer to a CLL.
 *  @param[in] places The number of places to move backward.
 *  @return #CL_SUCCESS if successful, otherwise #CL_BAD_ARGUMENT or
 *      #CL_EMPTY.
 *  @warning It is up to the caller to ensure that the list argument
 *      points to an actual list. Passing a pointer to an uninitialised
 *      list would be a <B> very bad thing. </B>
 */
uint8 cl_move_backward(CL_LIST *list, uint32 places);

/**
 *  @brief Get the object of the current node.
 *  @param[in] list A pointer to a CLL.
 *  @param[out] tag A pointer to the returned object's tag.
 *  @param[out] object A pointer to a pointer to the returned object.
 *  @return #CL_SUCCESS if successful, otherwise #CL_BAD_ARGUMENT.
 *  @remark This function does not remove the object from the node,
 *      nor does it remove the node from the CLL.
 *  @remark The tag parameter is optional, and may be set to NULL if
 *      the object's tag is not required.
 *  @warning It is up to the caller to ensure that the list argument
 *      points to an actual list. Passing a pointer to an uninitialised
 *      list would be a <B> very bad thing. </B>
 */
uint8 cl_get_current_object(CL_LIST *list, uint16 *tag, void **object);

/**
 *  @brief Get the node count of a CLL.
 *  @param[in] list A pointer to a CLL.
 *  @return The number of nodes in the CLL.
 *  @remark If the CLL is empty, a count of zero will be returned.
 */
uint32 cl_get_count(CL_LIST *list);

/**
 *  @brief Destroy a CLL.
 *  @param[in] list A pointer to a CLL.
 *  @return #CL_SUCCESS if successful, otherwise #CL_BAD_ARGUMENT.
 *  @remark Deletes all nodes from the CLL, and sets the node
 *      count to zero.
 *  @warning It is up to the caller to ensure that the list argument
 *      points to an actual list. Passing a pointer to an uninitialised
 *      list would be a <B> very bad thing. </B>
 */
uint8 cl_destroy(CL_LIST *list);

#endif

/****************************************************************************
 *  End of File
 ****************************************************************************/
