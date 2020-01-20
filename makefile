.PHONY: big 

SRC := big_int.cpp \
      main.cpp 

big : $(SRC) 
	g++ -g --coverage $(SRC) -o $@
	./big
	@gcov $(SRC) -m

clean:
	rm -f *.o bin

