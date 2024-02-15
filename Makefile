TARGET = main
OBJS = main.o 
OBJS += gamestate.o gamecontext.o gameobject.o component.o
OBJS += math.o loadimage.o
OBJS += itemlist.o
CFLAGS = -g
LIBDIR  =
LIBS = -lstdc++ -lSDL2main -lSDL2 -lGL -lGLU -lglut -lz \
         -lpspvfpu -lpsphprm -lpspsdk -lpspctrl -lpspumd -lpsprtc -lpsppower -lpspgum -lpspgu -lpspaudiolib -lpspaudio -lpsphttp -lpspssl -lpspwlan \
         -lpspnet_adhocmatching -lpspnet_adhoc -lpspnet_adhocctl -lm -lpspvram
BUILD_PRX = 1
EXTRA_TARGETS   = EBOOT.PBP
PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

# Run game on PPSSPP
test: EBOOT.PBP
	/snap/bin/ppsspp-emu.ppsspp-sdl $(shell pwd)/EBOOT.PBP
