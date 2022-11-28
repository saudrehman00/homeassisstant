CC := g++
FLAGS := -lwthttp -lwt -lsqlite3 -L/usr/local/lib -lcurlpp -lcurl -I/usr/local/include
TARGET := Assistant
<<<<<<< HEAD
DATA := Database.o NoteMap.o Note.o Logger.o LogMessage.o LoginInfo.o LocationInfo.o
UTIL := Authenticate.o Calculator.o Request.o Requester.o NewsRequester.o WeatherRequester.o GeoRequester.o Subject.o
GUI := MainUI.o LoginForm.o NoteUI.o ClockUI.o SettingsUI.o ClockPage.o LocationUI.o CalculatorUI.o ConversionUI.o WeatherUI.o NewsUI.o
=======
UTIL := Authenticate.o LoginInfo.o Database.o NoteMap.o Note.o SettingsUI.o Logger.o LogMessage.o Calculator.o AccountUI.o
GUI := Main.o LoginForm.o NoteUI.o ClockUI.o ClockPage.o LocationUI.o CalculatorUI.o ConversionUI.o WeatherUI.o NewsUI.o
>>>>>>> 3839f4cfd142baa111165e41db289871653bedd4

all: $(TARGET)

$(TARGET): $(DATA) $(UTIL) $(GUI)
	$(CC) -o $(TARGET) Assistant.cpp $^ $(FLAGS)
	make clean

MainUI.o: gui/main/MainUI.h gui/main/MainUI.cpp
	$(CC) -c gui/main/MainUI.cpp

Authenticate.o: auth/Authenticate.h auth/Authenticate.cpp
	$(CC) -c auth/Authenticate.cpp

LoginForm.o: gui/login/LoginForm.h gui/login/LoginForm.cpp
	$(CC) -c gui/login/LoginForm.cpp

LoginInfo.o: data/login/LoginInfo.h data/login/LoginInfo.cpp
	$(CC) -c data/login/LoginInfo.cpp

Database.o: data/db/Database.h data/db/Database.cpp
	$(CC) -c data/db/Database.cpp

Logger.o: data/logger/Logger.h data/logger/Logger.cpp
	$(CC) -c data/logger/Logger.cpp

LogMessage.o: data/logger/LogMessage.h data/logger/LogMessage.cpp
	$(CC) -c data/logger/LogMessage.cpp

NoteUI.o: gui/note/NoteUI.h gui/note/NoteUI.cpp
	$(CC) -c gui/note/NoteUI.cpp

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

<<<<<<< HEAD
LocationInfo.o: data/location/LocationInfo.h data/location/LocationInfo.cpp
	$(CC) -c data/location/LocationInfo.cpp

Request.o: web/Request.h web/Request.cpp
	$(CC) -c web/Request.cpp

Requester.o: web/Requester.h web/Requester.cpp
	$(CC) -c web/Requester.cpp

NewsRequester.o: web/NewsRequester.h web/NewsRequester.cpp
	$(CC) -c web/NewsRequester.cpp

WeatherRequester.o: web/WeatherRequester.h web/WeatherRequester.cpp
	$(CC) -c web/WeatherRequester.cpp

GeoRequester.o: web/GeoRequester.h web/GeoRequester.cpp
	$(CC) -c web/GeoRequester.cpp

Subject.o: gui/settings/Subject.h gui/settings/Subject.cpp
	$(CC) -c gui/settings/Subject.cpp
=======
	
AccountUI.o: gui/account/AccountUI.h gui/account/AccountUI.cpp
	$(CC) -c gui/account/AccountUI.cpp
>>>>>>> 3839f4cfd142baa111165e41db289871653bedd4

clean:
	-rm *.o $(objects)
