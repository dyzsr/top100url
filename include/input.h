#ifndef INPUT_H
#define INPUT_H

#include <cstdio>

class Input {
	public:
		Input(FILE *f, const char *mode, size_t _buf_sz);
		Input(const char *filename, const char *flags, size_t _buf_sz);
		~Input();

		size_t getdb(size_t *dest);
		size_t getd(size_t *dest);
		size_t getsb(char *dest, size_t n);
		size_t gets(char *dest, size_t n);

	private:
		FILE *fpi;
		char *buf;

		size_t buf_sz;
		size_t sz;
		size_t ptr;

		int getc();
};

#endif
