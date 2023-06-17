#include <stdio.h>
#include <stdlib.h>
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
            char first_digit = line[0];
            if (atoi(&first_digit) % 2 == 0) // if ((first_digit - '0') % 2 == 0)
                printf("fata\n");
            else 
                printf("baiat\n");
        }
    }
    
    while (wait(NULL) > 0);
    
    fclose(file);

    return 0;
}
