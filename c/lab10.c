#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE_LENGTH 250

int main(int argc, char* argv[]) 
{
    setbuf(stdout, NULL);

    if (argc < 2) 
    {
        fprintf(stderr, "parametru invalid");
        return 1;
    }
    
    char* dirname = argv[1];
    
    for (int i = 2; i < argc; i++) 
    {   
        char filePath[MAX_LINE_LENGTH];
        snprintf(filePath, sizeof(filePath), "%s/%s", dirname, argv[i]);
        FILE* file = fopen(filePath, "r");
        
        if (!file)
        {
            fprintf(stderr, "parametru invalid");
            return 1;
        }
        
        int pipefd[2];  
        if (pipe(pipefd) == -1) 
	{
            fprintf(stderr, "Pipe failed\n");
            return 1;
        }
        
        pid_t pid = fork();
		
        if (pid < 0) 
	{
            fprintf(stderr, "Fork failed\n");
            return 1;
        }
        
        if (pid == 0) 
	{
            close(pipefd[0]);  
            
            int count = 0;
            char line[MAX_LINE_LENGTH];
            
            while (fgets(line, sizeof(line), file) != NULL)
            {
                count++;
            }
			
            write(pipefd[1], &count, sizeof(int));
            close(pipefd[1]); 
            exit(1); 
        }
        else 
	{
            close(pipefd[1]); 
            
            int result;
            read(pipefd[0], &result, sizeof(int));
            printf("%d\n", result-1);  
            
            close(pipefd[0]); 
        }
        
        fclose(file);
    }
    
    while (wait(NULL) > 0); 
    
    return 0;
}
