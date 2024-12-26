PROGRAM1 = first_program
PROGRAM2 = second_program
CFLAGS = -O3
SOURCE1 = first.cpp
SOURCE2 = second.cpp
OBJECT1 = first.o
OBJECT2 = second.o
COMPILER = g++

all: $(PROGRAM1) $(PROGRAM2)

$(PROGRAM1): $(OBJECT1)
	@$(COMPILER) $(CFLAGS) $(OBJECT1) -o $(PROGRAM1)

$(PROGRAM2): $(OBJECT2)
	@$(COMPILER) $(CFLAGS) $(OBJECT2) -o $(PROGRAM2)

$(OBJECT1): $(SOURCE1)
	@$(COMPILER) $(CFLAGS) -c $(SOURCE1) -o $(OBJECT1)

$(OBJECT2): $(SOURCE2)
	@$(COMPILER) $(CFLAGS) -c $(SOURCE2) -o $(OBJECT2)

clean:
	@rm -rf $(OBJECT1) $(OBJECT2) $(PROGRAM1) $(PROGRAM2)

fclean:
	@rm -f $(OBJECT1) $(OBJECT2)

re: fclean all

