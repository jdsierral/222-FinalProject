EXE = Stimm
NAME = main
TEST_ARGS = 0.1
LOCAL_OBJECTS = AudioProcessor.cpp Convolver.cpp Rotator.cpp SerialReader.cpp /home/pi/Developer/Stimmung/FFT_CODE/complex.cpp /home/pi/Developer/Stimmung/FFT_CODE/fft.cpp /home/pi/Developer/Stimmung/mit-hrtf-lib-master/source/mit_hrtf_lib.cpp
OTHER_CLEANS = *.wav


#OS = MACOSX
#OSLIBS = -framework CoreAudio -framework CoreMidi -framework CoreFoundation

OS = LINUX
OSLIBS = -lasound

RM = /bin/rm
TRASH = /usr/local/bin/trash

# Set the Path for the STK directory
STK_PATH = /home/pi/Developer/STK

LIBSTK_SRC = $(STK_PATH)/src
LIBSTK_INCLUDE = $(STK_PATH)/include
vpath %.h $(LIBSTK_INCLUDE)

# LOCAL_OBJECTS is a list of separately compiled object files IN THE
# CURRENT WORKING DIRECTORY (i.e., not including STK modules, which
# will be found in the STK library):

# OTHER PATHS TO INCLUDE

LIB_FFT = /home/pi/Developer/Stimmung/FFT_CODE
LIB_HRTF = /home/pi/Developer/Stimmung/mit-hrtf-lib-master
LIB_HRTF_INCLUDE = $(LIB_HRTF)/include
LIB_HRTF_SRC = $(LIB_HRTF)/source
LIB_HRTF_NORMAL = $(LIB_HRTF_SRC)/normal
LIB_HRTF_DIFFUSE= $(LIB_HRTF_SRC)/diffuse
LIB_SRC = /home/pi/Developer/Stimmung/src


CC       = g++
DEFS     =  -D_STK_DEBUG_ -D__STK_REALTIME__ -D__OS_$(OS)__
CFLAGS   = -g -Wall -O0 -I$(LIBSTK_INCLUDE) -I$(LIB_FFT) -I$(LIB_HRTF_INCLUDE) -I$(LIB_HRTF_NORMAL) -I$(LIB_HRTF_DIFFUSE) -std=c++11

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
	$(RM) -f $(OTHER_CLEANS)
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

$(NAME): $(NAME).cpp $(LOCAL_OBJECTS) $(LIBSTK) $(LIB_HRTF_SOURCE)
	$(CC) $(CFLAGS) $(DEFS) -o ../Builds/$(EXE) $(NAME).cpp $(LOCAL_OBJECTS) $(LIBRARY)



