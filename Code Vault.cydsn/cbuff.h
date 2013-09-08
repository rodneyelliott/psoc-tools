/****************************************************************************
 *
 *  File:           cbuff.h
 *  Module:         Circular Buffer Library
 *  Project:        Code Vault
 *  Workspace:      PSoC Tools
 *
 *  Author:         Rodney B. Elliott
 *  Date:           23 August 2013
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
#ifndef CBUFF_H
#define CBUFF_H
/**
 *  @file cbuff.h
 *  @brief Circular buffer library interface.
 *
 *  <H3> Introduction </H3>
 *
 *  The circular buffer library is a collection of functions that enable the
 *  programmer to make use of the abstract data structure known as the
 *  circular buffer within their project.
 *
 *  A circular buffer may be thought of as a circular linked list (CLL) with
 *  certain access restrictions. These restrictions enforce the classic first
 *  in, first out (FIFO) protocol, making a circular buffer ideal for storing
 *  streaming data. Furthermore, unlike a CLL, the maximum number of nodes
 *  allowed in a circular buffer may be specified. Should a new node be added
 *  to a circular buffer that has reached its node limit, the new node will
 *  overwrite the oldest node in the buffer, thus maintaining the limit.
 *
 *  A typical library circular buffer consists of one or more @em nodes, with
 *  each node containing a pointer to a single @em object. By abstracting the
 *  structure of the circular buffer away from its content, the library is
 *  able to provide a single set of functions that are able to manipulate
 *  @em all circular buffers, regardless of their content. This includes
 *  heterogeneous circular buffers in which the type of object stored within
 *  the circular buffer varies from node to node. In order to accomplish this
 *  however, the structure of the nodes that comprise the circular buffer must
 *  be made as generic as possible.
 *
 *  The nodes of a library circular buffer thus contain the following fields:
 *
 *  -# Tag. A tag used to identify this node's object type.
 *  -# Previous. A pointer to the previous node in the circular buffer.
 *  -# Next. A pointer to the next node in the circular buffer.
 *  -# Object. A pointer to this node's object.
 *
 *  Note that each circular buffer node contains a pointer to an object,
 *  rather than the object itself. Whilst the library is responsible for
 *  managing the object pointer, it is up to the programmer to manage the
 *  actual object. This includes everything from its creation, right though
 *  to its eventual destruction.
 *
 *  <H3> Use </H3>
 *
 *  In order to use the library, the programmer must start by declaring an
 *  instance of a CB_LIST structure with scope appropriate to the intended
 *  application. This instance must be initialised to zero, ie:
 *
 *  @code CB_LIST cb_list = {0}; @endcode
 *
 *  With the instance declared, nodes may be added to the empty circular
 *  buffer using the library function cb_add_new(), and removed using the
 *  function cb_remove_old().
 *
 *  The functions cb_get_new_object() and cb_get_old_object() may be used
 *  to examine an object without removing its node from the circular buffer,
 *  whilst cb_get_limit() and cb_set_limit() may be used to get and set the
 *  maximum number of nodes allowed in the buffer respectively. The function
 *  cb_get_count() returns the number of nodes in the circular buffer, and
 *  cb_destroy() deletes all nodes from a buffer.
 *
 *  For further information about these library functions, please refer to the
 *  individual function documentation. For examples of their use, please see
 *  the circular buffer test library.
 *
 *  <H3> Hardware </H3>
 *
 *  The circular buffer library has no hardware requirements.
 *
 *  <H3> Further Reading </H3>
 *
 *  Circular linked list library (cllist.h)
 *
 *  <a href = "http://en.wikipedia.org/wiki/Circular_buffer">
 *      Circular buffer (Wikipedia) </a>
 */
 
/****************************************************************************
 *  Modules
 ****************************************************************************/
#include "cllist.h"

/****************************************************************************
 *  Definitions and Macros
 ****************************************************************************/
/**
 *  @brief Generic success.
 */
#define CB_SUCCESS                      0

/**
 *  @brief Generic failure.
 */
#define CB_FAILURE                      1

/**
 *  @brief Memory was unable to be allocated from the heap.
 *
 *  Any function returning this value will free any memory that was
 *  successfully allocated from the heap prior to the allocation failure.
 */
#define CB_NO_MEMORY                    2

/**
 *  @brief A bad argument was passed to a function.
 */
#define CB_BAD_ARGUMENT                 3

/**
 *  @brief The circular buffer is empty.
 */
#define CB_EMPTY                        4

/****************************************************************************
 *  Typedefs and Structures
 ****************************************************************************/
/**
 *  @brief A circular buffer based upon a circular linked list (CLL).
 */
typedef struct CB_LIST
{
    /**
     *  @brief A pointer to a CLL.
     */
    CL_LIST *list;
    
    /**
     *  @brief The maximum number of nodes allowed in the CLL.
     */
    uint32 limit;
} CB_LIST;

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
/**
 *  @brief Add a new node to a circular buffer.
 *  @param[in] buffer A pointer to a circular buffer.
 *  @param[in] tag A tag used to identify the new node's object type.
 *  @param[in] object A pointer to the new node's object.
 *  @return #CB_SUCCESS if successful, otherwise #CB_BAD_ARGUMENT or
 *      #CB_NO_MEMORY.
 *  @warning It is up to the caller to ensure that the buffer argument
 *      points to an actual circular buffer. Passing a pointer to an
 *      uninitialised circular buffer would be a <B> very bad thing. </B>
 */
uint8 cb_add_new(CB_LIST *buffer, uint16 tag, void *object);

/**
 *  @brief Remove the oldest node from a circular buffer.
 *  @param[in] buffer A pointer to a circular buffer.
 *  @param[out] object A pointer to a pointer to the returned object.
 *  @return #CB_SUCCESS if successful, otherwise #CB_BAD_ARGUMENT or
 *      #CB_EMPTY.
 *  @remark The object parameter is optional, and may be set to NULL if the
 *      object is not required.
 *  @warning It is up to the caller to ensure that the buffer argument
 *      points to an actual circular buffer. Passing a pointer to an
 *      uninitialised circular buffer would be a <B> very bad thing. </B>
 */
uint8 cb_remove_old(CB_LIST *buffer, void **object);

/**
 *  @brief Get the object of the oldest node of a circular buffer.
 *  @param[in] buffer A pointer to a circular buffer.
 *  @param[out] tag A pointer to the returned object's tag.
 *  @param[out] object A pointer to a pointer to the returned object.
 *  @return #CB_SUCCESS if successful, otherwise #CB_BAD_ARGUMENT or
 *      #CB_EMPTY.
 *  @remark The tag parameter is optional, and may be set to NULL if
 *      the object's tag is not required.
 *  @warning It is up to the caller to ensure that the buffer argument
 *      points to an actual circular buffer. Passing a pointer to an
 *      uninitialised circular buffer would be a <B> very bad thing. </B>
 */
uint8 cb_get_old_object(CB_LIST *buffer, uint16 *tag, void **object);

/**
 *  @brief Get the object of the newest node of a circular buffer.
 *  @param[in] buffer A pointer to a circular buffer.
 *  @param[out] tag A pointer to the returned object's tag.
 *  @param[out] object A pointer to a pointer to the returned object.
 *  @return #CB_SUCCESS if successful, otherwise #CB_BAD_ARGUMENT or
 *      #CB_EMPTY.
 *  @remark The tag parameter is optional, and may be set to NULL if
 *      the object's tag is not required.
 *  @warning It is up to the caller to ensure that the buffer argument
 *      points to an actual circular buffer. Passing a pointer to an
 *      uninitialised circular buffer would be a <B> very bad thing. </B>
 */
uint8 cb_get_new_object(CB_LIST *buffer, uint16 *tag, void **object);

/**
 *  @brief Get the node count of a circular buffer.
 *  @param[in] buffer A pointer to a circular buffer.
 *  @return The number of nodes in the circular buffer.
 *  @remark If the buffer argument is NULL, a count of zero will be returned.
 */
uint32 cb_get_count(CB_LIST *buffer);

/**
 *  @brief Get the node limit of a circular buffer.
 *  @param[in] buffer A pointer to a circular buffer.
 *  @return The maximum number of nodes allowed in the circular buffer.
 *  @remark If the buffer argument is NULL, a limit of zero will be returned.
 */
uint32 cb_get_limit(CB_LIST *buffer);

/**
 *  @brief Set the node limit of a circular buffer.
 *  @param[in] buffer A pointer to a circular buffer.
 *  @param[in] limit The maximum number of nodes allowed in the circular
 *      buffer.
 *  @return #CB_SUCCESS if successful, otherwise #CB_BAD_ARGUMENT or
 *      #CB_FAILURE.
 *  @remark It is up to the caller to ensure that the number of nodes in the
 *      circular buffer is less than the proposed limit. Failure to do so will
 *      result in this function returning #CB_FAILURE.
 *  @remark Set the limit to zero to allow the circular buffer to grow without
 *      limit.
 */
uint8 cb_set_limit(CB_LIST *buffer, uint32 limit);

/**
 *  @brief Destroy a circular buffer.
 *  @param[in] buffer A pointer to a circular buffer.
 *  @return #CB_SUCCESS if successful, otherwise #CB_BAD_ARGUMENT.
 *  @remark Deletes all nodes from the circular buffer.
 *  @warning It is up to the caller to ensure that the buffer argument
 *      points to an actual circular buffer. Passing a pointer to an
 *      uninitialised circular buffer would be a <B> very bad thing. </B>
 */
uint8 cb_destroy(CB_LIST *buffer);

#endif

/****************************************************************************
 *  End of File
 ****************************************************************************/
