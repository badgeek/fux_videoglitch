# build flags
INCLUDES = -I$(PD_DIR)/include
CPPFLAGS = -g -O2 -fPIC -freg-struct-return -Os -falign-loops=32 -falign-functions=32 -falign-jumps=32 -funroll-loops -ffast-math -mmmx

# Docker parameters
DOCKER_IMAGE=constructionsincongrues/fux_videoglitch
DOCKER_IMAGE_TAG=`git rev-parse --short HEAD`

UNAME := $(shell uname -s)
ifeq ($(UNAME),Linux)
 PD_APP_DIR = /usr/lib/pd-extended
 PD_DIR = /home/manticore/puredata/0.42/Pd
 GEM_DIR = /home/manticore/puredata/0.42/Gem
 CPPFLAGS += -DLINUX
 INCLUDES += -I/usr/include/lqt -fopenmp -I/usr/include/ImageMagick -I/usr/include/lqt -I/usr/include/avifile-0.7 -I/usr/include/FTGL -I/usr/include/freetype2 -I/usr/include/FTGL -I/usr/include/freetype2 -I$(GEM_DIR) -I$(PD_DIR) -I$(PD_DIR)
 LDFLAGS = -export_dynamic -shared
 LIBS = -shared -Wl,--export-dynamic -lftgl -lv4l2 -lv4l1 -laviplay -L/usr/lib -lquicktime -lpthread -lm -lz -ldl -lquicktime -lpthread -lm -lz -ldl -lMagick++ -ldv -lmpeg3 -lstdc++ -lGLU -lGL -lXext -lXxf86vm -lXext -lX11 -ldl -lz -lm -lpthread -lfreeimage
 EXTENSION = pd_linux
endif
ifeq ($(UNAME),Darwin)
 PD_APP_DIR = /Applications/Pd-extended.app/Contents/Resources
 PD_DIR = /Applications/Pd-extended.app/Contents/Resources/src/pd
 GEM_DIR = /Applications/Pd-extended.app/Contents/Resources/src/Gem
 CPPFLAGS += -DDARWIN -fpascal-strings -arch i386
 INCLUDES += -I/sw/include -I$(GEM_DIR) -I$(PD_DIR) -I$(PD_DIR)
 LDFLAGS = -c -arch i386
 LIBS = -arch i386 -dynamiclib -mmacosx-version-min=10.3 -undefined dynamic_lookup -framework QuickTime -framework Carbon -framework AGL -framework OpenGL -arch i386 -lstdc++ -ldl -lz -lm -lpthread -lfreeimage -L/sw/lib -L$(PD_APP_DIR)/bin -L$(PD_DIR)
 EXTENSION = pd_darwin
endif

.SUFFIXES = $(EXTENSION)

SOURCES = fux_videoglitch

all:
	g++ $(LDFLAGS) $(INCLUDES) $(CPPFLAGS) -o glitchWrapper.o -c glitchWrapper.cpp
	g++ $(LDFLAGS) $(INCLUDES) $(CPPFLAGS) -o fux_videoglitch.o -c fux_videoglitch.cpp
	g++ -o $(SOURCES).$(EXTENSION) $(LIBS) ./*.o
	rm -fr ./*.o

all-docker:
	make PD_DIR=/usr/include/pd GEM_DIR=/usr/include/Gem IMAGEMAGIK_DIR=/usr/include/ all

deploy:
	rm -fr $(PD_APP_DIR)/extra/$(SOURCES).$(EXTENSION)
	mv *.$(EXTENSION) $(PD_APP_DIR)/extra/

clean:
	rm -f $(SOURCES)*.o
	rm -f $(SOURCES)*.$(EXTENSION)

distro: clean all
	rm *.o

docker-attach:
	docker run --rm -it -v $(PWD):/usr/local/src $(DOCKER_IMAGE) /bin/bash

docker-compile:
	docker run --rm -v $(PWD):/usr/local/src $(DOCKER_IMAGE)

docker-image:
	docker build -t $(DOCKER_IMAGE):$(DOCKER_IMAGE_TAG) .
	docker tag $(DOCKER_IMAGE):$(DOCKER_IMAGE_TAG) $(DOCKER_IMAGE):latest

docker-push:
	docker push $(DOCKER_IMAGE):$(DOCKER_IMAGE_TAG)
	docker push $(DOCKER_IMAGE):latest
