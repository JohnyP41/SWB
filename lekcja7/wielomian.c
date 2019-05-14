#include <stdio.h>
#include<math.h>

int a,b,c,d;
int delta(int a, int b,int c)
{
    return b*b-4*a*c;
}

float e(int a,int  b)
{
    return ((-b)/(2*a));
}

float pierwX1(int  a, int  b, int  delta)
{
    return (-b+sqrt(delta))/(2*a);
}

float pierwX2(int  a, int  b, int  delta)
{
    return (-b-sqrt(delta))/(2*a);
}
int xliniowe(int c, int b)
{
    return -c/b;
}

int main ()
{
    printf("Rownanie kwadratowe: a*x*x+b*x+c=0 \n");
    printf("Podaj a: ");
    scanf("%d", &a);
    printf("Podaj b: ");
    scanf("%d", &b);
    printf("Podaj c: ");
    scanf("%d", &c);
    printf("Podaj a: ");
    
    if (delta(a,b,c)<0){
        printf("Rownanie nie ma rozwiazan \n)");
    } else if (delta(a,b,c)==0) {
            printf("Jest tylko jedno rozwiazanie:\n x= %f",e(a,b));
        printf("\n");
    } else if (delta(a,b,c)>0 && a!=0) {  //poprawa dopisac warunek
        printf("Sa dwa rozwiazania rowne: \n x1=%f",pierwX1(a,b,delta(a,b,c)));
        printf("x2=%f, ", pierwX2(a,b,delta(a,b,c)));
        printf("\n");
    }

    if (a==0) {
        printf("X jest rowne: %d \n", xliniowe(c,b));
    } else {
        d=delta(a,b,c);
        printf("Delta rownania wynosi: %d \n", d);
    }
    return 0;
}
