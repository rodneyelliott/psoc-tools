/****************************************************************************
 *
 *  File:           rtime.h
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
#ifndef RTIME_H
#define RTIME_H
/**
 *  @file rtime.h
 *  @brief Real-time clock library interface.
 *
 *  <H3> Introduction </H3>
 *
 *  The real-time clock library is a collection of functions that enable the
 *  programmer to use the real-time clock (RTC) component within their
 *  project.
 *
 *  The RT_DATA structure used by the library is the same as that used by the
 *  RTC component API itself. When reading temporal (date and time) values
 *  from the RTC component, an RT_DATA structure supplied by the programmer
 *  is used as the destination, and when writing temporal values to the RTC
 *  component, a private RT_DATA structure is used as the source.
 *
 *  In order to preserve the integrity of the RTC component, programmers do
 *  not have direct access to the private RT_DATA structure. Any changes to
 *  its temporal values must instead be made using the library functions
 *  rt_set_date() and rt_set_time().
 *
 *  <H3> Use </H3>
 *
 *  In order to use the library, the programmer must start by calling the
 *  function rt_start(). This starts the RTC component and initialises the
 *  private RT_DATA structure. The functions rt_set_date() and rt_set_time()
 *  may be used to change the temporal values of the private RT_DATA
 *  structure. The RTC component may then be updated with these new values
 *  using the function rt_write().
 *
 *  To retrieve the current date and time from the RTC component, first read
 *  temporal values using the library function rt_read(). These values may
 *  then be converted into an ASCII string ready for storage or display using
 *  the function rt_convert(). Finally, the library function rt_stop() stops
 *  the RTC component.
 *
 *  For further information about these library functions, please refer to
 *  the individual function documentation.
 *
 *  <H3> Hardware </H3>
 *
 *  The RTC library has been designed to run on a Cypress CY8CKIT-001
 *  development kit fitted with a PSoC5 CY8C5568AXI-060 module. It requires
 *  access to the following components:
 *
 *  - RTC_1
 *
 *  The PSoC5 module must be fitted with a 32.768kHz crystal, and the 'XTAL
 *  32kHz' source must be enabled in the clock section of the project design
 *  wide resource (*.cydwr) file.
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
#define RT_SUCCESS                      0

/**
 *  @brief Generic failure.
 */
#define RT_FAILURE                      1

/**
 *  @brief Memory was unable to be allocated from the heap.
 *
 *  Any function returning this value will free any memory that was
 *  successfully allocated from the heap prior to the allocation failure.
 */
#define RT_NO_MEMORY                    2

/**
 *  @brief A bad argument was passed to a function.
 */
#define RT_BAD_ARGUMENT                 3

/****************************************************************************
 *  Typedefs and Structures
 ****************************************************************************/
/**
 *  @brief Temporal values.
 */
typedef struct RT_DATA
{
    /**
     *  @brief Second value (0-59).
     */
    uint8 Sec;
    
    /**
     *  @brief Minute value (0-59).
     */
    uint8 Min;
    
    /**
     *  @brief Hour value (0-23).
     */
    uint8 Hour;
    
    /**
     *  @brief Day of the week value (1-7).
     */
    uint8 DayOfWeek;
    
    /**
     *  @brief Day of the month value (1-31).
     */
    uint8 DayOfMonth;
    
    /**
     *  @brief Day of the year value (1-365).
     */
    uint16 DayOfYear;
    
    /**
     *  @brief Month value (1-12).
     */
    uint8 Month;
    
    /**
     *  @brief Year value (1900-2200).
     */
    uint16 Year;
} RT_DATA;

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/
/**
 *  @brief Start the RTC component used by the library.
 *  @return #RT_SUCCESS if successful, otherwise #RT_NO_MEMORY.
 *  @warning This must be the first library function to be called.
 */
uint8 rt_start(void);

/**
 *  @brief Stop the RTC component used by the library.
 *  @return #RT_SUCCESS if successful, otherwise #RT_FAILURE.
 *  @remark This should be the last library function to be called.
 */
uint8 rt_stop(void);

/**
 *  @brief Write temporal values to the RTC component.
 *  @return #RT_SUCCESS if successful, otherwise #RT_FAILURE.
 *  @remark Writes values from the private RT_DATA structure
 *      to the RTC component.
 */
uint8 rt_write(void);

/**
 *  @brief Read temporal values from the RTC component.
 *  @param[in] timestamp A pointer to the returned temporal values.
 *  @return #RT_SUCCESS if successful, otherwise #RT_BAD_ARGUMENT or
 *      #RT_FAILURE.
 */
uint8 rt_read(RT_DATA *timestamp);

/**
 *  @brief Set the current date.
 *  @param[in] day Day value.
 *  @param[in] month Month value.
 *  @param[in] year Year value.
 *  @return #RT_SUCCESS if successful, otherwise #RT_BAD_ARGUMENT or
 *      #RT_FAILURE.
 *  @remark Writes date values to the private RT_DATA structure.
 */
uint8 rt_set_date(uint8 day, uint8 month, uint16 year);

/**
 *  @brief Set the current time.
 *  @param[in] hour Hour value.
 *  @param[in] minute Minute value.
 *  @param[in] second Second value.
 *  @return #RT_SUCCESS if successful, otherwise #RT_BAD_ARGUMENT or
 *      #RT_FAILURE.
 *  @remark Writes time values to the private RT_DATA structure.
 */
uint8 rt_set_time(uint8 hour, uint8 minute, uint8 second);

/**
 *  @brief Convert temporal values to an ASCII string.
 *  @param[in] timestamp A pointer to the temporal values to convert.
 *  @param[in] string A pointer to the returned string.
 *  @return #RT_SUCCESS if successful, otherwise #RT_BAD_ARGUMENT.
 *  @remark String format is 'DD/MM/YYY HH:MM:SS' where 'DD' is the
 *      day value et cetera.
 *  @remark It is up to the caller to allocate sufficient space for the
 *      string.
 */
uint8 rt_convert(RT_DATA *timestamp, char *string);

#endif

/****************************************************************************
 *  End of File
 ****************************************************************************/
