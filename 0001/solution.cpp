#include <iostream>
#include <map>

using namespace std;

const int INPUT[] = {10, 15, 3, 7};
const int K = 17;

int main(int argc, char *argv[]) {
	std::map<int, int> mem;

	/*
	 * Time: O(N)
	 * Memory: O(N)
	 */
	for (int i = 0; i < sizeof(INPUT) / sizeof(int); i++) {
		auto it = mem.find(INPUT[i]);

		if (it != mem.end()) {
			std::cout << "YES: " << it->first << ' ' << it->second << std::endl;
			return 0;
		}

		mem[K - INPUT[i]] = INPUT[i];
	}

	std::cout << "No.\n";

     return 0;
}
