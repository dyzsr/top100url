#ifndef OUTPUT_H
#define OUTPUT_H

#include <cstdio>

class Output {
	public:
		Output(FILE *f, size_t buf_sz);
		~Output();

		void putdb(const size_t v);
		void putsb(const char *s);
		void putd(const size_t v);
		void puts(const char *s);
		void flush();

	private:
		FILE *fpo;
		char *buf;

		size_t BUF_SZ;
		size_t p;

		void putc(char c);
};

#endif
