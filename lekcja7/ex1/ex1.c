/* Ponizszy program prosi uzytkownika o podanie imienia, wita go i podaje
   jego real ID. Mozna by oczekiwac, ze w przypadku imienia 16-literowego
   lub dluzszego, zmienna uid zostanie nadpisana i program wypisze niepra-
   widlowy ID uzytkownika. Tak sie jednak nie dzieje. Uzywajac gdb wyja-
   snij, dlaczego.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

struct user_info
{
    uid_t uid;
    char name[16];
};

int main(int argc, char *argv[])
{
    struct user_info info;
    info.uid = getuid();

    printf("Podaj imie: ");
    scanf("%s", info.name);
    printf("Witaj, %s!\nTwoj UID to %d.\n", info.name, (int) info.uid);
    return 0;
}

