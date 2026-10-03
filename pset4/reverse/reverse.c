#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");

        return 1;
    }

    // Open input file for reading
    FILE* in_file = fopen(argv[1], "r");

    if (in_file == NULL)
    {
        printf("Could not open file\n");

        return 1;
    }

    // Read header
    WAVHEADER header;
    int header_size = sizeof(WAVHEADER);
    fread(&header, header_size, 1, in_file);

    // Use check_format to ensure WAV format
    if (!check_format(header))
    {
        printf("Input is not a WAV file\n");

        return 1;
    }
    
    // Open output file for writing
    FILE* out_file = fopen(argv[2], "w");

    if (out_file == NULL)
    {
        printf("Could not open file\n");

        return 1;
    }
    
    // Write header to file
    fwrite(&header, header_size, 1, out_file);

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(header);

    // Write reversed audio to file
    BYTE buffer[block_size];
    fseek(in_file, 0, SEEK_END);
    int block = (ftell(in_file) - header_size) / block_size;

    for (int i = block - 1; i >= 0; i--)
    {
        fseek(in_file, header_size + i*block_size, SEEK_SET);
        fread(buffer, block_size, 1, in_file);
        fwrite(buffer, block_size, 1, out_file);
    }
    
    fclose(in_file);
    fclose(out_file);

    return 0;
}

int check_format(WAVHEADER header)
{
    BYTE wav[] = {'W', 'A', 'V', 'E'};

    for (int i = 0; i < 4; i++)
    {
        if (header.format[i] != wav[i])
        {
            return 0;
        }
    }
    
    return 1;
}

int get_block_size(WAVHEADER header)
{
    int bytes_per_sample = header.bitsPerSample / 8;
    int block_size = header.numChannels * bytes_per_sample;

    return block_size;
}