compile:
	g++ -std=c++17 -o api_server src/main.cpp -I Crow/include -lboost_system -lboost_thread -lpthread
