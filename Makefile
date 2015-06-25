CFLAGS = -Wall

ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS  = $(shell root-config --libs)
EVELIBS  = $(shell root-config --evelibs)

BASE_PATH = /Users/souvik/CMSRift/OculusSDK_025

INC_PATH = -I $(BASE_PATH)/LibOVR/Include/ -I $(BASE_PATH)/LibOVR/Src
LIB_PATH = -L /Users/souvik/OculusSDK/LibOVR/Lib/MacOS/Debug  
LINK_LIB = -lovr

all:	Oculus

clean:
	rm -rf *.o

Oculus: Oculus.o
	c++ Oculus.o -o Oculus $(LIB_PATH) $(LINK_LIB) -framework Carbon -framework IOKit $(ROOTFLAGS) $(ROOTLIBS) $(EVELIBS)

Oculus.o: Oculus.cc
	c++ $(CFLAGS) -c Oculus.cc $(INC_PATH) $(ROOTFLAGS)

# $(CFLAGS) $(INC_PATH)
# $(CFLAGS) $(INC_PATH)  $(LIB_PATH) $(LINK_LIB) -framework Carbon -framework IOKit 
