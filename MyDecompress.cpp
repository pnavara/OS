#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int fileParse(FILE* destination, FILE* decomp, char fName[])
{

    if (destination == NULL)
    {
        return -1;
    }

    char arr[128];
    int count = 0;
    int begin = -1;
    int end = -1;

    while (!feof(destination))
    {
        bool printed = false;

	//if no elements,exit
        if ((fscanf(destination, "%s", arr)) != 1)
        {
            break;
        }

        count++;//display

        for (int i = 0; i < strlen(arr); i++)
        {
            if (arr[i] == '+' || arr[i] == '-')
            {

                //setting index
                if (begin == -1)
                {
                    begin = i;
                }
              
                else
                {
                    end = i;
                }

                if (end != -1)
                {
                    int var = 0;

                    //convert chars into an ints
                    for(int j = begin + 1; j < end; j++)
                    {
                        var = var * 10 + ( arr[j] - '0' );
                    }
                    
                    //replace '-' with 0s
                    if (arr[begin] == '-')
                    {
                        for ( int k = 0; k < var; k++)
                        {
                            fprintf(varomp, "%s", "0");
                        }
                    }

                    //replace '+' with 0s
                    else if (arr[begin] == '+')
                    {
                        for ( int k = 0; k < var; k++)
                        {
                            fprintf(decomp, "%s", "1");
                        }
                    }

                    end = -1;
                    begin = -1;
                }
            }
            else {

                if (begin == -1 && end == -1)
                {
                    fprintf(decomp, "%c", arr[i]);
                }
            }
        }
        
        fprintf(decomp, "\n");
    }

    fclose(decomp);
    fclose(destination);

    return 0;

}

int main(int argc, char* argv[])
{
    FILE * destination;
    FILE * decomp;

    if (argc == 3)
    {
        char* fName = argv[1];
        char* outFName = argv[2];
        destination = fopen(fName,"r");

        if (destination == NULL)
        {
            perror("Error opening file.\n");
            return -1;
        }
    
        decomp = fopen(outFName, "w");

        //parse the file
        if (fileParse(destination, decomp, fName) == -1)
        {
            perror("Error Parsing File");
            return -1;
        }

        printf("Decompress Completed\n");
    }
    else
    {
        perror("Enter input and outpu files\n");
        return -1;
    }

    return 0;
}
