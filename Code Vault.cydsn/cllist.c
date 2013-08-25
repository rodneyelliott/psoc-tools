/****************************************************************************
 *
 *  File:           cllist.c
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
/**
 *  @file cllist.c
 *  @brief Circular linked list library implementation.
 */
 
/****************************************************************************
 *  Modules
 ****************************************************************************/
#include <device.h>
#include <stdlib.h>

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
uint8 cl_add_after(CL_LIST *list, uint16 tag, void *object)
{
    DL_LIST *new_node;
    uint8 result = CL_BAD_ARGUMENT;
    
    if (list != NULL)
    {
        result = dl_create(tag, object, &new_node);
        
        if (result == DL_SUCCESS)
        {
            if (list->count == 0)
            {
                list->list = new_node;
                list->list->previous = new_node;
                list->list->next = new_node;
            }
            else
            {
                new_node->previous = list->list;
                new_node->next = list->list->next;
                list->list->next = new_node;
                new_node->next->previous = new_node;
            }
        
            ++list->count;
        }
    }
    
    return result;
}

uint8 cl_add_before(CL_LIST *list, uint16 tag, void *object)
{
    DL_LIST *new_node;
    uint8 result = CL_BAD_ARGUMENT;
    
    if (list != NULL)
    {
        result = dl_create(tag, object, &new_node);
        
        if (result == DL_SUCCESS)
        {
            if (list->count == 0)
            {
                list->list = new_node;
                list->list->previous = new_node;
                list->list->next = new_node;
            }
            else
            {
                new_node->previous = list->list->previous;
                new_node->next = list->list;
                list->list->previous->next = new_node;
                list->list->previous = new_node;
            }
        
            ++list->count;
        }
    }
    
    return result;
}

uint8 cl_remove_current(CL_LIST *list, void **object)
{
    DL_LIST *current_node;
    DL_LIST *next_node;
    DL_LIST *previous_node;
    uint8 result = CL_BAD_ARGUMENT;
    
    if (list != NULL)
    {
        if (list->count > 0)
        {
            current_node = list->list;
            previous_node = current_node->previous;
            next_node = current_node->next;
            
            if (list->count == 1)
            {
                list->list = NULL;
            }
            else
            {
                list->list = previous_node;
                next_node->previous = previous_node;
                previous_node->next = next_node;
            }
            
            if (object != NULL)
            {
                *object = current_node->object;
            }
            
            free(current_node);
            
            --list->count;
            
            result = CL_SUCCESS;
        }
        else
        {
            result = CL_EMPTY;
        }
    }
    
    return result;
}

uint8 cl_move_forward(CL_LIST *list, uint32 places)
{
    uint32 i;
    uint8 result = CL_BAD_ARGUMENT;
    
    if (list != NULL)
    {
        if (list->count > 0)
        {
            if (places > list->count / 2)
            {
                places = list->count - places;
                
                for (i = 0 ; i < places ; i++)
                {
                    list->list = list->list->previous;
                }
            }
            else
            {
                for (i = 0 ; i < places ; i++)
                {
                    list->list = list->list->next;
                }
            }
            
            result = CL_SUCCESS;
        }
        else
        {
            result = CL_EMPTY;
        }
    }
    
    return result;
}

uint8 cl_move_backward(CL_LIST *list, uint32 places)
{
    uint32 i;
    uint8 result = CL_BAD_ARGUMENT;
    
    if (list != NULL)
    {
        if (list->count > 0)
        {
            if (places > list->count / 2)
            {
                places = list->count - places;
                
                for (i = 0 ; i < places ; i++)
                {
                    list->list = list->list->next;
                }
            }
            else
            {
                for (i = 0 ; i < places ; i++)
                {
                    list->list = list->list->previous;
                }
            }
            
            result = CL_SUCCESS;
        }
        else
        {
            result = CL_EMPTY;
        }
    }
    
    return result;
}

uint8 cl_get_current_object(CL_LIST *list, uint16 *tag, void **object)
{
    uint8 result = CL_BAD_ARGUMENT;
    
    if (list != NULL && object != NULL)
    {
        if (list->count > 0)
        {
            if (tag != NULL)
            {
                *tag = list->list->tag;
            }
            
            *object = list->list->object;
            
            result = CL_SUCCESS;
        }
        else
        {
            result = CL_EMPTY;
        }
    }
    
    return result;
}

uint32 cl_get_count(CL_LIST *list)
{
    uint32 count = 0;
    
    if (list != NULL)
    {
        count = list->count;
    }
    
    return count;
}

uint8 cl_destroy(CL_LIST *list)
{
    uint8 result = CL_BAD_ARGUMENT;
    
    if (list != NULL)
    {
        while (list->count > 0)
        {
            cl_remove_current(list, NULL);
        }
        
        result = CL_SUCCESS;
    }
    
    return result;
}

/****************************************************************************
 *  Local Functions
 ****************************************************************************/

/****************************************************************************
 *  End of File
 ****************************************************************************/
