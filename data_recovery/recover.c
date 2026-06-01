#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check for appropriate usage
    if (argc != 2)
    {
        printf("Usage: ./recover [filename]\n");
        return 1;
    }

    // Open files
    char *filename = argv[1];
    FILE *src = fopen(filename, "rb");
    if (src == NULL)
    {
        printf("Cannot open file.\n");
        return 1;
    }

    // Malloc for buffer
    BYTE *buffer = malloc(513 * sizeof(BYTE));
    BYTE *buffer1 = malloc(513 * sizeof(BYTE));
    char *name = malloc(8 * sizeof(char));

    // Read from argv[1]
    int img = -1;
    while (fread(buffer, sizeof(BYTE), 512, src) != 0)
    {
        if (img < 0)
        {
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
                (buffer[3] & 0xf0) == 0xe0)
            {
                img += 1;
                sprintf(name, "%03i.jpg", img);
                FILE *dst = fopen(name, "wb");
                if (dst == NULL)
                {
                    printf("Cannot open file.\n");
                    return 1;
                }
                if (img != 0)
                {
                    fwrite(buffer1, sizeof(BYTE), 512, dst);
                }

                fwrite(buffer, sizeof(BYTE), 512, dst);

                while (fread(buffer1, sizeof(BYTE), 512, src) != 0)
                {
                    if ((buffer1[0] != 0xff || buffer1[1] != 0xd8 || buffer1[2] != 0xff ||
                         (buffer1[3] & 0xf0) != 0xe0))
                    {
                        fwrite(buffer1, sizeof(BYTE), 512, dst);
                    }
                    if (buffer1[0] == 0xff && buffer1[1] == 0xd8 && buffer1[2] == 0xff &&
                        (buffer1[3] & 0xf0) == 0xe0)
                    {

                        break;
                    }
                }

                fclose(dst);
            }
            else
            {
                continue;
            }
        }

        else
        {
            img += 1;
            sprintf(name, "%03i.jpg", img);
            FILE *dst = fopen(name, "wb");
            if (dst == NULL)
            {
                printf("Cannot open file.\n");
                return 1;
            }
            if (img != 0)
            {
                fwrite(buffer1, sizeof(BYTE), 512, dst);
            }

            fwrite(buffer, sizeof(BYTE), 512, dst);

            while (fread(buffer1, sizeof(BYTE), 512, src) != 0)
            {
                if ((buffer1[0] != 0xff || buffer1[1] != 0xd8 || buffer1[2] != 0xff ||
                     (buffer1[3] & 0xf0) != 0xe0))
                {
                    fwrite(buffer1, sizeof(BYTE), 512, dst);
                }
                if (buffer1[0] == 0xff && buffer1[1] == 0xd8 && buffer1[2] == 0xff &&
                    (buffer1[3] & 0xf0) == 0xe0)
                {

                    break;
                }
            }

            fclose(dst);
        }
    }

    // Clean-up
    fclose(src);
    free(buffer);
    free(buffer1);
    free(name);

    return 0;
}
