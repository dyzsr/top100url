#include "../include/input.h"

#include <cstring>
#include <cassert>
#include <cctype>

Input::Input(FILE *f, const char *mode, size_t _buf_sz):
	buf_sz(_buf_sz), sz(0), ptr(0)
{
	fpi = freopen(NULL, mode, f);
	assert(fpi != NULL);
	assert(buf_sz > 0);

	buf = new char[buf_sz];
	assert(buf != NULL);
	memset(buf, -1, buf_sz * sizeof(char));
}

Input::Input(const char *filename, const char *mode, size_t _buf_sz):
	buf_sz(_buf_sz), sz(0), ptr(0)
{
	fpi = fopen(filename, mode);
	assert(fpi != NULL);
	assert(buf_sz > 0);

	buf = new char[buf_sz];
	assert(buf != NULL);
	memset(buf, -1, buf_sz * sizeof(char));
}

Input::~Input()
{
	fclose(fpi);
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
		sz = fread(buf, sizeof(char), buf_sz, fpi);
		if (sz == 0)
			return EOF;
		ptr = 0;
	}
	unsigned char c = buf[ptr];
	ptr++;
	return c;
}
