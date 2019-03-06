all:
	g++ driver.cpp -o driver -O3 -std=c++11 -lpthread -ltins -lboost_regex -lboost_iostreams

debug:
	g++ driver.cpp -o driver -g -std=c++11 -lpthread -ltins -lboost_regex -lboost_iostreams

clean:
	rm ./driver
