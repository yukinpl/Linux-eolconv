#CXX = clang++
CXX = g++
#CXX_FLAGS = -std=c++17 -lc++fs
CXX_FLAGS = -std=c++17 -lstdc++fs
OBJS = main.o
INC=
BUILDDIR=./build
TARGETDIR=./bin
TARGET=eolconv

all : $(TARGET)

init :
	rm -rf $(BUILDDIR)
	rm -rf $(TARGETDIR)
	mkdir  $(BUILDDIR)
	mkdir  $(TARGETDIR)

$(TARGET) : $(OBJS)
	$(CXX) $(CXX_FLAGS) -o $(TARGETDIR)/$(TARGET) $(BUILDDIR)/$(OBJS)

main.o : main.cpp
	$(CXX) $(CXX_FLAGS) -o $(BUILDDIR)/main.o -c main.cpp

clean :
	rm -rf $(BUILDDIR)/$(OBJS)
	rm -rf $(TARGETDIR)/$(TARGET)

.PHONY : clean
.PSEUDO : all clean
