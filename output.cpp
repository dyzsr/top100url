#include "output.h"

#include <cstring>
#include <cassert>
#include <cctype>

Output::Output(FILE *f, size_t buf_sz):
	fpo(f), BUF_SZ(buf_sz), p(0)
{
	assert(BUF_SZ > 0);
	assert(fpo != NULL);

	buf = new char[BUF_SZ];
	assert(buf != NULL);
}

Output::~Output()
{
	delete[] buf;
}

void Output::putdb(const size_t v)
{
	char *p = (char *)(&v);
	for (int i = 0; i < sizeof(size_t); i++) {
		putc(p[i]);
	}
}

void Output::putsb(const char *s)
{
	for (size_t i = 0; s[i]; i++) {
		putc(s[i]);
	}
	putc(0);
}

void Output::putd(const size_t v)
{
}

void Output::puts(const char *s)
{
	for (size_t i = 0; s[i]; i++) {
		putc(s[i]);
	}
	putc('\n');
}

inline void Output::putc(char c)
{
	buf[p] = c;
	p++;
	if (p >= BUF_SZ) {
		fwrite(buf, sizeof(char), BUF_SZ, fpo);
		p = 0;
	}
}

void Output::flush()
{
	if (p > 0) {
		fwrite(buf, sizeof(char), p, fpo);
		p = 0;
	}
}

