/****************************************************************************
 *
 *  File:           error_test.h
 *  Module:         Error Management Test Library
 *  Project:        Code Vault
 *  Workspace:      PSoC Tools
 *
 *  Author:         Rodney B. Elliott
 *  Date:           27 August 2013
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
#ifndef ERROR_TEST_H
#define ERROR_TEST_H
/**
 *  @file error_test.h
 *  @brief Error management test library interface.
 *
 *  <H3> Introduction </H3>
 *
 *  The error management test library contains a single function that tests
 *  each of the functions that comprise the error management library.
 *
 *  This function, ert_test_1(), provides complete coverage of the error
 *  management library codebase, with one exception. Those error management
 *  library functions that call malloc(), either directly or indirectly,
 *  have not had their #ER_NO_MEMORY return value tested.
 *
 *  <H3> Use </H3>
 *
 *  In order to use the library, the programmer must first connect the target
 *  system to a serial terminal configured as 57600 8-N-1. To run the test,
 *  simply call the function ert_test_1() and observe the serial output, which
 *  should be as follows.
 *
 *  @code
 *  ERROR MANAGEMENT LIBRARY TEST
 *
 *  Test    Function                Result
 *  ----    --------                ------
 *     1    er_add_standard()       PASS
 *     2    er_add_standard()       PASS
 *     3    er_add_standard()       PASS
 *     4    er_add_standard()       PASS
 *     -    Initialise test...      PASS
 *     5    er_add_standard()       PASS
 *     6    er_add_standard()       PASS
 *     7    er_add_standard()       PASS
 *     -    Initialise test...      PASS
 *     8    er_add_standard()       PASS
 *     -    Initialise test...      PASS
 *     9    er_add_standard()       PASS
 *    10    er_add_standard()       PASS
 *     -    Initialise test...      PASS
 *    11    er_add_standard()       PASS
 *    12    er_add_standard()       PASS
 *     -    Initialise test...      PASS
 *    13    er_add_standard()       PASS
 *    14    er_add_standard()       PASS
 *     -    Initialise test...      PASS
 *    15    er_add_standard()       PASS
 *     -    Initialise test...      PASS
 *    16    er_add_special()        PASS
 *    17    er_add_special()        PASS
 *    18    er_add_special()        PASS
 *    19    er_add_special()        PASS
 *    20    er_add_special()        PASS
 *    21    er_add_special()        PASS
 *    22    er_add_special()        PASS
 *    23    er_add_special()        PASS
 *     -    Initialise test...      PASS
 *    24    er_add_special()        PASS
 *    25    er_add_special()        PASS
 *     -    Initialise test...      PASS
 *    26    er_add_special()        PASS
 *     -    Initialise test...      PASS
 *    27    er_add_special()        PASS
 *     -    Initialise test...      PASS
 *    28    er_add_special()        PASS
 *    29    er_add_special()        PASS
 *     -    Initialise test...      PASS
 *    30    er_add_special()        PASS
 *    31    er_add_special()        PASS
 *     -    Initialise test...      PASS
 *    32    er_add_special()        PASS
 *    33    er_add_special()        PASS
 *     -    Initialise test...      PASS
 *    34    er_add_special()        PASS
 *    35    er_get_first_object()   PASS
 *    36    er_get_first_object()   PASS
 *    37    er_get_first_object()   PASS
 *    38    er_get_first_object()   PASS
 *    39    er_get_first_object()   PASS
 *    40    er_get_first_object()   PASS
 *    41    er_get_first_object()   PASS
 *    42    er_get_first_object()   PASS
 *    43    er_get_last_object()    PASS
 *    44    er_get_last_object()    PASS
 *    45    er_get_last_object()    PASS
 *    46    er_get_last_object()    PASS
 *    47    er_get_last_object()    PASS
 *    48    er_get_last_object()    PASS
 *    49    er_get_last_object()    PASS
 *    50    er_get_last_object()    PASS
 *    51    er_get_message()        PASS
 *    52    er_get_message()        PASS
 *    53    er_get_message()        PASS
 *    54    er_get_message()        PASS
 *    55    er_get_message()        PASS
 *    56    er_get_message()        PASS
 *     -    Initialise test...      PASS
 *    57    er_get_message()        PASS
 *    58    er_get_message()        PASS
 *    59    er_get_message()        PASS
 *    60    er_remove()             PASS
 *    61    er_remove()             PASS
 *    62    er_remove()             PASS
 *    63    er_remove()             PASS
 *    64    er_get_count()          PASS
 *    65    er_get_count()          PASS
 *    66    er_get_count()          PASS
 *    67    er_get_timestamp()      PASS
 *    68    er_get_timestamp()      PASS
 *    69    er_get_timestamp()      PASS
 *    70    er_get_timestamp()      PASS
 *    71    er_get_timestamp()      PASS
 *    72    er_get_location()       PASS
 *    73    er_get_location()       PASS
 *    74    er_get_location()       PASS
 *    75    er_get_location()       PASS
 *    76    er_get_location()       PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *    77    er_convert_timestamp()  PASS
 *    78    er_convert_timestamp()  PASS
 *    79    er_convert_timestamp()  PASS
 *    80    er_convert_timestamp()  PASS
 *    81    er_convert_timestamp()  PASS
 *     -    Initialise test...      PASS
 *    82    er_convert_location()   PASS
 *    83    er_convert_location()   PASS
 *    84    er_convert_location()   PASS
 *    85    er_convert_location()   PASS
 *    86    er_convert_location()   PASS
 *    87    er_destroy()            PASS
 *    88    er_destroy()            PASS
 *
 *  TEST PASSED
 *  @endcode
 *
 *  <H3> Hardware </H3>
 *
 *  The error management test library has been designed to run on a Cypress
 *  CY8CKIT-001 development kit fitted with a PSoC5 CY8C5568AXI-060 module. It
 *  requires access to the following components:
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
#define ERT_SUCCESS                     0

/**
 *  @brief Generic failure.
 */
#define ERT_FAILURE                     1

/**
 *  @brief Memory was unable to be allocated from the heap.
 *
 *  Any function returning this value will free any memory that was
 *  successfully allocated from the heap prior to the allocation failure.
 */
#define ERT_NO_MEMORY                   2

/**
 *  @brief A bad argument was passed to a function.
 */
#define ERT_BAD_ARGUMENT                3

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
 *  @brief Tests the functions of the error management library.
 */
void ert_test_1(void);

#endif

/****************************************************************************
 *  End of File
 ****************************************************************************/
