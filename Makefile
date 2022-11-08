CC := g++
FLAGS := -lwthttp -lwt -lsqlite3
TARGET := Assistant

all: $(TARGET)

$(TARGET): $(TARGET).o Login.o
	$(CC) -o $@ $^ -lwthttp -lwt

clean:
	-rm *.o $(objects)
