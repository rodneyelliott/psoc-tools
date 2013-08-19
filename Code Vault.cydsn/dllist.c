/****************************************************************************
 *
 *  File:           dllist.c
 *  Module:         Doubly Linked List Library
 *  Project:        Code Vault
 *  Workspace:      PSoC Tools
 *
 *  Author:         Rodney B. Elliott
 *  Date:           20 August 2013
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
 *  @file dllist.c
 *  @brief Doubly linked list library implementation.
 */

/****************************************************************************
 *  Modules
 ****************************************************************************/
#include <device.h>
#include <stdlib.h>

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
uint8 dl_create(uint16 tag, void *object, DL_LIST **node)
{
    DL_LIST *new_node;
    uint8 result = DL_BAD_ARGUMENT;
    
    if (object != NULL && node != NULL)
    {
        new_node = malloc(sizeof(*new_node));
    
        if (new_node != NULL)
        {
            new_node->previous = NULL;
            new_node->next = NULL;
            new_node->tag = tag;
            new_node->object = object;
            
            *node = new_node;
            
            result = DL_SUCCESS;
        }
        else
        {
            *node = NULL;
            
            result = DL_NO_MEMORY;
        }
    }
    
    return result;
}

uint8 dl_insert_before(DL_LIST *node, DL_LIST *new_node)
{
    uint8 result = DL_BAD_ARGUMENT;
    
    if (node != NULL && new_node != NULL)
    {
        new_node->next = node;
        new_node->previous = node->previous;
        
        node->previous = new_node;

        if (new_node->previous != NULL)
        {
            new_node->previous->next = new_node;
        }
        
        result = DL_SUCCESS;
    }
    
    return result;
}

uint8 dl_insert_after(DL_LIST *node, DL_LIST *new_node)
{
    uint8 result = DL_BAD_ARGUMENT;
    
    if (node != NULL && new_node != NULL)
    {
        new_node->previous = node;
        new_node->next = node->next;
        
        node->next = new_node;
        
        if (new_node->next != NULL)
        {
            new_node->next->previous = new_node;
        }
        
        result = DL_SUCCESS;
    }
    
    return result;
}

DL_LIST *dl_get_first(DL_LIST *list)
{
    if (list != NULL)
    {
        while (list->previous != NULL)
        {
            list = list->previous;
        }
    }
    
    return list;
}

uint8 dl_add_first(DL_LIST **list, uint16 tag, void *object)
{ 
    DL_LIST *first_node;
    DL_LIST *new_node;
    uint8 result = DL_BAD_ARGUMENT;
 
    if (list != NULL)
    {
        result = dl_create(tag, object, &new_node);
        
        if (result == DL_SUCCESS)
        {
            if (*list == NULL)
            {
                *list = new_node;
            }
            else
            {
                first_node = dl_get_first(*list);
                dl_insert_before(first_node, new_node);
            }
        }
    }

    return result;
}

DL_LIST *dl_get_last(DL_LIST *list)
{
    if (list != NULL)
    {
        while (list->next != NULL)
        {
            list = list->next;
        }
    }
    
    return list;
}

uint8 dl_add_last(DL_LIST **list, uint16 tag, void *object)
{
    DL_LIST *last_node;
    DL_LIST *new_node;
    uint8 result = DL_BAD_ARGUMENT;

    if (list != NULL)
    {
        result = dl_create(tag, object, &new_node);
        
        if (result == DL_SUCCESS)
        {
            if (*list == NULL)
            {
                *list = new_node;
            }
            else
            {
                last_node = dl_get_last(*list);
                dl_insert_after(last_node, new_node);
            }
        }
    }

    return result;
}

DL_LIST *dl_get_previous(DL_LIST *node)
{
    if (node != NULL)
    {
        node = node->previous;
    }

    return node;
}

uint8 dl_add_before(DL_LIST **node, uint16 tag, void *object)
{
    DL_LIST *new_node;
    uint8 result = DL_BAD_ARGUMENT;
    
    if (node != NULL)
    {
        result = dl_create(tag, object, &new_node);
        
        if (result == DL_SUCCESS)
        {
            if (*node == NULL)
            {
                *node = new_node;
            }
            else
            {
                dl_insert_before(*node, new_node);
            }
        }
    }
    
    return result;
}

DL_LIST *dl_get_next(DL_LIST *node)
{
    if (node != NULL)
    {
        node = node->next;
    }

    return node;
}

uint8 dl_add_after(DL_LIST **node, uint16 tag, void *object)
{
    DL_LIST *new_node;
    uint8 result = DL_BAD_ARGUMENT;
    
    if (node != NULL)
    {
        result = dl_create(tag, object, &new_node);
        
        if (result == DL_SUCCESS)
        {
            if (*node == NULL)
            {
                *node = new_node;
            }
            else
            {
                dl_insert_after(*node, new_node);
            }
        }
    }
    
    return result;
}

uint32 dl_get_count(DL_LIST *list)
{
    uint32 count = 0;
    DL_LIST *next_node = list;    
    DL_LIST *previous_node = list;

    if (list != NULL)
    {
        ++count;
        
        while ((previous_node = dl_get_previous(previous_node)) != NULL)
        {
            ++count;
        }
        
        while ((next_node = dl_get_next(next_node)) != NULL)
        {
            ++count;
        }
    }
    
    return count;
}

uint8 dl_get_object(DL_LIST *node, uint16 *tag, void **object)
{
    uint8 result = DL_BAD_ARGUMENT;
    
    if (node != NULL && object != NULL)
    {
        *object = node->object;
        
        if (tag != NULL)
        {
            *tag = node->tag;
        }
        
        result = DL_SUCCESS;
    }
    
    return result;
}

uint8 dl_extract(DL_LIST *node)
{
    uint8 result = DL_BAD_ARGUMENT;
    
    if (node != NULL)
    {
        if (node->previous != NULL)
        {
            node->previous->next = node->next;
        }
        
        if (node->next != NULL)
        {
            node->next->previous = node->previous;
        }
        
        node->previous = NULL;
        node->next = NULL;
        
        result = DL_SUCCESS;
    }
    
    return result;
}

uint8 dl_delete(DL_LIST *node)
{
    uint8 result = dl_extract(node);
    
    if (result == DL_SUCCESS)
    {
        free(node);
    }
    
    return result;
}

uint8 dl_destroy(DL_LIST **list)
{
    DL_LIST *marker;
    DL_LIST *next_node;    
    DL_LIST *previous_node;
    uint8 result = DL_BAD_ARGUMENT;

    if (list != NULL)
    {
        if (*list != NULL)
        {
            previous_node = (*list)->previous;
            
            while (previous_node != NULL)
            {
                marker = previous_node->previous;
                dl_delete(previous_node);
                previous_node = marker;
            }

            next_node = *list;
            
            do
            {
                marker = next_node->next;
                dl_delete(next_node);
                next_node = marker;
            } while (next_node != NULL);
            
            *list = NULL;
            
            result = DL_SUCCESS;
        }
    }
    
    return result;
}

uint8 dl_join(DL_LIST *list_a, DL_LIST *list_b)
{
    uint8 result = DL_BAD_ARGUMENT;
    
    if (list_a != NULL && list_b != NULL)
    {
        list_a = dl_get_last(list_a);
        list_b = dl_get_first(list_b);

        list_a->next = list_b;
        list_b->previous = list_a;
        
        result = DL_SUCCESS;
    }
    
    return result;
}

uint8 dl_exchange(DL_LIST *node_a, DL_LIST *node_b)
{
    uint8 result = DL_BAD_ARGUMENT;
    DL_LIST *t_0;
    DL_LIST *t_1;
    DL_LIST *t_2;
    DL_LIST *t_3;

    if (node_a != NULL && node_b != NULL)
    {
        if (node_a->next == node_b)
        {
            dl_extract(node_a);
            dl_insert_after(node_b, node_a);
        }
        else if (node_b->next == node_a)
        {
            dl_extract(node_b);
            dl_insert_after(node_a, node_b);
        }
        else
        {
            t_0 = node_a->previous;
            t_1 = node_a->next;
            t_2 = node_b->previous;
            t_3 = node_b->next;

            dl_extract(node_a);
            dl_extract(node_b);

            if (t_2 != NULL)
            {
                dl_insert_after(t_2, node_a);
            }
            else
            {
                dl_insert_before(t_3, node_a);
            }

            if (t_0 != NULL)
            {
                dl_insert_after(t_0, node_b);
            }
            else
            {
                dl_insert_before(t_1, node_b);
            }
        }
        
        result = DL_SUCCESS;
    }
    
    return result;
}

uint8 dl_update(DL_LIST **node, uint16 new_tag, void *new_object)
{
    DL_LIST *new_node;
    uint8 result = DL_BAD_ARGUMENT;
    
    if (node != NULL)
    {
        result = dl_create(new_tag, new_object, &new_node);
        
        if (result == DL_SUCCESS)
        {
            if (*node != NULL)
            {
                dl_insert_before(*node, new_node);
                dl_delete(*node);
                *node = new_node;
            }
            else
            {
                *node = new_node;
            }
        }
    }
    
    return result;
}

/****************************************************************************
 *  Local Functions
 ****************************************************************************/

/****************************************************************************
 *  End of File
 ****************************************************************************/
