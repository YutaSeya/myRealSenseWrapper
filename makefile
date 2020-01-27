COMPILER  = g++
CFLAGS    = -g -MMD -MP -Wall -Wextra -Winit-self -Wno-missing-field-initializers -std=c++11 $(shell pkg-config --cflags opencv)

LDFLAGS = -pthread $(shell pkg-config --libs --static opencv) -lrealsense2 

LIBS      =
INCLUDE   = -I./Inc/ \
						-I./

TARGET    = ./build/$(shell basename `readlink -f .`)

SOURCES   = main.cpp \
						realSensseWrapper.cpp
#$(wildcard Src/peripheral/*.cpp) 


OBJDIR    = ./build
OBJECTS = $(addprefix $(OBJDIR)/,$(notdir $(SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(SOURCES)))
DEPENDS   = $(OBJECTS:.o=.d)

$(TARGET): $(OBJECTS) $(LIBS)
	$(COMPILER) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o:%.cpp
	-mkdir -p $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: clean $(TARGET)

run:
	$(TARGET)

clean:
	-rm -rf $(OBJDIR)

-include $(DEPENDS)