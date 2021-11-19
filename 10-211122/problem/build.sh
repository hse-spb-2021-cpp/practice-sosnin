# !/bin/bash

PARENT_PATH=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )

export BOOST_PATH="/home/anton/.conan/data/boost/1.71.0/_/_/package/d72453799bbec5e24612ab5b45f1bbdbb51c3391/"
echo BOOST_PATH=$BOOST_PATH

export LD_LIBRARY_PATH="/home/anton/.conan/data/boost/1.71.0/_/_/package/d72453799bbec5e24612ab5b45f1bbdbb51c3391/lib/"

echo Building 01-boost-header-only.cpp as 01
g++ $PARENT_PATH/01-boost-header-only.cpp -I$BOOST_PATH/include -o 01
./01

echo Building 02-boost-link-filesystem.cpp as 02
g++ $PARENT_PATH/02-boost-link-filesystem.cpp -I$BOOST_PATH/include -L$BOOST_PATH/lib -lboost_filesystem -o 02
./02

echo Building 03-boost-dll
g++ $PARENT_PATH/03-boost-dll/main.cpp -I$BOOST_PATH/include -L$BOOST_PATH/lib -lboost_filesystem -ldl -o 03-main
g++ $PARENT_PATH/03-boost-dll/plugin_a.cpp -fPIC -shared -I$BOOST_PATH/include -o liba.so
g++ $PARENT_PATH/03-boost-dll/plugin_b.cpp -fPIC -shared  -I$BOOST_PATH/include -o libb.so
./03-main liba.so
./03-main libb.so

echo Building 10-add-virtual.cpp as 10
g++ $PARENT_PATH/10-add-virtual.cpp -o 10
./10