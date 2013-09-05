/****************************************************************************
 *
 *  File:           deque_test.h
 *  Module:         Deque Test Library
 *  Project:        Code Vault
 *  Workspace:      PSoC Tools
 *
 *  Author:         Rodney B. Elliott
 *  Date:           20 August 2013
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
#ifndef DEQUE_TEST_H
#define DEQUE_TEST_H
/**
 *  @file deque_test.h
 *  @brief Deque test library interface.
 *
 *  <H3> Introduction </H3>
 *
 *  The deque test library contains a single function that tests each of the
 *  functions that comprise the deque library.
 *
 *  This function, det_test_1(), provides complete coverage of the deque
 *  library codebase, with one exception. Those deque library functions that
 *  call dl_create() have not had their #DE_NO_MEMORY return value tested.
 *
 *  <H3> Use </H3>
 *
 *  In order to use the library, the programmer must first connect the target
 *  system to a serial terminal configured as 57600 8-N-1. To run the test,
 *  simply call the function det_test_1() and observe the serial output, which
 *  should be as follows.
 *
 *  @code
 *  DEQUE LIBRARY TEST
 *  
 *  Test    Function                Result
 *  ----    --------                ------
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     1    de_add_first()          PASS
 *     2    de_add_first()          PASS
 *     3    de_add_first()          PASS
 *     4    de_add_first()          PASS
 *     5    de_add_first()          PASS
 *     6    de_add_first()          PASS
 *     7    de_add_first()          PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     8    de_add_last()           PASS
 *     9    de_add_last()           PASS
 *    10    de_add_last()           PASS
 *    11    de_add_last()           PASS
 *    12    de_add_last()           PASS
 *    13    de_add_last()           PASS
 *    14    de_add_last()           PASS
 *    15    de_remove_first()       PASS
 *    16    de_remove_first()       PASS
 *    17    de_remove_first()       PASS
 *    18    de_remove_first()       PASS
 *    19    de_remove_first()       PASS
 *    20    de_remove_first()       PASS
 *    21    de_remove_first()       PASS
 *    22    de_remove_last()        PASS
 *    23    de_remove_last()        PASS
 *    24    de_remove_last()        PASS
 *    25    de_remove_last()        PASS
 *    26    de_remove_last()        PASS
 *    27    de_remove_last()        PASS
 *    28    de_remove_last()        PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *    29    de_get_first_object()   PASS
 *    30    de_get_first_object()   PASS
 *    31    de_get_first_object()   PASS
 *    32    de_get_first_object()   PASS
 *    33    de_get_first_object()   PASS
 *    34    de_get_first_object()   PASS
 *    35    de_get_first_object()   PASS
 *    36    de_get_first_object()   PASS
 *    37    de_get_last_object()    PASS
 *    38    de_get_last_object()    PASS
 *    39    de_get_last_object()    PASS
 *    40    de_get_last_object()    PASS
 *    41    de_get_last_object()    PASS
 *    42    de_get_last_object()    PASS
 *    43    de_get_last_object()    PASS
 *    44    de_get_last_object()    PASS
 *    45    de_get_count()          PASS
 *    46    de_get_count()          PASS
 *    47    de_get_limit()          PASS
 *    48    de_get_limit()          PASS
 *    49    de_set_limit()          PASS
 *    50    de_set_limit()          PASS
 *    51    de_set_limit()          PASS
 *    52    de_set_limit()          PASS
 *    53    de_set_limit()          PASS
 *    54    de_destroy()            PASS
 *    55    de_destroy()            PASS
 *    56    de_destroy()            PASS
 *  
 *  TEST PASSED
 *  @endcode
 *
 *  Alternatively, if no serial terminal is available, the det_test_1() return
 *  value may be checked to see if the test completed successfully or not.
 *
 *  <H3> Hardware </H3>
 *
 *  The deque test library has been designed to run on a Cypress CY8CKIT-001
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
#define DET_SUCCESS                     0

/**
 *  @brief Generic failure.
 */
#define DET_FAILURE                     1

/**
 *  @brief Memory was unable to be allocated from the heap.
 *
 *  Any function returning this value will free any memory that was
 *  successfully allocated from the heap prior to the allocation failure.
 */
#define DET_NO_MEMORY                   2

/**
 *  @brief A bad argument was passed to a function.
 */
#define DET_BAD_ARGUMENT                3

/****************************************************************************
 *  Typedefs and Structures
 ****************************************************************************/
/**
 *  @brief The deque test library object.
 */
typedef struct DET_OBJECT
{
    /**
     *  @brief A pointer to an ASCII string.
     */
    char *string;
    
    /**
     *  @brief The object identification number.
     */
    uint8 number;
} DET_OBJECT;

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
/**
 *  @brief Tests the functions of the deque library.
 *  @return #DET_SUCCESS if successful, otherwise #DET_FAILURE.
 */
uint8 det_test_1(void);

#endif

/****************************************************************************
 *  End of File
 ****************************************************************************/
