/****************************************************************************
 *
 *  File:           state.h
 *  Module:         Finite State Machine Library
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
#ifndef STATE_H
#define STATE_H
/**
 *  @file state.h
 *  @brief Finite state machine library interface.
 *
 *  <H3> Introduction </H3>
 *
 *  The finite state machine library is a collection of functions that enable
 *  the programmer to deploy the abstract model of computation known as the
 *  finite state machine (FSM) within their project.
 *
 *  A typical FSM consists of several @em states, each of which describes a
 *  particular system configuration. Each state is normally associated with
 *  one or more @em events. When an event occurs, it causes the system to
 *  @em transition from one state to another. A transition consists of a set
 *  of @em actions that are performed whenever an event or other matching
 *  condition occurs.
 *
 *  The library FSM is text-based, meaning that input and output take place
 *  via a serial terminal. Because serial terminals (both real and virtual)
 *  come equipped with a keyboard, they are ideal for providing a rich user
 *  interface while consuming a minimum of application resources.
 *
 *  The library consists of several functional elements, the first of which is
 *  the circular buffer used to hold FSM input. This is a first-in, first-out
 *	(FIFO) buffer. Each time the user presses a key, the library creates a
 *	node and inserts it into the circular buffer.
 *
 *  Each node contains a pointer to an object that is normally owned by the
 *  library - that is, the library is responsible for the object's creation,
 *  right through to its eventual destruction. There is one situation where
 *  the programmer is responsible for the object's destruction, and this is
 *  described in detail later on. Objects contain a record of a key that was
 *  pressed by the user.
 *
 *  By default, the circular buffer is restricted to containing a maximum of
 *  64 nodes. This limit may be increased, decreased, or removed altogether
 *  using the function st_set_limit(). Programmers are advised not to remove
 *  the limit completely however, as doing so may result in their application
 *	running out of memory. With the limit in place, the worst that can happen
 *	is that new FSM input overwrites old FSM input before the application has
 *	had a chance to process it.
 *
 *  The library continually scans the circular buffer, searching for valid
 *  user input. When input matching an event of the current state is found,
 *  it @em triggers that event. Note that the circular buffer is contained
 *  within a private library data structure, and is unable to be directly
 *  assessed by the programmer. This data structure also contains several
 *  other members, including those used to track the current state of the
 *  FSM, as well as the most recent event to occur. The library contains
 *  several functions that allow the programmer to manipulate the members
 *  of the private data structure indirectly, although this should not
 *  normally be necessary.
 *
 *  The second functional element is the array of system events. This holds
 *  a list of valid FSM inputs for each system state. It is this array that
 *  the library compares the content of the circular buffer to when looking
 *  for valid input.
 *
 *  The third functional element is the array of pointers to so-called action
 *  functions. The library uses these functions to effect the actual state
 *  transitions. For each entry in the array of system events, there is a
 *  matching entry in the array of action functions. Action functions are
 *  named after the state and event to which they pertain.
 *
 *  The library supports three types of input:
 *
 *  -#  Predefined text.
 *  -#  Arbitrary text.
 *  -#  Hardware events.
 *
 *  Predefined text is known at compile-time, and is often used to provide the
 *  user with a fixed set of options to choose from. Predefined text should be
 *  placed into the event array exactly as the user is expected to type it. To
 *  illustrate, consider a state that contains four valid inputs - "1", "2",
 *  "3", and "4". As none of these inputs contain a carriage-return (CR), an
 *  event will be triggered as soon as one of the four numbers is entered by
 *  the user. Programmers may add non-printable characters to predefined text
 *  if they so wish. For example, a CR could be added to the four inputs above
 *  to yield "1\r", "2\r" et cetera.
 *
 *	When scanning for predefined text, the library will automatically remove
 *	matching user input from the circular buffer. It also removes user input
 *	that does not match any of the entries in the array of system events for
 *	the current state. If the user were to type "XXX3\r" in the example from
 *	the preceding paragraph, the library would remove the "XXX" characters
 *	from the circular buffer as soon as they were typed. The serial terminal
 *	would continue to display the "XXX" characters, as the library does not
 *  remove them from the serial terminal screen buffer.
 *
 *  @code
 *  ADDRESS BOOK
 *
 *  1.  New Entry
 *  2.  Search by First Name
 *  3.  Search by Last Name
 *  4.  Previous Screen
 *
 *  >> 2
 *  @endcode
 *
 *  Arbitrary text is not known until run-time. It is often used to provide
 *  the user with the ability to enter file names and the like. Because the
 *  text is not known at compile-time, it cannot be entered into the system
 *  event array in the same manner as predefined text. Instead, the library
 *  uses placeholder text to represent arbitrary input. The programmer must
 *  enter "_arbitrary_input" into the event array whenever they want the
 *  user to be able to enter arbitrary text.
 *
 *  As previously stated, the library continually scans the circular buffer
 *  looking for valid user input. In the case of predefined text, comparing
 *  the content of the circular buffer to the array of system events is all
 *  that is required to determine if particular input is valid or not. This
 *  is not the case with arbitrary text however.
 *
 *  During normal operation, arbitrary text is expected to end with a CR. The
 *  library scans the circular buffer looking for a CR whenever the system
 *  event array contains the placeholder text "_arbitrary_input". When a CR
 *  is found, it triggers a call to the action function corresponding to the
 *  event array entry.
 *
 *  Note that unlike predefined text, it is up to the programmer to remove
 *  arbitrary text from the circular buffer. The functions st_get_count(),
 *  st_copy_buffer(), and st_empty_buffer() are available to help with this.
 *  The programmer may also choose to have the library ignore any CR that it
 *  finds in the circular buffer while scanning. If this option is selected,
 *  not only is the programmer responsible for removing arbitrary text from
 *  the buffer, they are also responsible for transitioning the FSM to the
 *  next state whenever a suitable event occurs.
 *
 *  @code
 *  SAVE DATA
 *
 *  Please enter the name of the file you wish to save the data to.
 *
 *  >> calibration_data.txt
 *  @endcode
 *
 *  Hardware events may be used to trigger a state transition based upon the
 *  occurrence of a hardware-related event such as the expiry of a timer, or
 *  a button being pressed. The library uses placeholder text to represent a
 *  hardware event in the same manner as it does with arbitrary text. In the
 *	case of of a hardware event, the text used is "_hardware_event".
 *
 *  Unlike predefined and arbitrary text input, a hardware event does not
 *  result in nodes being added to the circular buffer. Instead, a bit is
 *  set in the status byte contained within the libraries private data
 *  structure. This bit is cleared by the library automatically.
 *
 *  Two functions are responsible for bringing the various library elements
 *  together. The function st_is_valid_input() is used to scan the circular
 *  buffer for valid input, whilst st_transition() calls the correct action
 *  function when valid input is detected.
 *
 *  <H3> Use </H3>
 *
 *  Whilst the library is fully-functional, it is not intended to be deployed
 *  by the programmer in its current form. Rather, its purpose is to serve as
 *  a design template that the programmer may adapt to suit their particular
 *  application requirements.
 *
 *	The programmer is encouraged to run the library FSM by calling the test
 *  function stt_test_2(), the state diagram for which is included below.
 *
 *	@image html state.jpg
 *
 *  <H3> Hardware </H3>
 *
 *  The FSM library has been designed to run on a Cypress CY8CKIT-001
 *  development kit fitted with a PSoC5 CY8C5568AXI-060 module. It requires
 *  access to the following components:
 *
 *  - isr_2
 *  - UART_1
 *
 *  Pin P1_2 on the development kit prototype area must be connected to the
 *  UART RX pin, and pin P1_7 must be connected to the UART TX pin. Ensure
 *  that the RS_232PWR jumper is also set.
 *
 *  <H3> Further Reading </H3>
 *
 *  Circular buffer library (cbuff.h)
 *
 *  <a href = "http://en.wikipedia.org/wiki/Finite-state_machine">
 *      Finite state machine (Wikipedia) </a>
 *
 *  <a href = "http://johnsantic.com/comp/state.html">
 *      Writing Efficient State Machines in C </a>
 */
 
/****************************************************************************
 *  Modules
 ****************************************************************************/
#include "cbuff.h"

/****************************************************************************
 *  Definitions and Macros
 ****************************************************************************/
/**
 *  @brief Generic success.
 */
#define ST_SUCCESS                      0

/**
 *  @brief Generic failure.
 */
#define ST_FAILURE                      1

/**
 *  @brief Memory was unable to be allocated from the heap.
 *
 *  Any function returning this value will free any memory that was
 *  successfully allocated from the heap prior to the allocation failure.
 */
#define ST_NO_MEMORY                    2

/**
 *  @brief A bad argument was passed to a function.
 */
#define ST_BAD_ARGUMENT                 3

/**
 *  @brief The circular buffer is empty.
 */
#define ST_EMPTY                        4

/**
 *  @brief Generic falsehood.
 */
#define ST_FALSE                        0

/**
 *  @brief Generic truth.
 */
#define ST_TRUE                         1

/**
 *  @brief Status byte hardware mask.
 *
 *  Used to indicate that a hardware event has occurred.
 */
#define ST_HARDWARE_EVENT               0x01

/**
 *  @brief Status byte carriage-return (CR) mask.
 *
 *  Used to indicate that arbitrary text will be terminated with a CR.
 */
#define ST_CARRIAGE_RETURN              0x02

/**
 *  @brief The circular buffer node limit.
 */
#define ST_NODE_LIMIT                   64

/****************************************************************************
 *  Typedefs and Structures
 ****************************************************************************/
/**
 *  @brief Finite state machine (FSM) information.
 */
typedef struct ST_DATA
{
    /**
     *  The library circular buffer.
     */
    CB_LIST buffer;
    
    /**
     *  @brief The most recent event to occur.
     */
    uint16 event;
    
    /**
     *  @brief The current state.
     */
    uint16 state;
    
    /**
     *  @brief The status of the FSM.
     *
     *  This member may be one or more of the following values.
     *
     *  Value              | Description
     *  ------------------ | ---------------------------------------------
     *  @b ST_HARDWARE_EVENT  | A hardware event has occurred.
     *  @b ST_CARRIAGE_RETURN | Arbitrary text will be terminated with a CR.
     */
    uint8 status;
} ST_DATA;

/**
 *  @brief Key information.
 */
typedef struct ST_OBJECT
{
    /**
     *  @brief The most recent key to be pressed.
     */
    char *key;
} ST_OBJECT;

/**
 *  @brief Permitted events.
 */
enum ST_EVENTS
{
    ST_EVENT_0,
    ST_EVENT_1,
    ST_EVENT_2,
    
    /**
     *  @brief The maximum event number supported by the FSM.
     */
    ST_EVENT_MAXIMUM
};

/**
 *  @brief Permitted states.
 */
enum ST_STATES
{
    ST_STATE_0,
    ST_STATE_1,
    ST_STATE_2,
    ST_STATE_3,
    ST_STATE_4,
    ST_STATE_5,
    
    /**
     *  @brief The maximum state number supported by the FSM.
     */
    ST_STATE_MAXIMUM
};

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
/**
 *  @brief Start the components used by the library.
 *  @remark Sets the circular buffer size limit to #ST_NODE_LIMIT, and
 *      sets the #ST_CARRIAGE_RETURN bit.
 *  @warning This must be the first library function to be called.
 */
void st_start(void);

/**
 *  @brief Stop the components used by the library.
 *  @remark This should be the last library function to be called.
 */
void st_stop(void);

/**
 *  @brief Manually add a key object to the circular buffer.
 *  @param[in] key A pointer to the most recent key to be pressed.
 *  @return #ST_SUCCESS if successful, otherwise #ST_BAD_ARGUMENT or
 *      #ST_NO_MEMORY.
 */
uint8 st_add_key(char *key);

/**
 *  @brief Scan the circular buffer for valid input.
 *  @return #ST_SUCCESS if successful, otherwise #ST_FAILURE.
 *  @remark It is up to the programmer to remove arbitrary text from the
 *      circular buffer. Predefined text will be automatically removed.
 *  @remark If the #ST_CARRIAGE_RETURN bit has been cleared, it is up to
 *      the programmer to transition the FSM to the next state.
 *  @see st_get_count()
 *  @see st_copy_buffer()
 *  @see st_empty_buffer()
 */
uint8 st_is_valid_input(void);

/**
 *  @brief Transition the FSM to the next state.
 */
void st_transition(void);

/**
 *  @brief Get the node limit of the circular buffer.
 *  @return The maximum number of nodes allowed in the circular buffer.
 */
uint32 st_get_limit(void);

/**
 *  @brief Set the node limit of the circular buffer.
 *  @param[in] limit The maximum number of nodes allowed in the circular
 *      buffer.
 *  @return #ST_SUCCESS if successful, otherwise #ST_FAILURE.
 *  @remark It is up to the caller to ensure that the number of nodes in the
 *      circular buffer is less than the proposed limit. Failure to do so will
 *      result in this function returning #ST_FAILURE.
 *  @remark Set the limit to zero to allow the circular buffer to grow without
 *      limit.
 */
uint8 st_set_limit(uint32 limit);

/**
 *  @brief Get the node count of the circular buffer.
 *  @return The number of nodes in the circular buffer.
 */
uint32 st_get_count(void);

/**
 *  @brief Set a library status bit.
 *  @param[in] mask The mask of the bit to set.
 *
 *  This member may be one or more of the following values.
 *
 *  Value              | Description
 *  ------------------ | ---------------------------------------------
 *  @b ST_HARDWARE_EVENT  | A hardware event has occurred.
 *  @b ST_CARRIAGE_RETURN | Arbitrary text will be terminated with a CR.
 */
void st_set_bit(uint8 mask);

/**
 *  @brief Clear a library status bit.
 *  @param[in] mask The mask of the bit to clear.
 *
 *  This member may be one or more of the following values.
 *
 *	Value              | Description
 *  ------------------ | ---------------------------------------------
 *  @b ST_HARDWARE_EVENT  | A hardware event has occurred.
 *  @b ST_CARRIAGE_RETURN | Arbitrary text will be terminated with a CR.
 */
void st_clear_bit(uint8 mask);

/**
 *  @brief Set the library state.
 *  @param[in] state The new state.
 *  @return #ST_SUCCESS if successful, otherwise #ST_BAD_ARGUMENT.
 *  @remark It is up to the caller to ensure that the state is less
 *      than #ST_STATE_MAXIMUM. Failure to do so will result in this
 *      function returning #ST_BAD_ARGUMENT.
 */
uint8 st_set_state(uint16 state);

/**
 *  @brief Copy the content of the circular buffer.
 *  @param[out] string A pointer to the returned buffer content.
 *  @return #ST_SUCCESS if successful, otherwise #ST_BAD_ARGUMENT or
 *      #ST_EMPTY.
 *  @remark It is up to the caller to allocate sufficient space for the
 *      string.
 *  @see st_get_count()
 */
uint8 st_copy_buffer(char *string);

/**
 *  @brief Empty the circular buffer.
 *  @remark Deletes all nodes from the circular buffer.
 */
void st_empty_buffer(void);

/**
 *  @brief State zero event zero action function.
 *
 *	This function displays the "modifying the library" text block, and sets
 *	the FSM state to ST_STATE_1. Three predefined text events are defined
 *	for this state.
 */
void st_state_0_event_0(void);

/**
 *  @brief State one event zero action function.
 *
 *	This function displays the "modifying the library - system event array"
 *	text block, delays for ten seconds, and then sets the FSM state to
 *	ST_STATE_2. A single hardware event is defined for this state.
 */
void st_state_1_event_0(void);

/**
 *  @brief State one event one action function.
 *
 *	This function displays the "modifying the library - action function array"
 *	text block, and sets the FSM state to ST_STATE_3.  A single predefined
 *	text event is defined for this state.
 */
void st_state_1_event_1(void);

/**
 *  @brief State one event two action function.
 *
 *	This function displays the "modifying the library - action functions" text
 *	block, and sets the FSM state to ST_STATE_4. A single arbitrary text
 *	event is defined for this state.
 */
void st_state_1_event_2(void);

/**
 *  @brief State two event zero action function.
 *
 *	This function returns the FSM to ST_STATE_1. It does this by calling the
 *	st_state_0_event_0() action function.
 */
void st_state_2_event_0(void);

/**
 *  @brief State three event zero action function.
 *
 *	This function returns the FSM to ST_STATE_1. It does this by calling the
 *	st_state_0_event_0() action function.
 */
void st_state_3_event_0(void);

/**
 *  @brief State four event zero action function.
 *
 *	This function displays the "certificate of completion" text block, and
 *	removes the arbitrary text from the circular buffer after copying it to
 *	a local string. It also sets the FSM state to ST_STATE_5. There are no
 *	events defined for this state.
 */
void st_state_4_event_0(void);

#endif

/****************************************************************************
 *  End of File
 ****************************************************************************/
