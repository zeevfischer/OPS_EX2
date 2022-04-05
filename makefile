cc=gcc
AR=ar
OBJECTS_MAIN=main.o
FLAGS= -Wall -g 

all: main
# main
main: $(OBJECTS_MAIN)
	$(cc) $(FLAGS) -o main $(OBJECTS_MAIN)

$(OBJECTS_MAIN): main.c
	$(cc) $(FLAGS) -c main.c

.PHONY: clean all
clean:
	rm -f *.o  *.a *.so main