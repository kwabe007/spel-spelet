
#Compiler
CC= g++

#Compiler flags
CFLAGS= -c -Wall -std=c++11

#Source files
SOURCES= date.cpp julian.cpp gregorian.cpp westerndate.cpp
TESTSRC= test.cpp kattistime.cpp

#Object files
OBJSRC= $(SOURCES:.cpp=.o)
OBJTEST= $(TESTSRC:.cpp=.o)

compsrc: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES)

ctest: $(TESTSRC)
	$(CC) $(CFLAGS) $(TESTSRC)

clean:
	rm -f $(OBJSRC) $(OBJTEST) malware.exe

linkmytest:
	$(CC) $(OBJSRC) $(OBJTEST) -o malware.exe

all: compsrc ctest linkmytest


