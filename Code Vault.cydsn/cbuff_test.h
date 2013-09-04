/****************************************************************************
 *
 *  File:           cbuff_test.h
 *  Module:         Circular Buffer Test Library
 *  Project:        Code Vault
 *  Workspace:      PSoC Tools
 *
 *  Author:         Rodney B. Elliott
 *  Date:           23 August 2013
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
#ifndef CBUFF_TEST_H
#define CBUFF_TEST_H
/**
 *  @file cbuff_test.h
 *  @brief Circular buffer test library interface.
 *
 *  <H3> Introduction </H3>
 *
 *  The circular buffer test library contains a single function that tests
 *  each of the functions that comprise the circular buffer library.
 *
 *  This function, cbt_test_1(), provides complete coverage of the circular
 *  buffer library codebase, with one exception. Those circular buffer library
 *  functions that call malloc(), either directly or indirectly, have not had
 *  their #CB_NO_MEMORY return value tested.
 *
 *  <H3> Use </H3>
 *
 *  In order to use the library, the programmer must first connect the target
 *  system to a serial terminal configured as 57600 8-N-1. To run the test,
 *  simply call the function cbt_test_1() and observe the serial output, which
 *  should be as follows.
 *
 *  @code
 *  CIRCULAR BUFFER LIBRARY TEST
 *
 *  Test    Function                Result
 *  ----    --------                ------
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     1    cb_add_new()            PASS
 *     2    cb_add_new()            PASS
 *     3    cb_add_new()            PASS
 *     4    cb_add_new()            PASS
 *     5    cb_add_new()            PASS
 *     6    cb_add_new()            PASS
 *     7    cb_add_new()            PASS
 *     8    cb_remove_old()         PASS
 *     9    cb_remove_old()         PASS
 *    10    cb_remove_old()         PASS
 *    11    cb_remove_old()         PASS
 *    12    cb_remove_old()         PASS
 *    13    cb_remove_old()         PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *    14    cb_get_old_object()     PASS
 *    15    cb_get_old_object()     PASS
 *    16    cb_get_old_object()     PASS
 *    17    cb_get_old_object()     PASS
 *    18    cb_get_old_object()     PASS
 *    19    cb_get_old_object()     PASS
 *    20    cb_get_old_object()     PASS
 *    21    cb_get_old_object()     PASS
 *    22    cb_get_new_object()     PASS
 *    23    cb_get_new_object()     PASS
 *    24    cb_get_new_object()     PASS
 *    25    cb_get_new_object()     PASS
 *    26    cb_get_new_object()     PASS
 *    27    cb_get_new_object()     PASS
 *    28    cb_get_new_object()     PASS
 *    29    cb_get_old_object()     PASS
 *    30    cb_get_count()          PASS
 *    31    cb_get_count()          PASS
 *    32    cb_get_count()          PASS
 *    33    cb_get_limit()          PASS
 *    34    cb_get_limit()          PASS
 *    35    cb_set_limit()          PASS
 *    36    cb_set_limit()          PASS
 *    37    cb_set_limit()          PASS
 *    38    cb_destroy()            PASS
 *    39    cb_destroy()            PASS
 *    40    cb_destroy()            PASS
 *
 *  TEST PASSED
 *  @endcode
 *
 *  Alternatively, if no serial terminal is available, the cbt_test_1() return
 *  value may be checked to see if the test completed successfully or not.
 *
 *  <H3> Hardware </H3>
 *
 *  The circular buffer test library has been designed to run on a Cypress
 *  CY8CKIT-001 development kit fitted with a PSoC5 CY8C5568AXI-060 module. It
 *  requires access to the following components:
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
#define CBT_SUCCESS                     0

/**
 *  @brief Generic failure.
 */
#define CBT_FAILURE                     1

/**
 *  @brief Memory was unable to be allocated from the heap.
 *
 *  Any function returning this value will free any memory that was
 *  successfully allocated from the heap prior to the allocation failure.
 */
#define CBT_NO_MEMORY                   2

/**
 *  @brief A bad argument was passed to a function.
 */
#define CBT_BAD_ARGUMENT                3

/****************************************************************************
 *  Typedefs and Structures
 ****************************************************************************/
/**
 *  @brief The circular buffer test library object.
 */
typedef struct CBT_OBJECT
{
    /**
     *  @brief A pointer to an ASCII string.
     */
    char *string;
    
    /**
     *  @brief The object identification number.
     */
    uint8 number;
} CBT_OBJECT;

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
/**
 *  @brief Tests the functions of the circular buffer library.
 *  @return #CBT_SUCCESS if successful, otherwise #CBT_FAILURE.
 */
uint8 cbt_test_1(void);

#endif

/****************************************************************************
 *  End of File
 ****************************************************************************/
