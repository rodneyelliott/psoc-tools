/****************************************************************************
 *
 *  File:           queue.c
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
/**
 *  @file queue.c
 *  @brief Queue library implementation.
 */
 
/****************************************************************************
 *  Modules
 ****************************************************************************/
#include <device.h>

#include "queue.h"
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
uint8 qu_add_last(QU_LIST *queue, uint16 tag, void *object)
{
    uint8 result = QU_BAD_ARGUMENT;
    
    if (queue != NULL && object != NULL)
    {
        if ((queue->limit == 0) ||
            (queue->limit > 0 && queue->count < queue->limit))
        {
            result = dl_add_last(&queue->list, tag, object);
            
            if (result == DL_SUCCESS)
            {
                ++queue->count;
            }
        }
        else
        {
            result = QU_FULL;
        }
    }
    
    return result;
}

uint8 qu_remove_first(QU_LIST *queue, void **object)
{
    DL_LIST *first_node;
    DL_LIST *next_node;
    uint8 result = QU_SUCCESS;

    if (queue != NULL)
    {
        if (queue->count > 0)
        {
            first_node = dl_get_first(queue->list);
            next_node = dl_get_next(first_node);
            
            if (object != NULL)
            {
                result = dl_get_object(first_node, NULL, object);
            }
        
            if (result == DL_SUCCESS)
            {
                queue->list = next_node;
            
                dl_delete(first_node);
            
                --queue->count;
            }
        }
        else
        {
            result = QU_EMPTY;
        }
    }
    else
    {
        result = QU_BAD_ARGUMENT;
    }
    
    return result;
}

uint8 qu_get_first_object(QU_LIST *queue, uint16 *tag, void **object)
{
    uint8 result = QU_BAD_ARGUMENT;

    if (queue != NULL)
    {
        if (queue->count > 0)
        {
            result = dl_get_object(dl_get_first(queue->list), tag, object);
        }
        else
        {
            result = QU_EMPTY;
        }
    }
    
    return result;
}

uint32 qu_get_count(QU_LIST *queue)
{
    uint32 count = 0;
    
    if (queue != NULL)
    {
        count = queue->count;
    }
    
    return count;
}

uint32 qu_get_limit(QU_LIST *queue)
{
    uint32 limit = 0;
    
    if (queue != NULL)
    {
        limit = queue->limit;
    }
    
    return limit;
}

uint8 qu_set_limit(QU_LIST *queue, uint32 limit)
{
    uint8 result = QU_BAD_ARGUMENT;
    
    if (queue != NULL)
    {
        queue->limit = limit;
        
        result = QU_SUCCESS;
    }
    
    return result;
}

uint8 qu_destroy(QU_LIST *queue)
{
    uint8 result = QU_BAD_ARGUMENT;
    
    if (queue != NULL)
    {
        while (qu_get_count(queue) > 0)
        {
            qu_remove_first(queue, NULL);
        }
        
        result = QU_SUCCESS;
    }
    
    return result;
}

/****************************************************************************
 *  Local Functions
 ****************************************************************************/

/****************************************************************************
 *  End of File
 ****************************************************************************/
