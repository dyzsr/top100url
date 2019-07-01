#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <random>

#include "../include/output.h"

const char *basic = "ooooooooooooooooooooooooooooooo";

int main(int argc, char *argv[]) {
	if (argc != 2)
		exit(1);

	int max_count = atoi(argv[1]);

	std::default_random_engine gen;
	std::uniform_int_distribution<int> rd0(0, 4);
	std::uniform_int_distribution<> rd1(0, 25);
	std::uniform_int_distribution<> rd2(1, 100);


	int length = strlen(basic);

	char str[256];

	Output out(stdout, "w", (1 << 28));

	for (int count = 0; count < max_count; count++) {
		int i = 0;
		for (; i < length; i++) {
			if (rd0(gen) == 0) {
				int z = rd1(gen);
				str[i] = (char)('a' + z);
			} else {
				str[i] = basic[i];
			}
		}
		if (rd0(gen) == 1) {
			int len = rd2(gen);
			for (int j = 0; j < len; i++, j++) {
				if (rd0(gen) == 0) {
					int z = rd1(gen);
					str[i] = (char)('a' + z);
				} else {
					str[i] = str[j];
				}
			}
		}
		str[i] = 0;
		out.puts(str);
	}

	return 0;
}
