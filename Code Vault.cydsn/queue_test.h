/****************************************************************************
 *
 *  File:           queue_test.h
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
#ifndef QUEUE_TEST_H
#define QUEUE_TEST_H
/**
 *  @file queue_test.h
 *  @brief Queue test library interface.
 *
 *  <H3> Introduction </H3>
 *
 *  The queue test library contains a single function that tests each of the
 *  functions that comprise the queue library.
 *
 *  This function, qut_test_1(), provides complete coverage of the queue
 *  library codebase, with one exception. Those queue library functions that
 *  call dl_create() have not had their #QU_NO_MEMORY return value tested.
 *
 *  <H3> Use </H3>
 *
 *  In order to use the library, the programmer must first connect the target
 *  system to a serial terminal configured as 57600 8-N-1. To run the test,
 *  simply call the function qut_test_1() and observe the serial output, which
 *  should be as follows.
 *
 *  @code
 *  QUEUE LIBRARY TEST
 *  
 *  Test    Function                Result
 *  ----    --------                ------
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     1    qu_add_last()           PASS
 *     2    qu_add_last()           PASS
 *     3    qu_add_last()           PASS
 *     4    qu_add_last()           PASS
 *     5    qu_add_last()           PASS
 *     6    qu_add_last()           PASS
 *     7    qu_add_last()           PASS
 *     8    qu_remove_first()       PASS
 *     9    qu_remove_first()       PASS
 *    10    qu_remove_first()       PASS
 *    11    qu_remove_first()       PASS
 *    12    qu_remove_first()       PASS
 *    13    qu_remove_first()       PASS
 *    14    qu_remove_first()       PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *    15    qu_get_first_object()   PASS
 *    16    qu_get_first_object()   PASS
 *    17    qu_get_first_object()   PASS
 *    18    qu_get_first_object()   PASS
 *    19    qu_get_first_object()   PASS
 *    20    qu_get_first_object()   PASS
 *    21    qu_get_first_object()   PASS
 *    22    qu_get_first_object()   PASS
 *    23    qu_get_count()          PASS
 *    24    qu_get_count()          PASS
 *    25    qu_get_limit()          PASS
 *    26    qu_get_limit()          PASS
 *    27    qu_set_limit()          PASS
 *    28    qu_set_limit()          PASS
 *    29    qu_set_limit()          PASS
 *    30    qu_set_limit()          PASS
 *    31    qu_set_limit()          PASS
 *    32    qu_destroy()            PASS
 *    33    qu_destroy()            PASS
 *    34    qu_destroy()            PASS
 *  
 *  TEST PASSED
 *  @endcode
 *
 *  Alternatively, if no serial terminal is available, the qut_test_1() return
 *  value may be checked to see if the test completed successfully or not.
 *
 *  <H3> Hardware </H3>
 *
 *  The queue test library has been designed to run on a Cypress CY8CKIT-001
 *  development kit fitted with a PSoC5 CY8C5568AXI-060 module. It requires
 *  access to the following components:
 *
 *  - UART_1
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
#define QUT_SUCCESS                     0

/**
 *  @brief Generic failure.
 */
#define QUT_FAILURE                     1

/**
 *  @brief Memory was unable to be allocated from the heap.
 *
 *  Any function returning this value will free any memory that was
 *  successfully allocated from the heap prior to the allocation failure.
 */
#define QUT_NO_MEMORY                   2

/**
 *  @brief A bad argument was passed to a function.
 */
#define QUT_BAD_ARGUMENT                3

/****************************************************************************
 *  Typedefs and Structures
 ****************************************************************************/
/**
 *  @brief The queue test library object.
 */
typedef struct QUT_OBJECT
{
    /**
     *  @brief A pointer to an ASCII string.
     */
    char *string;
    
    /**
     *  @brief The object identification number.
     */
    uint8 number;
} QUT_OBJECT;

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
/**
 *  @brief Tests the functions of the queue library.
 *  @return #QUT_SUCCESS if successful, otherwise #QUT_FAILURE.
 */
uint8 qut_test_1(void);

#endif

/****************************************************************************
 *  End of File
 ****************************************************************************/
