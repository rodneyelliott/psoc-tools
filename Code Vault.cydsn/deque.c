/****************************************************************************
 *
 *  File:           deque.c
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
/**
 *  @file deque.c
 *  @brief Deque library implementation.
 */
 
/****************************************************************************
 *  Modules
 ****************************************************************************/
#include <device.h>

#include "deque.h"
#include "dllist.h"

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
uint8 de_add_first(DE_LIST *deque, uint16 tag, void *object)
{
    uint8 result = DE_BAD_ARGUMENT;
    
    if (deque != NULL && object != NULL)
    {
        if ((deque->limit == 0) ||
            (deque->limit > 0 && deque->count < deque->limit))
        {
            result = dl_add_first(&deque->list, tag, object);
            
            if (result == DL_SUCCESS)
            {
                ++deque->count;
            }
        }
        else
        {
            result = DE_FULL;
        }
    }
    
    return result;
}

uint8 de_add_last(DE_LIST *deque, uint16 tag, void *object)
{
    uint8 result = DE_BAD_ARGUMENT;
    
    if (deque != NULL && object != NULL)
    {
        if ((deque->limit == 0) ||
            (deque->limit > 0 && deque->count < deque->limit))
        {
            result = dl_add_last(&deque->list, tag, object);
            
            if (result == DL_SUCCESS)
            {
                ++deque->count;
            }
        }
        else
        {
            result = DE_FULL;
        }
    }
    
    return result;
}

uint8 de_remove_first(DE_LIST *deque, void **object)
{
    DL_LIST *first_node;
    DL_LIST *next_node;
    uint8 result = DE_SUCCESS;

    if (deque != NULL)
    {
        if (deque->count > 0)
        {
            first_node = dl_get_first(deque->list);
            next_node = dl_get_next(first_node);
            
            if (object != NULL)
            {
                result = dl_get_object(first_node, NULL, object);
            }
        
            if (result == DL_SUCCESS)
            {
                deque->list = next_node;
            
                dl_delete(first_node);
            
                --deque->count;
            }
        }
        else
        {
            result = DE_EMPTY;
        }
    }
    else
    {
        result = DE_BAD_ARGUMENT;
    }
    
    return result;
}

uint8 de_remove_last(DE_LIST *deque, void **object)
{
    DL_LIST *last_node;
    DL_LIST *previous_node;
    uint8 result = DE_SUCCESS;

    if (deque != NULL)
    {
        if (deque->count > 0)
        {
            last_node = dl_get_last(deque->list);
            previous_node = dl_get_previous(last_node);
            
            if (object != NULL)
            {
                result = dl_get_object(last_node, NULL, object);
            }
        
            if (result == DL_SUCCESS)
            {
                deque->list = previous_node;
            
                dl_delete(last_node);
            
                --deque->count;
            }
        }
        else
        {
            result = DE_EMPTY;
        }
    }
    else
    {
        result = DE_BAD_ARGUMENT;
    }
    
    return result;
}

uint8 de_get_first_object(DE_LIST *deque, uint16 *tag, void **object)
{
    uint8 result = DE_BAD_ARGUMENT;

    if (deque != NULL)
    {
        if (deque->count > 0)
        {
            result = dl_get_object(dl_get_first(deque->list), tag, object);
        }
        else
        {
            result = DE_EMPTY;
        }
    }
    
    return result;
}

uint8 de_get_last_object(DE_LIST *deque, uint16 *tag, void **object)
{
    uint8 result = DE_BAD_ARGUMENT;

    if (deque != NULL)
    {
        if (deque->count > 0)
        {
            result = dl_get_object(dl_get_last(deque->list), tag, object);
        }
        else
        {
            result = DE_EMPTY;
        }
    }
    
    return result;
}

uint32 de_get_count(DE_LIST *deque)
{
    uint32 count = 0;
    
    if (deque != NULL)
    {
        count = deque->count;
    }
    
    return count;
}

uint32 de_get_limit(DE_LIST *deque)
{
    uint32 limit = 0;
    
    if (deque != NULL)
    {
        limit = deque->limit;
    }
    
    return limit;
}

uint8 de_set_limit(DE_LIST *deque, uint32 limit)
{
    uint8 result = DE_BAD_ARGUMENT;
    
    if (deque != NULL)
    {
        if ((deque->count > limit) && (limit != 0))
        {
            result = DE_FAILURE;
        }
        else
        {
            deque->limit = limit;
        
            result = DE_SUCCESS;
        }
    }
    
    return result;
}

uint8 de_destroy(DE_LIST *deque)
{
    uint8 result = DE_BAD_ARGUMENT;
    
    if (deque != NULL)
    {
        while (de_get_count(deque) > 0)
        {
            de_remove_first(deque, NULL);
        }
        
        result = DE_SUCCESS;
    }
    
    return result;
}

/****************************************************************************
 *  Local Functions
 ****************************************************************************/

/****************************************************************************
 *  End of File
 ****************************************************************************/
