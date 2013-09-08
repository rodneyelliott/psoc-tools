/****************************************************************************
 *
 *  File:           misc.h
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
#ifndef MISC_H
#define MISC_H
/**
 *  @file misc.h
 *  @brief Miscellaneous function library interface.
 *
 *  <H3> Introduction </H3>
 *
 *  The miscellaneous function library is a collection of oddball functions
 *  that currently do not belong anywhere else. These functions may be moved
 *  into more specialised libraries in a future major release, or they may
 *  not.
 *
 *  <H3> Use </H3>
 *
 *  Because of the disparate nature of the functions that comprise the
 *  library, it is not possible to provide information covering their
 *  collective use.
 *
 *  For further information about the library functions, please refer to the
 *  individual function documentation. For examples of their use, please see
 *  the miscellaneous function test library.
 *
 *  <H3> Hardware </H3>
 *
 *  The miscellaneous function library has no hardware requirements.
 *
 *  <H3> Further Reading </H3>
 *
 *  <a href = "http://www.amazon.com/
        C-Programming-Language-2nd-Edition/dp/0131103628">
 *      The C Programming Language, Second Edition (Amazon) </a>
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
#define MI_SUCCESS                      0

/**
 *  @brief Generic failure.
 */
#define MI_FAILURE                      1

/**
 *  @brief Memory was unable to be allocated from the heap.
 *
 *  Any function returning this value will free any memory that was
 *  successfully allocated from the heap prior to the allocation failure.
 */
#define MI_NO_MEMORY                    2

/**
 *  @brief A bad argument was passed to a function.
 */
#define MI_BAD_ARGUMENT                 3

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
 *  @brief Unsigned integer to ASCII string conversion.
 *  @param[in] number The unsigned integer to convert.
 *  @param[out] string A pointer to the returned string.
 *  @return #MI_SUCCESS if successful, otherwise #MI_BAD_ARGUMENT.
 *  @remark Combines the itoa() and reverse() functions from K&R.
 *  @remark It is up to the caller to allocate sufficient space for the
 *      string.
 */
uint8 mi_utoa(uint32 number, char *string);

#endif

/****************************************************************************
 *  End of File
 ****************************************************************************/
