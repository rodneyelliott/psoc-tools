/****************************************************************************
 *
 *  File:           rtime_test.c
 *  Module:         Real-Time Clock Test Library
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
 *  @file rtime_test.c
 *  @brief Real-time clock test library implementation.
 */
 
/****************************************************************************
 *  Modules
 ****************************************************************************/
#include <device.h>
#include <string.h>

#include "rtime.h"
#include "rtime_test.h"

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
uint8 rtt_test_1(void)
{
    RT_DATA data_0;
    uint8 result = RTT_SUCCESS;
    char string[20] = {0};
        
    UART_1_Start();
    
    UART_1_PutString("\x1b\x5b\x32\x4a");
    UART_1_PutString("REAL-TIME CLOCK LIBRARY TEST\r\n");
    UART_1_PutString("\r\n");
    UART_1_PutString("Test\tFunction\t\tResult\r\n");
    UART_1_PutString("----\t--------\t\t------\r\n");
        
    /*
     *  Test rt_set_date().
     */
    if (result == RTT_SUCCESS)
    {   
        if (rt_set_date(27, 8, 2013) == RT_FAILURE)
        {
            UART_1_PutString("   1\trt_set_date()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   1\trt_set_date()\t\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    /*
     *  Initialise rt_set_date() test.
     */
    if (result == RTT_SUCCESS)
    {
        if (rt_start() == RT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    /*
     *  Test rt_set_date().
     */
    if (result == RTT_SUCCESS)
    {   
        if (rt_set_date(27, 8, 0) == RT_BAD_ARGUMENT)
        {
            UART_1_PutString("   2\trt_set_date()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   2\trt_set_date()\t\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    if (result == RTT_SUCCESS)
    {    
        if (rt_set_date(27, 0, 2013) == RT_BAD_ARGUMENT)
        {
            UART_1_PutString("   3\trt_set_date()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   3\trt_set_date()\t\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    if (result == RTT_SUCCESS)
    {    
        if (rt_set_date(0, 8, 2013) == RT_BAD_ARGUMENT)
        {
            UART_1_PutString("   4\trt_set_date()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   4\trt_set_date()\t\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    if (result == RTT_SUCCESS)
    {   
        if (rt_set_date(27, 8, 2013) == RT_SUCCESS)
        {
            UART_1_PutString("   5\trt_set_date()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   5\trt_set_date()\t\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    /*
     *  Initialise rt_set_time() test.
     */
    if (result == RTT_SUCCESS)
    {
        if (rt_stop() == RT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    /*
     *  Test rt_set_time().
     */
    if (result == RTT_SUCCESS)
    {   
        if (rt_set_time(8, 24, 44) == RT_FAILURE)
        {
            UART_1_PutString("   6\trt_set_time()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   6\trt_set_time()\t\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    /*
     *  Initialise rt_set_time() test.
     */
    if (result == RTT_SUCCESS)
    {
        if (rt_start() == RT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    /*
     *  Test rt_set_time().
     */
    if (result == RTT_SUCCESS)
    {        
        if (rt_set_time(8, 24, 255) == RT_BAD_ARGUMENT)
        {
            UART_1_PutString("   7\trt_set_time()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   7\trt_set_time()\t\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    if (result == RTT_SUCCESS)
    {    
        if (rt_set_time(8, 255, 44) == RT_BAD_ARGUMENT)
        {
            UART_1_PutString("   8\trt_set_time()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   8\trt_set_time()\t\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    if (result == RTT_SUCCESS)
    {    
        if (rt_set_time(255, 24, 44) == RT_BAD_ARGUMENT)
        {
            UART_1_PutString("   9\trt_set_time()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   9\trt_set_time()\t\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    if (result == RTT_SUCCESS)
    {    
        if (rt_set_time(8, 24, 44) == RT_SUCCESS)
        {
            UART_1_PutString("  10\trt_set_time()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  10\trt_set_time()\t\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    /*
     *  Initialise rt_write() test.
     */
    if (result == RTT_SUCCESS)
    {
        if (rt_stop() == RT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    /*
     *  Test rt_write().
     */
    if (result == RTT_SUCCESS)
    {   
        if (rt_write() == RT_FAILURE)
        {
            UART_1_PutString("  11\trt_write()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  11\trt_write()\t\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    /*
     *  Initialise rt_write() test.
     */
    if (result == RTT_SUCCESS)
    {
        if (rt_start() == RT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    /*
     *  Test rt_write().
     */
    if (result == RTT_SUCCESS)
    {   
        if (rt_write() == RT_SUCCESS)
        {
            UART_1_PutString("  12\trt_write()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  12\trt_write()\t\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    /*
     *  Initialise rt_read() test.
     */
    if (result == RTT_SUCCESS)
    {
        if (rt_stop() == RT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    /*
     *  Test rt_read().
     */
    if (result == RTT_SUCCESS)
    {   
        if (rt_read(&data_0) == RT_FAILURE)
        {
            UART_1_PutString("  13\trt_read()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  13\trt_read()\t\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    /*
     *  Initialise rt_read() test.
     */
    if (result == RTT_SUCCESS)
    {
        if (rt_start() == RT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    /*
     *  Test rt_read().
     */
    if (result == RTT_SUCCESS)
    {        
        if (rt_read(NULL) == RT_BAD_ARGUMENT)
        {
            UART_1_PutString("  14\trt_read()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  14\trt_read()\t\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    if (result == RTT_SUCCESS)
    {
        if (rt_read(&data_0) == RT_SUCCESS)
        {
            UART_1_PutString("  15\trt_read()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  15\trt_read()\t\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    if (result == RTT_SUCCESS)
    {
        if (data_0.Year == 1918)
        {
            UART_1_PutString("  16\trt_read()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  16\trt_read()\t\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    /*
     *  Test rt_convert().
     */
    if (result == RTT_SUCCESS)
    {
        if (rt_convert(NULL, NULL) == RT_BAD_ARGUMENT)
        {
            UART_1_PutString("  17\trt_convert()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  17\trt_convert()\t\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    if (result == RTT_SUCCESS)
    {
        if (rt_convert(NULL, string) == RT_BAD_ARGUMENT)
        {
            UART_1_PutString("  18\trt_convert()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  18\trt_convert()\t\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    if (result == RTT_SUCCESS)
    {
        if (rt_convert(&data_0, NULL) == RT_BAD_ARGUMENT)
        {
            UART_1_PutString("  19\trt_convert()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  19\trt_convert()\t\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    /*
     *  Initialise rt_convert() test.
     */
    if (result == RTT_SUCCESS)
    {
        if (rt_set_date(1, 2, 2013) == RT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    if (result == RTT_SUCCESS)
    {
        if (rt_set_time(3, 4, 5) == RT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    if (result == RTT_SUCCESS)
    {
        if (rt_write() == RT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    if (result == RTT_SUCCESS)
    {
        if (rt_read(&data_0) == RT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    /*
     *  Test rt_convert().
     */
    if (result == RTT_SUCCESS)
    {
        if (rt_convert(&data_0, string) == RT_SUCCESS)
        {
            UART_1_PutString("  20\trt_convert()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  20\trt_convert()\t\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
        
    if (result == RTT_SUCCESS)
    {   
        if (strcmp(string, "01/02/2013 03:04:05") == 0)
        {
            UART_1_PutString("  21\trt_convert()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  21\trt_convert()\t\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    /*
     *  Initialise rt_convert() test.
     */
    if (result == RTT_SUCCESS)
    {
        if (rt_set_date(11, 12, 2013) == RT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    if (result == RTT_SUCCESS)
    {
        if (rt_set_time(12, 13, 14) == RT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    if (result == RTT_SUCCESS)
    {
        if (rt_write() == RT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    if (result == RTT_SUCCESS)
    {
        if (rt_read(&data_0) == RT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    /*
     *  Test rt_convert().
     */
    if (result == RTT_SUCCESS)
    {
        if (rt_convert(&data_0, string) == RT_SUCCESS)
        {
            UART_1_PutString("  22\trt_convert()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  22\trt_convert()\t\tPASS\r\n");
            result = RTT_FAILURE;
        }
    }
        
    if (result == RTT_SUCCESS)
    {   
        if (strcmp(string, "11/12/2013 12:13:14") == 0)
        {
            UART_1_PutString("  23\trt_convert()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  23\trt_convert()\t\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    /*
     *  Initialise rt_convert() test.
     */
    if (result == RTT_SUCCESS)
    {
        if (rt_set_time(0, 0, 0) == RT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    if (result == RTT_SUCCESS)
    {
        if (rt_write() == RT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    if (result == RTT_SUCCESS)
    {
        if (rt_read(&data_0) == RT_SUCCESS)
        {
            UART_1_PutString("   -\tInitialise test...\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("   -\tInitialise test...\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
    
    /*
     *  Test rt_convert().
     */
    if (result == RTT_SUCCESS)
    {
        if (rt_convert(&data_0, string) == RT_SUCCESS)
        {
            UART_1_PutString("  24\trt_convert()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  24\trt_convert()\t\tPASS\r\n");
            result = RTT_FAILURE;
        }
    }
    
    if (result == RTT_SUCCESS)
    {   
        if (strcmp(string, "11/12/2013 00:00:00") == 0)
        {
            UART_1_PutString("  25\trt_convert()\t\tPASS\r\n");
        }
        else
        {
            UART_1_PutString("  25\trt_convert()\t\tFAIL\r\n");
            result = RTT_FAILURE;
        }
    }
     
    /*
     *  Report test result.
     */
    if (result == RTT_SUCCESS)
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
    while ((UART_1_ReadTxStatus() & UART_1_TX_STS_FIFO_EMPTY) !=
        UART_1_TX_STS_FIFO_EMPTY)
    {
        CyDelay(1);
    }
    
    UART_1_Stop();
    rt_stop();
    
    return result;
}

/****************************************************************************
 *  Local Functions
 ****************************************************************************/

/****************************************************************************
 *  End of File
 ****************************************************************************/
