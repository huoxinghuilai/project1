#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
        char *cmd1 = "wo shi shui?";
        char *cmd2[50];
        char *flag1, *flag2;
        int i = 0;
        int n = 0;
        flag2 = flag1 = cmd1;
        while (*flag1 != '\0')
        {
                if(*flag1 == ' ')
                {
                        cmd2[i] = (char *)malloc(sizeof(char) * (n + 1));
                        strncpy(cmd2[i], flag2, n);
                        strcat(cmd2[i], "\0");
                        printf("%s\n", cmd2[i]);
                        flag2 = flag2 + n + 1;
                        i++;
                        flag1++;
                        n = 0;
                        continue;
                }
                flag1++;
                n++;
        }

        cmd2[i] = (char *)malloc(sizeof(char) * (n + 1));
        strncpy(cmd2[i], flag2, n);
        strcat(cmd2[i], "\0");
	printf("%s\n", cmd2[i]);
}




