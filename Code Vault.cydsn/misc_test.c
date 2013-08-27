/****************************************************************************
 *
 *  File:           misc_test.c
 *  Module:         Miscellaneous Function Test Library
 *  Project:        Code Vault
 *  Workspace:      PSoC Tools
 *
 *  Author:         Rodney B. Elliott
 *  Date:           26 August 2013
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
 *  @file misc_test.c
 *  @brief Miscellaneous function test library implementation.
 */
 
/****************************************************************************
 *  Modules
 ****************************************************************************/
#include <device.h>
#include <string.h>

#include "misc.h"
#include "misc_test.h"

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
void mit_test_1(void)
{
    uint8 result = MIT_SUCCESS;
    char string[11] = {0};

    UART_1_Start();
    
    UART_1_PutString("\x1b\x5b\x32\x4a");
    UART_1_PutString("MISCELLANEOUS FUNCTION LIBRARY TEST\r\n");
    UART_1_PutString("\r\n");
    UART_1_PutString("Test\tFunction\t\tResult\r\n");
    UART_1_PutString("----\t--------\t\t------\r\n");
    
    /*
     *  Test mi_utoa();
     */
    if (result == MIT_SUCCESS)
    {    
        if (mi_utoa(0, NULL) == MI_BAD_ARGUMENT)
        {
            UART_1_PutString("   1\tmi_utoa()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   1\tmi_utoa()\t\tFAIL\r\n");
            result = MIT_FAILURE;
        }
    }
    
    if (result == MIT_SUCCESS)
    {    
        if (mi_utoa(0, string) == MI_SUCCESS)
        {
            if (strcmp(string, "0") == 0)
            {
                UART_1_PutString("   2\tmi_utoa()\t\tPASS\r\n");
            }
            else
            {
                UART_1_PutString("   2\tmi_utoa()\t\tFAIL\r\n");
                result = MIT_FAILURE;
            }
        }
        else
        {
            UART_1_PutString("   2\tmi_utoa()\t\tFAIL\r\n");
            result = MIT_FAILURE;
        }
    }
    
    if (result == MIT_SUCCESS)
    {    
        if (mi_utoa(255, string) == MI_SUCCESS)
        {
            if (strcmp(string, "255") == 0)
            {
                UART_1_PutString("   3\tmi_utoa()\t\tPASS\r\n");
            }
            else
            {
                UART_1_PutString("   3\tmi_utoa()\t\tFAIL\r\n");
                result = MIT_FAILURE;
            }
        }
        else
        {
            UART_1_PutString("   3\tmi_utoa()\t\tFAIL\r\n");
            result = MIT_FAILURE;
        }
    }
    
    if (result == MIT_SUCCESS)
    {    
        if (mi_utoa(65535, string) == MI_SUCCESS)
        {
            if (strcmp(string, "65535") == 0)
            {
                UART_1_PutString("   4\tmi_utoa()\t\tPASS\r\n");
            }
            else
            {
                UART_1_PutString("   4\tmi_utoa()\t\tFAIL\r\n");
                result = MIT_FAILURE;
            }
        }
        else
        {
            UART_1_PutString("   4\tmi_utoa()\t\tFAIL\r\n");
            result = MIT_FAILURE;
        }
    }
    
    if (result == MIT_SUCCESS)
    {    
        if (mi_utoa(4294967295u, string) == MI_SUCCESS)
        {
            if (strcmp(string, "4294967295") == 0)
            {
                UART_1_PutString("   5\tmi_utoa()\t\tPASS\r\n");
            }
            else
            {
                UART_1_PutString("   5\tmi_utoa()\t\tFAIL\r\n");
                result = MIT_FAILURE;
            }
        }
        else
        {
            UART_1_PutString("   5\tmi_utoa()\t\tFAIL\r\n");
            result = MIT_FAILURE;
        }
    }
        
    /*
     *  Report test result.
     */
    if (result == MIT_SUCCESS)
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
}

/****************************************************************************
 *  Local Functions
 ****************************************************************************/

/****************************************************************************
 *  End of File
 ****************************************************************************/
