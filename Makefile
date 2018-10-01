CFLAGS+=-Wall -Wextra -Wpedantic
LDFLAGS+=-DFLOAT_TYPE=double

.PHONY: all test clean
all: iir_test

iir_test: iir_test.c iir.c
	cc $(CFLAGS) -o $@ $^ $(LDFLAGS)

test: iir_test
	./iir_test

clean:
	rm -rf *.o *~ iir_test
