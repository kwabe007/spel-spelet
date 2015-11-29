var=area/areas.cpp


new:= $(patsubst %.cpp,%.o, $(notdir $(var)))
out:
	echo $(var)
	echo $(new)
