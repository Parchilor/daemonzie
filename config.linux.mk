CROSS_COMPILER = mipsel-openwrt-linux-

CC = $(CROSS_COMPILER)gcc
CXX = $(CROSS_CONPILER)g++
LD = $(CXX)
AR = $(CROSS_COMPILER)ar
OBJCOPY = $(CROSS_COMPILER)objcopy
LN:=ln -s
INSTALL:= cp -a
INSTALL_BIN:=install -m0755
INSTALL_DIR:=install -d -m0755
INSTALL_DATA:=install -m0665
INSTALL_CONF:=install -m0665

#COMPIE.c=$(CROSS_COMPILER)$(CC) $(CFLAGS) $(CPPFLAGS) -c
#COMPIE.cxx=$(CROSS_COMPILER)$(CXX) $(CFLAGS) $(CPPFLAGS) -c
#LINK.c=$(CROSS_COMPILER)$(CC) $(CFKAGS) $(CPPFLAGS) $(LDFLAGS)
#LINK.cxx=$(CROSS_COMPILER)$(CXX) $(CFKAGS) $(CPPFLAGS) $(LDFLAGS)

CFLAGS	= -Wall -O0 -g
CXXFLAGS	=
LDFLAGS	=
ARFLAGS	=
INCLUDE_DIRS	= $(ROOT)/include
LIBRARY_DIRS	= $(ROOT)/lib
LIBRARY_NAMES	= 
OUTPUTDIR	:= Debug
EXCEPTDIRS := $(OUTPUTDIR) include files Sai

#SUBDIRS := $(shell find . -maxdepth 1 -type d)
SUBDIRS := $(ROOT)/lib $(ROOT)/src
SUBDIRS := $(basename $(patsubst ./%,%,$(SUBDIRS)))
SUBDIRS := $(filter-out $(EXCEPTDIRS),$(SUBDIRS))

CFLAGS	+= $(addprefix -I,$(INCLUDE_DIRS))
LDFLAGS	+= $(addprefix -L,$(LIBRARY_DIRS))
LDFLAGS	+= $(addprefix -l,$(LIBRARY_NAMES))
