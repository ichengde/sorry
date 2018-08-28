#/bin/sh
cd cmake-build-debug
make
./server &
./server_test
