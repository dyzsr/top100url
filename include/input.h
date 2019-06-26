#ifndef INPUT_H
#define INPUT_H

#include <cstdio>

class Input {
	public:
		Input(FILE *f, size_t buf_sz);
		~Input();

		size_t getsb(char *dest, size_t n);
		size_t gets(char *dest, size_t n);

	private:
		FILE *fpi;
		char *buf;

		size_t BUF_SZ;
		size_t sz;
		size_t p;

		char getc();
};

#endif
