#ifndef OUTPUT_H
#define OUTPUT_H

#include <cstdio>

class Output {
	public:
		Output(FILE *f, const char *mode, size_t _buf_sz);
		Output(const char *filename, const char *mode, size_t _buf_sz);
		~Output();

		void putdb(size_t v);
		void putsb(const char *s);
		void putd(size_t v);
		void puts(const char *s);
		void flush();

	private:
		FILE *fpo;
		char *buf;

		size_t buf_sz;
		size_t ptr;

		void putc(char c);
};

#endif
