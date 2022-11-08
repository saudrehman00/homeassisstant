CC := g++
FLAGS := -lwthttp -lwt -lsqlite3
TARGET := Assistant

all: $(TARGET)

$(TARGET): Authenticate.o LoginForm.o LoginInfo.o Database.o ListUI.o ListMap.o List.o
	$(CC) -o $(TARGET) Assistant.cpp $^ $(FLAGS)
	make clean

Authenticate.o: auth/Authenticate.h auth/Authenticate.cpp
	$(CC) -c auth/Authenticate.cpp

LoginForm.o: gui/LoginForm.h gui/LoginForm.cpp
	$(CC) -c gui/LoginForm.cpp

LoginInfo.o: data/login/LoginInfo.h data/login/LoginInfo.cpp
	$(CC) -c data/login/LoginInfo.cpp

Database.o: data/db/Database.h data/db/Database.cpp
	$(CC) -c data/db/Database.cpp

ListUI.o: gui/ListUI.h gui/ListUI.cpp
	$(CC) -c gui/ListUI.cpp

ListMap.o: data/list/ListMap.h data/list/ListMap.cpp
	$(CC) -c data/list/ListMap.cpp

List.o: data/list/List.h data/list/List.cpp
	$(CC) -c data/list/List.cpp

Calculator: calculator/Calculator.cpp
	$(CC) Calculator.cpp -o Calculator
    
Profiles: data/user/ProfileCreator.cpp
	$(CC) Profiles.cpp -o Profiles
    
clean:
	-rm *.o $(objects)
