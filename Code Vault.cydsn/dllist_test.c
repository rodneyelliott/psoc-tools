/****************************************************************************
 *
 *  File:           dllist_test.c
 *  Module:         Doubly Linked List Test Library
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
 *  @file dllist_test.c
 *  @brief Doubly linked list test library implementation.
 */

/****************************************************************************
 *  Modules
 ****************************************************************************/
#include <device.h>
#include <stdlib.h>

#include "dllist.h"
#include "dllist_test.h"

/****************************************************************************
 *  Definitions and Macros
 ****************************************************************************/
/**
 *  @brief Cypress CY8CKIT-001 development kit serial RX output pin.
 */
#define _CY8CKIT_RX                     CYREG_PRT1_PC2

/**
 *  @brief Cypress CY8CKIT-001 development kit serial TX output pin.
 */
#define _CY8CKIT_TX                     CYREG_PRT1_PC7

/**
 *  @brief The DLL test library object tag.
 */
#define _TAG                            200

/****************************************************************************
 *  Typedefs and Structures
 ****************************************************************************/

/****************************************************************************
 *  Prototypes of Local Functions
 ****************************************************************************/
/**
 *  @brief Create a new test object.
 *  @param[in] string A pointer to an ASCII string.
 *  @param[in] number The object identification number.
 *  @param[out] object A pointer to a pointer to the newly created object.
 *  @return #DLT_SUCCESS if successful, otherwise #DLT_NO_MEMORY.
 */
static uint8 _create_object(char *string, uint8 number, DLT_OBJECT **object);

/**
 *  @brief Destroy a test object.
 *  @param[in] object A pointer to a test object.
 */
static void _destroy_object(DLT_OBJECT *object);

/**
 *  @brief Walk a DLL, displaying test object ASCII strings.
 *  @param[in] list A pointer to a DLL.
 */
static void _walk_list(DL_LIST *list);

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/

/****************************************************************************
 *  Global Variables
 ****************************************************************************/

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
uint8 dlt_test_1(void)
{
    DL_LIST *list_1 = NULL;
    DL_LIST *list_2 = NULL;
    DL_LIST *list_3 = NULL;
    DL_LIST *list_4 = NULL;
    DL_LIST *node_1;
    DL_LIST *node_2;
    DL_LIST *node_3;
    DL_LIST *node_4;
    DL_LIST *node_5;
    DLT_OBJECT *object_0;
    DLT_OBJECT *object_1;
    DLT_OBJECT *object_2;
    DLT_OBJECT *object_3;
    DLT_OBJECT *object_4;
    DLT_OBJECT *object_5;
    DLT_OBJECT *object_6;
    DLT_OBJECT *object_7;
    DLT_OBJECT *object_8;
    DLT_OBJECT *object_9;
    uint8 result = DLT_SUCCESS;
    uint16 tag_0;
    
    UART_1_Start();
    
    UART_1_PutString("\x1b\x5b\x32\x4a");
    UART_1_PutString("DOUBLY LINKED LIST LIBRARY TEST\r\n");
    UART_1_PutString("\r\n");
    UART_1_PutString("Test\tFunction\t\tResult\r\n");
    UART_1_PutString("----\t--------\t\t------\r\n");
    
    /*
     *  Initialise dl_create() test.
     */
    if (result == DLT_SUCCESS)
    {
        if (_create_object("one", 1, &object_1) == DLT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    /*
     *  Test dl_create().
     */
    if (result == DLT_SUCCESS)
    {
        if (dl_create(NULL, _TAG, NULL) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("   1\tdl_create()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   1\tdl_create()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }    
    
    if (result == DLT_SUCCESS)
    {
        if (dl_create(NULL, _TAG, object_1) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("   2\tdl_create()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   2\tdl_create()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {    
        if (dl_create(&node_1, _TAG, NULL) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("   3\tdl_create()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   3\tdl_create()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_create(&node_1, _TAG, object_1) == DL_SUCCESS)
        {
            UART_1_PutString("   4\tdl_create()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   4\tdl_create()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    /*
     *  Initialise dl_insert_before() test.
     */
    if (result == DLT_SUCCESS)
    {
        if (_create_object("two", 2, &object_2) == DLT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
        
    if (result == DLT_SUCCESS)
    {
        if (_create_object("three", 3, &object_3) == DLT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_create(&node_2, _TAG, object_2) == DL_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_create(&node_3, _TAG, object_3) == DL_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
        
    /*
     *  Test dl_insert_before().
     */
    if (result == DLT_SUCCESS)
    {
        if (dl_insert_before(NULL, NULL) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("   5\tdl_insert_before()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   5\tdl_insert_before()\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_insert_before(NULL, node_1) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("   6\tdl_insert_before()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   6\tdl_insert_before()\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_insert_before(node_3, NULL) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("   7\tdl_insert_before()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   7\tdl_insert_before()\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_insert_before(node_3, node_1) == DL_SUCCESS)
        {
            UART_1_PutString("   8\tdl_insert_before()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   8\tdl_insert_before()\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_insert_before(node_3, node_2) == DL_SUCCESS)
        {
            UART_1_PutString("   9\tdl_insert_before()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   9\tdl_insert_before()\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    /*
     *  Initialise dl_insert_after() test.
     */
    if (result == DLT_SUCCESS)
    {
        if (_create_object("four", 4, &object_4) == DLT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
        
    if (result == DLT_SUCCESS)
    {
        if (_create_object("five", 5, &object_5) == DLT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_create(&node_4, _TAG, object_4) == DL_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_create(&node_5, _TAG, object_5) == DL_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
        
    /*
     *  Test dl_insert_after().
     */
    if (result == DLT_SUCCESS)
    {
        if (dl_insert_after(NULL, NULL) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  10\tdl_insert_after()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  10\tdl_insert_after()\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_insert_after(NULL, node_5) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  11\tdl_insert_after()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  11\tdl_insert_after()\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_insert_after(node_3, NULL) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  12\tdl_insert_after()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  12\tdl_insert_after()\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_insert_after(node_3, node_5) == DL_SUCCESS)
        {
            UART_1_PutString("  13\tdl_insert_after()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  13\tdl_insert_after()\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_insert_after(node_3, node_4) == DL_SUCCESS)
        {
            UART_1_PutString("  14\tdl_insert_after()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  14\tdl_insert_after()\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    /*
     *  Test dl_get_first().
     */
    if (result == DLT_SUCCESS)
    {
        if (dl_get_first(NULL) == NULL)
        {
            UART_1_PutString("  15\tdl_get_first()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  15\tdl_get_first()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_get_first(node_3) == node_1)
        {
            UART_1_PutString("  16\tdl_get_first()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  16\tdl_get_first()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    /*
     *  Initialise dl_add_first() test.
     */
    if (result == DLT_SUCCESS)
    {
        if (_create_object("six", 6, &object_6) == DLT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (_create_object("seven", 7, &object_7) == DLT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    /*
     *  Test dl_add_first().
     */
    if (result == DLT_SUCCESS)
    {
        if (dl_add_first(NULL, _TAG, NULL) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  17\tdl_add_first()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  17\tdl_add_first()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_add_first(NULL, _TAG, object_7) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  18\tdl_add_first()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  18\tdl_add_first()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_add_first(&list_1, _TAG, NULL) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  19\tdl_add_first()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  19\tdl_add_first()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_add_first(&list_1, _TAG, object_7) == DL_SUCCESS)
        {
            UART_1_PutString("  20\tdl_add_first()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  20\tdl_add_first()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_add_first(&list_1, _TAG, object_6) == DL_SUCCESS)
        {
            UART_1_PutString("  21\tdl_add_first()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  21\tdl_add_first()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    /*
     *  Test dl_get_last().
     */
    if (result == DLT_SUCCESS)
    {
        if (dl_get_last(NULL) == NULL)
        {
            UART_1_PutString("  22\tdl_get_last()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  22\tdl_get_last()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_get_last(node_3) == node_5)
        {
            UART_1_PutString("  23\tdl_get_last()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  23\tdl_get_last()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    /*
     *  Initialise dl_add_last() test.
     */
    if (result == DLT_SUCCESS)
    {
        if (_create_object("eight", 8, &object_8) == DLT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (_create_object("nine", 9, &object_9) == DLT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    /*
     *  Test dl_add_last().
     */
    if (result == DLT_SUCCESS)
    {
        if (dl_add_last(NULL, _TAG, NULL) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  24\tdl_add_last()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  24\tdl_add_last()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_add_last(NULL, _TAG, object_8) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  25\tdl_add_last()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  25\tdl_add_last()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_add_last(&list_2, _TAG, NULL) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  26\tdl_add_last()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  26\tdl_add_last()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_add_last(&list_2, _TAG, object_8) == DL_SUCCESS)
        {
            UART_1_PutString("  27\tdl_add_last()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  27\tdl_add_last()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_add_last(&list_2, _TAG, object_9) == DL_SUCCESS)
        {
            UART_1_PutString("  28\tdl_add_last()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  28\tdl_add_last()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    /*
     *  Test dl_get_previous().
     */
    if (result == DLT_SUCCESS)
    {
        if (dl_get_previous(NULL) == NULL)
        {
            UART_1_PutString("  29\tdl_get_previous()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  29\tdl_get_previous()\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_get_previous(node_3) == node_2)
        {
            UART_1_PutString("  30\tdl_get_previous()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  30\tdl_get_previous()\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    /*
     *  Test dl_add_before().
     */
    if (result == DLT_SUCCESS)
    {
        if (dl_add_before(NULL, _TAG, NULL) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  31\tdl_add_before()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  31\tdl_add_before()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_add_before(NULL, _TAG, object_2) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  32\tdl_add_before()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  32\tdl_add_before()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_add_before(&list_3, _TAG, NULL) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  33\tdl_add_before()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  33\tdl_add_before()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_add_before(&list_3, _TAG, object_2) == DL_SUCCESS)
        {
            UART_1_PutString("  34\tdl_add_before()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  34\tdl_add_before()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_add_before(&list_3, _TAG, object_1) == DL_SUCCESS)
        {
            UART_1_PutString("  35\tdl_add_before()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  35\tdl_add_before()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    /*
     *  Test dl_get_next().
     */
    if (result == DLT_SUCCESS)
    {
        if (dl_get_next(NULL) == NULL)
        {
            UART_1_PutString("  36\tdl_get_next()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  36\tdl_get_next()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_get_next(node_3) == node_4)
        {
            UART_1_PutString("  37\tdl_get_next()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  37\tdl_get_next()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    /*
     *  Test dl_add_after().
     */
    if (result == DLT_SUCCESS)
    {
        if (dl_add_after(NULL, _TAG, NULL) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  38\tdl_add_after()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  38\tdl_add_after()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_add_after(NULL, _TAG, object_3) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  39\tdl_add_after()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  39\tdl_add_after()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_add_after(&list_4, _TAG, NULL) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  40\tdl_add_after()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  40\tdl_add_after()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_add_after(&list_4, _TAG, object_3) == DL_SUCCESS)
        {
            UART_1_PutString("  41\tdl_add_after()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  41\tdl_add_after()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_add_after(&list_4, _TAG, object_4) == DL_SUCCESS)
        {
            UART_1_PutString("  42\tdl_add_after()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  42\tdl_add_after()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    /*
     *  Test dl_get_count().
     */
    if (result == DLT_SUCCESS)
    {
        if (dl_get_count(NULL) == 0)
        {
            UART_1_PutString("  43\tdl_get_count()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  43\tdl_get_count()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_get_count(node_3) == 5)
        {
            UART_1_PutString("  44\tdl_get_count()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  44\tdl_get_count()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    /*
     *  Test dl_get_object().
     */
    if (result == DLT_SUCCESS)
    {
        if (dl_get_object(NULL, NULL, NULL) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  45\tdl_get_object()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  45\tdl_get_object()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_get_object(NULL, NULL, (void **)&object_0) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  46\tdl_get_object()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  46\tdl_get_object()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_get_object(node_3, NULL, NULL) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  47\tdl_get_object()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  47\tdl_get_object()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_get_object(node_3, NULL, (void **)&object_0) == DL_SUCCESS)
        {
            UART_1_PutString("  48\tdl_get_object()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  48\tdl_get_object()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (object_0->number == 3)
        {
            UART_1_PutString("  49\tdl_get_object()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  49\tdl_get_object()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_get_object(node_3, &tag_0, (void **)&object_0) == DL_SUCCESS)
        {
            UART_1_PutString("  50\tdl_get_object()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  50\tdl_get_object()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (tag_0 == 200)
        {
            UART_1_PutString("  51\tdl_get_object()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  51\tdl_get_object()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    /*
     *  Test dl_extract().
     */
    if (result == DLT_SUCCESS)
    {
        if (dl_extract(NULL) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  52\tdl_extract()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  52\tdl_extract()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_extract(node_4) == DL_SUCCESS)
        {
            UART_1_PutString("  53\tdl_extract()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  53\tdl_extract()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    /*
     *  Test dl_delete().
     */
    if (result == DLT_SUCCESS)
    {
        if (dl_delete(NULL) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  54\tdl_delete()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  54\tdl_delete()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_delete(node_5) == DL_SUCCESS)
        {
            UART_1_PutString("  55\tdl_delete()\t\tPASS\r\n");
            node_5 = NULL;
        }
        else
        {
            UART_1_PutString("  55\tdl_delete()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    /*
     *  Test dl_destroy().
     */
    if (result == DLT_SUCCESS)
    {
        if (dl_destroy(NULL) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  56\tdl_destroy()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  56\tdl_destroy()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_destroy(&node_2) == DL_SUCCESS)
        {
            UART_1_PutString("  57\tdl_destroy()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  57\tdl_destroy()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (node_2 == NULL)
        {
            UART_1_PutString("  58\tdl_destroy()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  58\tdl_destroy()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    /*
     *  Test dl_join().
     */
    if (result == DLT_SUCCESS)
    {
        if (dl_join(NULL, NULL) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  59\tdl_join()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  59\tdl_join()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_join(NULL, list_2) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  60\tdl_join()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  60\tdl_join()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_join(list_1, NULL) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  61\tdl_join()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  61\tdl_join()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_join(list_1, list_2) == DL_SUCCESS)
        {
            UART_1_PutString("  62\tdl_join()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  62\tdl_join()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    /*
     *  Initialise dl_exchange() test.
     */
    if (result == DLT_SUCCESS)
    {
        if (dl_join(list_3, list_4) == DL_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_add_last(&list_4, _TAG, object_5) == DL_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_join(list_4, list_1) == DL_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        node_1 = dl_get_first(list_1);
        node_2 = list_3;
        node_3 = list_4;
    }
        
    /*
     *  Test dl_exchange().
     */
    if (result == DLT_SUCCESS)
    {
        if (dl_exchange(NULL, NULL) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  63\tdl_exchange()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  63\tdl_exchange()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_exchange(NULL, node_2) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  64\tdl_exchange()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  64\tdl_exchange()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_exchange(node_1, NULL) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  65\tdl_exchange()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  65\tdl_exchange()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_exchange(node_1, node_2) == DL_SUCCESS)
        {
            UART_1_PutString("  66\tdl_exchange()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  66\tdl_exchange()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_exchange(node_1, node_2) == DL_SUCCESS)
        {
            UART_1_PutString("  67\tdl_exchange()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  67\tdl_exchange()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_exchange(node_1, node_3) == DL_SUCCESS)
        {
            UART_1_PutString("  68\tdl_exchange()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  68\tdl_exchange()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_exchange(node_1, node_3) == DL_SUCCESS)
        {
            UART_1_PutString("  69\tdl_exchange()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  69\tdl_exchange()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    /*
     *  Test dl_update().
     */
    if (result == DLT_SUCCESS)
    {
        if (dl_update(NULL, _TAG, NULL) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  70\tdl_update()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  70\tdl_update()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_update(NULL, _TAG, object_1) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  71\tdl_update()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  71\tdl_update()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_update(&node_5, _TAG, NULL) == DL_BAD_ARGUMENT)
        {
            UART_1_PutString("  72\tdl_update()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  72\tdl_update()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        if (dl_update(&node_5, _TAG, object_1) == DL_SUCCESS)
        {
            UART_1_PutString("  73\tdl_update()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  73\tdl_update()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    if (result == DLT_SUCCESS)
    {
        object_0 = node_5->object;
        
        if (object_0->number == 1)
        {
            UART_1_PutString("  74\tdl_update()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  74\tdl_update()\t\tFAIL\r\n");
            result = DLT_FAILURE;
        }
    }
    
    /*
     *  Report test result.
     */
    if (result == DLT_SUCCESS)
    {
        UART_1_PutString("\r\n");
        UART_1_PutString("TEST PASSED\r\n");
    }
    else
    {
        UART_1_PutString("\r\n");
        UART_1_PutString("TEST FAILED\r\n");
    }
        
    /*
     *  Clean-up test.
     */
    _destroy_object(object_1);
    _destroy_object(object_2);
    _destroy_object(object_3);
    _destroy_object(object_4);
    _destroy_object(object_5);
    _destroy_object(object_6);
    _destroy_object(object_7);
    _destroy_object(object_8);
    _destroy_object(object_9);
    
    dl_delete(node_4);
    dl_destroy(&list_1);
    
    while ((UART_1_ReadTxStatus() & UART_1_TX_STS_FIFO_EMPTY) !=
        UART_1_TX_STS_FIFO_EMPTY)
    {
        CyDelay(1);
    }
    
    UART_1_Stop();
    
    return result;
}

/****************************************************************************
 *  Local Functions
 ****************************************************************************/
uint8 _create_object(char *string, uint8 number, DLT_OBJECT **object)
{
    DLT_OBJECT *new_object;
    uint8 result = DLT_NO_MEMORY;
    char *new_string;
    
    new_object = malloc(sizeof(*new_object));
        
    if (new_object != NULL)
    {
        new_object->number = number;
        
        new_string = malloc(strlen(string) + 1);
        
        if (new_string != NULL)
        {
            strcpy(new_string, string);
            new_object->string = new_string;
            
            *object = new_object;
            
            result = DLT_SUCCESS;
        }
        else
        {
            free(new_object);
        }
    }
    
    return result;
}

void _destroy_object(DLT_OBJECT *object)
{   
    free(object->string);
    free(object);
}

void _walk_list(DL_LIST *list)
{
    DL_LIST *node;
    DLT_OBJECT *object;
        
    for (node = dl_get_first(list) ; node != NULL ; node = node->next)
    {
        object = (DLT_OBJECT *)node->object;
        
        UART_1_PutString(object->string);
        UART_1_PutString("\r\n");
    }
}

/****************************************************************************
 *  End of File
 ****************************************************************************/
