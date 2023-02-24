#include <stdio.h>
#include <malloc.h>
#include <time.h>


typedef struct linked {
    int value;
    struct linked* pointer;
} list;

list* initList(int item) {
    list *first;
    first = malloc(sizeof(struct linked));
    *first = (list){.value = item, .pointer = NULL};
    return first;
}

list* push(int item, list *prev) {
    struct linked *next;
    next = malloc(sizeof(struct linked));
    next->value = item;
    next->pointer = prev;
    return next;
}

list* clear(list *last) {
    list *point = last;
    list *newPoint;
    while (point != NULL) {
        newPoint = point->pointer;
        free(point);
        point = newPoint;
    }
    return 0;
}

int show(list *l) {
    while (l->pointer != NULL) {
        printf("%i, ", l->value);
        l = l->pointer;
    }
    printf("%i\n", l->value);
    return 0;
}

int randSign() {
    return (rand() % 2 * 2 - 1);
}

int getSign(int x) {
    return x > 0;
}

list* create(int n) {
    int neg = n / 2, pos = neg, sign;
    sign = randSign(); // I thought about just make first value always positive, but it decreases amount of situations
    list* list1 = initList(sign * (rand() % 100 + 1));
    sign > 0 ? pos-- : neg--;
    for (int i = 0; i < n - 1; i++) {
        if (neg != 0 && pos != 0) {
            sign = randSign();
            list1 = push(sign * (rand() % 100 + 1), list1);
            sign > 0 ? pos-- : neg--;
        }
        else if (neg == 0) {
            list1 = push(rand() % 100 + 1, list1);
            pos--;
        }
        else {
            list1 = push(rand() % 100 * -1 - 1, list1);
            neg--;
        }
    }
    return list1;
}

list* sort(list *l) {
    list *first = l;
    list *last;
    int sign = !getSign(l->value);
     l = l->pointer;
    while (l->pointer != NULL) {
        if (sign == getSign(l->value)) {
            l = l->pointer;
            sign = !sign;
            continue;
        }
        last = l->pointer;
        while (getSign(last->value) != sign) {
            last = last->pointer;
        }
        int temp = last->value;
        last->value = l->value;
        l->value = temp;

        l = l->pointer;
        if (l->pointer == NULL) break;
        l = l->pointer;

    }
    return first;
}

int main() {
    int n;

    printf("Input n:");
    scanf("%i", &n);
    if (n == 0) {
        printf("I have this one: []");
        return 0;
    }
    if (n % 2 != 0) {
        printf("How i can make array with equal amount of negative and positive numbers with this length?");
        return 0;
    }
    srand(time(NULL));
    list *list1 = create(n);
    show(list1);
    list1 = sort(list1);
    show(list1);


    clear(list1);
    return 0;
}
