#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DELIMITER20 "####################"
#define DELIMITER40 DELIMITER20 DELIMITER20
#define DELIMITER80 DELIMITER40 DELIMITER40

const size_t maxlen = 256;

typedef struct char_node {
	struct char_node *lchild, *rchild;
	char data;
} char_node;

/**
 * Recursively build a binary tree from its pre-order and in-order traversal.
 * @param s1: start pointer of pre-order traversal in subtree.
 * @param t1: stop pointer of pre-order traversal in subtree.
 * @param s2: start pointer of in-order traversal in subtree.
 * @param t2: stop pointer of in-order traversal in subtree.
 * @return: the root node pointer of built subtree.
 */
char_node *pre_in_dfs(char *s1, char *t1, char *s2, char *t2) {
	if (s1 - t1 != s2 - t2) {
		fputs("Impossible to build a tree\n", stderr);
		exit(EXIT_FAILURE);
	}
	if (s1 == t1 && s2 == t2) return NULL;
	char *root_v = s2;
	for (; root_v != t2; ++root_v) if (*root_v == *s1) break;
	if (root_v == t2) {
		fputs("Characters' sets are not same.\n", stderr);
		fputs("Impossible to build a tree.\n", stderr);
		exit(EXIT_FAILURE);
	}
	/* By the way, get rid of the possibility of repeated chars */
	for (char *p = root_v + 1; p != t2; ++p)
		if (*p == *s1) {
			fputs("Same characters in one traversal.\n", stderr);
			fputs("Ambiguous correspondence.\n", stderr);
			exit(EXIT_FAILURE);
		}
	size_t lsize = root_v - s2;
	char_node *root = malloc(sizeof(char_node));
	root->data = *root_v;
	root->lchild = pre_in_dfs(s1 + 1, s1 + 1 + lsize, s2, root_v);
	root->rchild = pre_in_dfs(s1 + 1 + lsize, t1, root_v + 1, t2);
	return root;
}

void pre_order(char_node *root) {
	if (root == NULL) return;
	putchar(root->data);
	pre_order(root->lchild);
	pre_order(root->rchild);
}

void in_order(char_node *root) {
	if (root == NULL) return;
	in_order(root->lchild);
	putchar(root->data);
	in_order(root->rchild);
}

void post_order(char_node *root) {
	if (root == NULL) return;
	post_order(root->lchild);
	post_order(root->rchild);
	putchar(root->data);
}

int main() {
	char a1[maxlen];  // pre-order traversal
	char a2[maxlen];  // in-order traversal

	printf("Pre-order Traversal: ");
	fgets(a1, maxlen, stdin); size_t len1 = strlen(a1);
	if (a1[len1 - 1] == '\n') a1[--len1] = '\0';
	else while (getchar() != '\n');

	printf("In-order Traversal:  ");
	fgets(a2, maxlen, stdin); size_t len2 = strlen(a2);
	if (a2[len2 - 1] == '\n') a2[--len2] = '\0';
	else while (getchar() != '\n');

	puts(DELIMITER80);

	char_node *root = pre_in_dfs(a1, a1 + len1, a2, a2 + len2);
	printf("Pre-order Traversal:  "); pre_order(root);  putchar('\n');
	printf("In-order Traversal:   "); in_order(root);   putchar('\n');
	printf("Post-order Traversal: "); post_order(root); putchar('\n');

	return EXIT_SUCCESS;
}

#undef DELIMITER20
#undef DELIMITER40
#undef DELIMITER80
