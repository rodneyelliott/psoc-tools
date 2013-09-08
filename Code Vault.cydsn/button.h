/****************************************************************************
 *
 *  File:           button.h
 *  Module:         Button Library
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
#ifndef BUTTON_H
#define BUTTON_H
/**
 *  @file button.h
 *  @brief Button library interface.
 *
 *  <H3> Introduction </H3>
 *
 *  The button library is a collection of functions that enable the programmer
 *  to use of up to eight SPNO buttons as part of the physical user interface
 *  of their project.
 *
 *  The library uses a circular buffer to store button information. A node is
 *  added to the buffer whenever a button is pressed or released. Each node
 *  contains a pointer to a button object that is owned by the library. By
 *  adding a node when a button is both pressed and released, the library
 *  gives the programmer the ability to design user interfaces that permit
 *  multiple buttons to be pressed at once. It also gives programmers the
 *  ability to make use of the order in which buttons are pressed or released.
 *
 *  <H3> Use </H3>
 *
 *  In order to use the library, the programmer must start by declaring an
 *  instance of a CB_LIST structure with scope appropriate to the intended
 *  application. This instance must be initialised to zero, ie:
 *
 *  @code CB_LIST cb_list = {0}; @endcode
 *
 *  The library requires exclusive access to this instance. The programmer
 *  must not attempt to use the declared structure for any other purpose.
 *
 *  With the instance declared, the next step is start the library by calling
 *  the function bu_start(). This initialises the components used by the
 *  library. Nodes will then be automatically added to the circular buffer
 *  whenever a button is pressed or released. Nodes may also be manually 
 *  added to the buffer using the function bu_add_new(). Nodes are removed
 *  using the function bu_remove_old().
 *
 *  The functions bu_get_new_object() and bu_get_old_object() may be used
 *  to examine the newest and oldest button objects without removing their
 *  nodes from the buffer. The function bu_get_count() returns the number
 *  of nodes in the buffer, whilst bu_destroy() removes all nodes from the
 *  buffer. Finally, the function bu_stop() stops the components used by
 *  the library.
 *
 *  For further information about these library functions, please refer to the
 *  individual function documentation.
 *
 *  <H3> Hardware </H3>
 *
 *  The error management library has been designed to run on a Cypress
 *  CY8CKIT-001 development kit fitted with a PSoC5 CY8C5568AXI-060 module. It
 *  requires access to the following components:
 *
 *  - Clock_1
 *  - Debouncer_1-8
 *  - isr_1
 *  - Status_Reg_1
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
 *  These pin allocations may be changed by the programmer in the project
 *  design wide resource (*.cydwr) file to suit their particular application.
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
#define BU_SUCCESS                      0

/**
 *  @brief Generic failure.
 */
#define BU_FAILURE                      1

/**
 *  @brief Memory was unable to be allocated from the heap.
 *
 *  Any function returning this value will free any memory that was
 *  successfully allocated from the heap prior to the allocation failure.
 */
#define BU_NO_MEMORY                    2

/**
 *  @brief A bad argument was passed to a function.
 */
#define BU_BAD_ARGUMENT                 3

/**
 *  @brief The circular buffer is empty.
 */
#define BU_EMPTY                        4

/**
 *  @brief The button was pressed.
 */
#define BU_PRESSED                      0

/**
 *  @brief The button was released.
 */
#define BU_RELEASED                     1

/**
 *  @brief The button 1 register mask.
 *
 *  Button 1 is connected to pin component BUTTON_1. This is routed to bit 0
 *  of the status register component, hence the mask value of 0x01.
 */
#define BU_BUTTON_1                     0x01

/**
 *  @brief The button 2 register mask.
 *
 *  Button 2 is connected to pin component BUTTON_2. This is routed to bit 1
 *  of the status register component, hence the mask value of 0x02.
 */
#define BU_BUTTON_2                     0x02

/**
 *  @brief The button 3 register mask.
 *
 *  Button 3 is connected to pin component BUTTON_3. This is routed to bit 2
 *  of the status register component, hence the mask value of 0x04.
 */
#define BU_BUTTON_3                     0x04

/**
 *  @brief The button 4 register mask.
 *
 *  Button 4 is connected to pin component BUTTON_4. This is routed to bit 3
 *  of the status register component, hence the mask value of 0x08.
 */
#define BU_BUTTON_4                     0x08

/**
 *  @brief The button 5 register mask.
 *
 *  Button 5 is connected to pin component BUTTON_5. This is routed to bit 4
 *  of the status register component, hence the mask value of 0x10.
 */
#define BU_BUTTON_5                     0x10

/**
 *  @brief The button 6 register mask.
 *
 *  Button 6 is connected to pin component BUTTON_6. This is routed to bit 5
 *  of the status register component, hence the mask value of 0x20.
 */
#define BU_BUTTON_6                     0x20

/**
 *  @brief The button 7 register mask.
 *
 *  Button 7 is connected to pin component BUTTON_7. This is routed to bit 6
 *  of the status register component, hence the mask value of 0x40.
 */
#define BU_BUTTON_7                     0x40

/**
 *  @brief The button 8 register mask.
 *
 *  Button 8 is connected to pin component BUTTON_8. This is routed to bit 7
 *  of the status register component, hence the mask value of 0x80.
 */
#define BU_BUTTON_8                     0x80

/**
 *  @brief The no button register mask.
 *
 *  All button pins are configured as resistive pull-up. A status register
 *  value of 0xff thus indicates that none of the buttons are currently being
 *  pressed.
 */
#define BU_BUTTON_NONE                  0xff

/**
 *  @brief The button library object tag.
 */
#define TAG                             1000

/****************************************************************************
 *  Typedefs and Structures
 ****************************************************************************/
/**
 *  @brief Button information.
 */
typedef struct BU_OBJECT
{
    /**
     *  @brief The button number.
     */
    uint8 number;
    
    /**
     *  @brief The button state.
     *
     *  This member may be one of the following values.
     *
     *  Value       | Description
     *  ----------- | -------------------------
     *  @b BU_PRESSED  | The button was pressed.
     *  @b BU_RELEASED | The button was released.
     */
    uint8 state;
} BU_OBJECT;

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
/**
 *  @brief Start the components used by the library.
 *  @param[in] buffer A pointer to a circular buffer.
 *  @return #BU_SUCCESS if successful, otherwise #BU_BAD_ARGUMENT or
 *      #BU_FAILURE.
 *  @remark If this function is called more than once, it will
 *      return #BU_FAILURE.
 *  @warning This must be the first library function to be called.
 */
uint8 bu_start(CB_LIST *buffer);

/**
 *  @brief Stop the components used by the library.
 *  @param[in] buffer A pointer to a circular buffer.
 *  @return #BU_SUCCESS if successful, otherwise #BU_BAD_ARGUMENT.
 *  @remark If this function is called before bu_start(), it will
 *      return #BU_FAILURE.
 *  @remark This should be the last library function to be called.
 */
uint8 bu_stop(CB_LIST *buffer);

/**
 *  @brief Add a new button object to a circular buffer.
 *  @param[in] buffer A pointer to a circular buffer.
 *  @param[in] number The button number.
 *  @param[in] state The button state.
 *
 *  This member may be one of the following values.
 *
 *  Value       | Description
 *  ----------- | -------------------------
 *  @b BU_PRESSED  | The button was pressed.
 *  @b BU_RELEASED | The button was released.
 *
 *  @return #BU_SUCCESS if successful, otherwise #BU_BAD_ARGUMENT or
 *      #BU_NO_MEMORY.
 */
uint8 bu_add_new(CB_LIST *buffer, uint8 number, uint8 state);

/**
 *  @brief Remove the oldest button object from a circular buffer.
 *  @param[in] buffer A pointer to a circular buffer.
 *  @return #BU_SUCCESS if successful, otherwise #BU_BAD_ARGUMENT or
 *      #BU_EMPTY.
 */
uint8 bu_remove_old(CB_LIST *buffer);

/**
 *  @brief Get the newest button object of a circular buffer.
 *  @param[in] buffer A pointer to a circular buffer.
 *  @param[out] object A pointer to a pointer to the returned object.
 *  @return #BU_SUCCESS if successful, otherwise #BU_BAD_ARGUMENT or
 *      #BU_EMPTY.
 */
uint8 bu_get_new_object(CB_LIST *buffer, BU_OBJECT **object);

/**
 *  @brief Get the oldest button object of a circular buffer.
 *  @param[in] buffer A pointer to a circular buffer.
 *  @param[out] object A pointer to a pointer to the returned object.
 *  @return #BU_SUCCESS if successful, otherwise #BU_BAD_ARGUMENT or
 *      #BU_EMPTY.
 */
uint8 bu_get_old_object(CB_LIST *buffer, BU_OBJECT **object);

/**
 *  @brief Get the node count of a circular buffer.
 *  @param[in] buffer A pointer to a circular buffer.
 *  @return The number of nodes in the circular buffer.
 *  @remark If the buffer argument is NULL, a count of zero will be returned.
 */
uint32 bu_get_count(CB_LIST *buffer);

/**
 *  @brief Get the node limit of a circular buffer.
 *  @param[in] buffer A pointer to a circular buffer.
 *  @return The maximum number of nodes allowed in the circular buffer.
 *  @remark If the buffer argument is NULL, a limit of zero will be returned.
 */
uint32 bu_get_limit(CB_LIST *buffer);

/**
 *  @brief Set the node limit of a circular buffer.
 *  @param[in] buffer A pointer to a circular buffer.
 *  @param[in] limit The maximum number of nodes allowed in the circular
 *      buffer.
 *  @return #BU_SUCCESS if successful, otherwise #BU_BAD_ARGUMENT or
 *      #BU_FAILURE.
 *  @remark It is up to the caller to ensure that the number of nodes in the
 *      buffer is less than the proposed limit. Failure to do so will result
 *      in this function returning #BU_FAILURE.
 *  @remark Set the limit to zero to allow the buffer to grow without limit.
 */
uint8 bu_set_limit(CB_LIST *buffer, uint32 limit);

/**
 *  @brief Destroy a circular buffer.
 *  @param[in] buffer A pointer to a circular buffer.
 *  @return #BU_SUCCESS if successful, otherwise #BU_BAD_ARGUMENT or
 *      #BU_FAILURE.
 *  @remark It is up to the caller to ensure that the library components
 *      have been stopped prior to calling this function. Failure to do
 *      so will will result in this function returning #BU_FAILURE.
 *  @see bu_stop()
 */
uint8 bu_destroy(CB_LIST *buffer);

#endif

/****************************************************************************
 *  End of File
 ****************************************************************************/
