#include <sysinit.h>

#include "basic/basic.h"
#include "basic/config.h"


#include "lcd/render.h"
#include "lcd/allfonts.h"

#include "usbhid/usb.h"
#include "usbhid/usbcore.h"
#include "usbhid/usbhw.h"
#include "usbhid/usbcfg.h"
#include "usbhid/hiduser.h"
#include "usbhid/util.h"

#include <string.h>

#if CFG_USBMSC
#error "MSC is defined"
#endif

#if !CFG_USBHID1
#error "HID is not defined"
#endif


void backlightInit(void);
/**************************************************************************/

uint8_t InReport[USB_HID_IN_REPORT_SIZE];
uint8_t OutReport[USB_HID_OUT_REPORT_SIZE];
uint8_t once;
uint8_t xkey;

void GetInReport(void) {
    memset(InReport, 0, USB_HID_IN_REPORT_SIZE);
    if (xkey) { 
        InReport[2] = xkey;
        xkey = 0;
    }
}

void SetOutReport(void) {
    uint8_t i;
    for (i=0; i < USB_HID_OUT_REPORT_SIZE; i++) {
        if (OutReport[i]) {
            gpioSetValue(RB_LED0, 1);
            return;
        }
    }
    gpioSetValue(RB_LED0, 0);
    return;
}

void main_usbhid(void){
   char key;
   backlightInit();

   xkey=0;
   once =0;

   gpioSetDir(RB_SPI_SS0, gpioDirection_Input);
   gpioSetDir(RB_SPI_SS1, gpioDirection_Input);
   gpioSetDir(RB_SPI_SS2, gpioDirection_Input);
   gpioSetDir(RB_SPI_SS3, gpioDirection_Input);
   gpioSetDir(RB_SPI_SS4, gpioDirection_Input);
   gpioSetDir(RB_SPI_SS5, gpioDirection_Input);
   gpioIntDisable(RB_BUSINT),
   gpioSetDir(RB_BUSINT, gpioDirection_Input);

   gpioSetPullup(&IOCON_PIO2_5, gpioPullupMode_PullUp);
   gpioSetPullup(&IOCON_PIO2_4, gpioPullupMode_PullUp);
   gpioSetPullup(&IOCON_PIO2_8, gpioPullupMode_PullUp);
   gpioSetPullup(&IOCON_PIO3_2, gpioPullupMode_PullUp);
   gpioSetPullup(&IOCON_PIO3_1, gpioPullupMode_PullUp);
   gpioSetPullup(&IOCON_PIO2_10, gpioPullupMode_PullUp);
   gpioSetPullup(&IOCON_PIO3_0, gpioPullupMode_PullUp);
   while(1) {
    lcdDisplay();
    delayms(10);
    key = getInput();
    font=&Font_7x8;
    if(key==BTN_LEFT) {
        DoString(0,8,"Enter ISP!");
        lcdDisplay();
        ISPandReset();
    } else if (key==BTN_RIGHT) {
        DoString(0,8,"*****");
        lcdDisplay();
        key = 0;
        usbHIDInit();
        while(1) {
            if (gpioGetValue(RB_SPI_SS0)==0) {
                xkey = 4;
            } else if (gpioGetValue(RB_SPI_SS1)==0) {
                xkey = 5;
            } else if (gpioGetValue(RB_SPI_SS2)==0) {
                xkey = 6;
            } else if (gpioGetValue(RB_SPI_SS3)==0) {
                xkey = 7;
            } else if (gpioGetValue(RB_SPI_SS4)==0) {
                xkey = 8;
            } else if (gpioGetValue(RB_SPI_SS5)==0) {
                xkey = 9;
            } else if (gpioGetValue(RB_BUSINT)==0) {
                xkey = 10;
            } else {
                key = getInputRaw();
                if (key==BTN_LEFT) {
                    DoString(0,16,"LEFT ");
                    xkey = 80;
                } else if (key==BTN_RIGHT) {
                    DoString(0,16,"RIGHT");
                    xkey = 79;
                } else if (key==BTN_DOWN) {
                    DoString(0,16,"DOWN ");
                    xkey = 81;
                } else if (key==BTN_UP) {
                    DoString(0,16,"UP   ");
                    xkey = 82;
                } else if (key==BTN_ENTER) {
                    DoString(0,16,"ENTER");
                    xkey = 88;
                } else {
                    DoString(0,16,"------");
                }
                lcdDisplay();
            }
            work_queue();
        };
    }
    DoString(0,0,"U HID");
   }
};

