#include <stdio.h>
#include <stdlib.h>

struct list {
	struct list *next;
	long long data;
};

int main() {
	struct list *La = malloc(sizeof(struct list));
	struct list *Lb = malloc(sizeof(struct list));
	La->data = 0; La->next = NULL;
	Lb->data = 0; Lb->next = NULL;
	struct list *Ta = La;

	long long data;
	while (scanf("%lld", &data) != EOF) {
		Ta->next = malloc(sizeof(struct list));
		Ta = Ta->next;
		Ta->data = data;
		Ta->next = NULL;
	}

	struct list *p = La, *q = Lb;
	while (p->next != NULL) {
		if (~p->next->data & 1) {  // p->data is odd
			q->next = p->next;
			p->next = p->next->next;
			q = q->next;
			q->next = NULL;
		} else p = p->next;
	}

	printf("Odd list: ");
	for (p = La->next; p != NULL; p = p->next)
		printf(" %lld", p->data);
	putchar('\n');
	printf("Even list:");
	for (q = Lb->next; q != NULL; q = q->next)
		printf(" %lld", q->data);
	putchar('\n');

	return 0;
}
