/****************************************************************************
 *
 *  File:           error_test.c
 *  Module:         Error Management Test Library
 *  Project:        Code Vault
 *  Workspace:      PSoC Tools
 *
 *  Author:         Rodney B. Elliott
 *  Date:           27 August 2013
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
 *  @file error_test.c
 *  @brief Error management test library implementation.
 */
 
/****************************************************************************
 *  Modules
 ****************************************************************************/
#include <device.h>
#include <string.h>

#include "error.h"
#include "error_test.h"

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
uint8 ert_test_1(void)
{
    DE_LIST deque_1 = {0};
    DE_LIST deque_2 = {0};
    ER_LOCATION *location_0;
    char *message_0;
    ER_OBJECT *object_0;
    uint8 result = ERT_SUCCESS;
    char string_0[80];
    uint16 tag_0;
    RT_DATA *timestamp_0;
    
    UART_1_Start();
    
    UART_1_PutString("\x1b\x5b\x32\x4a");
    UART_1_PutString("ERROR MANAGEMENT LIBRARY TEST\r\n");
    UART_1_PutString("\r\n");
    UART_1_PutString("Test\tFunction\t\tResult\r\n");
    UART_1_PutString("----\t--------\t\t------\r\n");
    
    /*
     *  Test _add_standard().
     */
    if (result == ERT_SUCCESS)
    {
        if (_add_standard(NULL, E00900, ER_OPTIONS_NONE,
            NULL, __LINE__) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("   1\ter_add_standard()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   1\ter_add_standard()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (_add_standard(NULL, E00900, ER_OPTIONS_NONE,
            __FILE__, __LINE__) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("   2\ter_add_standard()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   2\ter_add_standard()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (_add_standard(&deque_1, E00900, ER_OPTIONS_NONE,
            NULL, __LINE__) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("   3\ter_add_standard()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   3\ter_add_standard()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (_add_standard(&deque_1, E00900, ER_OPTIONS_NONE,
            __FILE__, __LINE__) == ER_SUCCESS)
        {
            UART_1_PutString("   4\ter_add_standard()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   4\ter_add_standard()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Initialise _add_standard() test.
     */
    if (result == ERT_SUCCESS)
    {
        if (de_get_last_object(&deque_1, &tag_0,
            (void **)&object_0) == DE_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test _add_standard().
     */
    if (result == ERT_SUCCESS)
    {
        if (object_0->error_type == ER_STANDARD_TYPE)
        {
            UART_1_PutString("   5\ter_add_standard()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   5\ter_add_standard()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (object_0->error.number == E00900)
        {
            UART_1_PutString("   6\ter_add_standard()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   6\ter_add_standard()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (_add_standard(&deque_1, E00900, ER_OPTIONS_TIMESTAMP,
            __FILE__, __LINE__) == ER_FAILURE)
        {
            UART_1_PutString("   7\ter_add_standard()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   7\ter_add_standard()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Initialise _add_standard() test.
     */
    if (result == ERT_SUCCESS)
    {
        if (rt_start() == RT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test _add_standard().
     */
    if (result == ERT_SUCCESS)
    {   
        if (_add_standard(&deque_1, E00900, ER_OPTIONS_TIMESTAMP,
            __FILE__, __LINE__) == ER_SUCCESS)
        {
            UART_1_PutString("   8\ter_add_standard()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   8\ter_add_standard()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Initialise _add_standard() test.
     */
    if (result == ERT_SUCCESS)
    {
        if (de_get_last_object(&deque_1, &tag_0,
            (void **)&object_0) == DE_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test _add_standard().
     */
    if (result == ERT_SUCCESS)
    {
        if (object_0->timestamp->Year == 1918)
        {
            UART_1_PutString("   9\ter_add_standard()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   9\ter_add_standard()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (_add_standard(&deque_1, E00900, ER_OPTIONS_LOCATION,
            __FILE__, __LINE__) == ER_SUCCESS)
        {
            UART_1_PutString("  10\ter_add_standard()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  10\ter_add_standard()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Initialise _add_standard() test.
     */
    if (result == ERT_SUCCESS)
    {
        if (de_get_last_object(&deque_1, &tag_0,
            (void **)&object_0) == DE_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test _add_standard().
     */
    if (result == ERT_SUCCESS)
    {
        if (strcmp(object_0->location->file, ".\\error_test.c") == 0)
        {
            UART_1_PutString("  11\ter_add_standard()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  11\ter_add_standard()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (_add_standard(&deque_1, E00900,
            (ER_OPTIONS_TIMESTAMP | ER_OPTIONS_LOCATION),
            __FILE__, __LINE__) == ER_SUCCESS)
        {
            UART_1_PutString("  12\ter_add_standard()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  12\ter_add_standard()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Initialise _add_standard() test.
     */
    if (result == ERT_SUCCESS)
    {
        if (de_get_last_object(&deque_1, &tag_0,
            (void **)&object_0) == DE_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test _add_standard().
     */
    if (result == ERT_SUCCESS)
    {
        if (object_0->timestamp->Month == 11)
        {
            UART_1_PutString("  13\ter_add_standard()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  13\ter_add_standard()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (object_0->location->line == 333)
        {
            UART_1_PutString("  14\ter_add_standard()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  14\ter_add_standard()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Initialise _add_standard() test.
     */
    if (result == ERT_SUCCESS)
    {
        if (de_set_limit(&deque_1, 4) == DE_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test _add_standard().
     */
    if (result == ERT_SUCCESS)
    {
        if (_add_standard(&deque_1, E00900,
            (ER_OPTIONS_TIMESTAMP | ER_OPTIONS_LOCATION),
            __FILE__, __LINE__) == ER_FULL)
        {
            UART_1_PutString("  15\ter_add_standard()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  15\ter_add_standard()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Initialise _add_special() test.
     */
    if (result == ERT_SUCCESS)
    {
        if (de_set_limit(&deque_1, 0) == DE_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test _add_special().
     */
    if (result == ERT_SUCCESS)
    {
        if (_add_special(NULL, NULL, ER_OPTIONS_NONE,
            NULL, __LINE__) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  16\ter_add_special()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  16\ter_add_special()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (_add_special(NULL, NULL, ER_OPTIONS_NONE,
            __FILE__, __LINE__) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  17\ter_add_special()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  17\ter_add_special()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (_add_special(NULL, "Special message.", ER_OPTIONS_NONE,
            NULL, __LINE__) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  18\ter_add_special()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  18\ter_add_special()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (_add_special(NULL, "Special message.", ER_OPTIONS_NONE,
            __FILE__, __LINE__) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  19\ter_add_special()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  19\ter_add_special()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (_add_special(&deque_1, NULL, ER_OPTIONS_NONE,
            NULL, __LINE__) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  20\ter_add_special()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  20\ter_add_special()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (_add_special(&deque_1, NULL, ER_OPTIONS_NONE,
            __FILE__, __LINE__) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  21\ter_add_special()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  21\ter_add_special()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (_add_special(&deque_1, "Special message.", ER_OPTIONS_NONE,
            NULL, __LINE__) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  22\ter_add_special()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  22\ter_add_special()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (_add_special(&deque_1, "Special message.", ER_OPTIONS_NONE,
            __FILE__, __LINE__) == ER_SUCCESS)
        {
            UART_1_PutString("  23\ter_add_special()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  23\ter_add_special()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Initialise _add_special() test.
     */
    if (result == ERT_SUCCESS)
    {
        if (de_get_last_object(&deque_1, &tag_0,
            (void **)&object_0) == DE_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test _add_special().
     */
    if (result == ERT_SUCCESS)
    {
        if (object_0->error_type == ER_SPECIAL_TYPE)
        {
            UART_1_PutString("  24\ter_add_special()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  24\ter_add_special()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (strcmp(object_0->error.message, "Special message.") == 0)
        {
            UART_1_PutString("  25\ter_add_special()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  25\ter_add_special()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Initialise _add_special() test.
     */
    if (result == ERT_SUCCESS)
    {
        if (rt_stop() == RT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test _add_special().
     */
    if (result == ERT_SUCCESS)
    {
        if (_add_special(&deque_1, "Special message.", ER_OPTIONS_TIMESTAMP,
            __FILE__, __LINE__) == ER_FAILURE)
        {
            UART_1_PutString("  26\ter_add_special()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  26\ter_add_special()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Initialise _add_special() test.
     */
    if (result == ERT_SUCCESS)
    {
        if (rt_start() == RT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test _add_special().
     */
    if (result == ERT_SUCCESS)
    {
        if (_add_special(&deque_1, "Special message.", ER_OPTIONS_TIMESTAMP,
            __FILE__, __LINE__) == ER_SUCCESS)
        {
            UART_1_PutString("  27\ter_add_special()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  27\ter_add_special()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Initialise _add_special() test.
     */
    if (result == ERT_SUCCESS)
    {
        if (de_get_last_object(&deque_1, &tag_0,
            (void **)&object_0) == DE_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test _add_special().
     */
    if (result == ERT_SUCCESS)
    {
        if (object_0->timestamp->DayOfMonth == 11)
        {
            UART_1_PutString("  28\ter_add_special()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  28\ter_add_special()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test _add_special().
     */
    if (result == ERT_SUCCESS)
    {
        if (_add_special(&deque_1, "Special message.", ER_OPTIONS_LOCATION,
            __FILE__, __LINE__) == ER_SUCCESS)
        {
            UART_1_PutString("  29\ter_add_special()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  29\ter_add_special()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Initialise _add_special() test.
     */
    if (result == ERT_SUCCESS)
    {
        if (de_get_last_object(&deque_1, &tag_0,
            (void **)&object_0) == DE_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test _add_special().
     */
    if (result == ERT_SUCCESS)
    {
        if (strcmp(object_0->location->file, ".\\error_test.c") == 0)
        {
            UART_1_PutString("  30\ter_add_special()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  30\ter_add_special()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (_add_special(&deque_1, "Special message.",
            (ER_OPTIONS_TIMESTAMP | ER_OPTIONS_LOCATION),
            __FILE__, __LINE__) == ER_SUCCESS)
        {
            UART_1_PutString("  31\ter_add_special()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  31\ter_add_special()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Initialise _add_special() test.
     */
    if (result == ERT_SUCCESS)
    {
        if (de_get_last_object(&deque_1, &tag_0,
            (void **)&object_0) == DE_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test _add_special().
     */
    if (result == ERT_SUCCESS)
    {
        if (object_0->timestamp->Hour == 11)
        {
            UART_1_PutString("  32\ter_add_special()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  32\ter_add_special()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (object_0->location->line == 754)
        {
            UART_1_PutString("  33\ter_add_special()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  33\ter_add_special()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Initialise _add_special() test.
     */
    if (result == ERT_SUCCESS)
    {
        if (de_set_limit(&deque_1, 8) == DE_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test _add_special().
     */
    if (result == ERT_SUCCESS)
    {
        if (_add_special(&deque_1, "Special message.",
            (ER_OPTIONS_TIMESTAMP | ER_OPTIONS_LOCATION),
            __FILE__, __LINE__) == ER_FULL)
        {
            UART_1_PutString("  34\ter_add_special()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  34\ter_add_special()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test er_get_first_object().
     */
    if (result == ERT_SUCCESS)
    {
        if (er_get_first_object(NULL, NULL) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  35\ter_get_first_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  35\ter_get_first_object()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_get_first_object(NULL, &object_0) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  36\ter_get_first_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  36\ter_get_first_object()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_get_first_object(&deque_1, NULL) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  37\ter_get_first_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  37\ter_get_first_object()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_get_first_object(&deque_1, &object_0) == ER_SUCCESS)
        {
            UART_1_PutString("  38\ter_get_first_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  38\ter_get_first_object()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (object_0->error_type == ER_STANDARD_TYPE)
        {
            UART_1_PutString("  39\ter_get_first_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  39\ter_get_first_object()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (object_0->timestamp == NULL)
        {
            UART_1_PutString("  40\ter_get_first_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  40\ter_get_first_object()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (object_0->location == NULL)
        {
            UART_1_PutString("  41\ter_get_first_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  41\ter_get_first_object()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_get_first_object(&deque_2, &object_0) == ER_EMPTY)
        {
            UART_1_PutString("  42\ter_get_first_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  42\ter_get_first_object()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
     
    /*
     *  Test er_get_last_object().
     */
    if (result == ERT_SUCCESS)
    {
        if (er_get_last_object(NULL, NULL) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  43\ter_get_last_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  43\ter_get_last_object()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_get_last_object(NULL, &object_0) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  44\ter_get_last_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  44\ter_get_last_object()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_get_last_object(&deque_1, NULL) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  45\ter_get_last_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  45\ter_get_last_object()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_get_last_object(&deque_1, &object_0) == ER_SUCCESS)
        {
            UART_1_PutString("  46\ter_get_last_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  46\ter_get_last_object()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (object_0->error_type == ER_SPECIAL_TYPE)
        {
            UART_1_PutString("  47\ter_get_last_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  47\ter_get_last_object()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (object_0->timestamp != NULL)
        {
            UART_1_PutString("  48\ter_get_last_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  48\ter_get_last_object()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (object_0->location != NULL)
        {
            UART_1_PutString("  49\ter_get_last_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  49\ter_get_last_object()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_get_last_object(&deque_2, &object_0) == ER_EMPTY)
        {
            UART_1_PutString("  50\ter_get_last_object()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  50\ter_get_last_object()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test er_get_message().
     */
    if (result == ERT_SUCCESS)
    {
        if (er_get_message(NULL, NULL) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  51\ter_get_message()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  51\ter_get_message()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_get_message(NULL, &message_0) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  52\ter_get_message()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  52\ter_get_message()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_get_message(object_0, NULL) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  53\ter_get_message()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  53\ter_get_message()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }

    if (result == ERT_SUCCESS)
    {
        if (er_get_message(object_0, &message_0) == ER_SUCCESS)
        {
            UART_1_PutString("  54\ter_get_message()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  54\ter_get_message()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (object_0->error_type == ER_SPECIAL_TYPE)
        {
            UART_1_PutString("  55\ter_get_message()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  55\ter_get_message()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (strcmp(message_0, "Special message.") == 0)
        {
            UART_1_PutString("  56\ter_get_message()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  56\ter_get_message()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Initialise er_get_message() test.
     */
    if (result == ERT_SUCCESS)
    {
        if (er_get_first_object(&deque_1, &object_0) == ER_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test er_get_message().
     */
    if (result == ERT_SUCCESS)
    {
        if (er_get_message(object_0, &message_0) == ER_SUCCESS)
        {
            UART_1_PutString("  57\ter_get_message()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  57\ter_get_message()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (object_0->error_type == ER_STANDARD_TYPE)
        {
            UART_1_PutString("  58\ter_get_message()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  58\ter_get_message()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (strcmp(message_0, "E00900: Start of error management library error message block.") == 0)
        {
            UART_1_PutString("  59\ter_get_message()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  59\ter_get_message()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test er_remove().
     */
    if (result == ERT_SUCCESS)
    {
        if (er_remove(NULL) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  60\ter_remove()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  60\ter_remove()\t\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_remove(&deque_1) == ER_SUCCESS)
        {
            UART_1_PutString("  61\ter_remove()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  61\ter_remove()\t\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (deque_1.count == 7)
        {
            UART_1_PutString("  62\ter_remove()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  62\ter_remove()\t\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_remove(&deque_2) == ER_EMPTY)
        {
            UART_1_PutString("  63\ter_remove()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  63\ter_remove()\t\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test er_get_count().
     */
    if (result == ERT_SUCCESS)
    {
        if (er_get_count(NULL) == 0)
        {
            UART_1_PutString("  64\ter_get_count()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  64\ter_get_count()\t\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_get_count(&deque_1) == 7)
        {
            UART_1_PutString("  65\ter_get_count()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  65\ter_get_count()\t\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_get_count(&deque_2) == 0)
        {
            UART_1_PutString("  66\ter_get_count()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  66\ter_get_count()\t\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test er_get_timestamp().
     */
    if (result == ERT_SUCCESS)
    {
        if (er_get_timestamp(NULL, NULL) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  67\ter_get_timestamp()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  67\ter_get_timestamp()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_get_timestamp(NULL, &timestamp_0) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  68\ter_get_timestamp()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  68\ter_get_timestamp()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_get_timestamp(object_0, NULL) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  69\ter_get_timestamp()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  69\ter_get_timestamp()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_get_timestamp(object_0, &timestamp_0) == ER_SUCCESS)
        {
            UART_1_PutString("  70\ter_get_timestamp()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  70\ter_get_timestamp()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (timestamp_0 == NULL)
        {
            UART_1_PutString("  71\ter_get_timestamp()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  71\ter_get_timestamp()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test er_get_location().
     */
    if (result == ERT_SUCCESS)
    {
        if (er_get_location(NULL, NULL) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  72\ter_get_location()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  72\ter_get_location()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_get_location(NULL, &location_0) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  73\ter_get_location()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  73\ter_get_location()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_get_location(object_0, NULL) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  74\ter_get_location()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  74\ter_get_location()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_get_location(object_0, &location_0) == ER_SUCCESS)
        {
            UART_1_PutString("  75\ter_get_location()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  75\ter_get_location()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (location_0 == NULL)
        {
            UART_1_PutString("  76\ter_get_location()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  76\ter_get_location()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Initialise er_convert_timestamp() test.
     */
    if (result == ERT_SUCCESS)
    {
        if (er_get_last_object(&deque_1, &object_0) == ER_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_get_timestamp(object_0, &timestamp_0) == ER_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test er_convert_timestamp().
     */
    if (result == ERT_SUCCESS)
    {
        if (er_convert_timestamp(NULL, NULL) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  77\ter_convert_timestamp()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  77\ter_convert_timestamp()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_convert_timestamp(NULL, string_0) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  78\ter_convert_timestamp()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  78\ter_convert_timestamp()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_convert_timestamp(timestamp_0, NULL) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  79\ter_convert_timestamp()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  79\ter_convert_timestamp()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test er_convert_timestamp().
     */
    if (result == ERT_SUCCESS)
    {
        if (er_convert_timestamp(timestamp_0, string_0) == ER_SUCCESS)
        {
            UART_1_PutString("  80\ter_convert_timestamp()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  80\ter_convert_timestamp()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (strcmp(string_0, "11/11/1918 11:00:00") == ER_SUCCESS)
        {
            UART_1_PutString("  81\ter_convert_timestamp()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  81\ter_convert_timestamp()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Initialise er_convert_location() test.
     */
    if (result == ERT_SUCCESS)
    {
        if (er_get_location(object_0, &location_0) == ER_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test er_convert_location().
     */
    if (result == ERT_SUCCESS)
    {
        if (er_convert_location(NULL, NULL) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  82\ter_convert_location()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  82\ter_convert_location()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_convert_location(NULL, string_0) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  83\ter_convert_location()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  83\ter_convert_location()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_convert_location(location_0, NULL) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  84\ter_convert_location()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  84\ter_convert_location()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_convert_location(location_0, string_0) == ER_SUCCESS)
        {
            UART_1_PutString("  85\ter_convert_location()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  85\ter_convert_location()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (strcmp(string_0, "file .\\error_test.c line 754") == ER_SUCCESS)
        {
            UART_1_PutString("  86\ter_convert_location()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  86\ter_convert_location()\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Test er_destroy().
     */
    if (result == ERT_SUCCESS)
    {
        if (er_destroy(NULL) == ER_BAD_ARGUMENT)
        {
            UART_1_PutString("  87\ter_destroy()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  87\ter_destroy()\t\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    if (result == ERT_SUCCESS)
    {
        if (er_destroy(&deque_1) == ER_SUCCESS)
        {
            UART_1_PutString("  88\ter_destroy()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  88\ter_destroy()\t\tFAIL\r\n");
            result = ERT_FAILURE;
        }
    }
    
    /*
     *  Report test result.
     */
    if (result == ERT_SUCCESS)
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
    
    UART_1_Stop();
    
    return result;
}

/****************************************************************************
 *  Local Functions
 ****************************************************************************/

/****************************************************************************
 *  End of File
 ****************************************************************************/
