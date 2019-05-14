#include <stdio.h>
#include<math.h>


int min,max,*tabl, n;

int minimum(int *tab, int n) {
    int m =tabl[0];  //poprawa
    int i =0;
    for (i=0; i<n; i++) {
        if (m> tabl[i])
            m = tabl[i];
    }
    return m;
}

int maksimum(int *tab, int n) {
    int m =0;
    int i =0;
    for (i=0; i<n; i++) {
        if (m< tabl[i])
            m = tabl[i];
    }
    return m;
}

int sredni(int *tab, int n) {
    int avg =0;
    int i =0;
    for (i=0; i<n; i++) {
        avg+=tabl[i];
    }
    
    return avg/n;
}


int main ()
{
    printf("Tablice... znajdz wszystkie bledy :)\n");
    printf("Podaj Dlugosc tablicy od 0 do 100 \n");
    scanf("%d", &n);
    
    tabl = new int[n];
    printf("Podaj 1 element tablicy \n");
    scanf("%d", &tabl[0]); //tablica w c++ jest indeksowana od 0
    
    int i=0;
    for (int i=1; i<n; i++) { //poprawa
        printf("Podaj %d element tablicy \n", i+1); //poprawa
        scanf("%d", &tabl[i]);
    }

    printf("min tablicy to: %d\n", minimum(tabl, n));
    printf("max tablicy to: %d\n", maksimum(tabl, n));
    printf("avg tablicy to: %d\n", sredni(tabl, n));
    
    return 0;
}
