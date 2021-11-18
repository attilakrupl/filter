Build:

gcc main.cpp -o output -ludev ../../lib/x86/libEFWFilter.a -I ../../include/ -ludev -lpthread -Wall

g++ owncontroll.cpp -o output ../../lib/x64/libEFWFilter.a -I ../../include/ -shared -ludev -lpthread -lstdc++ -Wall

