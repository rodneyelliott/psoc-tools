/****************************************************************************
 *
 *  File:           main.c
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
/**
 *  @file main.c
 *  @brief Main program implementation.
 */
 
/****************************************************************************
 *  Modules
 ****************************************************************************/
#include <device.h>

//#include "button_test.h"
//#include "cbuff_test.h"
//#include "cllist_test.h"
//#include "deque_test.h"
//#include "dllist_test.h"
//#include "error_test.h"
//#include "main.h"
//#include "misc_test.h"
//#include "queue_test.h"
//#include "rtime_test.h"
#include "state_test.h"

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
/**
 *  @brief The main program.
 *  @remark Calls the test function of each of the libraries that comprise
 *      the code vault.
 */
void main()
{
    CyGlobalIntEnable;
    
    //dlt_test_1();
    //det_test_1();
    //qut_test_1();
    //clt_test_1();
    //cbt_test_1();
    //mit_test_1();
    //rtt_test_1();
    //ert_test_1();
    //but_test_1();
    //but_test_2();
    //stt_test_1();
    stt_test_2();
    
    for (;;)
    {
    }
}

/****************************************************************************
 *  Local Functions
 ****************************************************************************/

/****************************************************************************
 *  End of File
 ****************************************************************************/
