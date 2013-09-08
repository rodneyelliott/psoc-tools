/****************************************************************************
 *
 *  File:           error.c
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
/**
 *  @file error.c
 *  @brief Error management library implementation.
 */
 
/****************************************************************************
 *  Modules
 ****************************************************************************/
#include <device.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "misc.h"

/****************************************************************************
 *  Definitions and Macros
 ****************************************************************************/
/**
 *  @brief The error management library object tag.
 */
#define _TAG                            900

/****************************************************************************
 *  Typedefs and Structures
 ****************************************************************************/

/****************************************************************************
 *  Prototypes of Local Functions
 ****************************************************************************/
/**
 *  @brief Create and fill a new timestamp structure.
 *  @param[out] timestamp A pointer to a pointer to the returned timestamp
 *      information.
 *  @return #ER_SUCCESS if successful, otherwise #ER_NO_MEMORY or #ER_FAILURE.
 *  @warning It is up to the caller to ensure that the real-time clock
 *      component has been started prior to calling this function. Failure
 *      to do so will result in this function returning #ER_FAILURE.
 */
static uint8 _create_timestamp(RT_DATA **timestamp);

/**
 *  @brief Create and fill a new location structure.
 *  @param[out] location A pointer to a pointer to the returned location
 *      information.
 *  @param[in] file A pointer to the name of the file in which the
 *      error occurred.
 *  @param[in] line The line number at which the error occurred.
 *  @return #ER_SUCCESS if successful, otherwise #ER_NO_MEMORY.
 */
static uint8 _create_location(ER_LOCATION **location, char *file, int line);

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
 *  @param[in] file A pointer to the name of the file in which the
 *      error occurred.
 *  @param[in] line The line number at which the error occurred.
 *  @return #ER_SUCCESS if successful, otherwise #ER_BAD_ARGUMENT,
 *      #ER_NO_MEMORY, #ER_FULL, or #ER_FAILURE.
 *  @remark Adds a node to the rear of the deque.
 *  @warning It is up to the caller to ensure that the real-time clock
 *      component has been started prior to calling this function. Failure
 *      to do so will result in this function returning #ER_FAILURE when
 *      the timestamp error option is selected.
 */
uint8 _add_standard(DE_LIST *deque, uint32 number, uint8 options,
    char *file, int line);

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
 *  @param[in] file A pointer to the name of the file in which the
 *      error occurred.
 *  @param[in] line The line number at which the error occurred.
 *  @return #ER_SUCCESS if successful, otherwise #ER_BAD_ARGUMENT,
 *      #ER_NO_MEMORY, #ER_FULL, or #ER_FAILURE.
 *  @remark Adds a node to the rear of the deque.
 *  @warning It is up to the caller to ensure that the real-time clock
 *      component has been started prior to calling this function. Failure
 *      to do so will result in this function returning #ER_FAILURE when
 *      the timestamp error option is selected.
 */
uint8 _add_special(DE_LIST *deque, char *message, uint8 options,
    char *file, int line);

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/
/**
 *  @brief Standard error messages.
 */
char *ER_MESSAGES[ER_MAX] =
{
    "E00100: Start of main program error message block.",
    "E00200: Start of doubly linked list library error message block.",
    "E00300: Start of deque library error message block.",
    "E00400: Start of queue library error message block.",
    "E00500: Start of circular linked list library error message block.",
    "E00600: Start of circular buffer library error message block.",
    "E00700: Start of miscellaneous function library error message block.",
    "E00800: Start of real-time clock library error message block.",
    "E00900: Start of error management library error message block.",
    "E01000: Start of button library error message block."
};

/****************************************************************************
 *  Global Variables
 ****************************************************************************/

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
uint8 er_get_first_object(DE_LIST *deque, ER_OBJECT **object)
{
    uint8 result = ER_BAD_ARGUMENT;
    
    if (deque != NULL && object != NULL)
    {
        result = de_get_first_object(deque, NULL, (void **)object);
    }
    
    return result;
}

uint8 er_get_last_object(DE_LIST *deque, ER_OBJECT **object)
{
    uint8 result = ER_BAD_ARGUMENT;
    
    if (deque != NULL && object != NULL)
    {
        result = de_get_last_object(deque, NULL, (void **)object);
    }
    
    return result;
}

uint8 er_get_message(ER_OBJECT *object, char **message)
{
    char *new_message;
    uint8 result = ER_BAD_ARGUMENT;
    
    if (object != NULL && message != NULL)
    {
        if (object->error_type == ER_STANDARD_TYPE)
        {
            new_message = ER_MESSAGES[object->error.number];
        }
        else if (object->error_type == ER_SPECIAL_TYPE)
        {
            new_message = object->error.message;
        }
        
        *message = new_message;
        
        result = ER_SUCCESS;
    }
    
    return result;
}

uint8 er_remove(DE_LIST *deque)
{
    ER_OBJECT *object;
    uint8 result = ER_BAD_ARGUMENT;
    
    if (deque != NULL)
    {   
        result = de_remove_first(deque, (void **)&object);
        
        if (result == DE_SUCCESS)
        {
            if (object->timestamp != NULL)
            {
                free(object->timestamp);
            }
            
            if (object->location != NULL)
            {
                free(object->location->file);
                free(object->location);
            }
            
            free(object);
        }
    }
    
    return result;
}

uint32 er_get_count(DE_LIST *deque)
{
    return de_get_count(deque);
}

uint32 er_get_limit(DE_LIST *deque)
{
    return de_get_limit(deque);
}

uint8 er_set_limit(DE_LIST *deque, uint32 limit)
{
    return de_set_limit(deque, limit);
}

uint8 er_get_timestamp(ER_OBJECT *object, RT_DATA **timestamp)
{
    uint8 result = ER_BAD_ARGUMENT;
    
    if (object != NULL && timestamp != NULL)
    {
        *timestamp = object->timestamp;
        
        result = ER_SUCCESS;
    }
    
    return result;
}

uint8 er_get_location(ER_OBJECT *object, ER_LOCATION **location)
{
    uint8 result = ER_BAD_ARGUMENT;
    
    if (object != NULL && location != NULL)
    {
        *location = object->location;
        
        result = ER_SUCCESS;
    }
    
    return result;
}

uint8 er_convert_timestamp(RT_DATA *timestamp, char *string)
{
    uint8 result = ER_BAD_ARGUMENT;
    
    if (timestamp != NULL && string != NULL)
    {
        result = rt_convert(timestamp, string);
    }
    
    return result;
}

uint8 er_convert_location(ER_LOCATION *location, char *string)
{
    uint8 result = ER_BAD_ARGUMENT;
    char t[32] = {0};
    
    if (location != NULL && string != NULL)
    {
        strcpy(string, "file ");
        strcat(string, location->file);
        strcat(string, " line ");
        mi_utoa(location->line, t);
        strcat(string, t);
        
        result = ER_SUCCESS;
    }
    
    return result;
}

uint8 er_destroy(DE_LIST *deque)
{
    uint8 result = ER_BAD_ARGUMENT;
    
    if (deque != NULL)
    {
        while (de_get_count(deque) > 0)
        {
            er_remove(deque);
        }
    
        result = ER_SUCCESS;
    }
    
    return result;
}

/****************************************************************************
 *  Local Functions
 ****************************************************************************/
uint8 _add_standard(DE_LIST *deque, uint32 number, uint8 options,
    char *file, int line)
{
    ER_LOCATION *location = NULL;
    ER_OBJECT *object;
    uint8 result = ER_BAD_ARGUMENT;
    RT_DATA *timestamp = NULL;
    
    if (deque != NULL && file != NULL)
    {
        if (options & ER_OPTIONS_TIMESTAMP)
        {
            result = _create_timestamp(&timestamp);
        }
        else
        {
            result = ER_SUCCESS;
        }
        
        if ((options & ER_OPTIONS_LOCATION) && (result == ER_SUCCESS))
        {
            result = _create_location(&location, file, line);
            
            if (result != ER_SUCCESS)
            {
                if (options & ER_OPTIONS_TIMESTAMP)
                {
                    free(timestamp);
                }
            }
        }
        
        if (result == ER_SUCCESS)
        {
            object = malloc(sizeof(*object));
            
            if (object != NULL)
            {
                object->error_type = ER_STANDARD_TYPE;
                object->error.number = number;
                object->timestamp = timestamp;
                object->location = location;
                
                result = de_add_last(deque, _TAG, object);
                
                if (result != DE_SUCCESS)
                {
                    if (options & ER_OPTIONS_TIMESTAMP)
                    {
                        free(timestamp);
                    }
                    
                    if (options & ER_OPTIONS_LOCATION)
                    {
                        free(location->file);
                        free(location);
                    }
                    
                    free(object);
                }
            }
            else
            {
                if (options & ER_OPTIONS_TIMESTAMP)
                {
                    free(timestamp);
                }
                
                if (options & ER_OPTIONS_LOCATION)
                {
                    free(location->file);
                    free(location);
                }
                
                result = ER_NO_MEMORY;
            }
        }
    }
    
    return result;
}

uint8 _add_special(DE_LIST *deque, char *message, uint8 options,
    char *file, int line)
{
    ER_LOCATION *location = NULL;
    char *new_message;
    ER_OBJECT *object;
    uint8 result = ER_BAD_ARGUMENT;
    RT_DATA *timestamp = NULL;
    
    if (deque != NULL && message != NULL && file != NULL)
    {
        if (options & ER_OPTIONS_TIMESTAMP)
        {
            result = _create_timestamp(&timestamp);
        }
        else
        {
            result = ER_SUCCESS;
        }
        
        if ((options & ER_OPTIONS_LOCATION) && result == ER_SUCCESS)
        {
            result = _create_location(&location, file, line);
            
            if (result != ER_SUCCESS)
            {
                if (options & ER_OPTIONS_TIMESTAMP)
                {
                    free(timestamp);
                }
            }
        }
        
        if (result == ER_SUCCESS)
        {
            object = malloc(sizeof(*object));
            
            if (object != NULL)
            {
                object->error_type = ER_SPECIAL_TYPE;
                
                new_message = malloc(strlen(message) + 1);
                
                if (new_message != NULL)
                {
                    strcpy(new_message, message);
                    object->error.message = new_message;
                }
                else
                {
                    free(object);
                    
                    result = ER_NO_MEMORY;
                }
            }
            
            if (result == ER_SUCCESS)
            {   
                object->timestamp = timestamp;
                object->location = location;
                
                result = de_add_last(deque, _TAG, object);
                
                if (result != DE_SUCCESS)
                {
                    if (options & ER_OPTIONS_TIMESTAMP)
                    {
                        free(timestamp);
                    }
                    
                    if (options & ER_OPTIONS_LOCATION)
                    {
                        free(location->file);
                        free(location);
                    }
                    
                    free(object);
                }
            }
            else
            {
                if (options & ER_OPTIONS_TIMESTAMP)
                {
                    free(timestamp);
                }
                
                if (options & ER_OPTIONS_LOCATION)
                {
                    free(location->file);
                    free(location);
                }
                
                result = ER_NO_MEMORY;
            }
        }
    }
    
    return result;
}

uint8 _create_timestamp(RT_DATA **timestamp)
{
    RT_DATA *new_timestamp;
    uint8 result;
    
    new_timestamp = malloc(sizeof(*new_timestamp));
    
    if (new_timestamp != NULL)
    {
        result = rt_read(new_timestamp);
        
        if (result == RT_SUCCESS)
        {
            *timestamp = new_timestamp;
        }
    }
    else
    {
        result = ER_NO_MEMORY;
    }
    
    return result;
}

uint8 _create_location(ER_LOCATION **location, char *file, int line)
{
    char *new_file;
    ER_LOCATION *new_location;
    uint8 result;
    
    new_location = malloc(sizeof(*new_location));
    
    if (new_location != NULL)
    {
        new_location->line = line;
        
        new_file = malloc(strlen(file) + 1);
        
        if (new_file != NULL)
        {
            strcpy(new_file, file);
            new_location->file = new_file;
            
            *location = new_location;
            
            result = ER_SUCCESS;
        }
        else
        {
            free(new_location);
            
            result = ER_NO_MEMORY;
        }
    }
    else
    {
        result = ER_NO_MEMORY;
    }
    
    return result;
}

/****************************************************************************
 *  End of File
 ****************************************************************************/
