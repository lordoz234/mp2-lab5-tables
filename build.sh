if [ ! -d "build" ]; then
mkdir build
fi
T1=$1
T2="test"
T3="build"
if [ "$T1" = "$T3" ]; then
    cd build
    cmake ..
    make -j 2
elif [ "$T1" = "$T2" ]; then
    ./build/tests/Test_Target
else
    ./build/sample/Laba
fi
cd ..
