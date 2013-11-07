/****************************************************************************
 *
 *  File:           state.c
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
/**
 *  @file state.c
 *  @brief Finite state machine library implementation.
 */
 
/****************************************************************************
 *  Modules
 ****************************************************************************/
#include <device.h>
#include <stdlib.h>
#include <string.h>

#include "cbuff.h"
#include "state.h"

/****************************************************************************
 *  Definitions and Macros
 ****************************************************************************/
/**
 *  @brief The finite state machine library object tag.
 */
#define _TAG                            1100

/****************************************************************************
 *  Typedefs and Structures
 ****************************************************************************/

/****************************************************************************
 *  Prototypes of Local Functions
 ****************************************************************************/
/**
 *  @brief Create a new state object.
 *  @param[out] object A pointer to a pointer to the newly-created object.
 *  @param[in] key A pointer to the most recent key to be pressed.
 *  @return #ST_SUCCESS if successful, otherwise #ST_NO_MEMORY.
 */
static uint8 _create_object(ST_OBJECT **object, char *key);

/**
 *  @brief Compare circular buffer user input to valid input.
 *  @param[in] input A pointer to valid input.
 *  @param[in] buffer A pointer to a circular buffer.
 *  @return #ST_SUCCESS if successful, otherwise ST_FAILURE.
 */
static uint8 _compare(char *input, CB_LIST *buffer);

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/

/****************************************************************************
 *  Global Variables
 ****************************************************************************/
/**
 *  @brief The private ST_DATA structure used by the library.
 */
static ST_DATA _st_data = {{0}};        /* GCC bug 53119 requires double
                                           braces to suppress a warning
                                           about the initializer. */
                                           
/**
 *  @brief The array of system events.
 */
static char *_valid_inputs[ST_STATE_MAXIMUM][ST_EVENT_MAXIMUM] =
{
    {"C"},
    {"1", "2", "3"},
    {"_hardware_event"},
    {"\r"},
    {"_arbitrary_input"}
};

/**
 *  @brief The array of pointers to action functions.
 */
static void (*_action_functions[ST_STATE_MAXIMUM][ST_EVENT_MAXIMUM])(void) =
{
    {st_state_0_event_0},
    {st_state_1_event_0, st_state_1_event_1, st_state_1_event_2},
    {st_state_2_event_0},
    {st_state_3_event_0},
    {st_state_4_event_0}
};

static char *_state_0_event_0 = 
{
    "\x1b\x5b\x32\x4a"
    "MODIFYING THE LIBRARY\r\n"
    "\r\n"
    "The library FSM is hard-coded rather than interpreted. This means\r\n"
    "that modifying the library will require the programmer to rewrite\r\n"
    "some of its code. Before making a start on this task however, the\r\n"
    "programmer is advised to do the following:\r\n"
    "\r\n"
    "1. Make a backup copy of the library\r\n"
    "2. Complete the design of their FSM\r\n"
    "\r\n"
    "With the code backed-up, and the states and events of their FSM\r\n"
    "fully-described, the programmer can now begin to modify the code. To\r\n"
    "learn more, please select from one of the following options.\r\n"
    "\r\n"
    "[1] System event array\r\n"
    "[2] Action function array\r\n"
    "[3] Action functions\r\n"
    "\r\n"
    ">> "
};

static char *_state_1_event_0 = 
{
    "\x1b\x5b\x32\x4a"
    "MODIFYING THE LIBRARY - SYSTEM EVENT ARRAY\r\n"
    "\r\n"
    "The programmer should begin by filling the system event array. This\r\n"
    "contains the user input and other conditions that will trigger an\r\n"
    "event. The event array may be found in the global variable section\r\n"
    "of the library implementation file.\r\n"
    "\r\n"
    "Predefined text should be entered verbatim. Arbitrary text and any\r\n"
    "hardware events should have their corresponding placeholder text\r\n"
    "inserted into the system event array instead.\r\n"
    "\r\n"
    "[10 Second Delay] Previous screen\r\n"
    "\r\n"
    ">> "
};

static char *_state_1_event_1 = 
{
    "\x1b\x5b\x32\x4a"
    "MODIFYING THE LIBRARY - ACTION FUNCTION ARRAY\r\n"
    "\r\n"
    "Hving filled-out the system event array, the next step is to fill\r\n"
    "the action function array. This contains pointers to the action\r\n"
    "functions that will be called whenever the corresponding system\r\n"
    "event occurs.\r\n"
    "\r\n"
    "[ENTER] Previous Screen\r\n"
    "\r\n"
    ">> "
};

static char *_state_1_event_2 = 
{
    "\x1b\x5b\x32\x4a"
    "MODIFYING THE LIBRARY - ACTION FUNCTIONS\r\n"
    "\r\n"
    "The last step is to write the action functions whose pointers were\r\n"
    "entered into the action function array. The programmer is reminded\r\n"
    "to update the FSM state number within each action function.\r\n"
    "\r\n"
    "[Your Name]\r\n"
    "\r\n"
    ">> "
};

static char *_state_4_event_0_a = 
{
    "\x1b\x5b\x32\x4a"
    "************************************************************\r\n"
    "*\r\n"
    "*\t\tCERTIFICATE OF COMPLETION\r\n"
    "*\r\n"
    "*\r\n"
    "* This is to certify that:\r\n"
    "*\r\n"
};

static char *_state_4_event_0_b =
{
    "*\r\n"
    "* Has successfully explored the finite state machine\r\n"
    "* (FSM) library, and is ready to modify the code so\r\n"
    "* that it may be used in their application.\r\n"
    "*\r\n"
    "*\r\n"
    "* Signed: Rodney B. Elliott\r\n"
    "* Date:   20 September 2013\r\n"
    "*\r\n"
    "************************************************************\r\n"
};

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
/**
 *  @brief Finite state machine (FSM) interrupt service routine (ISR).
 */
CY_ISR(st_interrupt)
{
    char key;
    ST_OBJECT *object;
    uint8 result = ST_SUCCESS;
    uint8 size = UART_1_GetRxBufferSize();
    uint8 status = UART_1_ReadRxStatus();
    
    if (status & ~UART_1_RX_STS_FIFO_NOTEMPTY)
    {
        /*
         *  Add a "serial protocol error" message to your application error
         *  deque here if so desired.
         */
        
        UART_1_ClearRxBuffer();
        
        result = ST_FAILURE;
    }
    
    while (size > 0 && result == ST_SUCCESS)
    {
        key = (char)UART_1_ReadRxData();
        
        result = _create_object(&object, &key);
        
        if (result == ST_SUCCESS)
        {
            result = cb_add_new(&_st_data.buffer, _TAG, object);
            
            if (result != CB_SUCCESS)
            {
                free(object->key);
                free(object);
                
                /*
                 *  Add a "no memory" error message to your application error
                 *  deque here if so desired.
                 */
            }
        }
        else
        {
            /*
             *  Add a "no memory" error message to your application error
             *  deque here if so desired.
             */
        }
        
        --size;
    }
}

void st_start(void)
{   
    UART_1_Start();
    
    isr_2_StartEx(st_interrupt);
    isr_2_ClearPending();
    
    _st_data.status = ST_CARRIAGE_RETURN;
    
    cb_set_limit(&_st_data.buffer, ST_NODE_LIMIT);
}

void st_stop(void)
{
    UART_1_Stop();
    
    isr_2_Stop();
    
    cb_destroy(&_st_data.buffer);
}

uint8 st_add_key(char *key)
{
    ST_OBJECT *object;
    uint8 result = ST_BAD_ARGUMENT;
    
    if (key != NULL)
    {
        result = _create_object(&object, key);
            
        if (result == ST_SUCCESS)
        {
            result = cb_add_new(&_st_data.buffer, _TAG, object);
            
            if (result != CB_SUCCESS)
            {
                free(object->key);
                free(object);
            }
            else
            {
                result = ST_SUCCESS;
            }
        }
    }
    
    return result;
}

uint8 st_is_valid_input(void)
{
    uint32 i = 0;
    ST_OBJECT *object;
    uint8 result = ST_FAILURE;
    char *valid_input;
    
    if (_st_data.status & ST_HARDWARE_EVENT)
    {
        _st_data.status &= ~ST_HARDWARE_EVENT;
        
        for (i = 0 ; i < ST_EVENT_MAXIMUM ; i++)
        {
            valid_input = _valid_inputs[_st_data.state][i];
            
            if (strcmp(valid_input, "_hardware_event") == ST_SUCCESS)
            {
                _st_data.event = i;
                
                result = ST_SUCCESS;
            }
        }
    }
    else
    {
        if (cb_get_count(&_st_data.buffer) > 0)
        {
            /*
             *  Having the ISR insert a node into the circular buffer while
             *  it is being manipulated by the _compare() function would be
             *  a very bad thing. The easiest way to get around this is to
             *  disable the ISR, manipulate the buffer, and then enable the
             *  ISR again.
             */
            isr_2_Disable();
            
            do
            {
                valid_input = _valid_inputs[_st_data.state][i];
                
                if (_compare(valid_input, &_st_data.buffer) == ST_SUCCESS)
                {
                    _st_data.event = i;
                    
                    for (i = 0 ; i < strlen(valid_input) ; i++)
                    {
                        cb_remove_old(&_st_data.buffer, (void **)&object);
                        
                        free(object->key);
                        free(object);
                    }
                    
                    result = ST_SUCCESS;
                }
                else if (strcmp(valid_input, "_arbitrary_input")
                    == ST_SUCCESS)
                {
                    cb_get_new_object(&_st_data.buffer, NULL,
                        (void **)&object);
                    
                    if ((_st_data.status & ST_CARRIAGE_RETURN) &&
                        (*object->key == 0x0d))
                    {
                        _st_data.event = i;
                        
                        result = ST_SUCCESS;
                    }
                }
                
                ++i;
                
            } while (i < ST_EVENT_MAXIMUM && result == ST_FAILURE);
                    
            isr_2_StartEx(st_interrupt);
        }
    }
    
    return result;
}

void st_transition(void)
{
    _action_functions[_st_data.state][_st_data.event]();
}

uint32 st_get_limit(void)
{
    return cb_get_limit(&_st_data.buffer);
}

uint8 st_set_limit(uint32 limit)
{
    return cb_set_limit(&_st_data.buffer, limit);
}

uint32 st_get_count(void)
{
    return cb_get_count(&_st_data.buffer);
}

void st_set_bit(uint8 mask)
{
    _st_data.status |= mask;
}

void st_clear_bit(uint8 mask)
{
    _st_data.status &= ~mask;
}

uint8 st_set_state(uint16 state)
{
    uint8 result = ST_BAD_ARGUMENT;
    
    if (state < ST_STATE_MAXIMUM)
    {
        _st_data.state = state;
        
        result = ST_SUCCESS;
    }
    
    return result;
}

uint8 st_copy_buffer(char *string)
{
    uint32 count = cb_get_count(&_st_data.buffer);
    uint32 i = 0;
    CB_LIST *buffer = &_st_data.buffer;
    ST_OBJECT *object;
    uint8 result = ST_BAD_ARGUMENT;
    
    if (string != NULL)
    {
        if (count > 0)
        {
            isr_2_Disable();
            
            cl_move_backward(buffer->list, count - 1);
            
            do
            {
                cl_get_current_object(buffer->list, NULL,
                    (void **)&object);
                
                *(string + i) = *object->key;
                
                cl_move_forward(buffer->list, 1);
                
                ++i;
                
            } while (i < count);
            
            isr_2_StartEx(st_interrupt);
            
            result = ST_SUCCESS;
        }
        else
        {
            result = ST_EMPTY;
        }
    }
    
    return result;
}

void st_empty_buffer(void)
{
    cb_destroy(&_st_data.buffer);
}

void st_state_0_event_0(void)
{
    UART_1_PutString(_state_0_event_0);
    
    _st_data.state = ST_STATE_1;
}

void st_state_1_event_0(void)
{
    UART_1_PutString(_state_1_event_0);
    
    /*
     *  Generate a fake hardware event. This is done to avoid adding
     *  extra components to the library. Normally the hardware event
     *  flag would be set in the component ISR.
     */
    CyDelay(10000);
    _st_data.status |= ST_HARDWARE_EVENT;
    
    _st_data.state = ST_STATE_2;
}

void st_state_1_event_1(void)
{
    UART_1_PutString(_state_1_event_1);
    
    _st_data.state = ST_STATE_3;
}

void st_state_1_event_2(void)
{
    UART_1_PutString(_state_1_event_2);
    
    _st_data.state = ST_STATE_4;
}

void st_state_2_event_0(void)
{
    st_state_0_event_0();
}

void st_state_3_event_0(void)
{
    st_state_0_event_0();
}

void st_state_4_event_0(void)
{
    char display[60] = {0};
    char buffer[ST_NODE_LIMIT] = {0};
    uint8 size = st_get_count();

    strcpy(display, "*\t");

    if (size < 58)
    {
        st_copy_buffer(buffer);
        strcat(display, buffer);
        strcat(display, "\n");
    }
    else
    {
        strcat(display, "Name Too Long\r\n");
    }
    
    UART_1_PutString(_state_4_event_0_a);
    UART_1_PutString(display);
    UART_1_PutString(_state_4_event_0_b);
    
    st_empty_buffer();
    
    while ((UART_1_ReadTxStatus() & UART_1_TX_STS_FIFO_EMPTY) !=
        UART_1_TX_STS_FIFO_EMPTY)
    {
        CyDelay(1);
    }
    
    UART_1_Stop();
    
    st_stop();
    
    _st_data.state = ST_STATE_5;
}

/****************************************************************************
 *  Local Functions
 ****************************************************************************/
uint8 _create_object(ST_OBJECT **object, char *key)
{
    char *new_key;
    ST_OBJECT *new_object;
    uint8 result = ST_NO_MEMORY;
    
    new_object = malloc(sizeof(*new_object));
    
    if (object != NULL)
    {
        new_key = malloc(strlen(key) + 1);
        
        if (new_key != NULL)
        {
            strcpy(new_key, key);
            new_object->key = new_key;
            
            *object = new_object;
            
            result = ST_SUCCESS;
        }
        else
        {
            free(object);
        }
    }
    
    return result;
}

uint8 _compare(char *input, CB_LIST *buffer)
{
    uint32 buffer_size = cb_get_count(buffer);
    uint32 i;
    uint32 input_size = strlen(input);
    ST_OBJECT *object;
    uint8 result = ST_SUCCESS;

    if (buffer_size >= input_size && input != NULL)
    {
        cl_move_backward(buffer->list, input_size - 1);
        
        for (i = 0 ; i < input_size ; i++)
        {
            cl_get_current_object(buffer->list, NULL, (void **)&object);
            
            if (*(input + i) != *(object->key))
            {
                result = ST_FAILURE;
            }
            
            cl_move_forward(buffer->list, 1);
        }
        
        cl_move_backward(buffer->list, 1);
    }
    else
    {
        result = ST_FAILURE;
    }
    
    return result;
}

/****************************************************************************
 *  End of File
 ****************************************************************************/
