#include <stdio.h>
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
            return 1;
        } 
        else if (pid == 0) 
        {
            for (int i = 0; i < strlen(line); i++)
                if (line[i] == '0' || line[i] == '1' || line[i] == '2' || line[i] == '3' || line[i] == '4' || line[i] == '5' || line[i] == '6' || line[i] == '7' || line[i] == '8' || line[i] == '9')
                    printf("%c\n", line[i]);
        }
    }
    
    while (wait(NULL) > 0);

    fclose(file);

    return 0;
}
