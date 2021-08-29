####### Platform specifics

PLATFORM_OS				:= $(shell uname | cut -d_ -f1)
PLATFORM_ARCH			:= $(shell getconf LONG_BIT)
GXX_GTEQ_472			:= $(shell expr `g++ -dumpversion | sed -e 's/\.\([0-9][0-9]\)/\1/g' -e 's/\.\([0-9]\)/0\1/g' -e 's/^[0-9]\{3,4\}$$/&00/'` \>= 60300)

####### Compiler, tools and options

CHMOD					= chmod +x
CHKDIR					= test -d
MKDIR					= mkdir -p
RM						= rm -rf
CD						= cd
CP						= cp -rf
MV						= mv
AR						= ar rcs
LINK					= ln -s
SU						= sudo
RANLIB					= ranlib
VERBOSE					= -v
LDCOFIG					= ldconfig
EXPORT					= export
CHOWN					= chown $(USER).$(USER)

####### Flags

DEFINES					= -D_DEFAULT_SOURCE -D_GNU_SOURCE

GCC						= gcc
GXX						= g++
GCC_VERSION				=
GXX_VERSION				=

ifeq ($(GXX_GTEQ_472), 1)
	DEFINES				= -D_DEFAULT_SOURCE -D_GNU_SOURCE
	GCC_VERSION			= -std=c99
	GXX_VERSION			= -std=c++17
else
	DEFINES				= -D_BSD_SOURCE -D_GNU_SOURCE
	GCC_VERSION			= -std=c99
	GXX_VERSION			= -std=c++11
endif

GCCFLAGS				=
CXXFLAGS				=

####### Paths

INCS					+= -I/usr/local/include
INCS					+= -I/usr/include
ifeq ($(PLATFORM_ARCH), 32)
INCS					+= -I/usr/include/Linux32_i86-gnu
endif
ifeq ($(PLATFORM_ARCH), 64)
INCS					+= -I/usr/include/x86_64-linux-gnu
endif
LIBS					+= -L/usr/lib
LIBS					+= -L/usr/local/lib
ifeq ($(PLATFORM_ARCH), 32)
LIBS					+= -L/usr/lib/x32_i86-linux-gnu
endif
ifeq ($(PLATFORM_ARCH), 64)
LIBS					+= -L/usr/lib/x86_64-linux-gnu
endif
LIBS					+= -lGL
#LIBS					+= -lGLEW
LIBS					+= -lGLU
LIBS					+= -lSDL2
LIBS					+= -lSDL2_image
LIBS					+= -lSDL2_gfx
LIBS					+= -lSDL2_mixer
LIBS					+= -lSDL2_net
LIBS					+= -lSDL2_ttf
LIBS					+= -lopencv_core
LIBS					+= -lopencv_imgproc
LIBS					+= -lopencv_highgui
#LIBS					+= -lopencv_ml
#LIBS					+= -lopencv_video
#LIBS					+= -lopencv_features2d
#LIBS					+= -lopencv_calib3d
#LIBS					+= -lopencv_objdetect
#LIBS					+= -lopencv_contrib
#LIBS					+= -lopencv_legacy
#LIBS					+= -lopencv_flann 
#LIBS					+= -lopencv_xfeatures2d
#LIBS					+= -lopencv_imgcodecs
LIBS					+= -lusb-1.0
LIBS					+= -lmysqlclient
#LIBS					+= -lsqlite3
LIBS					+= -lzbar
LIBS					+= -lcrypto
LIBS					+= -lssl
LIBS					+= -lblkid
LIBS					+= -lX11
LIBS					+= -lXrandr
LIBS					+= -lrt
LIBS					+= -lm
LIBS					+= -ldl
LIBS					+= -lz
LIBS					+= -lpthread
ifeq ($(PLATFORM_ARCH), 32)
LIBS					+= -m32
endif
ifeq ($(PLATFORM_ARCH), 64)
LIBS					+= -m64
endif

####### Files

ABS_PATH				= $(shell pwd)

DIR_RSC					= resources
DIR_BUILD				= build
DIR_MOUNT				= mount
DIR_SRC					= src
DIR_INC					= includes

FILE_OBJ				= $(patsubst $(DIR_SRC)/%.cpp,$(DIR_BUILD)/%.o,$(wildcard $(DIR_SRC)/*/*.cpp))

ENGINE					= gorilla2d
ENGINE_LIB				= lib$(ENGINE)
ENGINE_VERSION			= 0.1.0

####### Installer and Unistaller

PATH_INSTALL_INC		= /usr/local/include/$(ENGINE_LIB)
PATH_INSTALL_LIB		= /usr/local/lib/$(ENGINE_LIB)
PATH_INSTALL_RSC		= /usr/local/share/$(ENGINE)
PATH_LD					= /etc/ld.so.conf.d/$(ENGINE_LIB)-$(ENGINE_VERSION).conf

####### Build

build-pre:
	@echo Building ... 

build-post:
	@echo Done.

.SECONDARY: build-pre build-post

######## Compiling all

all: build-debug
release: build-release

.PHONE: all release

###### Debug

build-debug: DEFINES  += -DDEBUG -DUSE_OPENCV
build-debug: CFLAGS   := -O0 -g3 -g -ggdb -O0 -Wall -W -Wextra -pedantic -pipe -fmessage-length=0 -rdynamic $(GCC_VERSION) $(DEFINES) -fPIC
build-debug: CXXFLAGS := -O0 -g3 -g -ggdb -O0 -Wall -W -Wextra -pedantic -pipe -fmessage-length=0 -rdynamic $(GXX_VERSION) $(DEFINES) -fPIC
build-debug: build-lib
	@$(MAKE) --no-print-directory build-post

.SECONDARY: build-debug

###### Release

build-release: DEFINES  +=
build-release: CFLAGS   := -g0 -pipe -fmessage-length=0 -rdynamic $(GCC_VERSION) $(DEFINES) -fPIC
build-release: CXXFLAGS := -g0 -pipe -fmessage-length=0 -rdynamic $(GXX_VERSION) $(DEFINES) -fPIC
build-release: build-lib
	@$(MAKE) --no-print-directory build-post

.SECONDARY: build-release

####### Strip

FILE_OBJ	:= $(strip $(FILE_OBJ))
INCS		:= $(strip $(INCS))
LIBS_LIB	:= $(strip $(LIBS))
DEFINES		:= $(strip $(DEFINES))
CFLAGS		:= $(strip $(CFLAGS))
CXXFLAGS	:= $(strip $(CXXFLAGS))

######## Compiling objects

build-lib: build-pre $(ENGINE_LIB)

$(ENGINE_LIB): $(FILE_OBJ)
	@$(CHKDIR) ./$(DIR_MOUNT) | $(MKDIR) $(DIR_MOUNT)
	@echo Creating $(ENGINE_LIB).so ...
	@$(GXX) -o $(ENGINE_LIB).so.$(ENGINE_VERSION) $< $(LIBS_LIB) -shared -Wl,-soname,$(ENGINE_LIB).so.$(ENGINE_VERSION)
	@echo Creating $(ENGINE_LIB).a...
	@$(AR) $(ENGINE_LIB).a.$(ENGINE_VERSION) $(FILE_OBJ)
	@$(LINK) $(ENGINE_LIB).so.$(ENGINE_VERSION) $(ENGINE_LIB).so
	@$(LINK) $(ENGINE_LIB).a.$(ENGINE_VERSION) $(ENGINE_LIB).a
	@$(CHMOD) $(ENGINE_LIB).a.$(ENGINE_VERSION)
	@$(MV) $(ENGINE_LIB).a ./$(DIR_MOUNT)
	@$(MV) $(ENGINE_LIB).a.$(ENGINE_VERSION) ./$(DIR_MOUNT)
	@$(MV) $(ENGINE_LIB).so ./$(DIR_MOUNT)
	@$(MV) $(ENGINE_LIB).so.$(ENGINE_VERSION) ./$(DIR_MOUNT)

$(DIR_BUILD)/%.o: $(DIR_SRC)/%.cpp $(DIR_INC)/%.h
	@echo Building file $@ in folder $(dir $@) ...
	@$(CHKDIR) $(DIR_BUILD) | $(MKDIR) $(DIR_BUILD)
	@$(CHKDIR) $(dir $@) | $(MKDIR) $(dir $@)
	@$(GXX) $(CXXFLAGS) -c $< -o $(@:$(DIR_SRC)/%.o=$(DIR_BUILD)/$(DIR_SRC)/%) $(APP_PATH_INC) $(INCS_LIB) $(LIBS_LIB)

.SECONDARY: build-lib $(ENGINE_LIB)

######## Cleanup

clean:
	@$(RM) $(DIR_MOUNT)/*
	@$(RM) $(DIR_BUILD)/*
	@echo Done.

.PHONY: clean 

######## Install and Unistall

install:
	@echo Installing ...
	@$(CHKDIR) $(PATH_INSTALL_INC) | $(SU) $(MKDIR) $(PATH_INSTALL_INC)
	@$(CHKDIR) $(PATH_INSTALL_LIB) | $(SU) $(MKDIR) $(PATH_INSTALL_LIB)
	@$(CHKDIR) $(PATH_INSTALL_RSC) | $(SU) $(MKDIR) $(PATH_INSTALL_RSC)
	@$(SU) $(RM) $(PATH_INSTALL_INC)/*
	@$(SU) $(RM) $(PATH_INSTALL_LIB)/*
	@$(SU) $(RM) $(PATH_INSTALL_RSC)/*
	@$(SU) $(CP) $(DIR_INC)/* $(PATH_INSTALL_INC)
	@$(SU) $(CP) $(DIR_MOUNT)/$(ENGINE_LIB).a $(PATH_INSTALL_LIB)/$(ENGINE_LIB).a.$(ENGINE_VERSION)
	@$(SU) $(CP) $(DIR_MOUNT)/$(ENGINE_LIB).so $(PATH_INSTALL_LIB)/$(ENGINE_LIB).so.$(ENGINE_VERSION)
	@$(SU) $(CP) $(DIR_RSC)/* $(PATH_INSTALL_RSC)
	@$(SU) $(LINK) $(PATH_INSTALL_LIB)/$(ENGINE_LIB).a.$(ENGINE_VERSION) $(PATH_INSTALL_LIB)/$(ENGINE_LIB).a
	@$(SU) $(LINK) $(PATH_INSTALL_LIB)/$(ENGINE_LIB).so.$(ENGINE_VERSION) $(PATH_INSTALL_LIB)/$(ENGINE_LIB).so
	@$(SU) $(RM) $(PATH_LD)
	@$(SU) /bin/bash -c 'echo $(PATH_INSTALL_LIB) > $(PATH_LD)'
	@$(SU) $(LDCOFIG)
	@echo Done.

uninstall:
	@echo Uninstalling ...
	@$(SU) $(RM) $(PATH_INSTALL_INC)
	@$(SU) $(RM) $(PATH_INSTALL_LIB)
	@$(SU) $(RM) $(PATH_INSTALL_RSC)
	@$(SU) $(RM) $(PATH_LD)
	@echo Done.

.PHONE: install uninstall
