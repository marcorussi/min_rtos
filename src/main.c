/*
 * The MIT License (MIT)
 *
 * Copyright (c) [2015] [Marco Russi]
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

/*
 * This file main.c represents the entry point of the software.
 *
 * Author : Marco Russi
 *
 * Evolution of the file:
 * 06/08/2015 - File created - Marco Russi
 *
*/

#include <stdbool.h>
#include <stdlib.h>
#include "p32mx795f512l.h"
#include "fw_common.h"

#include "int.h"
#include "rtos.h"
#include "rtos_cfg.h"


/* PIC32 ESK configuration fuses */
#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF, FPBDIV = DIV_2, POSCMOD = XT, FNOSC = PRIPLL, CP = OFF
#pragma config FMIIEN = OFF, FETHIO = OFF	// external PHY in RMII/alternate configuration




/* init port pins function */
LOCAL void initPins ( void )
{
    /* temporary set all digital */
    AD1PCFG = 0xFFFF;

    /* Switches */
    TRISDbits.TRISD6 = 1;
    TRISDbits.TRISD7 = 1;
    TRISDbits.TRISD13 = 1;

    /* Enable pullups on the Switch ports */
    CNENbits.CNEN15 = 1;
    CNENbits.CNEN16 = 1;
    CNENbits.CNEN19 = 1;

    /* LEDs pins as output */
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;
}




/* main function */
int main ( void )
{
    /* init port pins */
    initPins();

    /* init interrupts */
    INT_EnableInt();

    /* start RTOS */
    RTOS_startOperation(RTOS_CFG_KE_FIRST_STATE);

    while ( true )
    {
        /* call RTOS tsk execution function */
        RTOS_executeTask();
    }

    /* Execution should not come here during normal operation */
    
    return ( EXIT_FAILURE );
}



