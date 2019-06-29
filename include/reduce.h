#ifndef REDUCE_H
#define REDUCE_H

#include <vector>
#include <functional>

class Input;
class Output;
struct UrlCnt;

class Reduce {
	public:
		Reduce();

		std::pair<size_t, size_t> operator() (Input *in, Output *out);

	private:
		std::vector<UrlCnt> urls;
};

#endif
