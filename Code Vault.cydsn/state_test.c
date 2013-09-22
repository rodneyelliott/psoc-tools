/****************************************************************************
 *
 *  File:           state_test.c
 *  Module:         Finite State Machine Test Library
 *  Project:        Code Vault
 *  Workspace:      PSoC Tools
 *
 *  Author:         Rodney B. Elliott
 *  Date:           8 September 2013
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
 *  @file state_test.c
 *  @brief Finite state machine test library implementation.
 */
 
/****************************************************************************
 *  Modules
 ****************************************************************************/
#include <device.h>

#include "state.h"
#include "state_test.h"

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
static char *_state_none_event_none = 
{
    "\x1b\x5b\x32\x4a"
    "FINITE STATE MACHINE LIBRARY TEST\r\n"
    "\r\n"
    "Welcome to the finite state machine (FSM) library. The library FSM\r\n"
    "is intended to serve as a guide to show programmers how to go about\r\n"
    "modifying the library to suit their application requirements, in\r\n"
    "addition to demonstrating its various event options.\r\n"
    "\r\n"
    "Before continuing, please ensure that you have read the library HTML\r\n"
    "documentation, as the information it contains will not be repeated\r\n"
    "here. In addition, please ensure your serial terminal has been\r\n"
    "configured to \"echo typed characters locally\" as this will make\r\n"
    "understanding how user input is processed a lot easier.\r\n"
    "\r\n"
    "[C] Continue\r\n"
    "\r\n"
    ">> "
};

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
uint8 stt_test_1(void)
{
    uint8 result = STT_SUCCESS;
    char string_0[ST_NODE_LIMIT] = {0};
    
    UART_1_Start();
    
    UART_1_PutString("\x1b\x5b\x32\x4a");
    UART_1_PutString("FINITE STATE MACHINE LIBRARY TEST\r\n");
    UART_1_PutString("\r\n");
    UART_1_PutString("Test\tFunction\t\tResult\r\n");
    UART_1_PutString("----\t--------\t\t------\r\n");
    
    /*
     *  Initialise test.
     */
    if (result == STT_SUCCESS)
    {
        st_start();
        
        UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
    }
    
    /*
     *  Test st_add_key().
     */
    if (result == STT_SUCCESS)
    {
        if (st_add_key(NULL) == ST_BAD_ARGUMENT)
        {
            UART_1_PutString("   1\tst_add_key()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   1\tst_add_key()\t\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
    
    if (result == STT_SUCCESS)
    {
        if (st_add_key("A") == ST_SUCCESS)
        {
            UART_1_PutString("   2\tst_add_key()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   2\tst_add_key()\t\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
        
    /*
     *  Test st_get_limit().
     */
    if (result == STT_SUCCESS)
    {
        if (st_get_limit() == ST_NODE_LIMIT)
        {
            UART_1_PutString("   3\tst_get_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   3\tst_get_limit()\t\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
    
    /*
     *  Initialise st_set_limit() test.
     */
    if (result == STT_SUCCESS)
    {
        if (st_add_key("B") == ST_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
    
    if (result == STT_SUCCESS)
    {
        if (st_add_key("C") == ST_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
    
    /*
     *  Test st_set_limit().
     */
    if (result == STT_SUCCESS)
    {
        if (st_set_limit(1) == ST_FAILURE)
        {
            UART_1_PutString("   4\tst_set_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   4\tst_set_limit()\t\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
    
    if (result == STT_SUCCESS)
    {
        if (st_set_limit(0) == ST_SUCCESS)
        {
            UART_1_PutString("   5\tst_set_limit()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   5\tst_set_limit()\t\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
    
    /*
     *  Test st_copy_buffer().
     */
    if (result == STT_SUCCESS)
    {
        if (st_copy_buffer(NULL) == ST_BAD_ARGUMENT)
        {
            UART_1_PutString("   6\tst_copy_buffer()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   6\tst_copy_buffer()\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
    
    if (result == STT_SUCCESS)
    {
        if (st_copy_buffer(string_0) == ST_SUCCESS)
        {
            UART_1_PutString("   7\tst_copy_buffer()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   7\tst_copy_buffer()\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
    
    if (result == STT_SUCCESS)
    {
        if (strcmp(string_0, "ABC") == ST_SUCCESS)
        {
            UART_1_PutString("   8\tst_copy_buffer()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   8\tst_copy_buffer()\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
        
    /*
     *  Test st_get_count().
     */
    if (result == STT_SUCCESS)
    {
        if (st_get_count() == 3)
        {
            UART_1_PutString("   9\tst_get_count()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   9\tst_get_count()\t\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
        
    /*
     *  Test st_empty_buffer().
     */
    if (result == STT_SUCCESS)
    {
        st_empty_buffer();
        
        if (st_get_count() == 0)
        {
            UART_1_PutString("  10\tst_empty_buffer()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  10\tst_empty_buffer()\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
    
    /*
     *  Test st_copy_buffer().
     */
    if (result == STT_SUCCESS)
    {
        if (st_copy_buffer(string_0) == ST_EMPTY)
        {
            UART_1_PutString("  11\tst_copy_buffer()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  11\tst_copy_buffer()\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
    
    /*
     *  Test st_is_valid_input().
     */
    if (result == STT_SUCCESS)
    {
        if (st_is_valid_input() == ST_FAILURE)
        {
            UART_1_PutString("  12\tst_is_valid_input()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  12\tst_is_valid_input()\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
    
    /*
     *  Initialise st_is_valid_input() test.
     */
    if (result == STT_SUCCESS)
    {
        if (st_add_key("C") == ST_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
    
    /*
     *  Test st_is_valid_input().
     */
    if (result == STT_SUCCESS)
    {
        if (st_is_valid_input() == ST_SUCCESS)
        {
            UART_1_PutString("  13\tst_is_valid_input()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  13\tst_is_valid_input()\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
    
    if (result == STT_SUCCESS)
    {   
        if (st_get_count() == 0)
        {
            UART_1_PutString("  14\tst_is_valid_input()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  14\tst_is_valid_input()\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
    
    /*
     *  Test st_set_state().
     */
    if (result == STT_SUCCESS)
    {
        if (st_set_state(ST_STATE_MAXIMUM) == ST_BAD_ARGUMENT)
        {
            UART_1_PutString("  15\tst_set_state()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  15\tst_set_state()\t\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
     
    if (result == STT_SUCCESS)
    {
        if (st_set_state(ST_STATE_4) == ST_SUCCESS)
        {
            UART_1_PutString("  16\tst_set_state()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  16\tst_set_state()\t\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
    
    /*
     *  Initialise st_is_valid_input() test.
     */
    if (result == STT_SUCCESS)
    {
        if (st_add_key("\r") == ST_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
    
    /*
     *  Test st_is_valid_input().
     */
    if (result == STT_SUCCESS)
    {
        if (st_is_valid_input() == ST_SUCCESS)
        {
            UART_1_PutString("  17\tst_is_valid_input()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  17\tst_is_valid_input()\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
    
    if (result == STT_SUCCESS)
    {   
        if (st_get_count() == 1)
        {
            UART_1_PutString("  18\tst_is_valid_input()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  18\tst_is_valid_input()\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
    
    /*
     *  Initialise st_is_valid_input() test.
     */
    if (result == STT_SUCCESS)
    {
        if (st_set_state(ST_STATE_2) == ST_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
    
    /*
     *  Test st_is_valid_input().
     */
    if (result == STT_SUCCESS)
    {   
        if (st_is_valid_input() == ST_FAILURE)
        {
            UART_1_PutString("  19\tst_is_valid_input()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  19\tst_is_valid_input()\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
    
    if (result == STT_SUCCESS)
    {
        st_set_bit(ST_HARDWARE_EVENT);
        
        if (st_is_valid_input() == ST_SUCCESS)
        {
            UART_1_PutString("  20\tst_is_valid_input()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  20\tst_is_valid_input()\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
    
    /*
     *  Initialise st_is_valid_input() test.
     */
    if (result == STT_SUCCESS)
    {
        st_clear_bit(ST_CARRIAGE_RETURN);
        
        UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
    }
    
    /*
     *  Test st_is_valid_input().
     */
    if (result == STT_SUCCESS)
    {   
        if (st_is_valid_input() == ST_FAILURE)
        {
            UART_1_PutString("  21\tst_is_valid_input()\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  21\tst_is_valid_input()\tFAIL\r\n");
            result = STT_FAILURE;
        }
    }
        
    /*
     *  Report test result.
     */
    if (result == STT_SUCCESS)
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
    
    st_stop();
    
    return result;
}

void stt_test_2(void)
{
    st_start();
    
    UART_1_PutString(_state_none_event_none);
    
    for (;;)
    {
        if (st_is_valid_input() == ST_SUCCESS)
        {
            st_transition();
        }
    }
}

/****************************************************************************
 *  Local Functions
 ****************************************************************************/

/****************************************************************************
 *  End of File
 ****************************************************************************/
