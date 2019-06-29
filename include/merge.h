#ifndef MERGE_H
#define MERGE_H

#include <vector>
#include <string>
#include <functional>

class Input;
class Output;
struct UrlCnt;

class Merge {
	public:
		Merge();

		std::pair<size_t, size_t> operator() (const std::vector<Input *> &ins, Output *out);

	private:
		bool getUrlCnt(UrlCnt *urlcnt, Input *in);
		void putAndDelete(UrlCnt *urlcnt, Output *out);
};

#endif
