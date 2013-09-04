/****************************************************************************
 *
 *  File:           cllist_test.h
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
#ifndef CLLIST_TEST_H
#define CLLIST_TEST_H
/**
 *  @file cllist_test.h
 *  @brief Circular linked list test library interface.
 *
 *  <H3> Introduction </H3>
 *
 *  The circular linked list test library contains a single function that
 *  tests each of the functions that comprise the circular linked list (CLL)
 *  library.
 *
 *  This function, clt_test_1(), provides complete coverage of the CLL library
 *  codebase, with one exception. Those CLL library functions that call
 *  dl_create() have not had their #CL_NO_MEMORY return value tested.
 *
 *  <H3> Use </H3>
 *
 *  In order to use the library, the programmer must first connect the target
 *  system to a serial terminal configured as 57600 8-N-1. To run the test,
 *  simply call the function clt_test_1() and observe the serial output, which
 *  should be as follows.
 *
 *  @code
 *  CIRCULAR LINKED LIBRARY LIBRARY TEST
 *
 *  Test    Function                Result
 *  ----    --------                ------
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     1    cl_add_after()          PASS
 *     2    cl_add_after()          PASS
 *     3    cl_add_after()          PASS
 *     4    cl_add_after()          PASS
 *     5    cl_add_after()          PASS
 *     6    cl_add_after()          PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     7    cl_add_before()         PASS
 *     8    cl_add_before()         PASS
 *     9    cl_add_before()         PASS
 *    10    cl_add_before()         PASS
 *    11    cl_add_before()         PASS
 *    12    cl_add_before()         PASS
 *    13    cl_remove_current()     PASS
 *    14    cl_remove_current()     PASS
 *    15    cl_remove_current()     PASS
 *    16    cl_remove_current()     PASS
 *    17    cl_remove_current()     PASS
 *    18    cl_remove_current()     PASS
 *    19    cl_remove_current()     PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *    20    cl_move_forward()       PASS
 *    21    cl_move_forward()       PASS
 *    22    cl_move_forward()       PASS
 *    23    cl_move_forward()       PASS
 *    24    cl_move_forward()       PASS
 *    25    cl_move_backward()      PASS
 *    26    cl_move_backward()      PASS
 *    27    cl_move_backward()      PASS
 *    28    cl_move_backward()      PASS
 *    29    cl_move_backward()      PASS
 *    30    cl_get_current_object() PASS
 *    31    cl_get_current_object() PASS
 *    32    cl_get_current_object() PASS
 *    33    cl_get_current_object() PASS
 *    34    cl_get_current_object() PASS
 *    35    cl_get_current_object() PASS
 *    36    cl_get_current_object() PASS
 *    37    cl_get_current_object() PASS
 *    38    cl_get_count()          PASS
 *    39    cl_get_count()          PASS
 *    40    cl_destroy()            PASS
 *    41    cl_destroy()            PASS
 *    42    cl_destroy()            PASS
 *
 *  TEST PASSED
 *  @endcode
 *
 *  Alternatively, if no serial terminal is available, the clt_test_1() return
 *  value may be checked to see if the test completed successfully or not.
 *
 *  <H3> Hardware </H3>
 *
 *  The CLL test library has been designed to run on a Cypress CY8CKIT-001
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
#define CLT_SUCCESS                     0

/**
 *  @brief Generic failure.
 */
#define CLT_FAILURE                     1

/**
 *  @brief Memory was unable to be allocated from the heap.
 *
 *  Any function returning this value will free any memory that was
 *  successfully allocated from the heap prior to the allocation failure.
 */
#define CLT_NO_MEMORY                   2

/**
 *  @brief A bad argument was passed to a function.
 */
#define CLT_BAD_ARGUMENT                3

/****************************************************************************
 *  Typedefs and Structures
 ****************************************************************************/
/**
 *  @brief The CLL test library object.
 */
typedef struct CLT_OBJECT
{
    /**
     *  @brief A pointer to an ASCII string.
     */
    char *string;
    
    /**
     *  @brief The object identification number.
     */
    uint8 number;
} CLT_OBJECT;

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
/**
 *  @brief Tests the functions of the CLL library.
 *  @return #CLT_SUCCESS if successful, otherwise #CLT_FAILURE.
 */
uint8 clt_test_1(void);

#endif

/****************************************************************************
 *  End of File
 ****************************************************************************/
