g++ -g --std=c++17 -c -o build/option_test.o test/option_test.cpp -Isrc -Ilib/googletest/googletest/include -Ilib/googletest/googlemock/include

if [ $? -ne 0 ]; then
    exit $?
else
    g++ -o build/a.out build/option_test.o build/googletest/googlemock/libgmock.a build/googletest/googlemock/libgmock_main.a -pthread
fi

if [ $? -ne 0 ]; then
    exit $? 
else
    build/a.out
fi

