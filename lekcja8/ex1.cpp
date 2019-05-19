#include <cstdlib>
#include <ctime>
#include <cstdio>
#define SIZE 1000000

void init_tab_with_zeros(int *tab, int n) {
    for (int i = 0; i < n; i++) {
        tab[i] = 0;
    }
}

bool zeros_in_tab(int *tab, int n) {
    for (int i = 0; i < n; i++) {
        if (tab[i] == 0) {
            return true;
        }
    }
    return false;
}

void insert_random_values(int *tab, int n) {
    for (int i = 1; i <= n; i++) {
        int pos = rand() % n;
        tab[pos] = i;
    }
}

void init_tab(int *tab, int n) {
    for(int i=0;i<n;i++)
        tab[i]=i;
}

void print_tab(int *tab, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

void swap(int *tab, int i, int j) {
    int tmp = tab[i];
    tab[i] = tab[j];
    tab[j] = tmp;
}

int choose_index(int l, int r) {
    return l + (r-l) / 2;
}

int divide(int *tab, int l, int r) {
    int index = choose_index(l, r);
    int val = tab[index];
    swap(tab, index, r);
    int pos = l;
    for (int i = l; i < r; i++) {
        if (tab[i] < val) {
            swap(tab, i, pos);
            pos++;
        }
    }
    swap(tab, pos, r);
    return pos;
}

void quicksort(int *tab, int l, int r) {
    if (l < r) {
        int i = divide(tab, l, r);
        quicksort(tab, l, i-1);
        quicksort(tab, i+1, r);
    }
}

void sort(int *tab, int n) {
    quicksort(tab, 0, n-1);
}

int compare( const void* a, const void* b ) { 
     int* arg1 = (int*) a;
     int* arg2 = (int*) b;
     if( *arg1 < *arg2 ) return -1;
     else if( *arg1 == *arg2 ) return 0;
     else return 1;
}

int main() {
    srand(time(NULL));

    int tab[SIZE];
    init_tab(tab, SIZE);

    print_tab(tab, SIZE);

    qsort(tab,SIZE,sizeof(int),compare);

    print_tab(tab, SIZE);

    return 0;
}
