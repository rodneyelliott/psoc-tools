/****************************************************************************
 *
 *  File:           error.h
 *  Module:         Error Management Library
 *  Project:        Code Vault
 *  Workspace:      PSoC Tools
 *
 *  Author:         Rodney B. Elliott
 *  Date:           27 August 2013
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
#ifndef ERROR_H
#define ERROR_H
/**
 *  @file error.h
 *  @brief Error management library interface.
 *
 *  <H3> Introduction </H3>
 *
 *  The error management library is a collection of functions that enable the
 *  programmer to manage the reporting of errors within their project.
 *
 *  The library uses a deque structure to store error information. This has
 *  been chosen as the basis of the library due to the fact that the first
 *  error to occur tends to be more important than the last error to occur,
 *  and thus must be preserved. The use of a deque guarantees that this is
 *  always the case - unlike a circular buffer for instance.
 *
 *  Each node of the deque points to an error object that is owned by the
 *  library - that is, the library is responsible for everything from its
 *  creation to its eventual destruction. The library operates the deque
 *  as if it were a single-ended queue, with nodes being added to the rear
 *  of the queue, and nodes being removed from the front of the queue. The
 *  advantage of using a deque in this manner is that it gives the programmer
 *  the ability to examine both the last error object to be added, as well as
 *  the first - something that would be impossible were a queue to be used
 *  instead.
 *
 *  Two types of error object are supported by the library:
 *
 *  -# Standard. A standard error object is one that consists of a predefined
 *      error number and its corresponding predefined error message.
 *  -# Special. A special error object is one that contains an error message
 *      that has not been predefined.
 *
 *  Error numbers are enumerated below, whilst error.c contains the predefined
 *  error messages. Both types of error object may include the following
 *  optional information:
 *
 *  -# Timestamp. The date and time at which the error occurred.
 *  -# Location. The name and line number of the file in which the error
 *      occurred.
 *
 *  <H3> Use </H3>
 *
 *  In order to use the library, the programmer must start by declaring an
 *  instance of a DE_LIST structure with scope appropriate to the intended
 *  application. This instance must be initialised to zero, ie:
 *
 *  @code DE_LIST de_list = {0}; @endcode
 *
 *  The library requires exclusive access to this instance. The programmer
 *  must not attempt to use the declared structure for any other purpose.
 *
 *  With the instance declared, nodes may be added to the empty deque using
 *  the library functions er_add_standard() and er_add_special(), both of
 *  which add nodes to the rear of the deque. Nodes may be removed from the
 *  front of the deque using the function er_remove().
 *
 *  The functions er_get_first_object() and er_get_last_object() may be used
 *  to examine an error object without removing its node from the deque. The
 *  functions er_get_message(), er_get_timestamp(), and er_get_location() may
 *  then be used to examine the object's message, timestamp, and location
 *  respectively. Timestamp and location information may then be converted
 *  into ASCII strings ready for storage or display using the functions
 *  er_convert_timestamp() and er_convert_location(). The library function
 *  er_get_count() returns the number of nodes in the deque, and er_destroy()
 *  deletes all nodes from the deque.
 *
 *  For further information about these library functions, please refer to the
 *  individual function documentation. For examples of their use, please see
 *  the error management test library.
 *
 *  <H3> Hardware </H3>
 *
 *  The error management library has been designed to run on a Cypress
 *  CY8CKIT-001 development kit fitted with a PSoC5 CY8C5568AXI-060 module. It
 *  requires access to the following components:
 *
 *  - RTC_1
 *
 *  The PSoC5 module must be fitted with a 32.768kHz crystal, and the 'XTAL
 *  32kHz' source must be enabled in the clock section of the project design
 *  wide resource (*.cydwr) file.
 *
 *  <H3> Further Reading </H3>
 *
 *  Doubly-ended queue library (deque.h)
 *
 *  Real-time clock library (rtime.h)
 */
 
/****************************************************************************
 *  Modules
 ****************************************************************************/
#include "deque.h"
#include "rtime.h"

/****************************************************************************
 *  Definitions and Macros
 ****************************************************************************/
/**
 *  @brief Selectively generate Doxygen documentation.
 *
 *  Uncomment this definition when generating Doxygen documentation, and
 *  comment when compiling the codebase.
 */
//#define DOXYGEN

/**
 *  @brief Generic success.
 */
#define ER_SUCCESS                      0

/**
 *  @brief Generic failure.
 */
#define ER_FAILURE                      1

/**
 *  @brief Memory was unable to be allocated from the heap.
 *
 *  Any function returning this value will free any memory that was
 *  successfully allocated from the heap prior to the allocation failure.
 */
#define ER_NO_MEMORY                    2

/**
 *  @brief A bad argument was passed to a function.
 */
#define ER_BAD_ARGUMENT                 3

/**
 *  @brief The deque is empty.
 */
#define ER_EMPTY                        4

/**
 *  @brief The deque is full.
 */
#define ER_FULL                         5

/**
 *  @brief Selects no error options.
 */
#define ER_OPTIONS_NONE                 0x00

/**
 *  @brief Selects the timestamp error option.
 */
#define ER_OPTIONS_TIMESTAMP            0x01

/**
 *  @brief Selects the location error option.
 */
#define ER_OPTIONS_LOCATION             0x02

/**
 *  @brief Identifies a standard error object.
 */
#define ER_STANDARD_TYPE                0

/**
 *  @brief Identifies a special error object.
 */
#define ER_SPECIAL_TYPE                 1

#ifdef DOXYGEN
/**
 *  @brief Add a new standard error object to a deque.
 *  @param[in] deque A pointer to a deque.
 *  @param[in] number The standard error number.
 *  @param[in] options The selected error options.
 *
 *  This member may be one or more of the following values.
 *
 *  Value                | Description
 *  -------------------- | ------------------------------------
 *  @b ER_OPTIONS_NONE      | Selects no error options.
 *  @b ER_OPTIONS_TIMESTAMP | Selects the timestamp error option.
 *  @b ER_OPTIONS_LOCATION  | Selects the location error option.
 *
 *  @return #ER_SUCCESS if successful, otherwise #ER_BAD_ARGUMENT,
 *      #ER_NO_MEMORY, #ER_FULL, or #ER_FAILURE.
 *  @remark Adds a node to the rear of the deque.
 *  @warning It is up to the caller to ensure that the real-time clock
 *      component has been started prior to calling this function. Failure
 *      to do so will result in this function returning #ER_FAILURE if the
 *      timestamp error option is selected.
 */
uint8 er_add_standard(DE_LIST *deque, uint32 number, uint8 options);
#else
#define er_add_standard(DEQUE, NUMBER, OPTIONS) _add_standard(DEQUE, \
NUMBER, OPTIONS, __FILE__, __LINE__)
#endif

#ifdef DOXYGEN
/**
 *  @brief Add a new special error object to a deque.
 *  @param[in] deque A pointer to a deque.
 *  @param[in] message A pointer to the special message.
 *  @param[in] options The selected error options.
 *
 *  This member may be one or more of the following values.
 *
 *  Value                | Description
 *  -------------------- | ------------------------------------
 *  @b ER_OPTIONS_NONE      | Selects no error options.
 *  @b ER_OPTIONS_TIMESTAMP | Selects the timestamp error option.
 *  @b ER_OPTIONS_LOCATION  | Selects the location error option.
 *
 *  @return #ER_SUCCESS if successful, otherwise #ER_BAD_ARGUMENT,
 *      #ER_NO_MEMORY, #ER_FULL, or #ER_FAILURE.
 *  @remark Adds a node to the rear of the deque.
 *  @warning It is up to the caller to ensure that the real-time clock
 *      component has been started prior to calling this function. Failure
 *      to do so will result in this function returning #ER_FAILURE if the
 *      timestamp error option is selected.
 */
uint8 er_add_special(DE_LIST *deque, char *message, uint8 options);
#else
#define er_add_special(DEQUE, MESSAGE, OPTIONS) _add_standard(DEQUE, \
MESSSAGE, OPTIONS, __FILE__, __LINE__)
#endif

/****************************************************************************
 *  Typedefs and Structures
 ****************************************************************************/
/**
 *  @brief Error location information.
 */
typedef struct ER_LOCATION
{
    /**
     *  @brief The name of the file in which the error occurred.
     */
    char *file;
    
    /**
     *  @brief The line number at which the error occurred.
     */
    int line;
} ER_LOCATION;

/**
 *  @brief Error information.
 */
typedef struct ER_OBJECT
{
    /**
     *  @brief The type of error object.
     */
    uint8 error_type;

    union
    {
        /**
         *  @brief A standard error number.
         */
        uint32 number;
        
        /**
         *  @brief A special error message.
         */
        char *message;
    } error;
    /**<
     *  @brief A union of possible types of error.
     */

    /**
     *  @brief A pointer to the optional location information.
     */
    ER_LOCATION *location;
    
    /**
     *  @brief A pointer to the optional timestamp information.
     */
    RT_DATA *timestamp;
} ER_OBJECT;

/**
 *  @brief Standard error codes.
 */
typedef enum ER_CODES
{
    /* Start of main program error code block. */
    E00100,
    
    /* Start of doubly linked list library error code block. */
    E00200,
    
    /* Start of deque library error code block. */
    E00300,
    
    /* Start of queue library error code block. */
    E00400,
    
    /* Start of circular linked list library error code block. */
    E00500,
    
    /* Start of circular buffer library error code block. */
    E00600,
        
    /* Start of miscellaneous function library error code block. */
    E00700,
    
    /* Start of real-time clock library error code block. */
    E00800,
    
    /* Start of error management library error code block. */
    E00900,
    
    /* Start of button library error code block. */
    E01000,
    
    /* Start of finite state machine library error code block. */
    E01100,
            
    ER_MAX
} ER_CODES;

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
/**
 *  @brief Get the first error object of a deque.
 *  @param[in] deque A pointer to a deque.
 *  @param[out] object A pointer to a pointer to the returned error object.
 *  @return #ER_SUCCESS if successful, otherwise #ER_BAD_ARGUMENT or
 *      #ER_EMPTY.
 *  @remark This function does not remove the object from the node,
 *      nor does it remove the node from the deque.
 *  @warning It is up to the caller to ensure that the deque argument
 *      points to an actual deque. Passing a pointer to an uninitialised
 *      deque would be a <B> very bad thing. </B>
 */
uint8 er_get_first_object(DE_LIST *deque, ER_OBJECT **object);

/**
 *  @brief Get the last error object of a deque.
 *  @param[in] deque A pointer to a deque.
 *  @param[out] object A pointer to a pointer to the returned error object.
 *  @return #ER_SUCCESS if successful, otherwise #ER_BAD_ARGUMENT or
 *      #ER_EMPTY.
 *  @remark This function does not remove the object from the node,
 *      nor does it remove the node from the deque.
 *  @warning It is up to the caller to ensure that the deque argument
 *      points to an actual deque. Passing a pointer to an uninitialised
 *      deque would be a <B> very bad thing. </B>
 */
uint8 er_get_last_object(DE_LIST *deque, ER_OBJECT **object);

/**
 *  @brief Get the error object message.
 *  @param[in] object A pointer to an error object.
 *  @param[out] message A pointer to a pointer to the returned message.
 *  @return #ER_SUCCESS if successful, otherwise #ER_BAD_ARGUMENT.
 *  @remark In the case of a standard error object, this function returns a
 *      pointer to the message corresponding to the error number stored in the
 *      object. In the case of a special error object, this function returns
 *      a pointer to the error message stored in the object.
 */
uint8 er_get_message(ER_OBJECT *object, char **message);

/**
 *  @brief Remove an error object from a deque.
 *  @param[in] deque A pointer to a deque.
 *  @return #ER_SUCCESS if successful, otherwise #ER_BAD_ARGUMENT or
 *      #ER_EMPTY.
 *  @remark Removes a node from the front of the deque.
 */
uint8 er_remove(DE_LIST *deque);

/**
 *  @brief Get the node count of a deque.
 *  @param[in] deque A pointer to a deque.
 *  @return The number of nodes in the deque.
 *  @remark If the deque argument is NULL, a count of zero will be returned.
 */
uint32 er_get_count(DE_LIST *deque);

/**
 *  @brief Get the node limit of a deque.
 *  @param[in] deque A pointer to a deque.
 *  @return The maximum number of nodes allowed in the deque.
 *  @remark If the deque argument is NULL, a limit of zero will be returned.
 */
uint32 er_get_limit(DE_LIST *deque);

/**
 *  @brief Set the node limit of a deque.
 *  @param[in] deque A pointer to a deque.
 *  @param[in] limit The maximum number of nodes allowed in the deque.
 *  @return #ER_SUCCESS if successful, otherwise #ER_BAD_ARGUMENT or
 *      #ER_FAILURE.
 *  @remark It is up to the caller to ensure that the number of nodes in the
 *      deque is less than the proposed limit. Failure to do so will result
 *      in this function returning #ER_FAILURE.
 *  @remark Set the limit to zero to allow the deque to grow without limit.
 */
uint8 er_set_limit(DE_LIST *deque, uint32 limit);

/**
 *  @brief Get the error object timestamp information.
 *  @param[in] object A pointer to an error object.
 *  @param[out] timestamp A pointer to a pointer to the returned timestamp.
 *  @return #ER_SUCCESS if successful, otherwise #ER_BAD_ARGUMENT.
 *  @remark If the error object does not contain a timestamp structure,
 *      this function will return a NULL timestamp.
 */
uint8 er_get_timestamp(ER_OBJECT *object, RT_DATA **timestamp);

/**
 *  @brief Get the error object location information.
 *  @param[in] object A pointer to an error object.
 *  @param[out] location A pointer to a pointer to the returned location.
 *  @return #ER_SUCCESS if successful, otherwise #ER_BAD_ARGUMENT.
 *  @remark If the error object does not contain a location structure,
 *      this function will return NULL location.
 */
uint8 er_get_location(ER_OBJECT *object, ER_LOCATION **location);

/**
 *  @brief Convert timestamp information to an ASCII string
 *  @param[in] timestamp A pointer to the timestamp to convert.
 *  @param[out] string A pointer to the returned string.
 *  @return #ER_SUCCESS if successful, otherwise #ER_BAD_ARGUMENT.
 *  @remark String format is 'DD/MM/YYY HH:MM:SS' where 'DD' is the
 *      day value et cetera.
 *  @remark It is up to the caller to allocate sufficient space for the
 *      string.
 */
uint8 er_convert_timestamp(RT_DATA *timestamp, char *string);

/**
 *  @brief Convert location information to an ASCII string
 *  @param[in] location A pointer to the location to convert.
 *  @param[out] string A pointer to the returned string.
 *  @return #ER_SUCCESS if successful, otherwise #ER_BAD_ARGUMENT.
 *  @remark String format is 'file .\\FILE.c line LINE' where 'FILE' is the
 *      name of the file et cetera.
 *  @remark It is up to the caller to allocate sufficient space for the
 *      string.
 */
uint8 er_convert_location(ER_LOCATION *location, char *string);

/**
 *  @brief Destroy a deque.
 *  @param[in] deque A pointer to a deque.
 *  @return #ER_SUCCESS if successful, otherwise #ER_BAD_ARGUMENT.
 *  @remark Deletes all nodes from the deque, and sets the node
 *      count to zero.
 *  @warning It is up to the caller to ensure that the deque argument
 *      points to an actual deque. Passing a pointer to an uninitialised
 *      deque would be a <B> very bad thing. </B>
 */
uint8 er_destroy(DE_LIST *deque);

#endif

/****************************************************************************
 *  End of File
 ****************************************************************************/
