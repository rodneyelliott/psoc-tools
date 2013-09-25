/****************************************************************************
 *
 *  File:           cllist_test.c
 *  Module:         Circular Linked List Test Library
 *  Project:        Code Vault
 *  Workspace:      PSoC Tools
 *
 *  Author:         Rodney B. Elliott
 *  Date:           22 August 2013
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
 *  @file cllist_test.c
 *  @brief Circular linked list test library implementation.
 */
 
/****************************************************************************
 *  Modules
 ****************************************************************************/
#include <device.h>
#include <stdlib.h>

#include "cllist.h"
#include "cllist_test.h"

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
 *  @brief The CLL test library object tag.
 */
#define _TAG                            500

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
 *  @return #CLT_SUCCESS if successful, otherwise #CLT_NO_MEMORY.
 */
static uint8 _create_object(char *string, uint8 number, CLT_OBJECT **object);

/**
 *  @brief Destroy a test object.
 *  @param[in] object A pointer to a test object.
 */
static void _destroy_object(CLT_OBJECT *object);

/**
 *  @brief Walk a CLL, displaying test object ASCII strings.
 *  @param[in] list A pointer to a CLL.
 */
static void _walk_list(CL_LIST *list);

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/

/****************************************************************************
 *  Global Variables
 ****************************************************************************/

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
uint8 clt_test_1(void)
{
    CL_LIST list_1 = {0};
    CL_LIST list_2 = {0};
    CL_LIST list_3 = {0};
    CLT_OBJECT *object_0;
    CLT_OBJECT *object_1;
    CLT_OBJECT *object_2;
    CLT_OBJECT *object_3;
    CLT_OBJECT *object_4;
    uint8 result = CLT_SUCCESS;
    uint16 tag_0;
    
    UART_1_Start();
    
    UART_1_PutString("\x1b\x5b\x32\x4a");
    UART_1_PutString("CIRCULAR LINKED LIBRARY LIBRARY TEST\r\n");
    UART_1_PutString("\r\n");
    UART_1_PutString("Test\tFunction\t\tResult\r\n");
    UART_1_PutString("----\t--------\t\t------\r\n");
    
    /*
     *  Initialise cl_add_after() test.
     */
    if (result == CLT_SUCCESS)
    {
        if (_create_object("three", 3, &object_3) == CLT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (_create_object("four", 4, &object_4) == CLT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    /*
     *  Test cl_add_after().
     */
    if (result == CLT_SUCCESS)
    {
        if (cl_add_after(NULL, _TAG, NULL) == CL_BAD_ARGUMENT)
        {
            UART_1_PutString("   1\tcl_add_after()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   1\tcl_add_after()\t\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
     
    if (result == CLT_SUCCESS)
    {
        if (cl_add_after(NULL, _TAG, object_3) == CL_BAD_ARGUMENT)
        {
            UART_1_PutString("   2\tcl_add_after()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   2\tcl_add_after()\t\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (cl_add_after(&list_1, _TAG, NULL) == CL_BAD_ARGUMENT)
        {
            UART_1_PutString("   3\tcl_add_after()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   3\tcl_add_after()\t\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (cl_add_after(&list_1, _TAG, object_3) == CL_SUCCESS)
        {
            UART_1_PutString("   4\tcl_add_after()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   4\tcl_add_after()\t\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (cl_add_after(&list_1, _TAG, object_4) == CL_SUCCESS)
        {
            UART_1_PutString("   5\tcl_add_after()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   5\tcl_add_after()\t\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (list_1.count == 2)
        {
            UART_1_PutString("   6\tcl_add_after()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   6\tcl_add_after()\t\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    /*
     *  Initialise cl_add_before() test.
     */
    if (result == CLT_SUCCESS)
    {
        if (_create_object("one", 1, &object_1) == CLT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (_create_object("two", 2, &object_2) == CLT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    /*
     *  Test cl_add_before().
     */
    if (result == CLT_SUCCESS)
    {
        if (cl_add_before(NULL, _TAG, NULL) == CL_BAD_ARGUMENT)
        {
            UART_1_PutString("   7\tcl_add_before()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   7\tcl_add_before()\t\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
     
    if (result == CLT_SUCCESS)
    {
        if (cl_add_before(NULL, _TAG, object_1) == CL_BAD_ARGUMENT)
        {
            UART_1_PutString("   8\tcl_add_before()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   8\tcl_add_before()\t\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (cl_add_before(&list_2, _TAG, NULL) == CL_BAD_ARGUMENT)
        {
            UART_1_PutString("   9\tcl_add_before()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   9\tcl_add_before()\t\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (cl_add_before(&list_2, _TAG, object_1) == CL_SUCCESS)
        {
            UART_1_PutString("  10\tcl_add_before()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  10\tcl_add_before()\t\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (cl_add_before(&list_2, _TAG, object_2) == CL_SUCCESS)
        {
            UART_1_PutString("  11\tcl_add_before()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  11\tcl_add_before()\t\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (list_2.count == 2)
        {
            UART_1_PutString("  12\tcl_add_before()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  12\tcl_add_before()\t\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    /*
     *  Test cl_remove_current().
     */
    if (result == CLT_SUCCESS)
    {
        if (cl_remove_current(NULL, NULL) == CL_BAD_ARGUMENT)
        {
            UART_1_PutString("  13\tcl_remove_current()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  13\tcl_remove_current()\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (cl_remove_current(NULL, (void **)&object_0) == CL_BAD_ARGUMENT)
        {
            UART_1_PutString("  14\tcl_remove_current()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  14\tcl_remove_current()\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (cl_remove_current(&list_3, NULL) == CL_EMPTY)
        {
            UART_1_PutString("  15\tcl_remove_current()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  15\tcl_remove_current()\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (cl_remove_current(&list_2, NULL) == CL_SUCCESS)
        {
            UART_1_PutString("  16\tcl_remove_current()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  16\tcl_remove_current()\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (list_2.count == 1)
        {
            UART_1_PutString("  17\tcl_remove_current()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  17\tcl_remove_current()\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (cl_remove_current(&list_2, (void **)&object_0) == CL_SUCCESS)
        {
            UART_1_PutString("  18\tcl_remove_current()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  18\tcl_remove_current()\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (object_0->number == 2)
        {
            UART_1_PutString("  19\tcl_remove_current()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  19\tcl_remove_current()\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    /*
     *  Initialise cl_move_forward() test.
     */
    if (result == CLT_SUCCESS)
    {
        if (cl_add_after(&list_2, _TAG, object_1) == CL_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (cl_add_after(&list_2, _TAG, object_4) == CL_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (cl_add_after(&list_2, _TAG, object_3) == CL_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (cl_add_after(&list_2, _TAG, object_2) == CL_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
        
    /*
     *  Test cl_move_forward().
     */
    if (result == CLT_SUCCESS)
    {
        if (cl_move_forward(NULL, 0) == CL_BAD_ARGUMENT)
        {
            UART_1_PutString("  20\tcl_move_forward()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  20\tcl_move_forward()\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
        
    if (result == CLT_SUCCESS)
    {
        if (cl_move_forward(&list_2, 0) == CL_SUCCESS)
        {
            UART_1_PutString("  21\tcl_move_forward()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  21\tcl_move_forward()\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (cl_move_forward(&list_2, 1) == CL_SUCCESS)
        {
            UART_1_PutString("  22\tcl_move_forward()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  22\tcl_move_forward()\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }

    if (result == CLT_SUCCESS)
    {
        if (cl_move_forward(&list_2, 3) == CL_SUCCESS)
        {
            UART_1_PutString("  23\tcl_move_forward()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  23\tcl_move_forward()\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        object_0 = (CLT_OBJECT *)list_2.list->object;
    
        if (object_0->number == 1)
        {
            UART_1_PutString("  24\tcl_move_forward()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  24\tcl_move_forward()\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    /*
     *  Test cl_move_backward().
     */
    if (result == CLT_SUCCESS)
    {
        if (cl_move_backward(NULL, 0) == CL_BAD_ARGUMENT)
        {
            UART_1_PutString("  25\tcl_move_backward()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  25\tcl_move_backward()\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
        
    if (result == CLT_SUCCESS)
    {
        if (cl_move_backward(&list_2, 0) == CL_SUCCESS)
        {
            UART_1_PutString("  26\tcl_move_backward()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  26\tcl_move_backward()\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (cl_move_backward(&list_2, 1) == CL_SUCCESS)
        {
            UART_1_PutString("  27\tcl_move_backward()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  27\tcl_move_backward()\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }

    if (result == CLT_SUCCESS)
    {
        if (cl_move_backward(&list_2, 3) == CL_SUCCESS)
        {
            UART_1_PutString("  28\tcl_move_backward()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  28\tcl_move_backward()\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        object_0 = (CLT_OBJECT *)list_2.list->object;
    
        if (object_0->number == 1)
        {
            UART_1_PutString("  29\tcl_move_backward()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  29\tcl_move_backward()\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    /*
     *  Test cl_get_current_object().
     */
    if (result == CLT_SUCCESS)
    {
        if (cl_get_current_object(NULL, NULL, NULL) == CL_BAD_ARGUMENT)
        {
            UART_1_PutString("  30\tcl_get_current_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  30\tcl_get_current_object()\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (cl_get_current_object(NULL, NULL,
            (void **)&object_0) == CL_BAD_ARGUMENT)
        {
            UART_1_PutString("  31\tcl_get_current_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  31\tcl_get_current_object()\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (cl_get_current_object(&list_2, NULL, NULL) == CL_BAD_ARGUMENT)
        {
            UART_1_PutString("  32\tcl_get_current_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  32\tcl_get_current_object()\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (cl_get_current_object(&list_2, NULL,
            (void **)&object_0) == CL_SUCCESS)
        {
            UART_1_PutString("  33\tcl_get_current_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  33\tcl_get_current_object()\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (object_0->number == 1)
        {
            UART_1_PutString("  34\tcl_get_current_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  34\tcl_get_current_object()\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (cl_get_current_object(&list_2, &tag_0,
            (void **)&object_0) == CL_SUCCESS)
        {
            UART_1_PutString("  35\tcl_get_current_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  35\tcl_get_current_object()\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (tag_0 == 500)
        {
            UART_1_PutString("  36\tcl_get_current_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  36\tcl_get_current_object()\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (cl_get_current_object(&list_3, &tag_0,
            (void **)&object_0) == CL_EMPTY)
        {
            UART_1_PutString("  37\tcl_get_current_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  37\tcl_get_current_object()\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    /*
     *  Test cl_get_count().
     */
    if (result == CLT_SUCCESS)
    {
        if (cl_get_count(NULL) == 0)
        {
            UART_1_PutString("  38\tcl_get_count()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  38\tcl_get_count()\t\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (cl_get_count(&list_2) == 4)
        {
            UART_1_PutString("  39\tcl_get_count()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  39tcl_get_count()\t\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    /*
     *  Test cl_destroy().
     */
    if (result == CLT_SUCCESS)
    {
        if (cl_destroy(NULL) == CL_BAD_ARGUMENT)
        {
            UART_1_PutString("  40\tcl_destroy()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  40\tcl_destroy()\t\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (cl_destroy(&list_2) == CL_SUCCESS)
        {
            UART_1_PutString("  41\tcl_destroy()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  41\tcl_destroy()\t\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    if (result == CLT_SUCCESS)
    {
        if (list_2.count == 0)
        {
            UART_1_PutString("  42\tcl_destroy()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  42\tcl_destroy()\t\tFAIL\r\n");
            result = CLT_FAILURE;
        }
    }
    
    /*
     *  Report test result.
     */
    if (result == CLT_SUCCESS)
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
uint8 _create_object(char *string, uint8 number, CLT_OBJECT **object)
{
    CLT_OBJECT *new_object;
    uint8 result = CLT_NO_MEMORY;
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
            
            result = CLT_SUCCESS;
        }
        else
        {
            free(new_object);
        }
    }
    
    return result;
}

void _destroy_object(CLT_OBJECT *object)
{
    free(object->string);
    free(object);
}

void _walk_list(CL_LIST *list)
{
    uint32 count;
    CLT_OBJECT *object;
    
    for (count = 0 ; count < list->count ; count++)
    {
        object = (CLT_OBJECT *)list->list->object;
        
        UART_1_PutString(object->string);
        UART_1_PutString("\r\n");
        
        cl_move_forward(list, 1);
    }
}

/****************************************************************************
 *  End of File
 ****************************************************************************/
