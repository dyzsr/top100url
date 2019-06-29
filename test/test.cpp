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
	Input in(stdin, buf_sz);

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
	freopen(NULL, "rb", stdin);

	size_t buf_sz = (1 << 20);
	Input in(stdin, buf_sz);

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
	Output out(stdout, buf_sz);

	const size_t N = 65536;
	char *s = new char[N];
	for (size_t i = 0; i < 10; i++) {
		fgets(s, N, stdin);
		size_t len = strlen(s);
		if (len > 0)
			s[len - 1] = 0;
		out.puts(s);
	}
	out.flush();
	delete[] s;
}

void test_outputb()
{
	freopen(NULL, "wb", stdout);

	size_t buf_sz = (1 << 3);
	Output out(stdout, buf_sz);

	const size_t N = 65536;
	char *s = new char[N];
	for (size_t i = 0; i < 10; i++) {
		fgets(s, N, stdin);
		size_t len = strlen(s);
		if (len > 0)
			s[len - 1] = 0;
		out.putsb(s);
	}
	out.flush();
	delete[] s;
}

void test_partition()
{
	freopen(NULL, "wb", stdout);

	const char *dir = "._test_partition";
	char cmd[100];

	// create dir
	strcpy(cmd, "mkdir -p "); strcat(cmd, dir); system(cmd);
	// check
	strcpy(cmd, "ls -a | grep "); strcat(cmd, dir); system(cmd);

	size_t file_sz = (1 << 26);
	Partition part(file_sz);
	std::vector<FileInfo> files = part.partition(stdin, dir);

	printf("number of files: %zu\n", files.size());
	for (auto &info: files) {
		printf("file: %s, size: %zuM\n",
				info.filename.c_str(), info.size >> 20);
	}

	// remove dir
//	strcpy(cmd, "rm -rd "); strcat(cmd, dir); system(cmd);
	// check
//	strcpy(cmd, "ls -a | grep "); strcat(cmd, dir); system(cmd);
}

void test_reduce()
{
	freopen(NULL, "rb", stdin);
	freopen(NULL, "wb", stdout);
	Input in(stdin, 1 << 24);
	Output out(stdout, 1 << 24);
	Reduce reduce;
	auto res = reduce(&in, &out);
	fprintf(stderr, "Reduced, total input = %zu, total output = %zu.\n",
			res.first, res.second);
}

void view_urlcnt()
{
	freopen(NULL, "rb", stdin);
	Input in(stdin, 1 << 24);
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
		"._test_merge/iter-00-00000",
		"._test_merge/iter-00-00001",
		"._test_merge/iter-00-00002",
		"._test_merge/iter-00-00003",
		"._test_merge/iter-00-00004",
		"._test_merge/iter-00-00005",
		"._test_merge/iter-00-00006",
		"._test_merge/iter-00-00007",
	};

	std::vector<FILE *> fs(N);
	std::vector<Input *> ins(N);

	for (size_t i = 0; i < N; i++) {
		fs[i] = fopen(fnames[i], "rb");
		ins[i] = new Input(fs[i], 1 << 24);
	}

	FILE *fpo = fopen("._test_merge/iter-01-00000", "wb");
	{
		Output out(fpo, 1 << 24);
		
		Merge merge;
		auto res = merge(ins, &out);
		fprintf(stderr, "Merged, total input = %zu, total output = %zu.\n",
				res.first, res.second);
	}

	fclose(fpo);
	for (size_t i = 0; i < N; i++) {
		delete ins[i];
		fclose(fs[i]);
	}
}
