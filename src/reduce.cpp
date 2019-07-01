#include "../include/reduce.h"
#include "../include/input.h"
#include "../include/output.h"
#include "../include/utils.h"
#include "../include/config.h"

#include <algorithm>

Reduce::Reduce()
{}

std::pair<size_t, size_t> Reduce::operator() (Input *in, Output *out)
{
	char *str = new char[MAX_URL_SZ + 1];
	for (;;) {
		size_t n = in->getsb(str, MAX_URL_SZ);
		if (n == 0)
			break;

		// map url string to UrlCnt
		urls.emplace_back(str);
	}
	delete[] str;
	
	std::sort(urls.begin(), urls.end());
	size_t sz = 0;
	for (size_t i = 1; i < urls.size(); i++) {
		if (urls[sz] == urls[i])
			urls[sz].cnt += urls[i].cnt;
		else {
			++sz;
			urls[sz] = urls[i];
		}
	}
	sz++;

	for (size_t i = 0; i < sz; i++) {
		out->putdb(urls[i].hash);
		out->putdb(urls[i].cnt);
		out->putsb(urls[i].url.c_str());
	}
	out->flush();

	return std::make_pair(urls.size(), sz);
}
