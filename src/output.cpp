#include "../include/output.h"

#include <string>
#include <cstring>
#include <cassert>
#include <cctype>

Output::Output(FILE *f, size_t buf_sz):
	fpo(f), BUF_SZ(buf_sz), ptr(0)
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

void Output::putdb(size_t v)
{
	char *p = (char *)(&v);
	for (size_t i = 0; i < sizeof(size_t); i++) {
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

void Output::putd(size_t v)
{
	std::string str;
	while (v > 0) {
		str += (char)('0' + v % 10);
		v /= 10;
	}
	if (str.empty())
		str += '0';
	for (size_t i = str.size(); i > 0; i--) {
		putc(str[i - 1]);
	}
	putc('\n');
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
	buf[ptr] = c;
	ptr++;
	if (ptr >= BUF_SZ) {
		fwrite(buf, sizeof(char), BUF_SZ, fpo);
		ptr = 0;
	}
}

void Output::flush()
{
	if (ptr > 0) {
		fwrite(buf, sizeof(char), ptr, fpo);
		ptr = 0;
	}
}

