CC := g++
FLAGS := -lwthttp -lwt
TARGET := Assistant

all: $(TARGET)

$(TARGET): $(TARGET).cpp Login.o Data.o Components.o
	$(CC) Assistant.cpp $^ -o $@ $(FLAGS)
	touch $(TARGET)

Login.o: Authenticate.o LoginForm.o
	$(CC) -c $^ $(FLAGS)
	touch Login.o

Authenticate.o: auth/Authenticate.h auth/Authenticate.cpp
	$(CC) -c auth/Authenticate.cpp $(FLAGS)
	touch Authenticate.o

LoginForm.o: auth/LoginForm.h auth/LoginForm.cpp
	$(CC) -c auth/LoginForm.cpp $(FLAGS)
	touch LoginForm.o

Data.o: data/LoginInfo.h data/db/Database.h data/LoginInfo.cpp data/db/Database.cpp
	$(CC) -c data/LoginInfo.cpp data/db/Database.cpp -lsqlite3
	touch Data.o

Components.o: components/ChecklistUI.h components/ChecklistUI.cpp
	$(CC) -c components/ChecklistUI.cpp $(FLAGS)
	touch Components.o

clean:
	-rm *.o $(objects)