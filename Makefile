
TARGET = runner
OBJS = main.o

BUILD_PRX = 1
PSP_FW_VERSION = 660

CFLAGS = -O2 -G0 -Wall
LIBS = -lpspdebug -lpspdisplay -lpspctrl

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Runner PSP - Kaua Soares

include $(PSPSDK)/lib/build.mak
