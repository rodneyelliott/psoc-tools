/****************************************************************************
 *
 *  File:           dllist_test.h
 *  Module:         Doubly Linked List Test Library
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
#ifndef DLLIST_TEST_H
#define DLLIST_TEST_H
/**
 *  @file dllist_test.h
 *  @brief Doubly linked list test library interface.
 *
 *  <H3> Introduction </H3>
 *
 *  The doubly linked list test library contains a single function that tests
 *  each of the functions that comprise the doubly linked list (DLL) library.
 *
 *  This function, dlt_test_1(), provides complete coverage of the DLL library
 *  codebase, with one exception. The following dl_create() code fragment has
 *  not been tested:
 *
 *  @code
 *  {
 *      *node = NULL;
 *
 *      result = DL_NO_MEMORY;
 *  }
 *  @endcode
 *
 *  As a consequence, those DLL library functions that call dl_create() have
 *  not had their #DL_NO_MEMORY return value tested.
 *
 *  <H3> Use </H3>
 *
 *  In order to use the library, the programmer must first connect the target
 *  system to a serial terminal configured as 57600 8-N-1. To run the test,
 *  simply call the function dlt_test_1() and observe the serial output, which
 *  should be as follows.
 *
 *  @code
 *  DOUBLY LINKED LIST LIBRARY TEST
 *
 *  Test    Function                Result
 *  ----    --------                ------
 *     -    Initialise test...      PASS
 *     1    dl_create()             PASS
 *     2    dl_create()             PASS
 *     3    dl_create()             PASS
 *     4    dl_create()             PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     5    dl_insert_before()      PASS
 *     6    dl_insert_before()      PASS
 *     7    dl_insert_before()      PASS
 *     8    dl_insert_before()      PASS
 *     9    dl_insert_before()      PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *    10    dl_insert_after()       PASS
 *    11    dl_insert_after()       PASS
 *    12    dl_insert_after()       PASS
 *    13    dl_insert_after()       PASS
 *    14    dl_insert_after()       PASS
 *    15    dl_get_first()          PASS
 *    16    dl_get_first()          PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *    17    dl_add_first()          PASS
 *    18    dl_add_first()          PASS
 *    19    dl_add_first()          PASS
 *    20    dl_get_last()           PASS
 *    21    dl_get_last()           PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *    22    dl_add_last()           PASS
 *    23    dl_add_last()           PASS
 *    24    dl_add_last()           PASS
 *    25    dl_get_previous()       PASS
 *    26    dl_get_previous()       PASS
 *    27    dl_add_before()         PASS
 *    28    dl_add_before()         PASS
 *    29    dl_add_before()         PASS
 *    30    dl_get_next()           PASS
 *    31    dl_get_next()           PASS
 *    32    dl_add_after()          PASS
 *    33    dl_add_after()          PASS
 *    34    dl_add_after()          PASS
 *    35    dl_get_count()          PASS
 *    36    dl_get_count()          PASS
 *    37    dl_get_object()         PASS
 *    38    dl_get_object()         PASS
 *    39    dl_get_object()         PASS
 *    40    dl_get_object()         PASS
 *    41    dl_extract()            PASS
 *    42    dl_extract()            PASS
 *    43    dl_delete()             PASS
 *    44    dl_delete()             PASS
 *    45    dl_destroy()            PASS
 *    46    dl_destroy()            PASS
 *    47    dl_join()               PASS
 *    48    dl_join()               PASS
 *    49    dl_join()               PASS
 *    50    dl_join()               PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *    51    dl_exchange()           PASS
 *    52    dl_exchange()           PASS
 *    53    dl_exchange()           PASS
 *    54    dl_exchange()           PASS
 *    55    dl_exchange()           PASS
 *    56    dl_exchange()           PASS
 *    57    dl_exchange()           PASS
 *    58    dl_update()             PASS
 *    59    dl_update()             PASS
 *    60    dl_update()             PASS
 *
 *  TEST PASSED
 *  @endcode
 *
 *  <H3> Hardware </H3>
 *
 *  The DLL test library has been designed to run on a Cypress CY8CKIT-001
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
#define DLT_SUCCESS                     0

/**
 *  @brief Generic failure.
 */
#define DLT_FAILURE                     1

/**
 *  @brief Memory was unable to be allocated from the heap.
 *
 *  Any function returning this value will free any memory that was
 *  successfully allocated from the heap prior to the allocation failure.
 */
#define DLT_NO_MEMORY                   2

/**
 *  @brief A bad argument was passed to a function.
 */
#define DLT_BAD_ARGUMENT                3

/****************************************************************************
 *  Typedefs and Structures
 ****************************************************************************/
/**
 *  @brief The DLL test library object.
 */
typedef struct DLT_OBJECT
{
    /**
     *  @brief A pointer to an ASCII string.
     */
    char *string;
    
    /**
     *  @brief The object identification number.
     */
    uint8 number;
} DLT_OBJECT;

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
/**
 *  @brief Tests the functions of the DLL library.
 */
void dlt_test_1(void);

#endif

/****************************************************************************
 *  End of File
 ****************************************************************************/
