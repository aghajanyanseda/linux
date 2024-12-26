TARGET = interactive-shell
CFLAGS = -Wall -Wextra -Werror
SOURCE = main.cpp
OBJECT = main.o
COMPILER = g++

all: $(TARGET)

$(TARGET) : $(OBJECT)
	@ $(COMPILER) $(CFLAGS) $(OBJECT) -o $(TARGET)

$(OBJECT) : $(SOURCE)
	@ $(COMPILER) $(CFLAGS) -c $(SOURCE) -o $(OBJECT)

clean:
	@ rm -rf $(OBJECT) $(TARGET)

fclean:
	@ rm -f $(OBJECT)

