// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

typedef uint8_t ubyte1;
typedef int16_t byte2;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    ubyte1 *BYTE = malloc(HEADER_SIZE + 1);
    for (int i = 0; i < HEADER_SIZE; i++)
    {
        fread(&BYTE[i], sizeof(ubyte1), 1, input);
    }

    for (int i = 0; i < HEADER_SIZE; i++)
    {
        fwrite(&BYTE[i], sizeof(ubyte1), 1, output);
    }
    // Read samples from input file and write updated data to output file
    byte2 BYT;

    while (fread(&BYT, sizeof(byte2), 1, input) != 0)
    {
        BYT = BYT * factor;
        fwrite(&BYT, sizeof(byte2), 1, output);
    }

    free(BYTE);

    // Close files
    fclose(input);
    fclose(output);
}
