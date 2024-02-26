#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define BLOCK_SIZE 512
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    int i = 0;         // iteration to name the jpg files
    char FILE_NAME[8]; // to use with sprintf

    // create input and output file pointers
    FILE *PIF = fopen(argv[1], "r");
    FILE *POF = NULL;
    if (PIF == NULL)
    {
        printf("could not open the file %s.\n", argv[1]);
        return 2;
    }

    uint8_t BUFFER[BLOCK_SIZE];
    while (fread(BUFFER, BLOCK_SIZE, 1, PIF) == 1)
    {
        // check if the file is jpg
        if ((BUFFER[0] == 0xFF) && (BUFFER[1] == 0xD8) && (BUFFER[2] == 0XFF) && ((BUFFER[3] & 0xF0) == 0xE0))
        {
            // close any previous opened files
            if (POF != NULL)
            {
                fclose(POF);
            }
            // creat new name for file
            sprintf(FILE_NAME, "%03i.jpg", i++);
            // open the new-name file
            POF = fopen(FILE_NAME, "w");
            if (POF == NULL)
            {
                printf("can't open file \n");
                fclose(PIF);
                return 3;
            }
            // form the image
            fwrite(BUFFER, BLOCK_SIZE, 1, POF);
        }
        else
        {
            // check for a NOT JPG format file to append it to opened jpg or to search for jpg one
            if (POF != NULL)
            {
                // append this file to already opened jpg file
                fwrite(BUFFER, BLOCK_SIZE, 1, POF);
            }
            else
            {
                continue;
            }
        }
    }
    fclose(PIF);
    fclose(POF);
    return 0;
}
