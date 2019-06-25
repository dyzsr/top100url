#include "input.h"
#include "output.h"
#include <cstring>

void test_input() {
	size_t buf_sz = (1 << 3);
	Input in(stdin, buf_sz);

	const int N = 256;
	char s[N];

	for (int i = 0; i < 10; i++) {
		int sz = in.gets(s, N);
		if (sz == 0)
			break;

		puts(s);
	}
}

void test_inputb() {
	size_t buf_sz = (1 << 3);
	Input in(stdin, buf_sz);

	const int N = 256;
	char s[N];

	for (int i = 0; i < 10; i++) {
		int sz = in.getsb(s, N);
		if (sz == 0)
			break;

		puts(s);
	}
}

void test_output() {
	size_t buf_sz = (1 << 3);
	Output out(stdout, buf_sz);

	const int N = 65536;
	char *s = new char[N];
	for (int i = 0; i < 10; i++) {
		fgets(s, N, stdin);
		int len = strlen(s);
		if (len > 0)
			s[len - 1] = 0;
		out.puts(s);
	}
	out.flush();
	delete[] s;
}

void test_outputb() {
	size_t buf_sz = (1 << 3);
	Output out(stdout, buf_sz);

	const int N = 65536;
	char *s = new char[N];
	for (int i = 0; i < 10; i++) {
		fgets(s, N, stdin);
		int len = strlen(s);
		if (len > 0)
			s[len - 1] = 0;
		out.putsb(s);
	}
	out.flush();
	delete[] s;
}

int main(int argc, char *argv[]) {
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
	}
	return 0;
}
