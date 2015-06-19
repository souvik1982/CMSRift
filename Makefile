CFLAGS = -Wall -fno-rtti

BASE_PATH = /Users/souvik/CMSRift/OculusSDK_025

INC_PATH = -I $(BASE_PATH)/LibOVR/Include/ -I $(BASE_PATH)/LibOVR/Src
LIB_PATH = -L $(BASE_PATH)/LibOVR/Lib/MacOS/Debug -L $(BASE_PATH)/LibOVR/Lib/MacOS/LibOVR_With_Samples.build/Debug/ovr.build/Objects-normal/x86_64 -L $(BASE_PATH)/LibOVR/Lib/MacOS/LibOVR_With_Samples.build/Debug/ovr.build/Objects-normal/i386 
LINK_LIB = -lovr

all: Oculus

clean:
	rm Oculus *.o

Oculus: Oculus.o
	c++ $(CFLAGS) $(INC_PATH) Oculus.o $(LIB_PATH) $(LINK_LIB) -framework Carbon -framework IOKit -o Oculus

Oculus.o: Oculus.cc
	c++ $(CFLAGS) $(INC_PATH) -c Oculus.cc
