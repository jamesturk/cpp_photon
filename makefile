#This file is part of Photon (http://photon.sourceforge.net)
#Copyright (C) 2004-2005 James Turk
#
# Author:
#  James Turk (jpt2433@rit.edu)
#
# Version:
#  $Id: makefile,v 1.3 2005/02/27 05:52:22 cozman Exp $

INCLUDE_DIR = ./include
SRC_DIR = ./src
LIB_DIR = ./lib

SUBDIRS =  util util/filesys audio
INCLUDE_DIRS = $(INCLUDE_DIR) $(foreach dir,$(SUBDIRS),$(INCLUDE_DIR)/$(dir))
SRC_DIRS = $(SRC_DIR) $(foreach dir,$(SUBDIRS),$(SRC_DIR)/$(dir))

SRCS = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
INCLUDES = $(foreach dir,$(INCLUDE_DIRS),$(wildcard $(dir)/*.hpp))
OBJS = $(SRCS:.cpp=.o)

LIBS = -lphysfs -lglfw -lOpenGL32 -lOpenAL

LIBNAME = photon
LIBFILE = $(LIB_DIR)/lib$(LIBNAME).a

CXX = g++
CPPFLAGS_INCS = $(foreach dir,$(INCLUDE_DIRS),-I$(dir)) 
CPPFLAGS = -Wall $(CPPFLAGS_INCS) 

.PHONY: all clean

all: $(LIBFILE)

clean: 
	rm -f $(OBJS) $(LIBFILE)

$(LIBFILE): $(OBJS)
	@echo Building $(LIBFILE)...
	ar r $(LIBFILE) $(OBJS)
	ranlib $(LIBFILE)
