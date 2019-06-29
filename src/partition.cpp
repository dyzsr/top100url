#include "../include/partition.h"
#include "../include/input.h"
#include "../include/output.h"
#include "../include/utils.h"

#include <cstdlib>
#include <cassert>

Partition::Partition(size_t file_sz):
	FILE_SZ(file_sz), BUF_SZ(1 << 26)
{
	assert(FILE_SZ > 0);
}

Partition::~Partition()
{}

std::vector<FileInfo> Partition::operator() (FILE *fpi, const char *dir)
{
	Input in(fpi, BUF_SZ);

	std::vector<FileInfo> res;
	char fname[40];
	
	bool eof = false;
	while (!eof) {
		// set filename
		size_t n = res.size();

		sprintf(fname, "%s/part-%05zu", dir, n);

		// open tmp file
		FILE *fpo = fopen(fname, "wb");
		size_t sz;
		assert(fpo != NULL);
		{
			Output out(fpo, BUF_SZ);
			// read and partition input file
			eof = read_part(&in, &out, &sz);
		}
		fclose(fpo);
		
		res.emplace_back(fname, sz);
	}

	return res;
}

bool Partition::read_part(Input *in, Output *out, size_t *sz)
{
	size_t cnt = 0;
	bool eof = false;
	
	char *str = new char[65536];
	while (cnt < FILE_SZ) {
		size_t n = in->gets(str, 65536);
		if (n == 0) { // reach EOF
			eof = true;
			break;
		}
		out->putsb(str);
		cnt += n + 1; // add n to size
	}
	delete[] str;

	out->flush();	// clear the buffer
	*sz = cnt;
	return eof;
}
