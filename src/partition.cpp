#include "../include/partition.h"
#include "../include/input.h"
#include "../include/output.h"
#include "../include/utils.h"
#include "../include/config.h"

#include <cstdlib>
#include <cassert>

Partition::Partition(size_t _file_sz):
	file_sz(_file_sz)
{
	assert(file_sz > 0);
}

Partition::~Partition()
{}

std::pair<size_t, bool> Partition::operator() (Input &in, Output &out)
{
	size_t cnt = 0;
	bool eof = false;
	
	char *str = new char[MAX_URL_SZ + 1];
	while (cnt < file_sz) {
		size_t n = in.gets(str, MAX_URL_SZ);
		if (n == 0) { // reach EOF
			eof = true;
			break;
		}
		out.putsb(str);
		cnt += n + 1; // add n to size
	}
	delete[] str;

	return std::make_pair(cnt, eof);
}
