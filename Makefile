all: libmem.so test.out

libmem.so:
	cd ./mem && $(MAKE) && cp libmem.so ..

test.out:
	cd ./mem.test && $(MAKE) && cp test.out ..
	
clean:
	rm -f libmem.so test.out
	cd ./mem && $(MAKE) clean
	cd ./mem.test && $(MAKE) clean