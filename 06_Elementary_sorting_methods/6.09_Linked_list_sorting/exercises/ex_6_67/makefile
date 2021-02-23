LIBS     = -lstdc++
MYLIBS = main.o
CXXFLAGS = -Wall -time -O3 -g

.SUFFIXES: .cpp .o

# Create a list of source files.
SOURCES  = $(shell ls *.cpp)
# Create a list of object files from the source file lists.
OBJECTS = ${SOURCES:.cpp=.o}     
# Create a list of targets.
TARGETS = main.exe

# Build all targets by default
all: 	$(TARGETS)

# A rule to build .exe file out of a .o file
main.exe: $(MYLIBS)
	$(CXX) -o $@ $(MYLIBS) $(LIBS)
	@echo ================================================================================
	@echo Done building $@
	@echo ================================================================================
	@echo
	@echo

# A rule to build .o file out of a .cpp file
%.o: %.cpp 
	$(CXX) $(CXXFLAGS) -o $@ -c $<
	@echo ================================================================================
	@echo Done compiling $@
	@echo ================================================================================
	@echo
	@echo

main.o: main.cpp ../../../../List.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<
	@echo ================================================================================
	@echo Done compiling $@
	@echo ================================================================================
	@echo
	@echo

# A rule to clean all the intermediates and targets
clean:	
	rm -rf $(TARGETS) $(OBJECTS) *.out