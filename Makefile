
UNAME := $(shell uname)
ifeq ($(UNAME_S),Darwin)
	LLVM = llvm
else
	LLVM = xcrun llvm
endif

all: release

release: ./mem/libmem.so out

test: args += debug
test: export LLVM_PROFILE_FILE=./mem.test/mem.profraw
test: export LD_LIBRARY_PATH=./mem
test: export DYLD_LIBRARY_PATH=./mem
test: ./mem/libmem.so ./mem.test/test.out
	./mem.test/test.out 
	$(LLVM)-profdata merge -sparse ./mem.test/mem.profraw -o ./mem.test/mem.profdata
	$(LLVM)-cov report ./mem/libmem.so -instr-profile=./mem.test/mem.profdata
	
out:
	mkdir -p out
	cp ./mem/libmem.so ./out
	cp ./mem/header/mem.h ./out

./mem/libmem.so:
	cd ./mem && $(MAKE) $(args)

./mem.test/test.out:
	cd ./mem.test && $(MAKE) $(args)

	
clean:
	rm -fr libmem.so test.out libmem.so mem.h out
	cd ./mem && $(MAKE) clean
	cd ./mem.test && $(MAKE) clean
