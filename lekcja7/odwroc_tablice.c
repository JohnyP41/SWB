#include <stdio.h>
#include<math.h>

void wyswietl(int *t, int length) {
   printf("\n");
   int i=0;
   for (int i=0; i<length; i++) {
      printf("%d ", t[i]);
   }
}

int main ()
{
    int n=0;
    printf("Tablice... znajdz wszystkie bledy :)\n");
    printf("Podaj Dlugosc tablicy od 0 do 100 \n");
    scanf("%d", &n);
    
    int *tablica = new int[n];
    int i =0;
    for(int i=0; i<n; i++) {
      tablica[i]=i;
    }
    
    
    
    printf("Aktualna tablica to:  \n");
    wyswietl(tablica, n); //wyswietlamy cala tablice
    
    printf("\n odracamy tabice");
    
   ///błednie napisane odwracanie
    for (int i=0; i<n/2; i++) {
       int temp = tablica[n-i-1];
       tablica[n-i-1] = tablica[i];
       tablica[i] = temp;
    }
    
    printf("Odwrocana tablica to: wszystko ok?: ");
    wyswietl(tablica, n);
    return 0;
}
