#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "struct.h"

void EmitSortMenu() {
    long sz = 0;
    printf("Input array size: ");
    scanf("%li", &sz);
    School *x = genArray(sz);
    School *y = copyArray(x, sz);
    School *z = copyArray(x, sz); // 3 одинаковых массива для 3 сортировок
    // указатель на функцию сравнения (будет возвращать положительное, отрицательное или 0 в зависимости от отличия элементов и выбора возрастания/убывания)
    int (*compare)(const School*, const School*) = NULL; 
    // массив указателей на все функции сортировки
    void (*sort[])(School*, long, int (*compare)(const School*, const School*)) = {shaker_sort, merge_sort1, quick_sort};
    School *arrays[] = {x, y, z};
    const char *names[] = {"Shaker", "Merge", "Quick"};
    int choice;
    // printSchoolArray(x, sz, "Original Array");
    printf("Choose the sort:\n");
    printf("1 - In ascending order\n");
    printf("2 - In descending order\n");
    scanf("%d", &choice);
    switch(choice){
        case 1: 
            compare = compare_up_wrapper;
            break;
        case 2:
            compare = compare_down_wrapper;
            break;
        default: printf("Incorrect choice. Try again.\n");
    }
    for(int i = 0; i < 3; i++){
        checkSort(names[i], sort[i], arrays[i], sz, compare);
        // printSchoolArray(arrays[i], sz, names[i]);
    }
    free(x);
    free(y);
    free(z);
}

void EmitSearchMenu() {
    int search_choice;
    printf("Choose search type:\n1. Linear\n2. BST\n3. RBTree\n4. Benchmark all\n");
    scanf("%d", &search_choice);
    if (search_choice == 4) {
        benchmark_search();
    } 
    else {
        long n;
        printf("Enter data size: ");
        scanf("%ld", &n);
        School *arr = genArray(n);
        char key[MAX_LENGTH];
        printf("Enter key (full_name): ");
        getchar();
        fgets(key, MAX_LENGTH, stdin);
        key[strcspn(key, "\n")] = 0;

        clock_t start, end;
        switch (search_choice) {
            case 1: {
                start = clock();
                int index = linear_search(arr, n, key);
                end = clock();
                printf("Linear search time: %.6f sec. Index: %d\n", (double)(end - start)/CLOCKS_PER_SEC, index);
                break;
            }
            case 2: {
                BSTNode *bstRoot = NULL;
                for (long i = 0; i < n; i++)
                    bstRoot = BSTInsert(bstRoot, arr[i]);
                start = clock();
                BSTNode *result = BSTSearch(bstRoot, key);
                end = clock();
                printf("BST search time: %.6f sec. Found: %s\n", (double)(end - start)/CLOCKS_PER_SEC, result ? "Yes" : "No");
                freeBST(bstRoot);
                 break;
             }
             case 3: {
                RBNode *rbRoot = NULL;
                 for (long i = 0; i < n; i++)
                    RBInsert(&rbRoot, arr[i]);
                start = clock();
                RBNode *rbResult = RBSearch(rbRoot, key);
                end = clock();
                printf("RBTree search time: %.6f sec. Found: %s\n", (double)(end - start)/CLOCKS_PER_SEC, rbResult ? "Yes" : "No");
                freeRBTree(rbRoot);
                break;
            }
            default:
                printf("Invalid choice\n");
        }
        free(arr);
    }
}

void generate_full_name(char* full_name) {
    const char* first_names[] = {
        "John", "Mikhail", "Jack", "Emma", "Mike", 
        "Sarah", "Tom", "Lucy", "Sam", "Grace",
        "Ashab", "Vitaliy", "Kirill", "Mell", "Ivan",
        "Alexander", "Elena", "Dmitry", "Sophia", "Daniel",
        "Victoria", "Andrew", "Natalia", "Peter", "Anna",
        "George", "Maria", "Nicholas", "Catherine", "James"
    };
    const char* last_names[] = {
        "Wick", "Litvin", "Daniels", "Watson", "Tyson",
        "Davis", "Miller", "Wilson", "Taylor", "Moore",
        "Tamaev", "Tsal", "Pavlov", "Stroy", "Zolo",
        "Smith", "Johnson", "Williams", "Brown", "Jones",
        "Garcia", "Martinez", "Anderson", "Thomas", "White",
        "Harris", "Martin", "Thompson", "Young", "King"
    };
    int first_index = rand() % 30;
    int last_index = rand() % 30;
    int index = rand() % 100 + 1;
    sprintf(full_name, "%s %s %d", first_names[first_index], last_names[last_index], index);
}

void generate_quailification(char* qualification) {
    const char* qualifications[] = { "First", "Second", "High"};
    int index = rand() % 3;
    strcpy(qualification, qualifications[index]);
}

void generate_home_address(char* home_address) {
    const char* home_addresses[] = { "Litvinburg", "Bikini Bottom", "Mondstadt",
    "Springfield", "Cheboksary", "Kanash", "Pukovo",
    "Tsivilsk", "Odintsovo", "Orehovo-Zuevo"};
    int index = rand() % 10;
    strcpy(home_address, home_addresses[index]);
}

void generate_date_birth(char* date_birth) {
    int day = rand() % 28 + 1; // так-то несложно сюда добавить и проверку на февраль и високосный год, но было лень
    int month = rand() % 12 + 1;
    int year = 1980 + rand() % 15;
    sprintf(date_birth, "%02d.%02d.%d", day, month, year); // то же что и printf, но в массив
}

void generate_phone_number(char* phone_number) {
    phone_number[0] = '+';
    phone_number[1] = '7';
    for (int i = 2; i < 12; i++) {
        phone_number[i] = '0' + (rand() % 10);
    }
    phone_number[12] = '\0';
}

void generate_employment_date(char* employment_date) {
    int day = rand() % 28 + 1;
    int month = rand() % 12 + 1;
    int year = 2010 + rand() % 15;
    sprintf(employment_date, "%02d.%02d.%d", day, month, year);
}

School* genArray (long n) {
    srand(time(NULL));

    School* a = (School*)malloc(n * sizeof(School));
    if (!a) return NULL;
    for (int i = 0; i < n; i++) {
        generate_full_name(a[i].full_name);
        generate_quailification(a[i].qualification);
        generate_home_address(a[i].home_address);
        generate_date_birth(a[i].date_birth);
        generate_phone_number(a[i].phone_number);
        generate_employment_date(a[i].employment_date);
    }
    return a;
}

School* copyArray(School *a, long n) {
    School *x = (School*)malloc(n * sizeof(School));
    if (!x)
    return NULL;
    memcpy(x, a, n * sizeof(School));
    return x;
}

// по возрастанию
int compare_up(const void* p1, const void* p2){
    const School* x1 = (const School*)p1;
    const School* x2 = (const School*)p2;
    int cmp1 = strcmp(x1->full_name, x2->full_name);
    if (cmp1 != 0) {
        return cmp1;
    }
    int cmp2 = strcmp(x1->qualification, x2->qualification);
    if (cmp2 != 0) {
        return cmp2;
    }
    int cmp3 = strcmp(x1->home_address, x2->home_address);
    if (cmp3 != 0) {
        return cmp3;
    }
    int cmp4 = strcmp(x1->date_birth, x2->date_birth);
    if (cmp4 != 0) {
        return cmp4;
    }
    int cmp5 = strcmp(x1->phone_number, x2->phone_number);
    if (cmp5 != 0) {
        return cmp5;
    }
    int cmp6 = strcmp(x1->employment_date, x2->employment_date);
    if (cmp6 != 0) {
        return cmp6;
    }
    return x1->employment_date - x2->employment_date;
}
// по убыванию (инверсия возрастания)
int compare_down(const void* p1, const void* p2){
    const School* x1 = (const School*)p1;
    const School* x2 = (const School*)p2;
    int cmp1 = strcmp(x1->full_name, x2->full_name);
    if (cmp1 != 0) {
        return -cmp1;
    }
    int cmp2 = strcmp(x1->qualification, x2->qualification);
    if (cmp2 != 0) {
        return -cmp2;
    }
    int cmp3 = strcmp(x1->home_address, x2->home_address);
    if (cmp3 != 0) {
        return -cmp3;
    }
    int cmp4 = strcmp(x1->date_birth, x2->date_birth);
    if (cmp4 != 0) {
        return -cmp4;
    }
    int cmp5 = strcmp(x1->phone_number, x2->phone_number);
    if (cmp5 != 0) {
        return -cmp5;
    }
    int cmp6 = strcmp(x1->employment_date, x2->employment_date);
    if (cmp6 != 0) {
        return -cmp6;
    }
    return x2->employment_date - x1->employment_date;
}

// Функции-обёртки для приведения типов
int compare_up_wrapper(const School* a, const School* b) {
    return compare_up((const void*)a, (const void*)b);
}

int compare_down_wrapper(const School* a, const School* b) {
    return compare_down((const void*)a, (const void*)b);
}

void checkSort(const char *algName, void (*sort)(School*, long, int (*compare)(const School*, const School*)), School *a, long n, int (*compare)(const School*, const School*)) {
    clock_t t1 = clock(); // засекли старт
    sort(a, n, compare); // вызов переданной функции сортировки
    clock_t t2 = clock(); // засекли конец
    double sortTime = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("%s sort time for array of %li elements in seconds: %.6lf\n", algName, n, sortTime);
}

void shaker_sort(School* a, long n, int (*compare)(const School*, const School*)) {
    long left = 0;
    long right = n - 1;
    School tmp;
    do {
        // Проход справа налево (движение "вверх")
        for (long j = right; j > left; j--) {
            if (compare(&a[j - 1], &a[j]) > 0) {
                tmp = a[j - 1];
                a[j - 1] = a[j];
                a[j] = tmp;
            }
        }
        left++;
        // Проход слева направо (движение "вниз")
        for (long j = left; j < right; j++) {
            if (compare(&a[j], &a[j + 1]) > 0) {
                tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
        right--;
    } while (left <= right);
}
void merge(School* a, long low, long mid, long high, int (*compare)(const School*, const School*)) {
    School* b = (School*)malloc((high + 1 - low) * sizeof(School));
    long h, i, j, k;
    h = low;
    i = 0;
    j = mid + 1;
    while ((h <= mid) && (j <= high)) {
        if (compare(&a[h], &a[j]) <= 0) {
            b[i] = a[h];
            h++;
        }
        else {
            b[i] = a[j];
            j++;
        }
        i++;
    }
    if (h > mid) { // если все элементы из левой части уже расставлены
        for (k = j; k <= high; k++) {
            b[i] = a[k];
            i++;
        }
    }
    else { // если все элементы из правой части уже расставлены
        for (k = h; k <= mid; k++) {
            b[i] = a[k];
            i++;
        }
    }
    // копируем обратно из временного массива в исходный, временный сносим
    for (k = 0; k <= high - low; k++) {
        a[k + low] = b[k];
    }
    free(b);
}

School* merge_sort(School* a, long low, long high, int (*compare)(const School*, const School*)) {
    long mid;
    if (low < high) {
        mid = (low + high) / 2;
        merge_sort(a, low, mid, compare);
        merge_sort(a, mid + 1, high, compare);
        merge(a, low, mid, high, compare);
    }
    return a;
}

// по сути, это костыль для нормального вызова функции merge_sort, т.к. в ней требуется 4 элемента, а не 3, как у всех остальных сортировок
void merge_sort1(School* a, long n, int (*compare)(const School*, const School*)) {
    merge_sort(a, 0, n - 1, compare);
}

void qSort(School* a, int first, int last, int (*compare)(const School*, const School*)) {
    if (first < last) {
        int left = first, right = last;
        int middle_index = left + (right - left) / 2;
        School* middle = &a[middle_index]; // Указатель на опорный элемент
        do {
            while (compare(&a[left], middle) < 0) left++;
            while (compare(&a[right], middle) > 0) right--;
            if (left <= right) {
                School tmp = a[left];
                a[left] = a[right];
                a[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);

        qSort(a, first, right, compare);
        qSort(a, left, last, compare);
    }
}

void quick_sort(School* a, long n, int (*compare)(const School*, const School*)) {
    qSort(a, 0, n-1, compare);
}

void printSchoolArray(const School* arr, long n, const char* title) {
    printf("\n=== %s ===\n", title);
    for (int i = 0; i < n; i++) {
        printf("Element %d:\n", i + 1);
        printf("  Name: %s\n", arr[i].full_name);
        printf("  Qualification: %s\n", arr[i].qualification);
        printf("  Address: %s\n", arr[i].home_address);
        printf("  Birth Date: %s\n", arr[i].date_birth);
        printf("  Phone: %s\n", arr[i].phone_number);
        printf("  Employment: %s\n", arr[i].employment_date);
        printf("----------------------------\n");
    }
    printf("\n");
}

int linear_search(School *array, long n, const char *key) {
    for (long i = 0; i < n; i++) {
        if (strcmp(array[i].full_name, key) == 0) {
            return i;
        }
    }
    return -1;
}

BSTNode* BSTInsert(BSTNode *root, School data) {
    if (root == NULL) {
        BSTNode *newNode = (BSTNode*)malloc(sizeof(BSTNode));
        newNode->data = data;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    int cmp = strcmp(data.full_name, root->data.full_name);
    if (cmp < 0)
        root->left = BSTInsert(root->left, data);
    else
        root->right = BSTInsert(root->right, data);
    return root;
}

BSTNode* BSTSearch(BSTNode *root, const char *key) {
    if (root == NULL) return NULL;
    int cmp = strcmp(key, root->data.full_name);
    if (cmp == 0)
        return root;
    else if (cmp < 0)
        return BSTSearch(root->left, key);
    else
        return BSTSearch(root->right, key);
}

void freeBST(BSTNode *root) {
    if (root == NULL) return;
    freeBST(root->left);
    freeBST(root->right);
    free(root);
}

void leftRotate(RBNode **root, RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rightRotate(RBNode **root, RBNode *y) {
    RBNode *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;
    x->right = y;
    y->parent = x;
}

void RBInsertFixup(RBNode **root, RBNode *z) {
    while (z->parent != NULL && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode *y = z->parent->parent->right;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            RBNode *y = z->parent->parent->left;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

void RBInsert(RBNode **root, School data) {
    RBNode *z = (RBNode*)malloc(sizeof(RBNode));
    z->data = data;
    z->color = RED;
    z->left = z->right = z->parent = NULL;
    RBNode *y = NULL;
    RBNode *x = *root;
    while (x != NULL) {
        y = x;
        if (strcmp(z->data.full_name, x->data.full_name) < 0)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == NULL)
        *root = z;
    else if (strcmp(z->data.full_name, y->data.full_name) < 0)
        y->left = z;
    else
        y->right = z;
    RBInsertFixup(root, z);
}

RBNode* RBSearch(RBNode *root, const char *key) {
    if (root == NULL) return NULL;
    int cmp = strcmp(key, root->data.full_name);
    if (cmp == 0)
        return root;
    else if (cmp < 0)
        return RBSearch(root->left, key);
    else
        return RBSearch(root->right, key);
}

void freeRBTree(RBNode *root) {
    if (root == NULL) return;
    freeRBTree(root->left);
    freeRBTree(root->right);
    free(root);
}

void benchmark_search() {
    const long sizes[] = {100, 1000, 10000, 50000, 100000, 200000, 300000};
    const int num_sizes = sizeof(sizes)/sizeof(sizes[0]);
    const int iterations = 1000; // Количество повторов для малых n

    for (int i = 0; i < num_sizes; i++) {
        const long n = sizes[i];
        School *arr = genArray(n);
        int random_index = rand() % n;
        char key[MAX_LENGTH];
        strcpy(key, arr[random_index].full_name);

        // Линейный поиск
        clock_t start = clock();
        for (int k = 0; k < iterations; k++) {
            linear_search(arr, n, key);
        }
        double linear_time = (double)(clock() - start) / CLOCKS_PER_SEC / iterations;

        // BST
        BSTNode *bstRoot = NULL;
        for (long j = 0; j < n; j++) bstRoot = BSTInsert(bstRoot, arr[j]);
        
        start = clock();
        for (int k = 0; k < iterations; k++) {
            BSTSearch(bstRoot, key);
        }
        double bst_time = (double)(clock() - start) / CLOCKS_PER_SEC / iterations;
        freeBST(bstRoot);

        // RBTree
        RBNode *rbRoot = NULL;
        for (long j = 0; j < n; j++) RBInsert(&rbRoot, arr[j]);
        
        start = clock();
        for (int k = 0; k < iterations; k++) {
            RBSearch(rbRoot, key);
        }
        double rb_time = (double)(clock() - start) / CLOCKS_PER_SEC / iterations;
        freeRBTree(rbRoot);

        free(arr);
        printf("n=%ld: Linear=%.6f, BST=%.6f, RBTree=%.6f\n", n, linear_time, bst_time, rb_time);
    }
}