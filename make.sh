mkdir build
cd build
mkdir googletest
cd googletest
cmake ../../lib/googletest/
make -j 4
cd ..
g++ -g --std=c++17 ../test/option_test.cpp -I../src -I../lib/googletest/googletest/include -I../lib/googletest/googlemock/include -c
g++ option_test.o googletest/googlemock/libgmock.a googletest/googlemock/libgmock_main.a -pthread
./a.out
