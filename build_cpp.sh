mkdir build
cd build
cmake ../ -DCMAKE_INSTALL_PREFIX=../install/

make
make install

../install/bin/replacer
