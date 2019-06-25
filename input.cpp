#include "input.h"

#include <cstring>
#include <cassert>
#include <cctype>

Input::Input(FILE *f, size_t buf_sz):
	fpi(f), BUF_SZ(buf_sz), sz(0), p(0)
{
	assert(fpi != NULL);
	assert(BUF_SZ > 0);

	buf = new char[BUF_SZ];
	assert(buf != NULL);
	memset(buf, -1, BUF_SZ * sizeof(char));
}

Input::~Input()
{
	delete[] buf;
}

size_t Input::getsb(char *dest, size_t n)
{
	char c = getc();
	size_t cnt = 0;
	while (cnt < n && c != 0 && c != EOF) {
		dest[cnt] = c;
		c = getc();
		cnt++;
	}
	dest[cnt] = 0;
	return cnt;
}

size_t Input::gets(char *dest, size_t n)
{
	char c = getc();
	while (isspace(c))
		c = getc();
	if (c == EOF)
		return 0;

	size_t cnt = 0;
	while (cnt < n && !isspace(c) && c != EOF) {
		dest[cnt] = c;
		c = getc();
		cnt++;
	}
	dest[cnt] = 0;
	return cnt;
}

inline char Input::getc()
{
	if (p >= sz) {
		sz = fread(buf, sizeof(char), BUF_SZ, fpi);
		if (sz == 0)
			return EOF;
		p = 0;
	}
	char c = buf[p];
	p++;
	return c;
}
