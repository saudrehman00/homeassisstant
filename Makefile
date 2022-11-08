CC := g++
FLAGS := -lwthttp -lwt -lsqlite3
TARGET := Assistant

all: $(TARGET)

$(TARGET): $(TARGET).o Login.o
	$(CC) -o $@ $^ -lwthttp -lwt
	touch $(TARGET)

$(TARGET).o: Assistant.cpp
	$(CC) -o $^

Login.o: Authenticate.o LoginForm.o
	$(CC) -c $^
	touch Login.o

Authenticate.o: auth/Authenticate.cpp
	$(CC) -c $^ $(FLAGS)
	touch Authenticate.o

LoginForm.o: gui/LoginForm.cpp
	$(CC) -c $^ $(FLAGS)
	touch LoginForm.o

clean:
	-rm *.o $(objects)