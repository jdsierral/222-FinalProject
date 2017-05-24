EXE = Stimm
NAME = main
TEST_ARGS = 0.1
LOCAL_OBJECTS = 
OTHER_CLEANS = *.wav

# <STK>/myproj/Makefile-proj - Makefile shared by subdirectories.

# Choose one of the following two systems:

#OS = MACOSX
#OSLIBS = -framework CoreAudio -framework CoreMidi -framework CoreFoundation

OS = LINUX
OSLIBS = -lasound

# This is a simple manually written Makefile, tested on Linux and Mac
# OS X.  For a more elaborate automatically generated (by autotools)
# example, see <STK>/projects/examples/Makefile

# USAGE: In a subdirectory, such as ./delay, for example, have a
# Makefile that looks something like the following (without the '#'
# comment characters, of course):
#
# NAME = delay
# TEST_ARGS = gtr.wav
# LOCAL_OBJECTS = delayline.o
# OTHER_CLEANS = delay.wav
# include ../Makefile-proj
#
# See ./delay/Makefile for more explanation of these definitions.

# --- BEGIN SHARED MAKEFILE ---

RM = /bin/rm
TRASH = /usr/local/bin/trash

# The following STK path works when the current directory is parallel
# to, say, projects/examples
STK_PATH = /home/pi/Documents/Dev/STK

LIBSTK_SRC = $(STK_PATH)/src
LIBSTK_INCLUDE = $(STK_PATH)/include
vpath %.h $(LIBSTK_INCLUDE)

# LOCAL_OBJECTS is a list of separately compiled object files IN THE
# CURRENT WORKING DIRECTORY (i.e., not including STK modules, which
# will be found in the STK library):

CC       = g++
DEFS     =  -D_STK_DEBUG_ -D__STK_REALTIME__ -D__OS_$(OS)__
CFLAGS   = -g -Wall -O0 -I$(LIBSTK_INCLUDE) -std=c++11

# Here is the STK library itself (made fresh if necessary):
LIBSTK = $(LIBSTK_SRC)/libstk.a

# For listening to program test output, we use the STK's play.cpp example:
STK_EXAMPLES = $(STK_PATH)/projects/examples
STKPLAY = $(STK_EXAMPLES)/play

# The first make target is the default target:
all : $(NAME)

$(STKPLAY): $(STK_EXAMPLES)/play.cpp
	(cd $(STK_EXAMPLES); make play)

# Standard program test
t test : $(NAME) $(STKPLAY)
	./$(NAME) $(TEST_ARGS)
	$(STKPLAY) $(NAME).wav 44100

%.o : %.c
	$(CC) $(CFLAGS) $(DEFS) -c $(<) -o $@

clean :
	$(RM) -f $(NAME) $(LOCAL_OBJECTS) $(OTHER_CLEANS)
	$(RM) -fR *~ *.dSYM
	$(RM) -fR ../Builds/*
	$(TRASH) ../Bounces/*

strip :
	strip $(NAME)

LIBSTK = $(LIBSTK_SRC)/libstk.a

LIBRARY = -L$(LIBSTK_SRC) -lpthread -lstk $(OSLIBS)

$(LIBSTK): $(LIBSTK_SRC)/*.cpp $(LIBSTK_INCLUDE)/*.h
	(cd $(LIBSTK_SRC); make)

%.o: %.cpp %.c
	$(CC) $(CFLAGS) $(DEFS) -c $(<) -o $@

$(NAME): $(NAME).cpp $(LOCAL_OBJECTS) $(LIBSTK)
	$(CC) $(CFLAGS) $(DEFS) -o ../Builds/$(EXE) $(NAME).cpp $(LOCAL_OBJECTS) $(LIBRARY)



