/****************************************************************************
 *
 *  File:           button_test.h
 *  Module:         Button Test Library
 *  Project:        Code Vault
 *  Workspace:      PSoC Tools
 *
 *  Author:         Rodney B. Elliott
 *  Date:           4 September 2013
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
#ifndef BUTTON_TEST_H
#define BUTTON_TEST_H
/**
 *  @file button_test.h
 *  @brief Button test library interface.
 *
 *  <H3> Introduction </H3>
 *
 *  The button test library contains two functions that test each of the
 *  functions that comprise the button library.
 *
 *  The first function, but_test_1(), provides complete coverage of the button
 *  library codebase - with two exceptions. The first is that those library
 *  functions that call malloc(), either directly or indirectly, have not had
 *  their #BU_NO_MEMORY return value tested. The second is that it does not
 *  cover the button library interrupt service routine (ISR).
 *
 *  The second function, but_test_2(), provides complete coverage of the ISR.
 *
 *  <H3> Use </H3>
 *
 *  In order to use the library, the programmer must first connect the target
 *  system to a serial terminal configured as 57600 8-N-1. To run the test,
 *  simply call either function but_test_1() or but_test_2() and observe the
 *  serial output. In the case of but_test_1(), this should be as follows.
 *
 *  @code
 *  BUTTON LIBRARY TEST
 *
 *  Test    Function                Result
 *  ----    --------                ------
 *     1    bu_start()              PASS
 *     2    bu_start()              PASS
 *     3    bu_start()              PASS
 *     4    bu_stop()               PASS
 *     5    bu_stop()               PASS
 *     6    bu_stop()               PASS
 *     -    Initialise test...      PASS
 *     7    bu_add_new()            PASS
 *     8    bu_add_new()            PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     9    bu_get_new_object()     PASS
 *    10    bu_get_new_object()     PASS
 *    11    bu_get_new_object()     PASS
 *    12    bu_get_new_object()     PASS
 *    13    bu_get_new_object()     PASS
 *    14    bu_get_old_object()     PASS
 *    15    bu_get_old_object()     PASS
 *    16    bu_get_old_object()     PASS
 *    17    bu_get_old_object()     PASS
 *    18    bu_get_old_object()     PASS
 *    19    bu_get_count()          PASS
 *    20    bu_get_count()          PASS
 *    21    bu_remove_old()         PASS
 *    22    bu_remove_old()         PASS
 *    23    bu_remove_old()         PASS
 *    24    bu_remove_old()         PASS
 *     -    Initialise test...      PASS
 *    25    bu_remove_old()         PASS
 *    26    bu_get_limit()          PASS
 *    27    bu_get_limit()          PASS
 *     -    Initialise test...      PASS
 *    28    bu_set_limit()          PASS
 *    29    bu_set_limit()          PASS
 *    30    bu_set_limit()          PASS
 *    31    bu_destroy()            PASS
 *    32    bu_destroy()            PASS
 *     -    Initialise test...      PASS
 *    33    bu_destroy()            PASS
 *    34    bu_destroy()            PASS
 *
 *  TEST PASSED
 *  @endcode
 *
 *  In the case of but_test_2(), the serial output should be as follows.
 *
 *  @code
 *  BUTTON LIBRARY TEST
 *
 *  Button 1
 *  Button 2
 *  Button 3
 *  Button 4
 *  Button 5
 *  Button 6
 *  Button 7
 *  Button 8
 *  @endcode
 *
 *  While but_test_2() is running, the word 'PRESSED' should appear next to
 *  the name of any buttons pressed by the programmer.
 *
 *  <H3> Hardware </H3>
 *
 *  The button test library has been designed to run on a Cypress CY8CKIT-001
 *  development kit fitted with a PSoC5 CY8C5568AXI-060 module. It requires
 *  access to the following components:
 *
 *  - Clock_1
 *  - Debouncer_1-8
 *  - isr_1
 *  - Status_Reg_1
 *  - UART_1
 *
 *  The following pin components must also be connected to SPNO buttons that
 *  are terminated to ground:
 *
 *  Pin  | Button Name
 *  ---- | ------------
 *  @b P0_0 | Button 1
 *  @b P0_1 | Button 2
 *  @b P0_2 | Button 3
 *  @b P0_3 | Button 4
 *  @b P0_4 | Button 5
 *  @b P0_5 | Button 6
 *  @b P0_6 | Button 7
 *  @b P0_7 | Button 8
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
#define BUT_SUCCESS                     0

/**
 *  @brief Generic failure.
 */
#define BUT_FAILURE                     1

/**
 *  @brief Memory was unable to be allocated from the heap.
 *
 *  Any function returning this value will free any memory that was
 *  successfully allocated from the heap prior to the allocation failure.
 */
#define BUT_NO_MEMORY                   2

/**
 *  @brief A bad argument was passed to a function.
 */
#define BUT_BAD_ARGUMENT                3

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
 *  @brief Tests the functions of the button library.
 *  @return #BUT_SUCCESS if successful, otherwise #BUT_FAILURE.
 */
uint8 but_test_1(void);

/**
 *  @brief Tests the interrupt service routine (ISR) of the button library.
 */
void but_test_2(void);

#endif

/****************************************************************************
 *  End of File
 ****************************************************************************/
