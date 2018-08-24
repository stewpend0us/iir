CFLAGS+=-Wall
LDFLAGS+=-DFLOAT_TYPE=float

.PHONY: all
all: c_iir_test

c_iir_test: c_iir.c c_iir_test.c
	cc $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: test
test: c_iir_test
	./c_iir_test

.PHONY: clean
clean:
	rm -rf c_iir_test
