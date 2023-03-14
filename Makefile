all: test

test: export LD_LIBRARY_PATH=./mem
test: export DYLD_LIBRARY_PATH=./mem
test: ./mem/libmem.so ./mem.test/test.out
	./mem.test/test.out 

./mem/libmem.so:
	cd ./mem && $(MAKE)

./mem.test/test.out:
	cd ./mem.test && $(MAKE)
	
clean:
	rm -f libmem.so test.out
	cd ./mem && $(MAKE) clean
	cd ./mem.test && $(MAKE) clean