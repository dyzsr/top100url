#ifndef PARTITION_H
#define PARTITION_H

#include <functional>

class Input;
class Output;
struct FileInfo;

class Partition {
	public:
		Partition(size_t _file_sz);
		~Partition();

		std::pair<size_t, bool> operator() (Input &in, Output &out);

	private:
		size_t file_sz;

		bool read_part(Input &in, Output &out, size_t *sz);
};

#endif
