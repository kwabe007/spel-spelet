CC=g++
Flags=-Wall -std=c++11
Sources=test.cpp
Exe=virus.exe

comp: $(Sources)
	$(CC) $(Flags) $(Sources) -o $(Exe)

run: $(Exe)
	./$(Exe)

clean:
	rm -f $(Exe)

