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
    
    while (fgets(line, sizeof(line), file) != NULL)
    {
        pid_t pid = fork();
        
        if (pid < 0)
        {
            fprintf(stderr, "Fork failed\n");
            fclose(file);
            return 1;
        }
        else if (pid == 0)
        {
            int count = 0;
            char* token = strtok(line, " ");
            while (token)
            {
                count++;
                token = strtok(NULL, " ");
            }
            
            printf("%i\n", count);
        }
    }
    
    while (wait(NULL) > 0);
    
    fclose(file);

    return 0;
}
