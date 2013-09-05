/****************************************************************************
 *
 *  File:           queue.h
 *  Module:         Queue Library
 *  Project:        Code Vault
 *  Workspace:      PSoC Tools
 *
 *  Author:         Rodney B. Elliott
 *  Date:           21 August 2013
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
#ifndef QUEUE_H
#define QUEUE_H
/**
 *  @file queue.h
 *  @brief Queue library interface.
 *
 *  <H3> Introduction </H3>
 *
 *  The queue library is a collection of functions that enable the programmer
 *  to make use of the abstract data structure known as the queue within their
 *  project.
 *
 *  A queue, or single ended queue, is one that supports the addition of nodes
 *  to the rear of the queue, and the removal of nodes from the front of the
 *  queue only. Contrast this to a double ended queue, which supports the
 *  addition and removal of nodes from either end of the queue.
 *
 *  A typical library queue consists of one or more @em nodes, with each node
 *  containing a pointer to a single @em object. By abstracting the structure
 *  of the queue away from its content, the library is able to provide a
 *  single set of functions that are able to manipulate @em all queues,
 *  regardless of their content. This includes heterogeneous queues in which
 *  the type of object stored within the queue varies from node to node.
 *
 *  <H3> Use </H3>
 *
 *  In order to use the library, the programmer must start by declaring an
 *  instance of a QU_LIST structure with scope appropriate to the intended
 *  application. This instance must be initialised to zero, ie:
 *
 *  @code QU_LIST qu_list = {0}; @endcode
 *
 *  With the instance declared, nodes may be added to the empty queue using
 *  the library function qu_add_last(). Nodes may be removed from the queue
 *  using the function qu_remove_first().
 *
 *  The function qu_get_first_object() may be used to examine an object
 *  without removing its node from the queue, whilst qu_get_limit() and
 *  qu_set_limit() may be used to get and set the maximum number of nodes
 *  allowed in the queue respectively. The library function qu_get_count()
 *  returns the number of nodes in the queue, and qu_destroy() deletes all
 *  nodes from a queue.
 *
 *  For further information about these library functions, please refer to the
 *  individual function documentation.
 *
 *  <H3> Hardware </H3>
 *
 *  The queue library has no hardware requirements.
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
#define QU_SUCCESS                      0

/**
 *  @brief Generic failure.
 */
#define QU_FAILURE                      1

/**
 *  @brief Memory was unable to be allocated from the heap.
 *
 *  Any function returning this value will free any memory that was
 *  successfully allocated from the heap prior to the allocation failure.
 */
#define QU_NO_MEMORY                    2

/**
 *  @brief A bad argument was passed to a function.
 */
#define QU_BAD_ARGUMENT                 3

/**
 *  @brief The queue is empty.
 */
#define QU_EMPTY                        4

/**
 *  @brief The queue is full.
 */
#define QU_FULL                         5

/****************************************************************************
 *  Typedefs and Structures
 ****************************************************************************/
/**
 *  @brief A queue based upon a doubly linked list (DLL).
 */
typedef struct QU_LIST
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
} QU_LIST;

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
/**
 *  @brief Add a new node to a queue in last place.
 *  @param[in] queue A pointer to a queue.
 *  @param[in] tag A tag used to identify the new node's object type.
 *  @param[in] object A pointer to the new node's object.
 *  @return #QU_SUCCESS if successful, otherwise #QU_BAD_ARGUMENT,
 *      #QU_NO_MEMORY, or #QU_FULL.
 *  @warning It is up to the caller to ensure that the queue argument
 *      points to an actual queue. Passing a pointer to an uninitialised
 *      queue would be a <B> very bad thing. </B>
 */
uint8 qu_add_last(QU_LIST *queue, uint16 tag, void *object);

/**
 *  @brief Remove the first node from a queue.
 *  @param[in] queue A pointer to a queue.
 *  @param[out] object A pointer to a pointer to the returned object.
 *  @return #QU_SUCCESS if successful, otherwise #QU_BAD_ARGUMENT or
 *      #QU_EMPTY.
 *  @remark The object parameter is optional, and may be set to NULL if the
 *      object is not required.
 *  @warning It is up to the caller to ensure that the queue argument
 *      points to an actual queue. Passing a pointer to an uninitialised
 *      queue would be a <B> very bad thing. </B>
 */
uint8 qu_remove_first(QU_LIST *queue, void **object);

/**
 *  @brief Get the object of the first node of a queue.
 *  @param[in] queue A pointer to a queue.
 *  @param[out] tag A pointer to the returned object's tag.
 *  @param[out] object A pointer to a pointer to the returned object.
 *  @return #QU_SUCCESS if successful, otherwise #QU_BAD_ARGUMENT or
 *      #QU_EMPTY.
 *  @remark This function does not remove the object from the node,
 *      nor does it remove the node from the queue.
 *  @remark The tag parameter is optional, and may be set to NULL if
 *      the object's tag is not required.
 *  @warning It is up to the caller to ensure that the queue argument
 *      points to an actual queue. Passing a pointer to an uninitialised
 *      queue would be a <B> very bad thing. </B>
 */
uint8 qu_get_first_object(QU_LIST *queue, uint16 *tag, void **object);

/**
 *  @brief Get the node count of a queue.
 *  @param[in] queue A pointer to a queue.
 *  @return The number of nodes in the queue.
 *  @remark If the queue argument is NULL, a count of zero will be returned.
 */
uint32 qu_get_count(QU_LIST *queue);

/**
 *  @brief Get the node limit of a queue.
 *  @param[in] queue A pointer to a queue.
 *  @return The maximum number of nodes allowed in the queue.
 *  @remark If the queue argument is NULL, a limit of zero will be returned.
 */
uint32 qu_get_limit(QU_LIST *queue);

/**
 *  @brief Set the node limit of a queue.
 *  @param[in] queue A pointer to a queue.
 *  @param[in] limit The maximum number of nodes allowed in the queue.
 *  @return #QU_SUCCESS if successful, otherwise #QU_BAD_ARGUMENT or
 *      #QU_FAILURE.
 *  @remark It is up to the caller to ensure that the number of nodes in the
 *      queue is less than the proposed limit. Failure to do so will result
 *      in this function returning #QU_FAILURE.
 *  @remark Set the limit to zero to allow the queue to grow without limit.
 */
uint8 qu_set_limit(QU_LIST *queue, uint32 limit);

/**
 *  @brief Destroy a queue.
 *  @param[in] queue A pointer to a queue.
 *  @return #QU_SUCCESS if successful, otherwise #QU_BAD_ARGUMENT.
 *  @remark Deletes all nodes from the queue, and sets the node
 *      count to zero.
 *  @warning It is up to the caller to ensure that the queue argument
 *      points to an actual queue. Passing a pointer to an uninitialised
 *      queue would be a <B> very bad thing. </B>
 */
uint8 qu_destroy(QU_LIST *queue);

#endif

/****************************************************************************
 *  End of File
 ****************************************************************************/
