
#Compiler
CC= g++

#Compiler flags
CFLAGS= -c -Wall -std=c++11 
CTESTFLAGS= -Wall -std=c++11 -g -rdynamic

#Header files
HEADERS= conf.hpp intro.hpp parse.hpp debugmacro.hpp ui.hpp
TESTHDR= menu.hpp

#Source files
SOURCES= source.cpp intro.cpp menu.cpp parse.cpp ui.cpp matrix.cpp canvas.cpp scene.cpp
TESTSRC= test.cpp menus/menu.cpp parse.cpp ui.cpp matrix.cpp canvas.cpp scene.cpp areas/area.cpp areas/indoor.cpp areas/building.cpp entities/entity.cpp entities/organic.cpp entities/human.cpp battle.cpp conf.cpp funcobj/funcobj.cpp
DEBUGSRC= err.cpp

#Object files
OBJECTS= $(SOURCES:.cpp=.o)

#Name of executable
EXECUTABLE= run
TESTEXE= virus.dll

#Execution command
EXE= ./

#FIFO file
FIFOPATH= /tmp/fifo

#cerr dump file
CERRDUMP= cerrdump.txt

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
	$(EXE)$(TESTEXE) 2> $(CERRDUMP)

runtest_d: alltest
	$(EXE)$(TESTEXE) 2> $(FIFOPATH)
	
cleantest:
	rm -f $(TESTEXE)

#DEBUG
compdebug: $(DEBUGSRC)
	$(CC) $(DEBUGSRC) -o debug
crfile:
	mkfifo $(FIFOPATH)
rundebug: debug
	./debug < $(FIFOPATH)
