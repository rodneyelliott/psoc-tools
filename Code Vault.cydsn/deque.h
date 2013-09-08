/****************************************************************************
 *
 *  File:           deque.h
 *  Module:         Deque Library
 *  Project:        Code Vault
 *  Workspace:      PSoC Tools
 *
 *  Author:         Rodney B. Elliott
 *  Date:           20 August 2013
 *
 ****************************************************************************
 *
 *  Copyright:      2013 Rodney B. Elliott
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
#ifndef DEQUE_H
#define DEQUE_H
/**
 *  @file deque.h
 *  @brief Deque library interface.
 *
 *  <H3> Introduction </H3>
 *
 *  The deque library is a collection of functions that enable the programmer
 *  to make use of the abstract data structure known as the deque within their
 *  project.
 *
 *  A deque, or double-ended queue, is one which supports the addition and
 *  removal of nodes from either end of the queue. Contrast this method of
 *  operation to a single-ended queue which only supports the addition of
 *  nodes to the rear of the queue, and the removal of nodes from the front
 *  of the queue.
 *
 *  A typical library deque consists of one or more @em nodes, with each node
 *  containing a pointer to a single @em object. By abstracting the structure
 *  of the deque away from its content, the library is able to provide a
 *  single set of functions that are able to manipulate @em all deques,
 *  regardless of their content. This includes heterogeneous deques in which
 *  the type of object stored within the deque varies from node to node.
 *
 *  In order to accomplish this however, the structure of the nodes that
 *  comprise the deque must be made as generic as possible. This has been
 *  achieved by basing the deque upon a doubly linked list (DLL), and by
 *  using the same node structure as the DLL.
 *
 *  The nodes of a library deque thus contain the following fields:
 *
 *  -# Tag. A tag used to identify this node's object type.
 *  -# Previous. A pointer to the previous node in the deque.
 *  -# Next. A pointer to the next node in the deque.
 *  -# Object. A pointer to this node's object.
 *
 *  By comparing the deque interface to that of a DLL, it should be apparent
 *  that a deque is simply a DLL with certain access restrictions, and a node
 *  count.
 *
 *  Note that each deque node contains a pointer to an object, rather than the
 *  object itself. Whilst the library is responsible for managing the object
 *  pointer, it is up to the programmer to manage the actual object. This
 *  includes everything from its creation, right though to its eventual
 *  destruction.
 *
 *  <H3> Use </H3>
 *
 *  In order to use the library, the programmer must start by declaring an
 *  instance of a DE_LIST structure with scope appropriate to the intended
 *  application. This instance must be initialised to zero, ie:
 *
 *  @code DE_LIST de_list = {0}; @endcode
 *
 *  With the instance declared, nodes may be added to the empty deque using
 *  the library functions de_add_first() and de_add_last(). Nodes may be
 *  removed from the deque using the functions de_remove_first() and
 *  de_remove_last().
 *
 *  The functions de_get_first_object() and de_get_last_object() may be used
 *  to examine an object without removing its node from the deque, whilst
 *  de_get_limit() and de_set_limit() may be used to get and set the maximum
 *  number of nodes allowed in the deque respectively. The library function
 *  de_get_count() returns the number of nodes in the deque, and de_destroy()
 *  deletes all nodes from a deque.
 *
 *  For further information about these library functions, please refer to the
 *  individual function documentation. For examples of their use, please see
 *  the deque test library.
 *
 *  <H3> Hardware </H3>
 *
 *  The deque library has no hardware requirements.
 *
 *  <H3> Further Reading </H3>
 *
 *  Doubly linked list library (dllist.h)
 *
 *  <a href = "http://en.wikipedia.org/wiki/Double-ended_queue">
 *      Double-ended queue (Wikipedia)</a>
 *
 *  <a href = "http://www.amazon.com/
 *      C-Unleashed-Richard-Heathfield/dp/0672318962">
 *      C Unleashed (Amazon)</a>
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
#define DE_SUCCESS                      0

/**
 *  @brief Generic failure.
 */
#define DE_FAILURE                      1

/**
 *  @brief Memory was unable to be allocated from the heap.
 *
 *  Any function returning this value will free any memory that was
 *  successfully allocated from the heap prior to the allocation failure.
 */
#define DE_NO_MEMORY                    2

/**
 *  @brief A bad argument was passed to a function.
 */
#define DE_BAD_ARGUMENT                 3

/**
 *  @brief The deque is empty.
 */
#define DE_EMPTY                        4

/**
 *  @brief The deque is full.
 */
#define DE_FULL                         5

/****************************************************************************
 *  Typedefs and Structures
 ****************************************************************************/
/**
 *  @brief A deque based upon a doubly linked list (DLL).
 */
typedef struct DE_LIST
{
    /**
     *  @brief A pointer to a DLL.
     */
    DL_LIST *list;
    
    /**
     *  @brief The number of nodes in the DLL.
     */
    uint32 count;
    
    /**
     *  @brief The maximum number of nodes allowed in the DLL.
     */
    uint32 limit;
} DE_LIST;

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
/**
 *  @brief Add a new node to a deque in first place.
 *  @param[in] deque A pointer to a deque.
 *  @param[in] tag A tag used to identify the new node's object type.
 *  @param[in] object A pointer to the new node's object.
 *  @return #DE_SUCCESS if successful, otherwise #DE_BAD_ARGUMENT,
 *      #DE_NO_MEMORY, or #DE_FULL.
 *  @warning It is up to the caller to ensure that the deque argument
 *      points to an actual deque. Passing a pointer to an uninitialised
 *      deque would be a <B> very bad thing. </B>
 */
uint8 de_add_first(DE_LIST *deque, uint16 tag, void *object);

/**
 *  @brief Add a new node to a deque in last place.
 *  @param[in] deque A pointer to a deque.
 *  @param[in] tag A tag used to identify the new node's object type.
 *  @param[in] object A pointer to the new node's object.
 *  @return #DE_SUCCESS if successful, otherwise #DE_BAD_ARGUMENT,
 *      #DE_NO_MEMORY, or #DE_FULL.
 *  @warning It is up to the caller to ensure that the deque argument
 *      points to an actual deque. Passing a pointer to an uninitialised
 *      deque would be a <B> very bad thing. </B>
 */
uint8 de_add_last(DE_LIST *deque, uint16 tag, void *object);

/**
 *  @brief Remove the first node from a deque.
 *  @param[in] deque A pointer to a deque.
 *  @param[out] object A pointer to a pointer to the returned object.
 *  @return #DE_SUCCESS if successful, otherwise #DE_BAD_ARGUMENT or
 *      #DE_EMPTY.
 *  @remark The object parameter is optional, and may be set to NULL if the
 *      object is not required.
 *  @warning It is up to the caller to ensure that the deque argument
 *      points to an actual deque. Passing a pointer to an uninitialised
 *      deque would be a <B> very bad thing. </B>
 */
uint8 de_remove_first(DE_LIST *deque, void **object);

/**
 *  @brief Remove the last node from a deque.
 *  @param[in] deque A pointer to a deque.
 *  @param[out] object A pointer to a pointer to the returned object.
 *  @return #DE_SUCCESS if successful, otherwise #DE_BAD_ARGUMENT or
 *      #DE_EMPTY.
 *  @remark The object parameter is optional, and may be set to NULL if the
 *      object is not required.
 *  @warning It is up to the caller to ensure that the deque argument
 *      points to an actual deque. Passing a pointer to an uninitialised
 *      deque would be a <B> very bad thing. </B>
 */
uint8 de_remove_last(DE_LIST *deque, void **object);

/**
 *  @brief Get the object of the first node of a deque.
 *  @param[in] deque A pointer to a deque.
 *  @param[out] tag A pointer to the returned object's tag.
 *  @param[out] object A pointer to a pointer to the returned object.
 *  @return #DE_SUCCESS if successful, otherwise #DE_BAD_ARGUMENT or
 *      #DE_EMPTY.
 *  @remark This function does not remove the object from the node,
 *      nor does it remove the node from the deque.
 *  @remark The tag parameter is optional, and may be set to NULL if
 *      the object's tag is not required.
 *  @warning It is up to the caller to ensure that the deque argument
 *      points to an actual deque. Passing a pointer to an uninitialised
 *      deque would be a <B> very bad thing. </B>
 */
uint8 de_get_first_object(DE_LIST *deque, uint16 *tag, void **object);

/**
 *  @brief Get the object of the last node of a deque.
 *  @param[in] deque A pointer to a deque.
 *  @param[out] tag A pointer to the returned object's tag.
 *  @param[out] object A pointer to a pointer to the returned object.
 *  @return #DE_SUCCESS if successful, otherwise #DE_BAD_ARGUMENT or
 *      #DE_EMPTY.
 *  @remark This function does not remove the object from the node,
 *      nor does it remove the node from the deque.
 *  @remark The tag parameter is optional, and may be set to NULL if
 *      the object's tag is not required.
 *  @warning It is up to the caller to ensure that the deque argument
 *      points to an actual deque. Passing a pointer to an uninitialised
 *      deque would be a <B> very bad thing. </B>
 */
uint8 de_get_last_object(DE_LIST *deque, uint16 *tag, void **object);

/**
 *  @brief Get the node count of a deque.
 *  @param[in] deque A pointer to a deque.
 *  @return The number of nodes in the deque.
 *  @remark If the deque argument is NULL, a count of zero will be returned.
 */
uint32 de_get_count(DE_LIST *deque);

/**
 *  @brief Get the node limit of a deque.
 *  @param[in] deque A pointer to a deque.
 *  @return The maximum number of nodes allowed in the deque.
 *  @remark If the deque argument is NULL, a limit of zero will be returned.
 */
uint32 de_get_limit(DE_LIST *deque);

/**
 *  @brief Set the node limit of a deque.
 *  @param[in] deque A pointer to a deque.
 *  @param[in] limit The maximum number of nodes allowed in the deque.
 *  @return #DE_SUCCESS if successful, otherwise #DE_BAD_ARGUMENT or
 *      #DE_FAILURE.
 *  @remark It is up to the caller to ensure that the number of nodes in the
 *      deque is less than the proposed limit. Failure to do so will result
 *      in this function returning #DE_FAILURE.
 *  @remark Set the limit to zero to allow the deque to grow without limit.
 */
uint8 de_set_limit(DE_LIST *deque, uint32 limit);

/**
 *  @brief Destroy a deque.
 *  @param[in] deque A pointer to a deque.
 *  @return #DE_SUCCESS if successful, otherwise #DE_BAD_ARGUMENT.
 *  @remark Deletes all nodes from the deque, and sets the node
 *      count to zero.
 *  @warning It is up to the caller to ensure that the deque argument
 *      points to an actual deque. Passing a pointer to an uninitialised
 *      deque would be a <B> very bad thing. </B>
 */
uint8 de_destroy(DE_LIST *deque);

#endif

/****************************************************************************
 *  End of File
 ****************************************************************************/
