all: test

test: export LD_LIBRARY_PATH=./mem
test: export DYLD_LIBRARY_PATH=./mem
test: libmem.so test.out
	./mem.test/test.out 

libmem.so:
	cd ./mem && $(MAKE)

test.out:
	cd ./mem.test && $(MAKE)
	
clean:
	rm -f libmem.so test.out
	cd ./mem && $(MAKE) clean
	cd ./mem.test && $(MAKE) clean