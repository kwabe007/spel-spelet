
#Compiler
CC= g++

#Compiler flags
CFLAGS= -c -Wall -std=c++11

#Source files
SOURCES= date.cpp julian.cpp gregorian.cpp westerndate.cpp
TESTSRC= test.cpp kattistime.cpp
DATETESTSRC= datetest.cpp kattistime.cpp

#Object files
OBJSRC:= $(SOURCES:.cpp=.o)
OBJTEST:= $(TESTSRC:.cpp=.o)
OBJDATETEST:= $(DATETESTSRC:.cpp=.o)

compsrc: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES)

ctest: $(TESTSRC)
	$(CC) $(CFLAGS) $(TESTSRC)

cdatetest: $(DATETESTSRC)
	$(CC) $(CFLAGS) $(DATETESTSRC)

clean:
	rm -f $(OBJSRC) $(OBJTEST) $(OBJDATETEST)

linkmytest:
	$(CC) $(OBJSRC) $(OBJTEST) -o malware.exe

linkdatetest:
	$(CC) $(OBJSRC) $(OBJDATETEST) -o adware.png


