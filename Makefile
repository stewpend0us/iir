CFLAGS+=-Wall
LDFLAGS+=-DFLOAT_TYPE=double

.PHONY: all test clean
all: c_iir_test

c_iir_test: c_iir_test.c c_iir.c
	cc $(CFLAGS) -o $@ $^ $(LDFLAGS)

test: c_iir_test
	./c_iir_test

clean:
	rm -rf *.o *~ c_iir_test
