CFLAGS= -g -pedantic -std=c++11

autocomplete-map-my-unordered-map: autocomplete-map-my-unordered-map.cpp List-ED.h unordered_map-ED.h
	clang++ $(CFLAGS) autocomplete-map-my-unordered-map.cpp -o autocomplete-map-my-unordered-map

clean:
	rm autocomplete-map-my-unordered-map	
