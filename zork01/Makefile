CC = g++
OBJ = main.o Item.o Trigger.o Creature.o Room.o Container.o 

%.o:%.c 
	$(CC) $< -o $@

all: zork

zork: $(OBJ)
	$(CC) -o zork $^

clean:
	rm *.o zork
