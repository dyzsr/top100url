#include "../include/input.h"
#include "../include/output.h"
#include "../include/partition.h"
#include "../include/reduce.h"
#include "../include/merge.h"
#include "../include/utils.h"

#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <iostream>

void test_input();
void test_inputb();
void test_output();
void test_outputb();
void test_partition();
void test_reduce();
void view_urlcnt();
void test_merge();

int main(int argc, char *argv[])
{
	if (argc > 1) {
		if (strcmp(argv[1], "input") == 0) {
			test_input();
		}
		else if (strcmp(argv[1], "inputb") == 0) {
			test_inputb();
		}
		else if (strcmp(argv[1], "output") == 0) {
			test_output();
		}
		else if (strcmp(argv[1], "outputb") == 0) {
			test_outputb();
		}
		else if (strcmp(argv[1], "partition") == 0) {
			test_partition();
		}
		else if (strcmp(argv[1], "reduce") == 0) {
			test_reduce();
		}
		else if (strcmp(argv[1], "urlcnt") == 0) {
			view_urlcnt();
		}
		else if (strcmp(argv[1], "merge") == 0) {
			test_merge();
		}
	}
	return 0;
}

void test_input()
{
	size_t buf_sz = (1 << 20);
	Input in(stdin, "w", buf_sz);

	const size_t N = 256;
	char s[N];

	for (size_t i = 0; i < 10; i++) {
		size_t sz = in.gets(s, N);
		if (sz == 0)
			break;

		puts(s);
	}
}

void test_inputb()
{
//	freopen(NULL, "rb", stdin);
	size_t buf_sz = (1 << 20);
	Input in(stdin, "rb", buf_sz);

	const size_t N = 256;
	char s[N];

	for (size_t i = 0; i < 70; i++) {
		size_t sz = in.getsb(s, N);
		if (sz == 0)
			break;

		puts(s);
	}
}

void test_output()
{
	size_t buf_sz = (1 << 3);
	Output out(stdout, "w", buf_sz);

	const size_t N = 65536;
	char *s = new char[N];
	for (size_t i = 0; i < 10; i++) {
		fgets(s, N, stdin);
		size_t len = strlen(s);
		if (len > 0)
			s[len - 1] = 0;
		out.puts(s);
	}
//	out.flush();
	delete[] s;
}

void test_outputb()
{
	size_t buf_sz = (1 << 3);
	Output out(stdout, "wb", buf_sz);

	const size_t N = 65536;
	char *s = new char[N];
	for (size_t i = 0; i < 10; i++) {
		fgets(s, N, stdin);
		size_t len = strlen(s);
		if (len > 0)
			s[len - 1] = 0;
		out.putsb(s);
	}
//	out.flush();
	delete[] s;
}

void test_partition()
{
	char cmd[100];

	// create dir
	sprintf(cmd, "mkdir -p _test"); system(cmd);
	// check
	sprintf(cmd, "ls -a | grep _test"); system(cmd);

	size_t file_sz = (1 << 26);
	Partition partition(file_sz);

	Input in(stdin, "r", 1 << 24);
	char fname[40];
	std::vector<FileInfo> files;
	for (size_t i = 0;; i++) {
		sprintf(fname, "_test/part-%05zu", i);
		Output out(fname, "wb", 1 << 24);
		std::pair<size_t, bool> res = partition(in, out);
		files.emplace_back(fname, res.first);
		if (res.second)
			break;
	}

	printf("number of files: %zu\n", files.size());
	for (auto &file: files) {
		printf("file: %s, size: %zuM\n",
				file.filename.c_str(), file.size >> 20);
	}
}

void test_reduce()
{
	Input in(stdin, "rb", 1 << 24);
	Output out(stdout, "wb", 1 << 24);
	Reduce reduce;
	auto res = reduce(&in, &out);
	fprintf(stderr, "Reduced, total input = %zu, total output = %zu.\n",
			res.first, res.second);
}

void view_urlcnt()
{
	Input in(stdin, "rb", 1 << 24);
	char *str = new char [65536];
	for (size_t i = 0; i < 70; i++) {
		size_t hash, cnt;
		size_t a = in.getdb(&hash);
		size_t b = in.getdb(&cnt);
		size_t c = in.getsb(str, 65535);
		printf("a = %zu, b = %zu, c = %zu\n", a, b, c);
		printf("hash: %zu, count: %zu, url: %s\n", hash, cnt, str);
	}
	delete[] str;
}

void test_merge()
{
	const int N = 8;
	const char *fnames[N] = {
		"_test/iter-00-00000",
		"_test/iter-00-00001",
		"_test/iter-00-00002",
		"_test/iter-00-00003",
		"_test/iter-00-00004",
		"_test/iter-00-00005",
		"_test/iter-00-00006",
		"_test/iter-00-00007",
	};

	std::vector<FILE *> fs(N);
	std::vector<Input *> ins(N);

	for (size_t i = 0; i < N; i++) {
		ins[i] = new Input(fnames[i], "rb", 1 << 24);
	}

	Output out("_test/iter-01-00000", "wb", 1 << 24);

	Merge merge;
	auto res = merge(ins, &out);
	fprintf(stderr, "Merged, total input = %zu, total output = %zu.\n",
			res.first, res.second);

	for (size_t i = 0; i < N; i++) {
		delete ins[i];
	}
}
