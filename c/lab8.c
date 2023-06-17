#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 250

int main(int argc, char* argv[]) 
{
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
            fclose(file);
            return 1;
        }
        
        int count = 0;
        char line[MAX_LINE_LENGTH];
        
        while (fgets(line, sizeof(line), file) != NULL)
        {
            count++;
        }
            
        printf("%d\n", count - 1);
        fclose(file);
    }
    
    return 0;
}
