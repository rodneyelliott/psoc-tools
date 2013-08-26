/****************************************************************************
 *
 *  File:           misc.c
 *  Module:         Miscellaneous Function Library
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
/**
 *  @file misc.c
 *  @brief Miscellaneous function library implementation.
 */
 
/****************************************************************************
 *  Modules
 ****************************************************************************/
#include <device.h>
#include <string.h>

#include "misc.h"

/****************************************************************************
 *  Definitions and Macros
 ****************************************************************************/

/****************************************************************************
 *  Typedefs and Structures
 ****************************************************************************/

/****************************************************************************
 *  Prototypes of Local Functions
 ****************************************************************************/

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/

/****************************************************************************
 *  Global Variables
 ****************************************************************************/

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
uint8 mi_utoa(uint32 number, char *string)
{
    uint8 result = MI_BAD_ARGUMENT;
    
    if (string != NULL)
    {
        uint8 c = 0;
        uint8 i = 0;
        uint8 j = 0;
        
        do
        {
            string[i++] = number % 10 + '0';
        } while ((number /=10) > 0);
        
        string[i] = '\0';
        
        for (i = 0, j = strlen(string) - 1 ; i < j ; i++, j--)
        {
            c = string[i];
            string[i] = string[j];
            string[j] = c;
        }
        
        result = MI_SUCCESS;
    }
    
    return result;
}

/****************************************************************************
 *  Local Functions
 ****************************************************************************/

/****************************************************************************
 *  End of File
 ****************************************************************************/
