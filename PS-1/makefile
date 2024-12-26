EXEC = do-execute
CFLAGS = -Wall -Wextra -Werror
SOURCE = main.cpp
OBJECT = main.o
COMPILER = g++

all: $(EXEC)

$(EXEC) : $(OBJECT)
	@ $(COMPILER) $(CFLAGS) $(OBJECT) -o $(EXEC)

$(OBJECT) : $(SOURCE)
	@ $(COMPILER) $(CFLAGS) -c $(SOURCE) -o $(OBJECT)

clean:
	@ rm -rf $(OBJECT) $(EXEC)

fclean:
	@ rm -f $(OBJECT)

