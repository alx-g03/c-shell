#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_LINE_LENGTH 250
#define FIFO_NAME "myfifo"

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
        
        int fd; 
        mkfifo(FIFO_NAME, 0666);      
        
        pid_t pid = fork();
		
        if (pid < 0) 
	{
            fprintf(stderr, "Fork failed\n");
            return 1;
        }
        
        if (pid == 0) 
	{
            fd = open(FIFO_NAME, O_WRONLY);
            
            int count = 0;
            char line[MAX_LINE_LENGTH];
            
            while (fgets(line, sizeof(line), file) != NULL)
            {
                count++;
            }
            write(fd, &count, sizeof(int));
			
            close(fd);  
            
            exit(1);  
        }
        else 
	{
            fd = open(FIFO_NAME, O_RDONLY);
            
            int result;
            read(fd, &result, sizeof(int));
            
            printf("%d\n", result - 1);  
            
            close(fd);  
        }
        
        fclose(file);
    }
    
    while (wait(NULL) > 0);  
    
    return 0;
}
