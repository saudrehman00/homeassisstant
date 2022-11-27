CC := g++
FLAGS := -lwthttp -lwt -lsqlite3 
TARGET := Assistant
<<<<<<< HEAD
OBJ := Authenticate.o LoginForm.o LoginInfo.o Database.o Main.o NoteUI.o NoteMap.o Note.o ClockUI.o ClockPage.o SettingsUI.o LocationUI.o CalculatorUI.o ConversionUI.o WeatherUI.o Calculator.o
=======
UTIL := Authenticate.o LoginInfo.o Database.o NoteMap.o Note.o SettingsUI.o Calculator.o
GUI := Main.o LoginForm.o NoteUI.o ClockUI.o ClockPage.o LocationUI.o CalculatorUI.o ConversionUI.o WeatherUI.o NewsUI.o
>>>>>>> 063cc932ffdf0cfaf846adea938f22f7273e419b

all: $(TARGET)

$(TARGET): $(UTIL) $(GUI)
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

NoteUI.o: gui/NoteUI.h gui/NoteUI.cpp
	$(CC) -c gui/NoteUI.cpp

NoteMap.o: data/note/NoteMap.h data/note/NoteMap.cpp
	$(CC) -c data/note/NoteMap.cpp

Note.o: data/note/Note.h data/note/Note.cpp
	$(CC) -c data/note/Note.cpp

ClockUI.o: gui/clock/ClockUI.h gui/clock/ClockUI.cpp
	$(CC) -c gui/clock/ClockUI.cpp

ClockPage.o:  gui/clock/ClockPage.h gui/clock/ClockPage.cpp
	$(CC) -c gui/clock/ClockPage.cpp

SettingsUI.o: gui/settings/SettingsUI.h gui/settings/SettingsUI.cpp
	$(CC) -c gui/settings/SettingsUI.cpp

LocationUI.o: gui/settings/LocationUI.h gui/settings/LocationUI.cpp
	$(CC) -c gui/settings/LocationUI.cpp

CalculatorUI.o: gui/math/CalculatorUI.h gui/math/CalculatorUI.cpp
	$(CC) -c gui/math/CalculatorUI.cpp

ConversionUI.o: gui/math/ConversionUI.h gui/math/ConversionUI.cpp
	$(CC) -c gui/math/ConversionUI.cpp

Calculator.o: calculator/Calculator.h calculator/Calculator.cpp
	$(CC) -c calculator/Calculator.cpp

WeatherUI.o: gui/feed/WeatherUI.h gui/feed/WeatherUI.cpp
	$(CC) -c gui/feed/WeatherUI.cpp

NewsUI.o: gui/feed/NewsUI.h gui/feed/NewsUI.cpp
	$(CC) -c gui/feed/NewsUI.cpp

clean:
	-rm *.o $(objects)
