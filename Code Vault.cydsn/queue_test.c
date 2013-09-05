/****************************************************************************
 *
 *  File:           queue_test.c
 *  Module:         Queue Test Library
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
 *  @file queue_test.c
 *  @brief Queue test library implementation.
 */

/****************************************************************************
 *  Modules
 ****************************************************************************/
#include <device.h>
#include <stdlib.h>

#include "queue.h"
#include "queue_test.h"

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
 *  @brief The queue test library object tag.
 */
 #define _TAG                           400

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
 *  @return #QUT_SUCCESS if successful, otherwise #QUT_NO_MEMORY.
 */
static uint8 _create_object(char *string, uint8 number, QUT_OBJECT **object);

/**
 *  @brief Destroy a test object.
 *  @param[in] object A pointer to a test object.
 */
static void _destroy_object(QUT_OBJECT *object);

/**
 *  @brief Walk a queue, displaying test object ASCII strings.
 *  @param[in] queue A pointer to a queue.
 */
static void _walk_queue(QU_LIST *queue);

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/
 
/****************************************************************************
 *  Global Variables
 ****************************************************************************/
 
/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
uint8 qut_test_1(void)
{
    QU_LIST queue_1 = {0};
    QU_LIST queue_2 = {0};
    QUT_OBJECT *object_0;
    QUT_OBJECT *object_1;
    QUT_OBJECT *object_2;
    QUT_OBJECT *object_3;
    QUT_OBJECT *object_4;
    uint8 result = QUT_SUCCESS;
    uint16 tag_0;

    UART_1_Start();
    
    UART_1_PutString("\x1b\x5b\x32\x4a");
    UART_1_PutString("QUEUE LIBRARY TEST\r\n");
    UART_1_PutString("\r\n");
    UART_1_PutString("Test\tFunction\t\tResult\r\n");
    UART_1_PutString("----\t--------\t\t------\r\n");
    
    /*
     *  Initialise qu_add_last() test.
     */
    if (result == QUT_SUCCESS)
    {
        if (_create_object("three", 3, &object_3) == QUT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (_create_object("four", 4, &object_4) == QUT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    /*
     *  Test qu_add_last().
     */
    if (result == QUT_SUCCESS)
    {
        if (qu_add_last(NULL, _TAG, NULL) == QU_BAD_ARGUMENT)
        {
            UART_1_PutString("   1\tqu_add_last()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   1\tqu_add_last()\t\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (qu_add_last(NULL, _TAG, object_3) == QU_BAD_ARGUMENT)
        {
            UART_1_PutString("   2\tqu_add_last()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   2\tqu_add_last()\t\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (qu_add_last(&queue_1, _TAG, NULL) == QU_BAD_ARGUMENT)
        {
            UART_1_PutString("   3\tqu_add_last()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   3\tqu_add_last()\t\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {        
        if (qu_add_last(&queue_1, _TAG, object_3) == QU_SUCCESS)
        {
            UART_1_PutString("   4\tqu_add_last()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   4\tqu_add_last()\t\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        queue_1.limit = 1;
        
        if (qu_add_last(&queue_1, _TAG, object_3) == QU_FULL)
        {
            UART_1_PutString("   5\tqu_add_last()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   5\tqu_add_last()\t\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        queue_1.limit = 2;
        
        if (qu_add_last(&queue_1, _TAG, object_4) == QU_SUCCESS)
        {
            UART_1_PutString("   6\tqu_add_last()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   6\tqu_add_last()\t\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (queue_1.count == 2)
        {
            UART_1_PutString("   7\tqu_add_last()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   7\tqu_add_last()\t\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    /*
     *  Test qu_remove_first().
     */
    if (result == QUT_SUCCESS)
    {
        if (qu_remove_first(NULL, NULL) == QU_BAD_ARGUMENT)
        {
            UART_1_PutString("   8\tqu_remove_first()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   8\tqu_remove_first()\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (qu_remove_first(NULL, (void **)&object_0) == QU_BAD_ARGUMENT)
        {
            UART_1_PutString("   9\tqu_remove_first()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   9\tqu_remove_first()\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (qu_remove_first(&queue_2, NULL) == QU_EMPTY)
        {
            UART_1_PutString("  10\tqu_remove_first()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  10\tqu_remove_first()\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (qu_remove_first(&queue_1, NULL) == QU_SUCCESS)
        {
            UART_1_PutString("  11\tqu_remove_first()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  11\tqu_remove_first()\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (queue_1.count == 1)
        {
            UART_1_PutString("  12\tqu_remove_first()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  12\tqu_remove_first()\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (qu_remove_first(&queue_1, (void **)&object_0) == QU_SUCCESS)
        {
            UART_1_PutString("  13\tqu_remove_first()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  13\tqu_remove_first()\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (object_0->number == 4)
        {
            UART_1_PutString("  14\tqu_remove_first()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  14\tqu_remove_first()\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
        
    /*
     *  Initialise qu_get_first_object() test.
     */
    queue_1.limit = 0;
    
    if (result == QUT_SUCCESS)
    {
        if (_create_object("one", 1, &object_1) == QUT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (_create_object("two", 2, &object_2) == QUT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (qu_add_last(&queue_1, _TAG, object_4) == QU_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (qu_add_last(&queue_1, _TAG, object_3) == QU_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (qu_add_last(&queue_1, _TAG, object_2) == QU_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (qu_add_last(&queue_1, _TAG, object_1) == QU_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    /*
     *  Test qu_get_first_object().
     */
    if (result == QUT_SUCCESS)
    {
        if (qu_get_first_object(NULL, NULL, NULL) == QU_BAD_ARGUMENT)
        {
            UART_1_PutString("  15\tqu_get_first_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  15\tqu_get_first_object()\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (qu_get_first_object(NULL, NULL,
            (void **)&object_0) == QU_BAD_ARGUMENT)
        {
            UART_1_PutString("  16\tqu_get_first_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  16\tqu_get_first_object()\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (qu_get_first_object(&queue_1, NULL, NULL) == QU_BAD_ARGUMENT)
        {
            UART_1_PutString("  17\tqu_get_first_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  17\tqu_get_first_object()\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (qu_get_first_object(&queue_1, NULL,
            (void **)&object_0) == QU_SUCCESS)
        {
            UART_1_PutString("  18\tqu_get_first_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  18\tqu_get_first_object()\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (object_0->number == 4)
        {
            UART_1_PutString("  19\tqu_get_first_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  19\tqu_get_first_object()\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (qu_get_first_object(&queue_1, &tag_0,
            (void **)&object_0) == QU_SUCCESS)
        {
            UART_1_PutString("  20\tqu_get_first_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  20\tqu_get_first_object()\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (tag_0 == 400)
        {
            UART_1_PutString("  21\tqu_get_first_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  21\tqu_get_first_object()\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (qu_get_first_object(&queue_2, &tag_0,
            (void **)&object_0) == QU_EMPTY)
        {
            UART_1_PutString("  22\tqu_get_first_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  22\tqu_get_first_object()\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    /*
     *  Test qu_get_count().
     */
    if (result == QUT_SUCCESS)
    {
        if (qu_get_count(NULL) == 0)
        {
            UART_1_PutString("  23\tqu_get_count()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  23\tqu_get_count()\t\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (qu_get_count(&queue_1) == 4)
        {
            UART_1_PutString("  24\tqu_get_count()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  24\tqu_get_count()\t\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    /*
     *  Test qu_get_limit().
     */
    if (result == QUT_SUCCESS)
    {
        if (qu_get_limit(NULL) == 0)
        {
            UART_1_PutString("  25\tqu_get_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  25\tqu_get_limit()\t\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (qu_get_limit(&queue_1) == 0)
        {
            UART_1_PutString("  26\tqu_get_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  26\tqu_get_limit()\t\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    /*
     *  Test qu_set_limit().
     */
    if (result == QUT_SUCCESS)
    {
        if (qu_set_limit(NULL, 10) == QU_BAD_ARGUMENT)
        {
            UART_1_PutString("  27\tqu_set_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  27\tqu_set_limit()\t\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (qu_set_limit(&queue_1, 2) == QU_FAILURE)
        {
            UART_1_PutString("  28\tqu_set_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  28\tqu_set_limit()\t\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (qu_set_limit(&queue_1, 0) == QU_SUCCESS)
        {
            UART_1_PutString("  29\tqu_set_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  29\tqu_set_limit()\t\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (qu_set_limit(&queue_1, 10) == QU_SUCCESS)
        {
            UART_1_PutString("  30\tqu_set_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  30\tqu_set_limit()\t\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (queue_1.limit == 10)
        {
            UART_1_PutString("  31\tqu_set_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  31\tqu_set_limit()\t\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
        
    /*
     *  Test qu_destroy().
     */
    if (result == QUT_SUCCESS)
    {
        if (qu_destroy(NULL) == QU_BAD_ARGUMENT)
        {
            UART_1_PutString("  32\tqu_destroy()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  32\tqu_destroy()\t\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (qu_destroy(&queue_1) == QU_SUCCESS)
        {
            UART_1_PutString("  33\tqu_destroy()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  33\tqu_destroy()\t\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    if (result == QUT_SUCCESS)
    {
        if (queue_1.count == 0)
        {
            UART_1_PutString("  34\tqu_destroy()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  34\tqu_destroy()\t\tFAIL\r\n");
            result = QUT_FAILURE;
        }
    }
    
    /*
     *  Report test result.
     */
    if (result == QUT_SUCCESS)
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
uint8 _create_object(char *string, uint8 number, QUT_OBJECT **object)
{
    QUT_OBJECT *new_object;
    uint8 result = QUT_NO_MEMORY;
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
            
            result = QUT_SUCCESS;
        }
        else
        {
            free(new_object);
        }
    }
        
    return result;
}

void _destroy_object(QUT_OBJECT *object)
{
    free(object->string);
    free(object);
}

void _walk_queue(QU_LIST *queue)
{
    DL_LIST *node;
    QUT_OBJECT *object;
    
    for (node = dl_get_first(queue->list) ; node != NULL ; node = node->next)
    {
        object = node->object;
        
        UART_1_PutString(object->string);
        UART_1_PutString("\r\n");
        
    }
    
}

/****************************************************************************
 *  End of File
 ****************************************************************************/
