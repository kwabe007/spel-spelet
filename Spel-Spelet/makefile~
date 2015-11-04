#Compiler
CC= g++

#Compiler flags
CFLAGS= -c -Wall -std=c++11 
CTESTFLAGS= -Wall -std=c++11

#Header files
HEADERS= conf.hpp intro.hpp parse.hpp debugmacro.hpp ui.hpp
TESTHDR= menu.hpp

#Source files
SOURCES= source.cpp intro.cpp parse.cpp ui.cpp
TESTSRC= test.cpp menu.cpp

#Object files
OBJECTS= $(SOURCES:.cpp=.o)

#Name of executable
EXECUTABLE= run
TESTEXE= virus.dll

#Execution command
EXE= ./

#Dependencies for creating objects
$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

#Create only the object files
objects: $(OBJECTS)

#Create an executable
all: $(EXECUTABLE) 

#Remove objectfiles and the executable
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

#TEST FILE DEPENDENCIES
comptest: $(TESTSRC)
	$(CC) $(CTESTFLAGS) $(TESTSRC) -o $(TESTEXE)

alltest: cleantest comptest $(TESTEXE)

runtest: alltest
	$(EXE)$(TESTEXE)
	
cleantest:
	rm -f $(TESTEXE)
