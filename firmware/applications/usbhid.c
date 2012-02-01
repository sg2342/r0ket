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
            key = getInput();
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
            }
            lcdDisplay();
            delayms(10);
        };
    }
    DoString(0,0,"U HID");
   }
};

