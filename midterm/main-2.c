#include <stdio.h>
#include <string.h>

char tree[] = "\0ABCDEFG^HIJ^^^^";

void swap(char *lhs, char *rhs) {
	char t = *lhs; *lhs = *rhs; *rhs = t;
}

int main() {
	size_t len = strlen(tree + 1);
	for (size_t i = 2; i < len; i <<= 1)
		for (size_t j = 0; j << 1 < i; ++j)
			swap(&tree[i | j], &tree[(i | j) ^ (i - 1)]);
	puts(tree + 1);
}
