#!/bin/sh

# https://stackoverflow.com/questions/61103104/ld-unknown-option-platform-version-when-building-r-packages-from-source

#FLAGS="-O3 -ffast-math -opt-always-inline -optl-loop-unroll -optlo-memdep -optlo-loop-unroll -optlo-scalarizer -optlo-globalopt -optlo-loop-unswitch -optlo-mem2reg -optlo-prune-eh -optlo-O3 -optl-ffast-math -pthread -opt-loop-vectorize -opt-force-vector-width=64"
FLAGS="-ffast-math"

#export LDFLAGS="-L/usr/local/opt/llvm/lib -Wl,-rpath,/usr/local/opt/llvm/lib"
#export CPPFLAGS="-I/Users/snawaz/llvm10/ -"
LDFLAGS="-L/Users/snawaz/llvm10/lib -Wl,-rpath,/Users/snawaz/llvm10/lib"

# $ sysctl -a | grep machdep.cpu.feature
# $ sysctl -a | grep machdep.cpu.featuress

# NOTES:
#   - explore mllvm
#   - explore march, native and all
#   - msse and msse2 : https://stackoverflow.com/questions/45917280/what-is-the-minimum-supported-sse-flag-that-can-be-enabled-on-macos
#       - march=core2 -mtune=haswell
export PATH=/Users/snawaz/llvm10/bin:$PATH
rm -f image.ppm
#echo ${PATH}
#which clang++
#clang++ --version

# clang++ -v -S -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -mfpmath=sse -march=native -O3 $FLAGS -std=c++20 -I /Users/snawaz/llvm10/include/c++/v1 -I src $LDFLAGS -mlinker-version=451.3 src/main.cpp -o cpp-ray

clang++ -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -mfpmath=sse -march=native -O3 $FLAGS -std=c++20 -I /Users/snawaz/llvm10/include/c++/v1 -I src $LDFLAGS -mlinker-version=500.3 main.cpp -o main

#clang++ -v -std=c++17 -I /Users/snawaz/llvm10/include/c++/v1 -I /Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk/usr/include main.cpp -o cpp-ray
#clang++ -v -std=c++17 -I /Users/snawaz/llvm10/include/c++/v1 -isystem /Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk/usr/include -isystem /Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk/System/Library/Frameworks -I /Users/snawaz/llvm10/include/c++/v1 main.cpp -o cpp-ray
