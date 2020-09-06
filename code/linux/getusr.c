#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>


int main(void)
{
    char *login;
    struct passwd *pentry;

    if ((login = getlogin()) == NULL)
    {
        perror("getlogin");
        exit(EXIT_FAILURE);
    }

    if ((pentry = getpwnam(login)) == NULL)
    {
        perror("getpwdnam");
        exit(EXIT_FAILURE);
    }

    printf("user name: %s\n", pentry->pw_name);
    printf("uid      : %d\n", pentry->pw_uid);
    printf("gid      : %d\n", pentry->pw_gid);
    printf("gecos    : %s\n", pentry->pw_gecos);
    printf("home dir : %s\n", pentry->pw_dir);
    printf("passwd   : %s\n", pentry->pw_passwd);
    printf("shell    : %s\n", pentry->pw_shell);

    exit(EXIT_SUCCESS);
}