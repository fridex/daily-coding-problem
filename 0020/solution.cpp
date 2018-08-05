#include <iostream>

using namespace std;


/*
 *
 * Time: O(M+N)
 * Space: O(1)
 */
int main(void) {
	const int LIST1[] = {3, 7, 8, 10};
	const int LIST2[] = {99, 1, 8, 10};


	/*
	 * First, lets compute sizes of these lists - if we do not have this information
	 * available, this is still O(N + M).
	 */
	size_t list1_len = sizeof(LIST1) / sizeof(LIST1[0]);
	size_t list2_len = sizeof(LIST2) / sizeof(LIST1[0]);


	const int * pointer1 = &LIST1[0];
	const int * pointer2 = &LIST2[0];

	/*
	 * Now increase the "start" of pointers - we know the ending is shared,
	 * so the length of the ending sequence can be no more longer than the
	 * smaller sequence.
	 *
	 * BTW this can be compound, let's assubme there can be underflow :)
	 */
	if (list1_len > list2_len) {
		for (size_t i = 0; i != list1_len - list2_len; i++)
			pointer1++;
	} else {
		for (size_t i = 0; i != list2_len - list1_len; i++)
			pointer1++;
	}

	/*
	 * I assume the ending is always shared. In case of a real linked list
	 * there should be a test on end if these two lists do not end with the
	 * same sequence.
	 */
	while (*pointer1 != *pointer2) {
		pointer1++;
		pointer2++;
	}

	std::cout << *pointer1 << std::endl;

	return 0;
}
