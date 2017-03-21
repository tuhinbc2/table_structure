ALL = table.out

all: $(ALL)

CPP_PATH := ../table_pixel

C++ := g++

CPPFLAGS := -std=c++11 -Wall -Wextra

#LDLIBS := \
#	-lgtest \
#	-lpthread \


#INCLUDE := \
#	-I./$(CPP_PATH)

SRCS := $(shell find $(CPP_PATH) -name '*.cpp')

OBJS := $(SRCS:%.cpp=%.o)

.cpp.o:
	$(C++) $(CPPFLAGS) -o $@ -c -MP -MMD $<

table.out: $(OBJS)
	$(C++) $(CPPFLAGS) $(OBJS) -o table.out $(LIBS)

clean:
	$(RM) $(OBJS:%.o=%.d)
	$(RM) $(OBJS)
	$(RM) $(ALL)

-include $(OBJS:%.o=%.d)