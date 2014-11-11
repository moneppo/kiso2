LIBUV_PATH = libuv/build/Release/
LIBUV_NAME=libuv.a
YAML_CPP_PATH=yaml-cpp
EXE=kiso

GLFW_CFLAGS = $(shell pkg-config --cflags glfw3)
GLFW_LDFLAGS = $(shell pkg-config --static --libs glfw3)

CXX_FLAGS = -std=gnu++0x -g -O0 -I$(LIBUV_PATH)/include -I$(YAML_CPP_PATH)/include -I$(HTTP_PARSER_PATH) -I. -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -I$(YAMP_CPP_PATH)/include -Inanovg/src -Wno-deprecated-declarations $(GLFW_CFLAGS)

OS_NAME=$(shell uname -s)
ifeq (${OS_NAME},Darwin)
	RTLIB=
	JNI = -I/System/Library/Frameworks/JavaVM.framework/Headers
	LDFLAGS = -framework CoreFoundation -framework CoreServices -framework JavaVM -L/usr/local/lib/ $(LIBUV_PATH)/$(LIBUV_NAME) -framework Carbon -framework OpenGL nanovg/build/libnanovg.a $(GLFW_LDFLAGS)
else
	RTLIB=-lrt
	JNI=
	LDFLAGS = -lnanovg -L/usr/local/lib/ -l$(LIBUV_PATH)/$(LIBUV_NAME) -lGL -lGLU nanovg/build/libnanovg.a
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
	$(CXX) $(CXX_FLAGS) $(JNI) -c $< -o $@

