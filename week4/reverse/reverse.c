#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage : ./reverse input_file output_file\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *PIF = fopen(argv[1], "r");
    if (PIF == NULL)
    {
        printf("cant't open %s file\n", argv[1]);
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER BUFFER;

    fread(&BUFFER, sizeof(WAVHEADER), 1, PIF);

    // Use check_format to ensure WAV format
    // TODO #4
    if (!(check_format(BUFFER)))
    {
        printf(" not supported format\n");
        return 2;
    }

    // Open output file for writing
    // TODO #5
    FILE *POF = fopen(argv[2], "w");
    if (POF == NULL)
    {
        printf("can't open %s file\n", argv[2]);
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&BUFFER, sizeof(WAVHEADER), 1, POF);

    // Use get_block_size to calculate size of block
    // TODO #7
    int BLOCK_SIZE = get_block_size(BUFFER);

    // Write reversed audio to file
    // TODO #8

    // create a buffer to read into
    BYTE TRANS[BLOCK_SIZE];
    // set cursor before last block of data
    fseek(PIF, -1 * BLOCK_SIZE, SEEK_END);
    // iterate untill the cursor pass the header from left
    while (ftell(PIF) >= sizeof(BUFFER))
    {

        fread(TRANS, sizeof(TRANS), 1, PIF);
        fwrite(TRANS, sizeof(TRANS), 1, POF);
        fseek(PIF, -2 * BLOCK_SIZE, SEEK_CUR);
    }

    // ////////////////==================//////////////////////////
    // ===== this is one of my unsuccessful trial :( ===////
    // // get length of data blocks
    // fseek(PIF, 0, SEEK_END);
    // long int length = ftell(PIF) - sizeof(BUFFER);
    // // create a buffer to read into
    // BYTE TRANS[BLOCK_SIZE];
    // // iterate along the length of data
    // // fseek(PIF, -1 * BLOCK_SIZE, SEEK_END);
    // for (int i = 1; i <= length; i++)
    // {
    //     fseek(PIF, -i * BLOCK_SIZE, SEEK_END);
    //     fread(TRANS, sizeof(TRANS), 1, PIF);
    //     fwrite(TRANS, sizeof(TRANS), 1, POF);
    // }

    // /////////============================/////////////////////////

    // close opened files
    fclose(POF);
    fclose(PIF);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    if ((header.format[0] == 'W') && (header.format[1] == 'A') && (header.format[2] == 'V') && (header.format[3] == 'E'))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return (header.numChannels * (header.bitsPerSample / 8));
}