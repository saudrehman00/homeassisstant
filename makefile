default:
	g++ -std=c++11 -I/usr/local/include WebRequest.cpp -L/usr/local/lib -lcurlpp -lcurl -o test;
