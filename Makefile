option-test: build/option_test.o
	g++ -o build/a.out build/option_test.o build/googletest/googlemock/libgmock.a build/googletest/googlemock/libgmock_main.a -pthread
#googletest: lib/googletest/
#  cd build/googletest; cmake ../../lib/googletest; make -j 4; cd ../..
option_test.o: test/option_test.cpp src/option.hpp
	g++ -g --std=c++17 -c -o build/option_test.o test/option_test.cpp -Isrc -Ilib/googletest/googletest/include -Ilib/googletest/googlemock/include
