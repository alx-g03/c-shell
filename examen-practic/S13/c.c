#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "parametru invalid");
        return 1;
    }
    
    FILE* file = fopen(argv[1], "r");
    
    setbuf(file, NULL); ///!!!
    
    int x = atoi(argv[2]); ///!!!
    
    if (!file)
    {
        fprintf(stderr, "parametru invalid");
        return 1;
    }
    
    char line[255];
    
    while (fgets(line, sizeof(line), file) != NULL)
    {
        pid_t pid = fork();
        
        if (pid < 0)
        {
            fprintf(stderr, "Fork failed\n");
            return 1;
        } 
        else if (pid == 0)
        {
            if (strlen(line) - 1 > x)
            {
                printf("%s", line);
            }
            exit(0); ///!!!
        } 
    }
    
    fclose(file);
    
    while (wait(NULL) > 0); ///!!!
    
    return 0;
}
