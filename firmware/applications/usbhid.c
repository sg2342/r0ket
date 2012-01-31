#include <sysinit.h>

#include "basic/basic.h"
#include "basic/config.h"


#include "lcd/render.h"
#include "lcd/allfonts.h"

#include "usbhid/usb.h"
#include "usbhid/usbcore.h"
#include "usbhid/usbhw.h"
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

void main_usbhid(void){
   char key;

   backlightInit();


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
        usbHIDInit();
        while(1) {};
    }
    DoString(0,0,"U HID");
   }
};

void tick_usbhid(void){
    return;
}
