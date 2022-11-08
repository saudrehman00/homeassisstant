CC := g++
FLAGS := -lwthttp -lwt -lsqlite3
TARGET := Assistant

all: $(TARGET)

$(TARGET): $(TARGET).cpp Login.o Authenticate.o LoginForm.o Database.o List.o ListUI.o Calculator Profiles
	$(CC) $^ -o $@ $(FLAGS)
	touch $(TARGET)

Login.o: Authenticate.o LoginForm.o
	$(CC) -c $^ $(FLAGS)
	touch Login.o

LoginForm.o: gui/LoginForm.cpp
	$(CC) -c $^ $(FLAGS)
	touch LoginForm.o

Authenticate.o: auth/Authenticate.cpp
	$(CC) -c $^ $(FLAGS)
	touch Authenticate.o

Database.o: data/db/Database.cpp
	$(CC) -c $^ $(FLAGS)
	touch Database.o

List.o: data/list/List.cpp data/list/ListMap.cpp
	$(CC) -c $^ $(FLAGS)
	touch List.o

ListUI.o: gui/ListUI.cpp
	$(CC) -c $^ $(FLAGS)
	touch ListUI.o

Calculator: calculator/Calculator.cpp
	$(CC) -c $^ 
	touch Calculator

Profiles: data/user/ProfileCreator.cpp
	$(CC) -c $^ 
	touch Profiles

clean:
	-rm *.o $(objects)
