#ifndef PARTITION_H
#define PARTITION_H

#include <cstdio>
#include <vector>
#include <string>

class Input;
class Output;
struct FileInfo;

class Partition {
	public:
		Partition(size_t file_sz);
		~Partition();

		std::vector<FileInfo> operator() (FILE *fpi, const char *dir);

	private:
		size_t FILE_SZ;
		size_t BUF_SZ;

		bool read_part(Input *in, Output *out, size_t *sz);
};

#endif
