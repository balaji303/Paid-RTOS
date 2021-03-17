/****************************************************************************
* MInimal Real-time Operating System (MIROS)
* version 0.23 (matching lesson 23)
*
* This software is a teaching aid to illustrate the concepts underlying
* a Real-Time Operating System (RTOS). The main goal of the software is
* simplicity and clear presentation of the concepts, but without dealing
* with various corner cases, portability, or error handling. For these
* reasons, the software is generally NOT intended or recommended for use
* in commercial applications.
*
* Copyright (C) 2018 Miro Samek. All Rights Reserved.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <https://www.gnu.org/licenses/>.
*
* Contact Information:
* https://www.state-machine.com
****************************************************************************/
#include <stdint.h>
#include "paid.h"

void OSThread_start(
    OSThread *me,
    OSThreadHandler threadHandler,
    void *stkSto, uint32_t stkSize);

{
	  *(--sp_blinky1) = (1U << 24);  /* xPSR */
    *(--sp_blinky1) = (uint32_t)&main_blinky1; /* PC */
    *(--sp_blinky1) = 0x0000000EU; /* LR  */
    *(--sp_blinky1) = 0x0000000CU; /* R12 */
    *(--sp_blinky1) = 0x00000003U; /* R3  */
    *(--sp_blinky1) = 0x00000002U; /* R2  */
    *(--sp_blinky1) = 0x00000001U; /* R1  */
    *(--sp_blinky1) = 0x00000000U; /* R0  */
    /* additionally, fake registers R4-R11 */
    *(--sp_blinky1) = 0x0000000BU; /* R11 */
    *(--sp_blinky1) = 0x0000000AU; /* R10 */
    *(--sp_blinky1) = 0x00000009U; /* R9 */
    *(--sp_blinky1) = 0x00000008U; /* R8 */
    *(--sp_blinky1) = 0x00000007U; /* R7 */
    *(--sp_blinky1) = 0x00000006U; /* R6 */
    *(--sp_blinky1) = 0x00000005U; /* R5 */
    *(--sp_blinky1) = 0x00000004U; /* R4 */
	
}

