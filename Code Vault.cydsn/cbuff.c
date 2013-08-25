/****************************************************************************
 *
 *  File:           cbuff.c
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
/**
 *  @file cbuff.c
 *  @brief Circular buffer library implementation.
 */
 
/****************************************************************************
 *  Modules
 ****************************************************************************/
#include <device.h>
#include <stdlib.h>

#include "cbuff.h"
#include "cllist.h"

/****************************************************************************
 *  Definitions and Macros
 ****************************************************************************/

/****************************************************************************
 *  Typedefs and Structures
 ****************************************************************************/

/****************************************************************************
 *  Prototypes of Local Functions
 ****************************************************************************/

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/

/****************************************************************************
 *  Global Variables
 ****************************************************************************/

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
uint8 cb_add_new(CB_LIST *buffer, uint16 tag, void *object)
{
    uint8 result = CB_SUCCESS;
    
    if (buffer != NULL && object != NULL)
    {
        if (buffer->list == NULL)
        {
            CL_LIST *list = malloc(sizeof(*list));
            
            if (list != NULL)
            {
                list->count = 0;
                list->list = NULL;
                
                buffer->list = list;
            }
            else
            {
                result = CB_NO_MEMORY;
            }
        }
        
        if (result == CB_SUCCESS)
        {
            result = cl_add_after(buffer->list, tag, object);
            
            if (result == CL_SUCCESS)
            {
                cl_move_forward(buffer->list, 1);
                
                if ((buffer->limit != 0) &&
                    (buffer->list->count > buffer->limit))
                {
                    cl_move_forward(buffer->list, 1);
                    cl_remove_current(buffer->list, NULL);
                }
            }
        }
    }
    else
    {
        result = CB_BAD_ARGUMENT;
    }
    
    return result;
}

uint8 cb_remove_old(CB_LIST *buffer, void **object)
{
    uint8 result = CB_BAD_ARGUMENT;
    
    if (buffer != NULL)
    {
        if (buffer->list != NULL)
        {
            cl_move_forward(buffer->list, 1);
            cl_remove_current(buffer->list, object);
            
            if (buffer->list->list == NULL)
            {
                free(buffer->list);
                buffer->list = NULL;
            }
            
            result = CB_SUCCESS;
        }
        else
        {
            result = CB_EMPTY;
        }
    }
    
    return result;
}

uint8 cb_get_old_object(CB_LIST *buffer, uint16 *tag, void **object)
{
    uint8 result = CB_BAD_ARGUMENT;
    
    if (buffer != NULL && object != NULL)
    {
        if (buffer->list != NULL)
        {
            cl_move_forward(buffer->list, 1);
            result = cl_get_current_object(buffer->list, tag, object);
            cl_move_backward(buffer->list, 1);
        }
        else
        {
            result = CB_EMPTY;
        }
    }
    
    return result;
}

uint8 cb_get_new_object(CB_LIST *buffer, uint16 *tag, void **object)
{
    uint8 result = CB_BAD_ARGUMENT;
    
    if (buffer != NULL && object != NULL)
    {
        if (buffer->list != NULL)
        {
            result = cl_get_current_object(buffer->list, tag, object);
        }
        else
        {
            result = CB_EMPTY;
        }
    }
    
    return result;
}

uint32 cb_get_count(CB_LIST *buffer)
{
    uint32 count = 0;
    
    if (buffer != NULL)
    {
        if (buffer->list != NULL)
        {
            count = cl_get_count(buffer->list);
        }
    }
    
    return count;
}

uint32 cb_get_limit(CB_LIST *buffer)
{
    uint32 limit = 0;
    
    if (buffer != NULL)
    {
        limit = buffer->limit;
    }
    
    return limit;
}

uint8 cb_set_limit(CB_LIST *buffer, uint32 limit)
{
    uint8 result = CB_BAD_ARGUMENT;
    
    if (buffer != NULL)
    {
        buffer->limit = limit;
        
        result = CB_SUCCESS;
    }
    
    return result;
}

uint8 cb_destroy(CB_LIST *buffer)
{
    uint8 result = CB_BAD_ARGUMENT;
    
    if (buffer != NULL)
    {
        while (cb_get_count(buffer) > 0)
        {
            cb_remove_old(buffer, NULL);
        }
        
        result = CB_SUCCESS;
    }
    
    return result;
}

/****************************************************************************
 *  Local Functions
 ****************************************************************************/

/****************************************************************************
 *  End of File
 ****************************************************************************/
