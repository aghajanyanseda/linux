LIBRARY = libscheduler.so

APPLICATION = demo-app

CFLAGS = -O3 -Wall -std=c++11
LIBFLAGS = -L. -lscheduler -pthread

LIBRARY_SRC = scheduler.cpp
APP_SRC = main.cpp

LIBRARY_OBJ = scheduler.o
APP_OBJ = main.o

CC = g++

$(LIBRARY): $(LIBRARY_OBJ)
	@ $(CC) -fPIC $(LIBRARY_OBJ) -shared -o $(LIBRARY)

$(APPLICATION): $(APP_OBJ) $(LIBRARY)
	@ $(CC) $(CFLAGS) $(APP_OBJ) $(LIBFLAGS) -Wl,-rpath=./ -o $(APPLICATION)

$(LIBRARY_OBJ): $(LIBRARY_SRC)
	@ $(CC) $(CFLAGS) -fPIC -c $(LIBRARY_SRC) -o $(LIBRARY_OBJ)

$(APP_OBJ): $(APP_SRC)
	@ $(CC) $(CFLAGS) -c $(APP_SRC) -o $(APP_OBJ)

clean:
	@ rm -rf $(APP_OBJ) $(LIBRARY_OBJ) $(APPLICATION)

fclean:
	@ rm -f $(APP_OBJ) $(LIBRARY_OBJ) $(APPLICATION) $(LIBRARY)

re: fclean all

