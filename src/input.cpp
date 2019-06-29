#include "../include/input.h"

#include <cstring>
#include <cassert>
#include <cctype>

Input::Input(FILE *f, size_t buf_sz):
	fpi(f), BUF_SZ(buf_sz), sz(0), ptr(0)
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

size_t Input::getdb(size_t *dest)
{
	*dest = 0;
	char *p = (char *)dest;
	size_t cnt = 0;
	for (; cnt < sizeof(size_t); cnt++) {
		int c = getc();
		if (c == EOF)
			break;
		p[cnt] = c;
	}
	return cnt;
}

size_t Input::getsb(char *dest, size_t n)
{
	if (n == 0)
		return 0;

	int c = getc();
	size_t cnt = 0;
	while (c != 0 && c != EOF) {
		dest[cnt] = c;
		cnt++;
		if (cnt >= n)
			break;
		c = getc();
	}
	dest[cnt] = 0;
	return cnt;
}

size_t Input::gets(char *dest, size_t n)
{
	if (n == 0)
		return 0;

	int c = getc();
	while (isspace(c))
		c = getc();
	if (c == EOF)
		return 0;

	size_t cnt = 0;
	while (!isspace(c) && c != EOF) {
		dest[cnt] = c;
		cnt++;
		if (cnt == n)
			break;
		c = getc();
	}
	dest[cnt] = 0;
	return cnt;
}

inline int Input::getc()
{
	if (ptr >= sz) {
		sz = fread(buf, sizeof(char), BUF_SZ, fpi);
		if (sz == 0)
			return EOF;
		ptr = 0;
	}
	unsigned char c = buf[ptr];
	ptr++;
	return c;
}
