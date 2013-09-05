/****************************************************************************
 *
 *  File:           deque_test.c
 *  Module:         Deque Test Library
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
 *  @file deque_test.c
 *  @brief Deque test library implementation.
 */

/****************************************************************************
 *  Modules
 ****************************************************************************/
#include <device.h>
#include <stdlib.h>

#include "deque.h"
#include "deque_test.h"

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
 *  @brief The deque test library object tag.
 */
 #define _TAG                           300

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
 *  @return #DET_SUCCESS if successful, otherwise #DET_NO_MEMORY.
 */
static uint8 _create_object(char *string, uint8 number, DET_OBJECT **object);

/**
 *  @brief Destroy a test object.
 *  @param[in] object A pointer to a test object.
 */
static void _destroy_object(DET_OBJECT *object);

/**
 *  @brief Walk a deque, displaying test object ASCII strings.
 *  @param[in] deque A pointer to a deque.
 */
static void _walk_deque(DE_LIST *deque);

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/
 
/****************************************************************************
 *  Global Variables
 ****************************************************************************/
 
/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
uint8 det_test_1(void)
{
    DE_LIST deque_1 = {0};
    DE_LIST deque_2 = {0};
    DET_OBJECT *object_0;
    DET_OBJECT *object_1;
    DET_OBJECT *object_2;
    DET_OBJECT *object_3;
    DET_OBJECT *object_4;
    uint8 result = DET_SUCCESS;
    uint16 tag_0;

    UART_1_Start();
    
    UART_1_PutString("\x1b\x5b\x32\x4a");
    UART_1_PutString("DEQUE LIBRARY TEST\r\n");
    UART_1_PutString("\r\n");
    UART_1_PutString("Test\tFunction\t\tResult\r\n");
    UART_1_PutString("----\t--------\t\t------\r\n");
    
    /*
     *  Initialise de_add_first() test.
     */
    if (result == DET_SUCCESS)
    {
        if (_create_object("one", 1, &object_1) == DET_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (_create_object("two", 2, &object_2) == DET_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    /*
     *  Test de_add_first().
     */
    if (result == DET_SUCCESS)
    {
        if (de_add_first(NULL, _TAG, NULL) == DE_BAD_ARGUMENT)
        {
            UART_1_PutString("   1\tde_add_first()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   1\tde_add_first()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_add_first(NULL, _TAG, object_2) == DE_BAD_ARGUMENT)
        {
            UART_1_PutString("   2\tde_add_first()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   2\tde_add_first()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_add_first(&deque_1, _TAG, NULL) == DE_BAD_ARGUMENT)
        {
            UART_1_PutString("   3\tde_add_first()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   3\tde_add_first()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_add_first(&deque_1, _TAG, object_2) == DE_SUCCESS)
        {
            UART_1_PutString("   4\tde_add_first()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   4\tde_add_first()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        deque_1.limit = 1;
         
        if (de_add_first(&deque_1, _TAG, object_1) == DE_FULL)
        {
            UART_1_PutString("   5\tde_add_first()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   5\tde_add_first()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        deque_1.limit = 2;
         
        if (de_add_first(&deque_1, _TAG, object_1) == DE_SUCCESS)
        {
            UART_1_PutString("   6\tde_add_first()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   6\tde_add_first()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {    
        if (deque_1.count == 2)
        {
            UART_1_PutString("   7\tde_add_first()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   7\tde_add_first()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
        
    /*
     *  Initialise de_add_last() test.
     */
    if (result == DET_SUCCESS)
    {
        if (_create_object("three", 3, &object_3) == DET_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (_create_object("four", 4, &object_4) == DET_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    /*
     *  Test de_add_last().
     */
    if (result == DET_SUCCESS)
    {
        if (de_add_last(NULL, _TAG, NULL) == DE_BAD_ARGUMENT)
        {
            UART_1_PutString("   8\tde_add_last()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   8\tde_add_last()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_add_last(NULL, _TAG, object_3) == DE_BAD_ARGUMENT)
        {
            UART_1_PutString("   9\tde_add_last()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   9\tde_add_last()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_add_last(&deque_1, _TAG, NULL) == DE_BAD_ARGUMENT)
        {
            UART_1_PutString("  10\tde_add_last()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  10\tde_add_last()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_add_last(&deque_1, _TAG, object_3) == DE_FULL)
        {
            UART_1_PutString("  11\tde_add_last()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  11\tde_add_last()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        deque_1.limit = 0;
        
        if (de_add_last(&deque_1, _TAG, object_3) == DE_SUCCESS)
        {
            UART_1_PutString("  12\tde_add_last()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  12\tde_add_last()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_add_last(&deque_1, _TAG, object_4) == DE_SUCCESS)
        {
            UART_1_PutString("  13\tde_add_last()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  13\tde_add_last()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (deque_1.count == 4)
        {
            UART_1_PutString("  14\tde_add_last()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  14\tde_add_last()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    /*
     *  Test de_remove_first().
     */
    if (result == DET_SUCCESS)
    {
        if (de_remove_first(NULL, NULL) == DE_BAD_ARGUMENT)
        {
            UART_1_PutString("  15\tde_remove_first()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  15\tde_remove_first()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_remove_first(NULL, (void **)&object_0) == DE_BAD_ARGUMENT)
        {
            UART_1_PutString("  16\tde_remove_first()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  16\tde_remove_first()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_remove_first(&deque_2, NULL) == DE_EMPTY)
        {
            UART_1_PutString("  17\tde_remove_first()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  17\tde_remove_first()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_remove_first(&deque_1, NULL) == DE_SUCCESS)
        {
            UART_1_PutString("  18\tde_remove_first()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  18\tde_remove_first()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (deque_1.count == 3)
        {
            UART_1_PutString("  19\tde_remove_first()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  19\tde_remove_first()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_remove_first(&deque_1, (void **)&object_0) == DE_SUCCESS)
        {
            UART_1_PutString("  20\tde_remove_first()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  20\tde_remove_first()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (object_0->number == 2)
        {
            UART_1_PutString("  21\tde_remove_first()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  21\tde_remove_first()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    /*
     *  Test de_remove_last().
     */
    if (result == DET_SUCCESS)
    {
        if (de_remove_last(NULL, NULL) == DE_BAD_ARGUMENT)
        {
            UART_1_PutString("  22\tde_remove_last()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  22\tde_remove_last()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_remove_last(NULL, (void **)&object_0) == DE_BAD_ARGUMENT)
        {
            UART_1_PutString("  23\tde_remove_last()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  23\tde_remove_last()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_remove_last(&deque_2, NULL) == DE_EMPTY)
        {
            UART_1_PutString("  24\tde_remove_last()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  24\tde_remove_last()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_remove_last(&deque_1, NULL) == DE_SUCCESS)
        {
            UART_1_PutString("  25\tde_remove_last()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  25\tde_remove_last()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (deque_1.count == 1)
        {
            UART_1_PutString("  26\tde_remove_last()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  26\tde_remove_last()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_remove_last(&deque_1, (void **)&object_0) == DE_SUCCESS)
        {
            UART_1_PutString("  27\tde_remove_last()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  27\tde_remove_last()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (object_0->number == 3)
        {
            UART_1_PutString("  28\tde_remove_last()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  28\tde_remove_last()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
        
    /*
     *  Initialise de_get_first_object() test.
     */
    if (result == DET_SUCCESS)
    {
        if (de_add_first(&deque_1, _TAG, object_1) == DE_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_add_first(&deque_1, _TAG, object_2) == DE_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_add_first(&deque_1, _TAG, object_3) == DE_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_add_first(&deque_1, _TAG, object_4) == DE_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    /*
     *  Test de_get_first_object().
     */
    if (result == DET_SUCCESS)
    {
        if (de_get_first_object(NULL, NULL, NULL) == DE_BAD_ARGUMENT)
        {
            UART_1_PutString("  29\tde_get_first_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  29\tde_get_first_object()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_get_first_object(NULL, NULL,
            (void **)&object_0) == DE_BAD_ARGUMENT)
        {
            UART_1_PutString("  30\tde_get_first_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  30\tde_get_first_object()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_get_first_object(&deque_1, NULL, NULL) == DE_BAD_ARGUMENT)
        {
            UART_1_PutString("  31\tde_get_first_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  31\tde_get_first_object()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_get_first_object(&deque_1, NULL,
            (void **)&object_0) == DE_SUCCESS)
        {
            UART_1_PutString("  32\tde_get_first_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  32\tde_get_first_object()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (object_0->number == 4)
        {
            UART_1_PutString("  33\tde_get_first_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  33\tde_get_first_object()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_get_first_object(&deque_1, &tag_0,
            (void **)&object_0) == DE_SUCCESS)
        {
            UART_1_PutString("  34\tde_get_first_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  34\tde_get_first_object()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (tag_0 == 300)
        {
            UART_1_PutString("  35\tde_get_first_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  35\tde_get_first_object()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_get_first_object(&deque_2, &tag_0,
            (void **)&object_0) == DE_EMPTY)
        {
            UART_1_PutString("  36\tde_get_first_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  36\tde_get_first_object()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    /*
     *  Test de_get_last_object().
     */
    if (result == DET_SUCCESS)
    {
        if (de_get_last_object(NULL, NULL, NULL) == DE_BAD_ARGUMENT)
        {
            UART_1_PutString("  37\tde_get_last_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  37\tde_get_last_object()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_get_last_object(NULL, NULL,
            (void **)&object_0) == DE_BAD_ARGUMENT)
        {
            UART_1_PutString("  38\tde_get_last_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  38\tde_get_last_object()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_get_last_object(&deque_1, NULL, NULL) == DE_BAD_ARGUMENT)
        {
            UART_1_PutString("  39\tde_get_last_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  39\tde_get_last_object()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_get_last_object(&deque_1, NULL,
            (void **)&object_0) == DE_SUCCESS)
        {
            UART_1_PutString("  40\tde_get_last_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  40\tde_get_last_object()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (object_0->number == 1)
        {
            UART_1_PutString("  41\tde_get_last_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  41\tde_get_last_object()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_get_last_object(&deque_1, &tag_0,
            (void **)&object_0) == DE_SUCCESS)
        {
            UART_1_PutString("  42\tde_get_last_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  42\tde_get_last_object()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (tag_0 == 300)
        {
            UART_1_PutString("  43\tde_get_last_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  43\tde_get_last_object()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_get_last_object(&deque_2, &tag_0,
            (void **)&object_0) == DE_EMPTY)
        {
            UART_1_PutString("  44\tde_get_last_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  44\tde_get_last_object()\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    /*
     *  Test de_get_count().
     */
    if (result == DET_SUCCESS)
    {
        if (de_get_count(NULL) == 0)
        {
            UART_1_PutString("  45\tde_get_count()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  45\tde_get_count()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_get_count(&deque_1) == 4)
        {
            UART_1_PutString("  46\tde_get_count()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  46\tde_get_count()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    /*
     *  Test de_get_limit().
     */
    if (result == DET_SUCCESS)
    {
        if (de_get_limit(NULL) == 0)
        {
            UART_1_PutString("  47\tde_get_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  47\tde_get_limit()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_get_limit(&deque_1) == 0)
        {
            UART_1_PutString("  48\tde_get_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  48\tde_get_limit()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    /*
     *  Test de_set_limit().
     */
    if (result == DET_SUCCESS)
    {
        if (de_set_limit(NULL, 10) == DE_BAD_ARGUMENT)
        {
            UART_1_PutString("  49\tde_set_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  49\tde_set_limit()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_set_limit(&deque_1, 2) == DE_FAILURE)
        {
            UART_1_PutString("  50\tde_set_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  50\tde_set_limit()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_set_limit(&deque_1, 0) == DE_SUCCESS)
        {
            UART_1_PutString("  51\tde_set_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  51\tde_set_limit()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_set_limit(&deque_1, 10) == DE_SUCCESS)
        {
            UART_1_PutString("  52\tde_set_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  52\tde_set_limit()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (deque_1.limit == 10)
        {
            UART_1_PutString("  53\tde_set_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  53\tde_set_limit()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
        
    /*
     *  Test de_destroy().
     */
    if (result == DET_SUCCESS)
    {
        if (de_destroy(NULL) == DE_BAD_ARGUMENT)
        {
            UART_1_PutString("  54\tde_destroy()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  54\tde_destroy()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (de_destroy(&deque_1) == DE_SUCCESS)
        {
            UART_1_PutString("  55\tde_destroy()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  55\tde_destroy()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    if (result == DET_SUCCESS)
    {
        if (deque_1.count == 0)
        {
            UART_1_PutString("  56\tde_destroy()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  56\tde_destroy()\t\tFAIL\r\n");
            result = DET_FAILURE;
        }
    }
    
    /*
     *  Report test result.
     */
    if (result == DET_SUCCESS)
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
uint8 _create_object(char *string, uint8 number, DET_OBJECT **object)
{
    DET_OBJECT *new_object;
    uint8 result = DET_NO_MEMORY;
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
            
            result = DET_SUCCESS;
        }
        else
        {
            free(new_object);
        }
    }
    
    return result;
}

void _destroy_object(DET_OBJECT *object)
{
    free(object->string);
    free(object);
}

void _walk_deque(DE_LIST *deque)
{
    DL_LIST *node;
    DET_OBJECT *object;
    
    for (node = dl_get_first(deque->list) ; node != NULL ; node = node->next)
    {
        object = node->object;
        
        UART_1_PutString(object->string);
        UART_1_PutString("\r\n");
        
    }
}

/****************************************************************************
 *  End of File
 ****************************************************************************/
