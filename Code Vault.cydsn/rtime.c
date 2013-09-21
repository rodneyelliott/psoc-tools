/****************************************************************************
 *
 *  File:           rtime.c
 *  Module:         Real-Time Clock Library
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
 *  @file rtime.c
 *  @brief Real-time clock library implementation.
 */
 
/****************************************************************************
 *  Modules
 ****************************************************************************/
#include <device.h>
#include <stdlib.h>
#include <string.h>

#include "misc.h"
#include "rtime.h"

/****************************************************************************
 *  Definitions and Macros
 ****************************************************************************/
/**
 *  @brief Default library second value.
 */
#define _DEFAULT_SECOND                 0

/**
 *  @brief Default library minute value.
 */
#define _DEFAULT_MINUTE                 0

/**
 *  @brief Default library hour value.
 */
#define _DEFAULT_HOUR                   11

/**
 *  @brief Default library day value.
 */
#define _DEFAULT_DAY                    11

/**
 *  @brief Default library month value.
 */
#define _DEFAULT_MONTH                  11

/**
 *  @brief Default library year value.
 */
#define _DEFAULT_YEAR                   1918

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
/**
 *  @brief The private RT_DATA structure used by the library.
 */
static RT_DATA *_rt_data = NULL;

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
uint8 rt_start(void)
{
    uint8 result = RT_NO_MEMORY;
    
    _rt_data = malloc(sizeof(*_rt_data));
    
    if (_rt_data != NULL)
    {
        _rt_data->Sec = _DEFAULT_SECOND;
        _rt_data->Min = _DEFAULT_MINUTE;
        _rt_data->Hour = _DEFAULT_HOUR;
        _rt_data->DayOfMonth = _DEFAULT_DAY;
        _rt_data->Month = _DEFAULT_MONTH;
        _rt_data->Year = _DEFAULT_YEAR;
        
        rt_write();
        
        RTC_1_Start();
        
        result = RT_SUCCESS;
    }
    
    return result;
}

uint8 rt_stop(void)
{
    uint8 result = RT_FAILURE;
    
    if (_rt_data != NULL)
    {
        RTC_1_Stop();
    
        free(_rt_data);
        _rt_data = NULL;
        
        result = RT_SUCCESS;
    }
    
    return result;
}

uint8 rt_write(void)
{
    uint8 result = RT_FAILURE;
    
    if (_rt_data != NULL)
    {
        RTC_1_DisableInt();
        
        RTC_1_WriteSecond(_rt_data->Sec);
        RTC_1_WriteMinute(_rt_data->Min);
        RTC_1_WriteHour(_rt_data->Hour);
        RTC_1_WriteDayOfMonth(_rt_data->DayOfMonth);
        RTC_1_WriteMonth(_rt_data->Month);
        RTC_1_WriteYear(_rt_data->Year);
        
        RTC_1_EnableInt();
        
        result = RT_SUCCESS;
    }
    
    return result;
}

uint8 rt_read(RT_DATA *timestamp)
{
    uint8 result = RT_BAD_ARGUMENT;
    
    if (timestamp != NULL)
    {
        if (_rt_data != NULL)
        {
            *timestamp = *(RT_DATA *)RTC_1_ReadTime();
            
            result = RT_SUCCESS;
        }
        else
        {
            result = RT_FAILURE;
        }
    }
    
    return result;
}

uint8 rt_set_date(uint8 day, uint8 month, uint16 year)
{
    uint8 result = RT_SUCCESS;
    
    if (_rt_data != NULL)
    {
        if (day < 1 || day > 31)
        {
            result = RT_BAD_ARGUMENT;
        }
        
        if (month < 1 || month > 12)
        {
            result = RT_BAD_ARGUMENT;
        }
        
        if (year < 1900 || year > 2200)
        {
            result = RT_BAD_ARGUMENT;
        }
        
        if (result == RT_SUCCESS)
        {
            _rt_data->DayOfMonth = day;
            _rt_data->Month = month;
            _rt_data->Year = year;
        }
    }
    else
    {
        result = RT_FAILURE;
    }
                
    return result;
}

uint8 rt_set_time(uint8 hour, uint8 minute, uint8 second)
{
    uint8 result = RT_SUCCESS;
    
    if (_rt_data != NULL)
    {
        if (hour < 0 || hour > 23)
        {
            result = RT_BAD_ARGUMENT;
        }
        
        if (minute < 0 || minute > 59)
        {
            result = RT_BAD_ARGUMENT;
        }
        
        if (second < 0 || second > 59)
        {
            result = RT_BAD_ARGUMENT;
        }
        
        if (result == RT_SUCCESS)
        {
            _rt_data->Sec = second;
            _rt_data->Min = minute;
            _rt_data->Hour = hour;
        }
    }
    else
    {
        result = RT_FAILURE;
    }
                
    return result;
}

uint8 rt_convert(RT_DATA *timestamp, char *string)
{
    uint8 result = RT_BAD_ARGUMENT;
    
    if (timestamp != NULL && string != NULL)
    {
        char t[5] = {'\0'};
        
        strcpy(string, "");
        
        if (timestamp->DayOfMonth < 10)
        {
            strcpy(string, "0");
        }
        
        mi_utoa(timestamp->DayOfMonth, t);
        strcat(string, t);
        strcat(string, "/");
        
        if (timestamp->Month < 10)
        {
            strcat(string, "0");
        }
        
        mi_utoa(timestamp->Month, t);
        strcat(string, t);
        strcat(string, "/");
        
        mi_utoa(timestamp->Year, t);
        strcat(string, t);
        strcat(string, " ");
            
        if (timestamp->Hour == 0)
        {
            strcpy(t, "00");
            strcat(string, t);
        }
        else if (timestamp->Hour > 0 && timestamp->Hour < 10)
        {
            strcpy(t, "0");
            strcat(string, t);
            mi_utoa(timestamp->Hour, t);
            strcat(string, t);
        
        }
        else
        {
            mi_utoa(timestamp->Hour, t);
            strcat(string, t);
        }
        
        strcat(string, ":");
        
        if (timestamp->Min == 0)
        {
            strcpy(t, "00");
            strcat(string, t);
        }
        else if (timestamp->Min > 0 && timestamp->Min < 10)
        {
            strcpy(t, "0");
            strcat(string, t);
            mi_utoa(timestamp->Min, t);
            strcat(string, t);
        
        }
        else
        {
            mi_utoa(timestamp->Min, t);
            strcat(string, t);
        }
        
        strcat(string, ":");
        
        if (timestamp->Sec == 0)
        {
            strcpy(t, "00");
            strcat(string,t);
        }
        else if (timestamp->Sec > 0 && timestamp->Sec < 10)
        {
            strcpy(t, "0");
            strcat(string, t);
            mi_utoa(timestamp->Sec, t);
            strcat(string, t);
        
        }
        else
        {
            mi_utoa(timestamp->Sec, t);
            strcat(string, t);
        }
        
        result = RT_SUCCESS;
    }
    
    return result;
}

/****************************************************************************
 *  Local Functions
 ****************************************************************************/

/****************************************************************************
 *  End of File
 ****************************************************************************/
