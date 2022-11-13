CXX ?= g++
OBJDIR := $(shell [ -d obj ] || mkdir obj && echo "obj")
CXXFLAGS += -Wall -Wextra -std=c++17
LDFLAGS = 

TARGET = main
OBJ = String.o main.o

.PHONY: all

all: CXXFLAGS += -O3
all: $(TARGET) 

debug: CXXFLAGS += -g -DDEBUG -fsanitize=leak -fsanitize=undefined
debug: LDFLAGS += -fsanitize=address -lubsan -lasan 
debug: $(TARGET)

dev: CXXFLAGS += -g -DDEBUG
dev: $(TARGET)

.SECONDEXPANSION:
$(TARGET): $(patsubst %, $(OBJDIR)/%, $(OBJ))
	$(CXX) $(filter %.o, $^) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/%.d: %.cpp
	$(CXX) -MM $(CXXFLAGS) -o $@ $<

include $(patsubst %.o, $(OBJDIR)/%.d, $(OBJ))

clean:
	rm -rf $(TARGET) $(BUILD_DIR) obj
