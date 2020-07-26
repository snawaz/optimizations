
#CDIR=/Users/snawaz/llvm
#CC=$(CDIR)/bin/clang
#CC=clang

#FLAGS=-O3 -ffast-math -opt-always-inline -optl-loop-unroll
#FLAGS+=-optlo-memdep -optlo-loop-unroll -optlo-scalarizer -optlo-globalopt -optlo-loop-unswitch -optlo-mem2reg -optlo-prune-eh -optlo-O3 -optl-ffast-math
#FLAGS+=-pthread
#FLAGS+=-opt-loop-vectorize -opt-force-vector-width=8

#FLAGS+=-ftime-trace
#FLAGS+=-S
#FLAGS+=–flto
#FLAGS+=-fprofile-instr-generate  -fcoverage-mapping
#FLAGS+=-fprofile-instr-use=code.profdata

#set -gx LDFLAGS "-L/usr/local/opt/llvm/lib -Wl,-rpath,/usr/local/opt/llvm/lib"
#set -gx CPPFLAGS "-I/usr/local/opt/llvm/include"
# set -gx LDFLAGS "-L/usr/local/opt/llvm/lib"
#set -gx fish_user_paths "/usr/local/opt/llvm/bin" $fish_user_paths

	# PATH=$(CDIR)/bin:${PATH} $(CC) $(FLAGS) $(INCLUDES) -std=c++17 main.cpp -o cpp-ray
	#clang++ $(FLAGS) $(INCLUDES) -std=c++17 test.cpp -o test.s

SHOBJ_LDFLAGS ?= -mmacosx-version-min=10.14 -bundle -undefined dynamic_lookup -ldl -lpthread

compile:
	sh compile.sh
all:
	rm -f image.ppm
	#which clang++
	clang++ --version
	#clang++ -v $(FLAGS) $(NIX_CFLAGS_COMPILE) $(NIX_LDFLAGS) $(SHOBJ_LDFLAGS) -std=c++17 main.cpp -o cpp-ray
	clang++ -v $(FLAGS) -std=c++17 main.cpp -o cpp-ray
