/****************************************************************************
 *
 *  File:           cbuff_test.c
 *  Module:         Circular Buffer Test Library
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
 *  @file cbuff_test.c
 *  @brief Circular buffer test library implementation.
 */
 
/****************************************************************************
 *  Modules
 ****************************************************************************/
#include <device.h>
#include <stdlib.h>

#include "cbuff.h"
#include "cbuff_test.h"

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
 *  @brief The circular buffer test library object tag.
 */
 #define _TAG                           600
 
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
 *  @return #CBT_SUCCESS if successful, otherwise #CBT_NO_MEMORY.
 */
static uint8 _create_object(char *string, uint8 number, CBT_OBJECT **object);

/**
 *  @brief Destroy a test object.
 *  @param[in] object A pointer to a test object.
 */
static void _destroy_object(CBT_OBJECT *object);

/**
 *  @brief Walk a circular buffer, displaying test object ASCII strings.
 *  @param[in] buffer A pointer to a circular buffer.
 */
static void _walk_buffer(CB_LIST *buffer);

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/

/****************************************************************************
 *  Global Variables
 ****************************************************************************/

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
uint8 cbt_test_1(void)
{
    CB_LIST buffer_1 = {0};
    CB_LIST buffer_2 = {0};
    CBT_OBJECT *object_0;
    CBT_OBJECT *object_1;
    CBT_OBJECT *object_2;
    CBT_OBJECT *object_3;
    CBT_OBJECT *object_4;
    uint8 result = CBT_SUCCESS;
    uint16 tag_0;

    UART_1_Start();
    
    UART_1_PutString("\x1b\x5b\x32\x4a");
    UART_1_PutString("CIRCULAR BUFFER LIBRARY TEST\r\n");
    UART_1_PutString("\r\n");
    UART_1_PutString("Test\tFunction\t\tResult\r\n");
    UART_1_PutString("----\t--------\t\t------\r\n");
    
    /*
     *  Initialise cb_add_new() test.
     */
    if (result == CBT_SUCCESS)
    {
        if (_create_object("one", 1, &object_1) == CBT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (_create_object("two", 2, &object_2) == CBT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (_create_object("three", 3, &object_3) == CBT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    /*
     *  Test cb_add_new().
     */
    if (result == CBT_SUCCESS)
    {
        if (cb_add_new(NULL, _TAG, NULL) == CB_BAD_ARGUMENT)
        {
            UART_1_PutString("   1\tcb_add_new()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   1\tcb_add_new()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_add_new(NULL, _TAG, object_1) == CB_BAD_ARGUMENT)
        {
            UART_1_PutString("   2\tcb_add_new()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   2\tcb_add_new()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_add_new(&buffer_1, _TAG, NULL) == CB_BAD_ARGUMENT)
        {
            UART_1_PutString("   3\tcb_add_new()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   3\tcb_add_new()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_add_new(&buffer_1, _TAG, object_1) == CB_SUCCESS)
        {
            UART_1_PutString("   4\tcb_add_new()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   4\tcb_add_new()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        buffer_1.limit = 1;
        
        if (cb_add_new(&buffer_1, _TAG, object_2) == CB_SUCCESS)
        {
            UART_1_PutString("   5\tcb_add_new()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   5\tcb_add_new()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        buffer_1.limit = 2;
        
        if (cb_add_new(&buffer_1, _TAG, object_3) == CB_SUCCESS)
        {
            UART_1_PutString("   6\tcb_add_new()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   6\tcb_add_new()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {   
        if (buffer_1.list->count == 2)
        {
            UART_1_PutString("   7\tcb_add_new()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   7\tcb_add_new()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    /*
     *  Test cb_remove_old().
     */
    if (result == CBT_SUCCESS)
    {
        if (cb_remove_old(NULL, NULL) == CB_BAD_ARGUMENT)
        {
            UART_1_PutString("   8\tcb_remove_old()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   8\tcb_remove_old()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_remove_old(NULL, (void **)&object_0) == CB_BAD_ARGUMENT)
        {
            UART_1_PutString("   9\tcb_remove_old()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   9\tcb_remove_old()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_remove_old(&buffer_2, NULL) == CB_EMPTY)
        {
            UART_1_PutString("  10\tcb_remove_old()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  10\tcb_remove_old()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_remove_old(&buffer_1, NULL) == CB_SUCCESS)
        {
            UART_1_PutString("  11\tcb_remove_old()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  11\tcb_remove_old()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_remove_old(&buffer_1, (void **)&object_0) == CB_SUCCESS)
        {
            UART_1_PutString("  12\tcb_remove_old()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  12\tcb_remove_old()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (object_0->number == 3)
        {
            UART_1_PutString("  13\tcb_remove_old()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  13\tcb_remove_old()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    /*
     *  Initialise cb_get_old_object() test.
     */
     if (result == CBT_SUCCESS)
    {
        if (_create_object("four", 4, &object_4) == CBT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        buffer_1.limit = 0;
        
        if (cb_add_new(&buffer_1, _TAG, object_1) == CB_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_add_new(&buffer_1, _TAG, object_2) == CB_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_add_new(&buffer_1, _TAG, object_3) == CB_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_add_new(&buffer_1, _TAG, object_4) == CB_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    /*
     *  Test cb_get_old_object().
     */
    if (result == CBT_SUCCESS)
    {
        if (cb_get_old_object(NULL, NULL, NULL) == CB_BAD_ARGUMENT)
        {
            UART_1_PutString("  14\tcb_get_old_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  14\tcb_get_old_object()\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_get_old_object(NULL, NULL,
            (void **)&object_0) == CB_BAD_ARGUMENT)
        {
            UART_1_PutString("  15\tcb_get_old_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  15\tcb_get_old_object()\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_get_old_object(&buffer_1, NULL, NULL) == CB_BAD_ARGUMENT)
        {
            UART_1_PutString("  16\tcb_get_old_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  16\tcb_get_old_object()\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_get_old_object(&buffer_1, NULL,
            (void **)&object_0) == CB_SUCCESS)
        {
            UART_1_PutString("  17\tcb_get_old_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  17\tcb_get_old_object()\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (object_0->number == 1)
        {
            UART_1_PutString("  18\tcb_get_old_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  18\tcb_get_old_object()\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_get_old_object(&buffer_1, &tag_0,
            (void **)&object_0) == CB_SUCCESS)
        {
            UART_1_PutString("  19\tcb_get_old_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  19\tcb_get_old_object()\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (tag_0 == 600)
        {
            UART_1_PutString("  20\tcb_get_old_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  20\tcb_get_old_object()\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_get_old_object(&buffer_2, &tag_0,
            (void **)&object_0) == CB_EMPTY)
        {
            UART_1_PutString("  21\tcb_get_old_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  21\tcb_get_old_object()\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    /*
     *  Test cb_get_new_object().
     */
    if (result == CBT_SUCCESS)
    {
        if (cb_get_new_object(NULL, NULL, NULL) == CB_BAD_ARGUMENT)
        {
            UART_1_PutString("  22\tcb_get_new_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  22\tcb_get_new_object()\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_get_new_object(NULL, NULL,
            (void **)&object_0) == CB_BAD_ARGUMENT)
        {
            UART_1_PutString("  23\tcb_get_new_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  23\tcb_get_new_object()\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_get_new_object(&buffer_1, NULL, NULL) == CB_BAD_ARGUMENT)
        {
            UART_1_PutString("  24\tcb_get_new_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  24\tcb_get_new_object()\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_get_new_object(&buffer_1, NULL,
            (void **)&object_0) == CB_SUCCESS)
        {
            UART_1_PutString("  25\tcb_get_new_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  25\tcb_get_new_object()\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (object_0->number == 4)
        {
            UART_1_PutString("  26\tcb_get_new_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  26\tcb_get_new_object()\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_get_new_object(&buffer_1, &tag_0,
            (void **)&object_0) == CB_SUCCESS)
        {
            UART_1_PutString("  27\tcb_get_new_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  27tcb_get_new_object()\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (tag_0 == 600)
        {
            UART_1_PutString("  28\tcb_get_new_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  28\tcb_get_new_object()\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_get_new_object(&buffer_2, &tag_0,
            (void **)&object_0) == CB_EMPTY)
        {
            UART_1_PutString("  29\tcb_get_old_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  29\tcb_get_old_object()\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    /*
     *  Test cb_get_count().
     */
    if (result == CBT_SUCCESS)
    {
        if (cb_get_count(NULL) == 0)
        {
            UART_1_PutString("  30\tcb_get_count()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  30\tcb_get_count()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_get_count(&buffer_1) == 4)
        {
            UART_1_PutString("  31\tcb_get_count()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  31tcb_get_count()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_get_count(&buffer_2) == 0)
        {
            UART_1_PutString("  32\tcb_get_count()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  32tcb_get_count()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    /*
     *  Test cb_get_limit().
     */
    if (result == CBT_SUCCESS)
    {
        if (cb_get_limit(NULL) == 0)
        {
            UART_1_PutString("  33\tcb_get_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  33\tcb_get_limit()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_get_limit(&buffer_1) == 0)
        {
            UART_1_PutString("  34\tcb_get_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  34\tcb_get_limit()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    /*
     *  Test cb_set_limit().
     */
    if (result == CBT_SUCCESS)
    {
        if (cb_set_limit(NULL, 10) == CB_BAD_ARGUMENT)
        {
            UART_1_PutString("  35\tcb_set_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  35\tcb_set_limit()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_set_limit(&buffer_1, 2) == CB_FAILURE)
        {
            UART_1_PutString("  36\tcb_set_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  36\tcb_set_limit()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_set_limit(&buffer_1, 0) == CB_SUCCESS)
        {
            UART_1_PutString("  37\tcb_set_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  37\tcb_set_limit()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_set_limit(&buffer_1, 10) == CB_SUCCESS)
        {
            UART_1_PutString("  38\tcb_set_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  38\tcb_set_limit()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (buffer_1.limit == 10)
        {
            UART_1_PutString("  39\tcb_set_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  39\tcb_set_limit()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    /*
     *  Test cb_destroy().
     */
    if (result == CBT_SUCCESS)
    {
        if (cb_destroy(NULL) == CB_BAD_ARGUMENT)
        {
            UART_1_PutString("  40\tcb_destroy()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  40\tcb_destroy()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_destroy(&buffer_1) == CB_SUCCESS)
        {
            UART_1_PutString("  41\tcb_destroy()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  41\tcb_destroy()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
    
    if (result == CBT_SUCCESS)
    {
        if (cb_get_count(&buffer_1) == 0)
        {
            UART_1_PutString("  42\tcb_destroy()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  42\tcb_destroy()\t\tFAIL\r\n");
            result = CBT_FAILURE;
        }
    }
        
    /*
     *  Report test result.
     */
    if (result == CBT_SUCCESS)
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
    
    while (UART_1_ReadTxStatus() != UART_1_TX_STS_FIFO_EMPTY)
    {
        CyDelay(1);
    }
    
    UART_1_Stop();
    
    return result;
}

/****************************************************************************
 *  Local Functions
 ****************************************************************************/
uint8 _create_object(char *string, uint8 number, CBT_OBJECT **object)
{
    CBT_OBJECT *new_object;
    uint8 result = CBT_NO_MEMORY;
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
            
            result = CBT_SUCCESS;
        }
        else
        {
            free(new_object);
        }
    }
    
    return result;
}

void _destroy_object(CBT_OBJECT *object)
{
    free(object->string);
    free(object);
}

void _walk_buffer(CB_LIST *buffer)
{
    uint32 count;
    CBT_OBJECT *object;
    
    for (count = 0 ; count < buffer->list->count ; count++)
    {
        object = (CBT_OBJECT *)buffer->list->list->object;
        
        UART_1_PutString(object->string);
        UART_1_PutString("\r\n");
        
        cl_move_forward(buffer->list, 1);
    }
}

/****************************************************************************
 *  End of File
 ****************************************************************************/
