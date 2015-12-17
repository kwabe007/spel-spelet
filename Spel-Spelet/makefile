
#Compiler
CC:= g++

#Compiler flags
CFLAGS:= -Wall -std=c++11 -g -rdynamic

#Source files
AREAS:= areas/area.cpp areas/indoor.cpp areas/building.cpp areas/world.cpp
MENUS:= menus/menu.cpp
ENTITIES:= entities/entity.cpp entities/organic.cpp entities/human.cpp
FUNCTIONS:= funcobj/funcobj.cpp
UNSORTED:= parse.cpp ui.cpp matrix.cpp canvas.cpp scene.cpp battle.cpp conf.cpp
ITEMS:= items/item.cpp items/weapon.cpp items/consumable.cpp items/armor.cpp
TEXTS:= texts/text.cpp
TEST:= test.cpp
SOURCE:= $(AREAS) $(MENUS) $(ENTITIES) $(FUNCTIONS) $(UNSORTED) $(ITEMS) $(TEXTS) $(TEST)

#Object files
AREAOBJ= $(AREAS:.cpp=.o)
MENUOBJ= $(MENUS:.cpp=.o)
ENTOBJ=  $(ENTITIES:.cpp=.o)
FUNCOBJ=  $(FUNCTIONS:.cpp=.o)
UNSOBJ= $(UNSORTED:.cpp=.o)
ITEMOBJ= $(ITEMS:.cpp=.o)
TEXTOBJ= &(TEXTS:.cpp=.o)
TESTOBJ= $(TESTSRC:.cpp=.o) 
OBJECTS := $(patsubst %.cpp,%.o, $(notdir $(SOURCE)))

#Name of executable
EXECUTABLE= virus.dll

%.o : %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

#Create object files for areas
area: 
	$(CC) -c $(CFLAGS) $(AREAS)

#Create object files for menus
menu: $(MENUS)
	$(CC) -c $(CFLAGS) $(MENUS)

#Create object files for entities
enti: $(ENTITIES)
	$(CC) -c $(CFLAGS) $(ENTITIES)

#Create object files for funcobj
func: $(FUNCTIONS)
	$(CC) -c $(CFLAGS) $(FUNCTIONS)

#Create object files for misc
unso: $(UNSORTED)
	$(CC) -c $(CFLAGS) $(UNSORTED)

#Create object files for items
item: 
	$(CC) -c $(CFLAGS) $(ITEMS)

#Create object files for texts
text: 
	$(CC) -c $(CFLAGS) $(TEXTS)

#Create object files for test
test: $(TEST)
	$(CC) -c $(CFLAGS) $(TEST)

link:	
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

#Compile and link all
all: comp link
	
comp: $(SOURCE)
	$(CC) -c $(CFLAGS) $(SOURCE)

#Remove objectfiles and the executable
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
