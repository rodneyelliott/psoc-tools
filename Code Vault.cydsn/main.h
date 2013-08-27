/****************************************************************************
 *
 *  File:           main.h
 *  Module:         Main Program
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
#ifndef MAIN_H
#define MAIN_H
/**
 *  @file main.h
 *  @brief Main program interface.
 *
 *  <H3> Introduction </H3>
 *
 *  The main program contains the code necessary to test each of the libraries
 *  that comprise the code vault.
 *
 *  <H3> Use </H3>
 *
 *  In order to use the main program, the programmer must start by ensuring
 *  that the project hardware requirements have been met. These are detailed
 *  in the hardware section below.
 *
 *  With the hardware requirements met, the next step is to uncomment the test
 *  function of the library of interest. The project should then be built and
 *  downloaded to the target. The observed serial output should then be
 *  compared to the expected serial output for the library. This is listed in
 *  the corresponding test library interface file.
 *
 *  <H3> Hardware </H3>
 *
 *  The main program has been designed to run on a Cypress CY8CKIT-001
 *  development kit fitted with a PSoC5 CY8C5568AXI-060 module. It requires
 *  access to the following components:
 *
 *  - RTC_1
 *  - UART_1
 *
 *  The PSoC5 module must be fitted with a 32.768kHz crystal, and the 'XTAL
 *  32kHz' source must be enabled in the clock section of the project design
 *  wide resource (*.cydwr) file.
 *
 *  Pin P1_2 on the development kit prototype area must be connected to the
 *  UART RX pin, and pin P1_7 must be connected to the UART TX pin. Ensure
 *  that the RS_232PWR jumper is also set.
 */

/**
 *  @mainpage PSoC Tools
 *
 *  @section sec_introduction Introduction
 *
 *  PSoC Tools is a collection of projects that enable the programmer to
 *  quickly incorporate a range of useful functionality into their next
 *  Cypress PSoC embedded application.
 *
 *  The first project to be added to PSoC Tools is the Code Vault.
 */

/****************************************************************************
 *  Modules
 ****************************************************************************/

/****************************************************************************
 *  Definitions and Macros
 ****************************************************************************/

/****************************************************************************
 *  Typedefs and Structures
 ****************************************************************************/

/****************************************************************************
 *  Exported Variables
 ****************************************************************************/

/****************************************************************************
 *  Exported Functions
 ****************************************************************************/

#endif

/****************************************************************************
 *  End of File
 ****************************************************************************/
