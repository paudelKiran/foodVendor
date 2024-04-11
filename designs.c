#include <stdio.h>
// void homePage()
// {
//     printf("     _______              _    _    _               _\n");
//     printf("     _______              _    _    _               _\n");
//     printf("    (_______)            | |  | |  | |             | |\n");
//     printf("     _____ ___   ___   _ | |  | |  | |___ ____   _ | | ___   ____\n");
//     printf("    |  ___) _ \ / _ \ / || |   \ \/ / _  )  _ \ / || |/ _ \ / ___)\n");
//     printf("    | |  | |_| | |_| ( (_| |    \  ( (/ /| | | ( (_| | |_| | | \n");
//     printf("    |_|   \___/ \___/ \____|     \/ \____)_| |_|\____|\___/|_| \n");
// }

void print(char *temp)
{
    printf("%c", temp[2]);
}

int main()
{
    char temp[6];
    printf("hello :");
    scanf("%s", temp);
    print(temp);
}