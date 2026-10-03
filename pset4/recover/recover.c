#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int BLOCK_SIZE = 512;

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    /* Accept exactly one command-line argument, the name of a
    forensic image from which to recover JPEGs. */
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");

        return 1;
    }
    
    FILE *in_file = fopen(argv[1], "r");

    if (in_file == NULL)
    {
        printf("Could not open file\n");

        return 1;
    }
    
    BYTE buffer[BLOCK_SIZE];
    int img_count = 0; // Number of images recovered.
    FILE *out_file = NULL;
    char *out_file_name = malloc(8 * sizeof(char));

    while (fread(buffer, BLOCK_SIZE, 1, in_file))
    {        
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff
            && (buffer[3] & 0xf0) == 0xe0)
        {
            if (out_file != NULL)
            {
                fclose(out_file);
            }
            
            sprintf(out_file_name, "%03d.jpg", img_count);
            out_file = fopen(out_file_name, "w");
            img_count++;
        }
        
        if (out_file != NULL)
        {
            fwrite(buffer, BLOCK_SIZE, 1, out_file);
        }
    }
    
    free(out_file_name);
    fclose(in_file);
    fclose(out_file);

    return 0;
}