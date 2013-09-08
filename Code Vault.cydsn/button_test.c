/****************************************************************************
 *
 *  File:           button_test.c
 *  Module:         Button Test Library
 *  Project:        Code Vault
 *  Workspace:      PSoC Tools
 *
 *  Author:         Rodney B. Elliott
 *  Date:           4 September 2013
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
 *  @file button_test.c
 *  @brief Button test library implementation.
 */
 
/****************************************************************************
 *  Modules
 ****************************************************************************/
#include <device.h>

#include "button.h"
#include "button_test.h"

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
uint8 but_test_1(void)
{
    CB_LIST buffer_1 = {0};
    CB_LIST buffer_2 = {0};
    BU_OBJECT *object_0;
    uint8 result = BUT_SUCCESS;
    
    UART_1_Start();
    
    UART_1_PutString("\x1b\x5b\x32\x4a");
    UART_1_PutString("BUTTON LIBRARY TEST\r\n");
    UART_1_PutString("\r\n");
    UART_1_PutString("Test\tFunction\t\tResult\r\n");
    UART_1_PutString("----\t--------\t\t------\r\n");
    
    /*
     *  Test bu_start().
     */
    if (result == BUT_SUCCESS)
    {
        if (bu_start(NULL) == BU_BAD_ARGUMENT)
        {
            UART_1_PutString("   1\tbu_start()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   1\tbu_start()\t\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    if (result == BUT_SUCCESS)
    {
        if (bu_start(&buffer_1) == BU_SUCCESS)
        {
            UART_1_PutString("   2\tbu_start()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   2\tbu_start()\t\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    if (result == BUT_SUCCESS)
    {
        if (bu_start(&buffer_1) == BU_FAILURE)
        {
            UART_1_PutString("   3\tbu_start()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   3\tbu_start()\t\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    /*
     *  Test bu_stop().
     */
    if (result == BUT_SUCCESS)
    {
        if (bu_stop(NULL) == BU_BAD_ARGUMENT)
        {
            UART_1_PutString("   4\tbu_stop()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   4\tbu_stop()\t\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    if (result == BUT_SUCCESS)
    {
        if (bu_stop(&buffer_1) == BU_SUCCESS)
        {
            UART_1_PutString("   5\tbu_stop()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   5\tbu_stop()\t\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    if (result == BUT_SUCCESS)
    {
        if (bu_stop(&buffer_1) == BU_FAILURE)
        {
            UART_1_PutString("   6\tbu_stop()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   6\tbu_stop()\t\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    /*
     *  Initialise bu_add_new() test.
     */
    if (result == BUT_SUCCESS)
    {
        if (bu_start(&buffer_1) == BU_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    /*
     *  Test bu_add_new().
     */
    if (result == BUT_SUCCESS)
    {
        if (bu_add_new(NULL, 1, BU_PRESSED) == BU_BAD_ARGUMENT)
        {
            UART_1_PutString("   7\tbu_add_new()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   7\tbu_add_new()\t\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    if (result == BUT_SUCCESS)
    {
        if (bu_add_new(&buffer_1, 1, BU_PRESSED) == BU_SUCCESS)
        {
            UART_1_PutString("   8\tbu_add_new()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   8\tbu_add_new()\t\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
     
    /*
     *  Initialise bu_get_new_object() test.
     */
    if (result == BUT_SUCCESS)
    {
        if (bu_add_new(&buffer_1, 1, BU_RELEASED) == BU_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    if (result == BUT_SUCCESS)
    {
        if (bu_add_new(&buffer_1, 2, BU_PRESSED) == BU_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    /*
     *  Test bu_get_new_object().
     */
    if (result == BUT_SUCCESS)
    {
        if (bu_get_new_object(NULL, NULL) == BU_BAD_ARGUMENT)
        {
            UART_1_PutString("   9\tbu_get_new_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   9\tbu_get_new_object()\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    if (result == BUT_SUCCESS)
    {
        if (bu_get_new_object(NULL, &object_0) == BU_BAD_ARGUMENT)
        {
            UART_1_PutString("  10\tbu_get_new_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  10\tbu_get_new_object()\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    if (result == BUT_SUCCESS)
    {
        if (bu_get_new_object(&buffer_1, NULL) == BU_BAD_ARGUMENT)
        {
            UART_1_PutString("  11\tbu_get_new_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  11\tbu_get_new_object()\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    if (result == BUT_SUCCESS)
    {
        if (bu_get_new_object(&buffer_1, &object_0) == BU_SUCCESS)
        {
            UART_1_PutString("  12\tbu_get_new_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  12\tbu_get_new_object()\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    if (result == BUT_SUCCESS)
    {
        if ((object_0->number == 2) && (object_0->state == BU_PRESSED))
        {
            UART_1_PutString("  13\tbu_get_new_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  13\tbu_get_new_object()\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    /*
     *  Test bu_get_old_object().
     */
    if (result == BUT_SUCCESS)
    {
        if (bu_get_old_object(NULL, NULL) == BU_BAD_ARGUMENT)
        {
            UART_1_PutString("  14\tbu_get_old_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  14\tbu_get_old_object()\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    if (result == BUT_SUCCESS)
    {
        if (bu_get_old_object(NULL, &object_0) == BU_BAD_ARGUMENT)
        {
            UART_1_PutString("  15\tbu_get_old_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  15\tbu_get_old_object()\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    if (result == BUT_SUCCESS)
    {
        if (bu_get_old_object(&buffer_1, NULL) == BU_BAD_ARGUMENT)
        {
            UART_1_PutString("  16\tbu_get_old_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  16\tbu_get_old_object()\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    if (result == BUT_SUCCESS)
    {
        if (bu_get_old_object(&buffer_1, &object_0) == BU_SUCCESS)
        {
            UART_1_PutString("  17\tbu_get_old_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  17\tbu_get_old_object()\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    if (result == BUT_SUCCESS)
    {
        if ((object_0->number == 1) && (object_0->state == BU_PRESSED))
        {
            UART_1_PutString("  18\tbu_get_old_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  18\tbu_get_old_object()\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    /*
     *  Test bu_get_count().
     */
    if (result == BUT_SUCCESS)
    {
        if (bu_get_count(NULL) == 0)
        {
            UART_1_PutString("  19\tbu_get_count()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  19\tbu_get_count()\t\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    if (result == BUT_SUCCESS)
    {
        if (bu_get_count(&buffer_1) == 3)
        {
            UART_1_PutString("  20\tbu_get_count()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  20\tbu_get_count()\t\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    /*
     *  Test bu_remove_old().
     */
    if (result == BUT_SUCCESS)
    {
        if (bu_remove_old(NULL) == BU_BAD_ARGUMENT)
        {
            UART_1_PutString("  21\tbu_remove_old()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  21\tbu_remove_old()\t\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    if (result == BUT_SUCCESS)
    {
        if (bu_remove_old(&buffer_2) == BU_EMPTY)
        {
            UART_1_PutString("  22\tbu_remove_old()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  22\tbu_remove_old()\t\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    if (result == BUT_SUCCESS)
    {
        if (bu_remove_old(&buffer_1) == BU_SUCCESS)
        {
            UART_1_PutString("  23\tbu_remove_old()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  23\tbu_remove_old()\t\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    if (result == BUT_SUCCESS)
    {
        if (bu_get_count(&buffer_1) == 2)
        {
            UART_1_PutString("  24\tbu_remove_old()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  24\tbu_remove_old()\t\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    if (result == BUT_SUCCESS)
    {
        if (bu_get_old_object(&buffer_1, &object_0) == BU_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    if (result == BUT_SUCCESS)
    {
        if ((object_0->number == 1) && (object_0->state == BU_RELEASED))
        {
            UART_1_PutString("  25\tbu_remove_old()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  25\tbu_remove_old()\t\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    /*
     *  Test bu_get_limit().
     */
    if (result == BUT_SUCCESS)
    {
        if (bu_get_limit(NULL) == 0)
        {
            UART_1_PutString("  26\tbu_get_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  26\tbu_get_limit()\t\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    if (result == BUT_SUCCESS)
    {
        if (bu_get_limit(&buffer_1) == 0)
        {
            UART_1_PutString("  27\tbu_get_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  27\tbu_get_limit()\t\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    /*
     *  Initialise bu_set_limit() test.
     */
    if (result == BUT_SUCCESS)
    {
        if (bu_add_new(&buffer_1, 2, BU_RELEASED) == BU_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    /*
     *  Test bu_set_limit().
     */
    if (result == BUT_SUCCESS)
    {
        if (bu_set_limit(NULL, 10) == BU_BAD_ARGUMENT)
        {
            UART_1_PutString("  28\tbu_set_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  28\tbu_set_limit()\t\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    if (result == BUT_SUCCESS)
    {
        if (bu_set_limit(&buffer_1, 2) == BU_FAILURE)
        {
            UART_1_PutString("  29\tbu_set_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  29\tbu_set_limit()\t\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    if (result == BUT_SUCCESS)
    {
        if (bu_set_limit(&buffer_1, 4) == BU_SUCCESS)
        {
            UART_1_PutString("  30\tbu_set_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  30\tbu_set_limit()\t\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
        
    /*
     *  Test bu_destroy().
     */
    if (result == BUT_SUCCESS)
    {
        if (bu_destroy(NULL) == BU_BAD_ARGUMENT)
        {
            UART_1_PutString("  31\tbu_destroy()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  31\tbu_destroy()\t\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    if (result == BUT_SUCCESS)
    {
        if (bu_destroy(&buffer_1) == BU_SUCCESS)
        {
            UART_1_PutString("  32\tbu_destroy()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  32\tbu_destroy()\t\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    if (result == BUT_SUCCESS)
    {
        if (bu_get_count(&buffer_1) == 0)
        {
            UART_1_PutString("  33\tbu_destroy()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  33\tbu_destroy()\t\tFAIL\r\n");
            result = BUT_FAILURE;
        }
    }
    
    /*
     *  Report test result.
     */
    if (result == BUT_SUCCESS)
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
    while (UART_1_ReadTxStatus() != UART_1_TX_STS_FIFO_EMPTY)
    {
        CyDelay(1);
    }
    
    bu_stop(&buffer_1);
    
    UART_1_Stop();
    
    return result;
}

void but_test_2(void)
{
    CB_LIST buffer = {0};
    BU_OBJECT *object;
    uint8 status = 0;
    
    UART_1_Start();
    
    UART_1_PutString("\x1b\x5b\x32\x4a");
    UART_1_PutString("BUTTON LIBRARY TEST\r\n");
    UART_1_PutString("\r\n");
    UART_1_PutString("Button 1\r\n");
    UART_1_PutString("Button 2\r\n");
    UART_1_PutString("Button 3\r\n");
    UART_1_PutString("Button 4\r\n");
    UART_1_PutString("Button 5\r\n");
    UART_1_PutString("Button 6\r\n");
    UART_1_PutString("Button 7\r\n");
    UART_1_PutString("Button 8\r\n");
    
    bu_start(&buffer);
    
    for(;;)
    {
        if (bu_get_count(&buffer) > 0)
        {
            bu_get_old_object(&buffer, &object);
            
            UART_1_PutString("\x1b\x5b\x32\x4a");
            UART_1_PutString("BUTTON LIBRARY TEST\r\n");
            UART_1_PutString("\r\n");
            
            if ((object->number == 1) && (object->state == BU_PRESSED))
            {
                status |= BU_BUTTON_1;
            }
            else if ((object->number == 1) && (object->state == BU_RELEASED))
            {
                status ^= BU_BUTTON_1;
            }
            
            if ((object->number == 2) && (object->state == BU_PRESSED))
            {
                status |= BU_BUTTON_2;
            }
            else if ((object->number == 2) && (object->state == BU_RELEASED))
            {
                status ^= BU_BUTTON_2;
            }
            
            if ((object->number == 3) && (object->state == BU_PRESSED))
            {
                status |= BU_BUTTON_3;
            }
            else if ((object->number == 3) && (object->state == BU_RELEASED))
            {
                status ^= BU_BUTTON_3;
            }
            
            if ((object->number == 4) && (object->state == BU_PRESSED))
            {
                status |= BU_BUTTON_4;
            }
            else if ((object->number == 4) && (object->state == BU_RELEASED))
            {
                status ^= BU_BUTTON_4;
            }
            
            if ((object->number == 5) && (object->state == BU_PRESSED))
            {
                status |= BU_BUTTON_5;
            }
            else if ((object->number == 5) && (object->state == BU_RELEASED))
            {
                status ^= BU_BUTTON_5;
            }
            
            if ((object->number == 6) && (object->state == BU_PRESSED))
            {
                status |= BU_BUTTON_6;
            }
            else if ((object->number == 6) && (object->state == BU_RELEASED))
            {
                status ^= BU_BUTTON_6;
            }
            
            if ((object->number == 7) && (object->state == BU_PRESSED))
            {
                status |= BU_BUTTON_7;
            }
            else if ((object->number == 7) && (object->state == BU_RELEASED))
            {
                status ^= BU_BUTTON_7;
            }
            
            if ((object->number == 8) && (object->state == BU_PRESSED))
            {
                status |= BU_BUTTON_8;
            }
            else if ((object->number == 8) && (object->state == BU_RELEASED))
            {
                status ^= BU_BUTTON_8;
            }
            
            if (status & BU_BUTTON_1)
            {
                UART_1_PutString("Button 1\tPRESSED\r\n");
            }
            else
            {
                UART_1_PutString("Button 1\r\n");
            }
            
            if (status & BU_BUTTON_2)
            {
                UART_1_PutString("Button 2\tPRESSED\r\n");
            }
            else
            {
                UART_1_PutString("Button 2\r\n");
            }
            
            if (status & BU_BUTTON_3)
            {
                UART_1_PutString("Button 3\tPRESSED\r\n");
            }
            else
            {
                UART_1_PutString("Button 3\r\n");
            }
            
            if (status & BU_BUTTON_4)
            {
                UART_1_PutString("Button 4\tPRESSED\r\n");
            }
            else
            {
                UART_1_PutString("Button 4\r\n");
            }
            
            if (status & BU_BUTTON_5)
            {
                UART_1_PutString("Button 5\tPRESSED\r\n");
            }
            else
            {
                UART_1_PutString("Button 5\r\n");
            }
            
            if (status & BU_BUTTON_6)
            {
                UART_1_PutString("Button 6\tPRESSED\r\n");
            }
            else
            {
                UART_1_PutString("Button 6\r\n");
            }
            
            if (status & BU_BUTTON_7)
            {
                UART_1_PutString("Button 7\tPRESSED\r\n");
            }
            else
            {
                UART_1_PutString("Button 7\r\n");
            }
            
            if (status & BU_BUTTON_8)
            {
                UART_1_PutString("Button 8\tPRESSED\r\n");
            }
            else
            {
                UART_1_PutString("Button 8\r\n");
            }
            
            bu_remove_old(&buffer);
        }
    }
}

/****************************************************************************
 *  Local Functions
 ****************************************************************************/

/****************************************************************************
 *  End of File
 ****************************************************************************/
