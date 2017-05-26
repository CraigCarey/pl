CC=g++
LDLIBS=-lboost_system -lpthread
CXX_FLAGS=-std=c++11 -Wall
INC=-I/usr/include/boost

getLeagueBoost:
	$(CC) $(CXX_FLAGS) $(INC) $@.cpp -o $@ $(LDLIBS)

getLeagueHttp:
	$(CC) $(CXX_FLAGS) $@.cpp -o $@

all: getLeagueBoost getLeagueHttp

clean:
	rm -f getLeagueBoost getLeagueHttp a.out

.PHONY: all clean getLeagueBoost