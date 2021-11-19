# !/bin/bash

PARENT_PATH=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )

export BOOST_PATH="/home/anton/.conan/data/boost/1.71.0/_/_/package/d72453799bbec5e24612ab5b45f1bbdbb51c3391/"
echo BOOST_PATH=$BOOST_PATH

echo Building 01-boost-header-only.cpp as 01
g++ $PARENT_PATH/01-boost-header-only.cpp -I$BOOST_PATH/include -o 01

echo Building 02-boost-link-filesystem.cpp as 02
g++ $PARENT_PATH/02-boost-link-filesystem.cpp -I$BOOST_PATH/include -L$BOOST_PATH/lib -lboost_filesystem -o 02