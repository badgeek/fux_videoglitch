# change to your local directories!
PD_APP_DIR = /Applications/Pd-extended.app/Contents/Resources
PD_DIR = /Users/xcorex/Documents/Documents/Projects/Puredata/PdSource/Pd-0.42.5-extended/pd
GEM_DIR = /Users/xcorex/Documents/Documents/Projects/Puredata/PdSource/Pd-0.42.5-extended/Gem

# build flags

INCLUDES = -I$(PD_DIR)/include
CPPFLAGS = -g -O2 -fPIC -freg-struct-return -Os -falign-loops=32 -falign-functions=32 -falign-jumps=32 -funroll-loops -ffast-math -mmmx

UNAME := $(shell uname -s)
ifeq ($(UNAME),Linux)
 CPPFLAGS += -DLINUX
 INCLUDES += -I/usr/include/lqt -fopenmp -I/usr/include/ImageMagick -I/usr/include/lqt -I/usr/include/avifile-0.7 -I/usr/include/FTGL -I/usr/include/freetype2 -I/usr/include/FTGL -I/usr/include/freetype2 -I$(GEM_DIR)/src -I$(PD_DIR)/src -I$(PD_DIR)
 LDFLAGS = -export_dynamic -shared
 LIBS = -shared -Wl,--export-dynamic -lftgl -lv4l2 -lv4l1 -laviplay -L/usr/lib -lquicktime -lpthread -lm -lz -ldl -lquicktime -lpthread -lm -lz -ldl -lMagick++ -lMagickCore -ldv -lmpeg3 -lstdc++ -lGLU -lGL -lXext -lXxf86vm -lXext -lX11 -ldl -lz -lm -lpthread -lfreeimage
 EXTENSION = pd_linux
endif
ifeq ($(UNAME),Darwin)
 CPPFLAGS += -DDARWIN -fpascal-strings -arch i386
 INCLUDES += -I/sw/include -I$(GEM_DIR)/src -I$(PD_DIR)/src -I$(PD_DIR)
 LDFLAGS = -c -arch i386
 LIBS = -arch i386 -dynamiclib -mmacosx-version-min=10.3 -undefined dynamic_lookup -framework QuickTime -framework Carbon -framework AGL -framework OpenGL -arch i386 -lstdc++ -ldl -lz -lm -lpthread -lfreeimage -L/sw/lib -L$(PD_DIR)/bin -L$(PD_DIR)
 EXTENSION = pd_darwin
endif

.SUFFIXES = $(EXTENSION)

SOURCES = fux_videoglitch

all:
	g++ $(LDFLAGS) $(INCLUDES) $(CPPFLAGS) -o glitchWrapper.o -c glitchWrapper.cpp
	g++ $(LDFLAGS) $(INCLUDES) $(CPPFLAGS) -o fux_videoglitch.o -c fux_videoglitch.cpp
	g++ -o $(SOURCES).$(EXTENSION) $(LIBS) ./*.o
	rm -fr ./*.o
deploy:
	rm -fr $(PD_APP_DIR)/extra/$(SOURCES).$(EXTENSION)
	mv *.$(EXTENSION) $(PD_APP_DIR)/extra/
clean:
	rm -f $(SOURCES)*.o
	rm -f $(SOURCES)*.$(EXTENSION)
distro: clean all
	rm *.o
