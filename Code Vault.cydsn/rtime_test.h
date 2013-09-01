/****************************************************************************
 *
 *  File:           rtime_test.h
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
#ifndef RTIME_TEST_H
#define RTIME_TEST_H
/**
 *  @file rtime_test.h
 *  @brief Real-time clock test library interface.
 *
 *  <H3> Introduction </H3>
 *
 *  The real-time clock test library contains a single function that tests
 *  each of the functions that comprise the real-time clock (RTC) library.
 *
 *  This function, rtt_test_1(), provides complete coverage of the RTC library
 *  codebase, with one exception. Those RTC library functions that call
 *  malloc(), either directly or indirectly, have not had their #RT_NO_MEMORY
 *  return value tested.
 *
 *  <H3> Use </H3>
 *
 *  In order to use the library, the programmer must first connect the target
 *  system to a serial terminal configured as 57600 8-N-1. To run the test,
 *  simply call the function rtt_test_1() and observe the serial output, which
 *  should be as follows.
 *
 *  @code
 *  REAL-TIME CLOCK LIBRARY TEST
 *
 *  Test    Function                Result
 *  ----    --------                ------
 *     1    rt_set_date()           PASS
 *     -    Initialise test...      PASS
 *     2    rt_set_date()           PASS
 *     3    rt_set_date()           PASS
 *     4    rt_set_date()           PASS
 *     5    rt_set_date()           PASS
 *     -    Initialise test...      PASS
 *     6    rt_set_time()           PASS
 *     -    Initialise test...      PASS
 *     7    rt_set_time()           PASS
 *     8    rt_set_time()           PASS
 *     9    rt_set_time()           PASS
 *    10    rt_set_time()           PASS
 *     -    Initialise test...      PASS
 *    11    rt_write()              PASS
 *     -    Initialise test...      PASS
 *    12    rt_write()              PASS
 *     -    Initialise test...      PASS
 *    13    rt_read()               PASS
 *     -    Initialise test...      PASS
 *    14    rt_read()               PASS
 *    15    rt_read()               PASS
 *    16    rt_read()               PASS
 *    17    rt_convert()            PASS
 *    18    rt_convert()            PASS
 *    19    rt_convert()            PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *    20    rt_convert()            PASS
 *    21    rt_convert()            PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *    22    rt_convert()            PASS
 *    23    rt_convert()            PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *    24    rt_convert()            PASS
 *    25    rt_convert()            PASS
 *
 *  TEST PASSED
 *  @endcode
 *
 *  <H3> Hardware </H3>
 *
 *  The RTC test library has been designed to run on a Cypress CY8CKIT-001
 *  development kit fitted with a PSoC5 CY8C5568AXI-060 module. It requires
 *  access to the following components:
 *
 *  - RTC_1
 *  - UART_1
 *
 *  The PSoC5 module must be fitted with a 32.768kHz crystal, and the 'XTAL
 *  32kHz' source must be enabled in the clock section of the project design
 *  wide resource (*.cydwr) file.
 *
 *  Pin P1_2 on the development kit prototype area must be connected to the
 *  UART RX pin, and pin P1_7 must be connected to the UART TX pin. Ensure
 *  that the RS_232PWR jumper is also set.
 */
 
/****************************************************************************
 *  Modules
 ****************************************************************************/

/****************************************************************************
 *  Definitions and Macros
 ****************************************************************************/
/**
 *  @brief Generic success.
 */
#define RTT_SUCCESS                     0

/**
 *  @brief Generic failure.
 */
#define RTT_FAILURE                     1

/**
 *  @brief Memory was unable to be allocated from the heap.
 *
 *  Any function returning this value will free any memory that was
 *  successfully allocated from the heap prior to the allocation failure.
 */
#define RTT_NO_MEMORY                   2

/**
 *  @brief A bad argument was passed to a function.
 */
#define RTT_BAD_ARGUMENT                3

/****************************************************************************
 *  Typedefs and Structures
 ****************************************************************************/

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
/**
 *  @brief Tests the functions of the RTC library.
 */
void rtt_test_1(void);

#endif

/****************************************************************************
 *  End of File
 ****************************************************************************/
