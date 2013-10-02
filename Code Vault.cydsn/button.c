/****************************************************************************
 *
 *  File:           button.c
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
/**
 *  @file button.c
 *  @brief Button library implementation.
 */
 
/****************************************************************************
 *  Modules
 ****************************************************************************/
#include <device.h>
#include <stdlib.h>

#include "button.h"

/****************************************************************************
 *  Definitions and Macros
 ****************************************************************************/
/**
 *  @brief Button 1 pin.
 *
 *  The button 1 pin component is configured as resisitive pull-up, and the
 *  pin is connected to ground whenever the SPNO button attached to the pin
 *  is pressed.
 */
#define _BUTTON_1                       CYREG_PRT0_PC0

/**
 *  @brief Button 2 pin.
 *
 *  The button 2 pin component is configured as resisitive pull-up, and the
 *  pin is connected to ground whenever the SPNO button attached to the pin
 *  is pressed.
 */
#define _BUTTON_2                       CYREG_PRT0_PC1

/**
 *  @brief Button 3 pin.
 *
 *  The button 3 pin component is configured as resisitive pull-up, and the
 *  pin is connected to ground whenever the SPNO button attached to the pin
 *  is pressed.
 */
#define _BUTTON_3                       CYREG_PRT0_PC2

/**
 *  @brief Button 4 pin.
 *
 *  The button 4 pin component is configured as resisitive pull-up, and the
 *  pin is connected to ground whenever the SPNO button attached to the pin
 *  is pressed.
 */
#define _BUTTON_4                       CYREG_PRT0_PC3

/**
 *  @brief Button 5 pin.
 *
 *  The button 5 pin component is configured as resisitive pull-up, and the
 *  pin is connected to ground whenever the SPNO button attached to the pin
 *  is pressed.
 */
#define _BUTTON_5                       CYREG_PRT0_PC4

/**
 *  @brief Button 6 pin.
 *
 *  The button 6 pin component is configured as resisitive pull-up, and the
 *  pin is connected to ground whenever the SPNO button attached to the pin
 *  is pressed.
 */
#define _BUTTON_6                       CYREG_PRT0_PC5

/**
 *  @brief Button 7 pin.
 *
 *  The button 7 pin component is configured as resisitive pull-up, and the
 *  pin is connected to ground whenever the SPNO button attached to the pin
 *  is pressed.
 */
#define _BUTTON_7                       CYREG_PRT0_PC6

/**
 *  @brief Button 8 pin.
 *
 *  The button 8 pin component is configured as resisitive pull-up, and the
 *  pin is connected to ground whenever the SPNO button attached to the pin
 *  is pressed.
 */
#define _BUTTON_8                       CYREG_PRT0_PC7

/****************************************************************************
 *  Typedefs and Structures
 ****************************************************************************/

/****************************************************************************
 *  Prototypes of Local Functions
 ****************************************************************************/
/**
 *  @brief Create a new button object.
 *  @param[out] object A pointer to a pointer to the newly-created object.
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
 *  @return #BU_SUCCESS if successful, otherwise #BU_NO_MEMORY.
 */
uint8 _create_object(BU_OBJECT **object, uint8 number, uint8 state);

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/

/****************************************************************************
 *  Global Variables
 ****************************************************************************/
/**
 *  @brief The circular buffer used by the button interrupt service routine
 *      (ISR).
 */
static CB_LIST *_buffer = NULL;

/**
 *  @brief The previous state of the buttons.
 */
static uint8 _old_state = BU_BUTTON_NONE;

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
/**
 *  @brief Button interrupt service routine (ISR).
 */
CY_ISR(bu_interrupt)
{
    uint8 new_state = Status_Reg_1_Read();
    
    if ((new_state ^ _old_state) == BU_BUTTON_1)
    {
        if ((new_state & BU_BUTTON_1) == BU_BUTTON_1)
        {
            bu_add_new(_buffer, 1, BU_RELEASED);
        }
        else
        {
            bu_add_new(_buffer, 1, BU_PRESSED);
        }
    }
    
    if ((new_state ^ _old_state) == BU_BUTTON_2)
    {
        if ((new_state & BU_BUTTON_2) == BU_BUTTON_2)
        {
            bu_add_new(_buffer, 2, BU_RELEASED);
        }
        else
        {
            bu_add_new(_buffer, 2, BU_PRESSED);
        }
    }
    
    if ((new_state ^ _old_state) == BU_BUTTON_3)
    {
        if ((new_state & BU_BUTTON_3) == BU_BUTTON_3)
        {
            bu_add_new(_buffer, 3, BU_RELEASED);
        }
        else
        {
            bu_add_new(_buffer, 3, BU_PRESSED);
        }
    }
    
    if ((new_state ^ _old_state) == BU_BUTTON_4)
    {
        if ((new_state & BU_BUTTON_4) == BU_BUTTON_4)
        {
            bu_add_new(_buffer, 4, BU_RELEASED);
        }
        else
        {
            bu_add_new(_buffer, 4, BU_PRESSED);
        }
    }
    
    if ((new_state ^ _old_state) == BU_BUTTON_5)
    {
        if ((new_state & BU_BUTTON_5) == BU_BUTTON_5)
        {
            bu_add_new(_buffer, 5, BU_RELEASED);
        }
        else
        {
            bu_add_new(_buffer, 5, BU_PRESSED);
        }
    }
    
    if ((new_state ^ _old_state) == BU_BUTTON_6)
    {
        if ((new_state & BU_BUTTON_6) == BU_BUTTON_6)
        {
            bu_add_new(_buffer, 6, BU_RELEASED);
        }
        else
        {
            bu_add_new(_buffer, 6, BU_PRESSED);
        }
    }
    
    if ((new_state ^ _old_state) == BU_BUTTON_7)
    {
        if ((new_state & BU_BUTTON_7) == BU_BUTTON_7)
        {
            bu_add_new(_buffer, 7, BU_RELEASED);
        }
        else
        {
            bu_add_new(_buffer, 7, BU_PRESSED);
        }
    }
    
    if ((new_state ^ _old_state) == BU_BUTTON_8)
    {
        if ((new_state & BU_BUTTON_8) == BU_BUTTON_8)
        {
            bu_add_new(_buffer, 8, BU_RELEASED);
        }
        else
        {
            bu_add_new(_buffer, 8, BU_PRESSED);
        }
    }
    
    _old_state = new_state;
}

uint8 bu_start(CB_LIST *buffer)
{
    uint8 result = BU_BAD_ARGUMENT;
    
    if (buffer != NULL)
    {
        if (_buffer == NULL)
        {
            _buffer = buffer;

            isr_1_StartEx(bu_interrupt);
            isr_1_ClearPending();
                
            /*
             *  This delay gives the button pins time to go high.
             */
            CyDelay(10);
            
            result = BU_SUCCESS;
        }
        else
        {
            result = BU_FAILURE;
        }
    }
    
    return result;
}

uint8 bu_stop(CB_LIST *buffer)
{
    uint8 result = BU_BAD_ARGUMENT;
    
    if (buffer != NULL)
    {
        if (_buffer != NULL)
        {
            isr_1_Stop();
            
            _buffer = NULL;
            
            result = BU_SUCCESS;
        }
        else
        {
            result = BU_FAILURE;
        }
    }
    
    return result;
}

uint8 bu_add_new(CB_LIST *buffer, uint8 number, uint8 state)
{
    BU_OBJECT *object;
    uint8 result = BU_BAD_ARGUMENT;
    
    if (buffer != NULL)
    {
        result = _create_object(&object, number, state);
        
        if (result == BU_SUCCESS)
        {
            result = cb_add_new(buffer, TAG, object);
            
            if (result != CB_SUCCESS)
            {
                free(object);
            }
        }
    }
    
    return result;
}

uint8 bu_remove_old(CB_LIST *buffer)
{
    BU_OBJECT *object;
    uint8 result = BU_BAD_ARGUMENT;
    
    if (buffer != NULL)
    {
        result = cb_remove_old(buffer, (void **)&object);
        
        if (result == CB_SUCCESS)
        {
            free(object);
        }
    }
    
    return result;
}

uint8 bu_get_new_object(CB_LIST *buffer, BU_OBJECT **object)
{   
    return cb_get_new_object(buffer, NULL, (void **)object);
}

uint8 bu_get_old_object(CB_LIST *buffer, BU_OBJECT **object)
{
    return cb_get_old_object(buffer, NULL, (void **)object);
}

uint32 bu_get_count(CB_LIST *buffer)
{
    return cb_get_count(buffer);
}

uint32 bu_get_limit(CB_LIST *buffer)
{
    return cb_get_limit(buffer);
}

uint8 bu_set_limit(CB_LIST *buffer, uint32 limit)
{
    return cb_set_limit(buffer, limit);
}

uint8 bu_destroy(CB_LIST *buffer)
{
    uint8 result = BU_BAD_ARGUMENT;
    
    if (buffer != NULL)
    {
        if (_buffer == NULL)
        {
            while (bu_get_count(buffer) > 0)
            {
                bu_remove_old(buffer);
            }
            
            result = BU_SUCCESS;
        }
        else
        {
            result = BU_FAILURE;
        }
    }
    
    return result;
}

/****************************************************************************
 *  Local Functions
 ****************************************************************************/
uint8 _create_object(BU_OBJECT **object, uint8 number, uint8 state)
{
    BU_OBJECT *new_object;
    uint8 result = BU_NO_MEMORY;
    
    new_object = malloc(sizeof(*new_object));
    
    if (new_object != NULL)
    {
        new_object->number = number;
        new_object->state = state;
        
        *object = new_object;
        
        result = BU_SUCCESS;
    }
    
    return result;
}

/****************************************************************************
 *  End of File
 ****************************************************************************/
