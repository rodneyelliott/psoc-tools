/****************************************************************************
 *
 *  File:           misc_test.h
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
#ifndef MISC_TEST_H
#define MISC_TEST_H
/**
 *  @file misc_test.h
 *  @brief Miscellaneous function test library interface.
 *
 *  <H3> Introduction </H3>
 *
 *  The miscellaneous function test library contains a single function that
 *  tests each of the functions that comprise the miscellaneous function
 *  library.
 *
 *  This function, mit_test_1(), provides complete coverage of the
 *  miscellaneous function library codebase.
 *
 *  <H3> Use </H3>
 *
 *  In order to use the library, the programmer must first connect the target
 *  system to a serial terminal configured as 57600 8-N-1. To run the test,
 *  simply call the function mit_test_1() and observe the serial output, which
 *  should be as follows.
 *
 *  @code
 *  MISCELLANEOUS FUNCTION LIBRARY TEST
 *
 *  Test    Function                Result
 *  ----    --------                ------
 *     1    mi_utoa()               PASS
 *     2    mi_utoa()               PASS
 *     3    mi_utoa()               PASS
 *     4    mi_utoa()               PASS
 *     5    mi_utoa()               PASS
 *  
 *  TEST PASSED
 *  @endcode
 *
 *  Alternatively, if no serial terminal is available, the mit_test_1() return
 *  value may be checked to see if the test completed successfully or not.
 *
 *  <H3> Hardware </H3>
 *
 *  The miscellaneous function test library has been designed to run on a
 *  Cypress CY8CKIT-001 development kit fitted with a PSoC5 CY8C5568AXI-060
 *  module. It requires access to the following components:
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
#define MIT_SUCCESS                     0

/**
 *  @brief Generic failure.
 */
#define MIT_FAILURE                     1

/**
 *  @brief Memory was unable to be allocated from the heap.
 *
 *  Any function returning this value will free any memory that was
 *  successfully allocated from the heap prior to the allocation failure.
 */
#define MIT_NO_MEMORY                   2

/**
 *  @brief A bad argument was passed to a function.
 */
#define MIT_BAD_ARGUMENT                3

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
 *  @brief Tests the functions of the miscellaneous function library.
 *  @return #MIT_SUCCESS if successful, otherwise #MIT_FAILURE.
 */
uint8 mit_test_1(void);

#endif

/****************************************************************************
 *  End of File
 ****************************************************************************/
