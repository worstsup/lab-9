#ifndef DATABASE_H
#define DATABASE_H

#define MAX_LENGTH 40
#define MAXWORD 100

typedef struct {
	char full_name[MAX_LENGTH];
	char qualification[MAX_LENGTH];
	char home_address[MAX_LENGTH];
	char date_birth[MAX_LENGTH];
	char phone_number[MAX_LENGTH];
	char employment_date[MAX_LENGTH];
} School;

typedef struct BSTNode {
    School data;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

typedef enum { RED, BLACK } Color;

typedef struct RBNode {
    School data;
    Color color;
    struct RBNode *left;
    struct RBNode *right;
    struct RBNode *parent;
} RBNode;

School* genArray (long n);
School* copyArray(School *a, long n);
int compare_up(const void* p1, const void* p2);
int compare_down(const void* p1, const void* p2);
int compare_up_wrapper(const School* a, const School* b);
int compare_down_wrapper(const School* a, const School* b);
void checkSort(const char *algName, void (*sort)(School*, long, int (*compare)(const School*, const School*)), School *a, long n, int (*compare)(const School*, const School*));
void shaker_sort(School* a, long n, int (*compare)(const School*, const School*));
void merge(School* a, long low, long mid, long high, int (*compare)(const School*, const School*));
School* merge_sort(School* a, long low, long high, int (*compare)(const School*, const School*));
void merge_sort1(School* a, long n, int (*compare)(const School*, const School*));
void qSort(School* a, int first, int last, int (*compare)(const School*, const School*));
void quick_sort(School* a, long n, int (*compare)(const School*, const School*));
void generate_full_name(char* full_name);
void generate_quailification(char* qualification);
void generate_home_adress(char* home_address);
void generate_date_birth(char* date_birth);
void generate_phone_number(char* phone_number);
void generate_employment_date(char* employment_date);
void printSchoolArray(const School* arr, long n, const char* title);

int linear_search(School *array, long n, const char *key);
BSTNode* BSTInsert(BSTNode *root, School data);
BSTNode* BSTSearch(BSTNode *root, const char *key);
void freeBST(BSTNode *root);
void RBInsert(RBNode **root, School data);
RBNode* RBSearch(RBNode *root, const char *key);
void freeRBTree(RBNode *root);
void benchmark_search();
void RBInsertFixup(RBNode **root, RBNode *z);

void EmitSortMenu();
void EmitSearchMenu();

#endif