#include <iostream>
#include <stack>

using namespace std;

const int INPUT[] = {1, 2, 3, 4, 5};
//const int INPUT[] = {3, 2, 1};


/*
 * This solution does not require division - solution that would use division
 * simply computes the overall product and when printing it divides output by the
 * current item (time complexity would be O(N), space would be more optimal - O(1)).
 *
 * Time: O(N)
 * Space: O(N)
 */
int main(int argc, char *argv[]) {
	std::stack<int> stack;
	std::stack<int> final_stack;

	/*
	 * Compute product for all items in the array, avoid the last one.
	 */
	stack.push(INPUT[0]);
	size_t input_size = 0;
	for (size_t i = 1; i < sizeof(INPUT) / sizeof(int) - 1; i++) {
		stack.push(stack.top() * INPUT[i]);
		input_size++;
	}

	final_stack.push(stack.top());
	stack.pop();
	input_size++;

	if (input_size < 2) {
		std::cerr << "Input array has to be at least of size 2\n";
		return 1;
	}

	/*
	 * Now traverse back and accumulate product from the other side. At the
	 * end of each turn, mark the current item that was excluded from the
	 * current product.
	 */
	int acc = INPUT[input_size];
	for (size_t i = input_size - 1; i > 0; i--) {
		final_stack.push(acc * stack.top());
		stack.pop();
		acc *= INPUT[i];
	}

	// acc holds product of all items except the first one.
	std::cout << acc << std::endl;

	/*
	 * As results are in the reversed order, print them.
	 */
	while (! final_stack.empty()) {
		std::cout << final_stack.top() << std::endl;
		final_stack.pop();
	}

	return 0;
}
