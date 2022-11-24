CC := g++
FLAGS := -lwthttp -lwt -lsqlite3
TARGET := Assistant

all: $(TARGET)

$(TARGET): Authenticate.o LoginForm.o LoginInfo.o Database.o ListUI.o ListMap.o List.o ClockUI.o ClockPage.o SettingsUI.o LocationUI.o Main.o CalculatorUI.o
	$(CC) -o $(TARGET) Assistant.cpp $^ $(FLAGS)
	make clean

Main.o: gui/Main.h gui/Main.cpp
	$(CC) -c gui/Main.cpp

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

ClockUI.o: gui/clock/ClockUI.h gui/clock/ClockUI.cpp
	$(CC) -c gui/clock/ClockUI.cpp

ClockPage.o:  gui/clock/ClockPage.h gui/clock/ClockPage.cpp
	$(CC) -c gui/clock/ClockPage.cpp

SettingsUI.o: gui/settings/SettingsUI.h gui/settings/SettingsUI.cpp
	$(CC) -c gui/settings/SettingsUI.cpp

LocationUI.o: gui/settings/LocationUI.h gui/settings/LocationUI.cpp
	$(CC) -c gui/settings/LocationUI.cpp

CalculatorUI.o: gui/CalculatorUI.h gui/CalculatorUI.cpp
	$(CC) -c gui/CalculatorUI.cpp

clean:
	-rm *.o $(objects)
