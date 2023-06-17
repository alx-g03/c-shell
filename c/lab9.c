#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 250

void processFile(const char* dirname, const char* filename, int* errorFlag) 
{
    char filePath[MAX_LINE_LENGTH];
    snprintf(filePath, sizeof(filePath), "%s/%s", dirname, filename);
    FILE* file = fopen(filePath, "r");
    
    if (!file) 
    {
        fprintf(stderr, "parametru invalid");
        *errorFlag = 1;
        return;
    }
    
    int count = 0;
    char line[MAX_LINE_LENGTH];
    
    while (fgets(line, sizeof(line), file) != NULL) 
    {
        count++;
    }
    
    printf("%d\n",count - 1);
    fclose(file);
}

int main(int argc, char* argv[]) 
{
    if (argc < 2) 
    {
        fprintf(stderr, "parametru invalid");
        return 1;
    }
    
    char* dirname = argv[1];
    int errorFlag = 0;
    
    for (int i = 2; i < argc; i++) 
    {
        pid_t pid = fork();
        
        if (pid < 0) 
        {
            fprintf(stderr, "Fork failed\n");
            return 1;
        } 
        else if (pid == 0) 
        {
            processFile(dirname, argv[i], &errorFlag);
            return errorFlag;
        }
        
        int status;
        wait(&status);
        
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) 
        {
            errorFlag = 1;
            break;
        }
    }
    
    return 0;
}
