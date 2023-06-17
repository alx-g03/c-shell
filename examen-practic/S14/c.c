#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "parametru invalid");
        return 1;
    }
    
    FILE* file = fopen(argv[1], "r");
    
    if (!file)
    {
        fprintf(stderr, "parametru invalid");
        return 1;
    }
    
    setbuf(file, NULL);
    
    char line[255];
    int noline = 1;
    
    while (fgets(line, sizeof(line), file) != NULL)
    {
        pid_t pid = fork();
        
        if (pid < 0)
        {
            fprintf(stderr, "parametru invalid");
            return 1;
        }
        else if (pid == 0)
        {
            int param = 1;
            int x1, y1, x2, y2, x3, y3;
            
            char* token = strtok(line, " ");
            
            while (token)
            {
                if (param == 1)
                {
                    x1 = atoi(token);
                }
                
                if (param == 2)
                {
                    y1 = atoi(token);
                }
                
                if (param == 3)
                {
                    x2 = atoi(token);
                }
                
                if (param == 4)
                {
                    y2 = atoi(token);
                }
                
                if (param == 5)
                {
                    x3 = atoi(token);
                }
                
                if (param == 6)
                {
                    y3 = atoi(token);
                }
                
                param++;
                token = strtok(NULL, " ");
            }
            if ((y3 - y1) / (y2 - y1) == (x3 - x1) / (x2 - x1))
            {
                //printf("%i\n", noline);
                printf("yes\n");
            }
            else
            {
                printf("no\n");
            }
            
            noline++;
        }
    }
    
    while (wait(NULL) > 0);
    
    fclose(file);
    
    return 0;
}
