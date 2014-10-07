LIBUV_PATH = libuv
LIBUV_NAME=.libs/libuv.a
YAML_CPP_PATH=yaml-cpp
EXE=kiso

CXX_FLAGS = -std=gnu++0x -g -O0 -I$(LIBUV_PATH)/include -I$(YAML_CPP_PATH)/include -I$(HTTP_PARSER_PATH) -I. -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -I$(YAMP_CPP_PATH)/include -I/usr/local/include/cairo -Wno-deprecated-declarations

OS_NAME=$(shell uname -s)
ifeq (${OS_NAME},Darwin)
	RTLIB=
	JNI = -I/System/Library/Frameworks/JavaVM.framework/Headers
	LDFLAGS = -framework CoreFoundation -framework CoreServices -framework JavaVM -L/usr/local/lib/ -lcairo $(LIBUV_PATH)/$(LIBUV_NAME)
else
	RTLIB=-lrt
	JNI=
	LDFLAGS = -lcairo -L/usr/local/lib/ -l$(LIBUV_PATH)/$(LIBUV_NAME)
endif

YAML_CPP_SOURCES=$(shell ls $(YAML_CPP_PATH)/src/*.cpp)
YAML_CPP_OBJECTS = $(YAML_CPP_SOURCES:.cpp=.o)
SOURCES = $(shell ls *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXE)

$(LIBUV_PATH)/$(LIBUV_NAME):
	$(MAKE) -C $(LIBUV_PATH)
	
cleandeps:
	$(MAKE) -C libuv clean
	
clean:
	rm *.o
	rm kiso
	
$(EXE) : $(OBJECTS) $(YAML_CPP_OBJECTS)
	$(CXX) $(LDFLAGS) $(RTLIB) $(OBJECTS) $(YAML_CPP_OBJECTS) -o $(EXE)

%.o : %.cpp
	echo $(YAML_CPP_OBJECTS)
	$(CXX) $(CXX_FLAGS) $(JNI) -c $< -o $@

