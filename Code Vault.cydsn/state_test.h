/****************************************************************************
 *
 *  File:           state_test.h
 *  Module:         Finite State Machine Test Library
 *  Project:        Code Vault
 *  Workspace:      PSoC Tools
 *
 *  Author:         Rodney B. Elliott
 *  Date:           8 September 2013
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
#ifndef STATE_TEST_H
#define STATE_TEST_H
/**
 *  @file state_test.h
 *  @brief Finite state machine test library interface.
 *
 *  <H3> Introduction </H3>
 *
 *  The finite state machine test library contains two functions that test
 *  each of the functions that comprise the finite state machine (FSM)
 *  library.
 
 *  <H3> Use </H3>
 *
 *  In order to use the library, the programmer must first connect the target
 *  system to a serial terminal configured as 57600 8-N-1. To run the test,
 *  simply call either function stt_test_1() or stt_test_2() and observe the
 *  serial output. In the case of stt_test_1(), this should be as follows.
 *
 *  @code
 *  FINITE STATE MACHINE LIBRARY TEST
 *
 *  Test    Function                Result
 *  ----    --------                ------
 *     -    Initialise test...      PASS
 *     1    st_add_key()            PASS
 *     2    st_add_key()            PASS
 *     3    st_get_limit()          PASS
 *     -    Initialise test...      PASS
 *     -    Initialise test...      PASS
 *     4    st_set_limit()          PASS
 *     5    st_set_limit()          PASS
 *     6    st_copy_buffer()        PASS
 *     7    st_copy_buffer()        PASS
 *     8    st_copy_buffer()        PASS
 *     9    st_get_count()          PASS
 *    10    st_empty_buffer()       PASS
 *    11    st_copy_buffer()        PASS
 *    12    st_is_valid_input()     PASS
 *     -    Initialise test...      PASS
 *    13    st_is_valid_input()     PASS
 *    14    st_is_valid_input()     PASS
 *    15    st_set_state()          PASS
 *    16    st_set_state()          PASS
 *     -    Initialise test...      PASS
 *    17    st_is_valid_input()     PASS
 *    18    st_is_valid_input()     PASS
 *     -    Initialise test...      PASS
 *    19    st_is_valid_input()     PASS
 *    20    st_is_valid_input()     PASS
 *     -    Initialise test...      PASS
 *    21    st_is_valid_input()     PASS
 *
 *  TEST PASSED
 *  @endcode
 *
 *  Note that the following FSM library functions are tested implicitly
 *  by stt_test_1() rather than explicitly:
 *
 *  - st_start()
 *  - st_stop()
 *  - st_set_bit()
 *  - st_clear_bit()
 
 *  In the case of stt_test_2(), the serial output will vary depending on the
 *  current state.
 *
 *  <H3> Hardware </H3>
 *
 *  The FSM test library has been designed to run on a Cypress CY8CKIT-001
 *  development kit fitted with a PSoC5 CY8C5568AXI-060 module. It requires
 *  access to the following components:
 *
 *  - isr_2
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
#define STT_SUCCESS                     0

/**
 *  @brief Generic failure.
 */
#define STT_FAILURE                     1

/**
 *  @brief Memory was unable to be allocated from the heap.
 *
 *  Any function returning this value will free any memory that was
 *  successfully allocated from the heap prior to the allocation failure.
 */
#define STT_NO_MEMORY                   2

/**
 *  @brief A bad argument was passed to a function.
 */
#define STT_BAD_ARGUMENT                3

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
 *  @brief Tests the functions of the FSM library.
 *  @return #STT_SUCCESS if successful, otherwise #STT_FAILURE.
 */
uint8 stt_test_1(void);

/**
 *  @brief Tests the interrupt service routine (ISR) of the FSM library.
 */
void stt_test_2(void);

#endif

/****************************************************************************
 *  End of File
 ****************************************************************************/
