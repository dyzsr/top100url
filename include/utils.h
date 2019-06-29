#include <functional>
#include <string>

struct FileInfo {
	std::string filename;
	size_t size;

	FileInfo(const char *fname, size_t sz)
	{
		filename = std::string(fname);
		size = sz;
	}
};

struct UrlCnt {
	size_t hash;
	size_t cnt;
	std::string url;

	UrlCnt()
	{}

	UrlCnt(const char *_url):
		url(_url)
	{
		std::hash<std::string> str_hash;
		hash = str_hash(url);
		cnt = 1;
	}

	UrlCnt(size_t _hash, size_t _cnt, const char *_url):
		hash(_hash), cnt(_cnt), url(_url)
	{}

	bool operator< (const UrlCnt &o) const
	{
		return (hash != o.hash) ?
			hash < o.hash : url < o.url;
	}

	bool operator== (const UrlCnt &o) const
	{
		return hash == o.hash && url == o.url;
	}
};
