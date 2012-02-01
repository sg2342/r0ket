##########################################################################
# User configuration and firmware specific object files	
##########################################################################

OBJS =
OBJS += usbhw.o
OBJS += usbcore.o
OBJS += usbdesc.o
OBJS += usbuser.o
OBJS += hiduser.o
OBJS += util.o
#OBJS += demo.o

LIBNAME=usbhid

##########################################################################
# GNU GCC compiler flags
##########################################################################
ROOT_PATH?= ..
INCLUDE_PATHS = -I$(ROOT_PATH) -I../core -I.

include $(ROOT_PATH)/Makefile.inc

##########################################################################
# Actual work
##########################################################################

include $(ROOT_PATH)/Makefile.util
