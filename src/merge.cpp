#include "../include/merge.h"
#include "../include/utils.h"
#include "../include/input.h"
#include "../include/output.h"

#include <queue>

typedef std::pair<UrlCnt *, size_t> Item;

struct CMP {
	bool operator() (const Item &a, const Item &b)
	{
		return *(b.first) < *(a.first);
	}
};

Merge::Merge()
{}

std::pair<size_t, size_t> Merge::operator() (const std::vector<Input *> &ins, Output *out)
{
	/*** Merge sort ***/
	std::priority_queue<Item, std::vector<Item>, CMP> pq;

	std::vector<char> iseof(ins.size(), 0);

	for (size_t i = 0; i < ins.size(); i++) {
		UrlCnt *urlcnt = new UrlCnt;
		iseof[i] = getUrlCnt(urlcnt, ins[i]);
		pq.push(std::make_pair(urlcnt, i));
	}

	size_t tot_in = 0;
	size_t tot_out = 0;

	UrlCnt *least = nullptr;
	while (pq.size()) {
		// pop the least from the queue
		Item item = pq.top(); pq.pop();
		tot_in++;

		UrlCnt *urlcnt = item.first;
		size_t j = item.second;

		if (least == nullptr)
			least = urlcnt;
		else if (*least == *urlcnt) {
			least->cnt += urlcnt->cnt;
			delete urlcnt;
		}
		else {
			putAndDelete(least, out);
			least = urlcnt;
			tot_out++;
		}

		if (!iseof[j]) {
			// get a new item from files
			urlcnt = new UrlCnt;
			iseof[j] = getUrlCnt(urlcnt, ins[j]);
			pq.push(std::make_pair(urlcnt, j));
		}
	}

	if (least != nullptr) {
		putAndDelete(least, out);
		tot_out++;
	}

	out->flush();

	return std::make_pair(tot_in, tot_out);
}

bool Merge::getUrlCnt(UrlCnt *urlcnt, Input *in)
{
	size_t hash, cnt, n;

	n = in->getdb(&hash);
	if (n < sizeof(size_t)) // EOF
		return true;

	n = in->getdb(&cnt);
	if (n < sizeof(size_t))
		return true;

	char *str = new char[65536];
	n = in->getsb(str, 65535);
	if (n == 0)
		return true;

	urlcnt->hash = hash;
	urlcnt->cnt = cnt;
	urlcnt->url = std::string(str);

	delete[] str;
	return false;
}

void Merge::putAndDelete(UrlCnt *urlcnt, Output *out)
{
	out->putdb(urlcnt->hash);
	out->putdb(urlcnt->cnt);
	out->putsb(urlcnt->url.c_str());
	delete urlcnt;
}
