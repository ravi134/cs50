#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
FILE *pf;
FILE *img;

int main(int argc, char *argv[])
{
    if (argc != 2)
        printf("Usage: ./recover image\n");

    BYTE buffer[512];
    pf = fopen(argv[1], "r");
    int ct = 0;
    char fname[8];

    while(fread(buffer, 512, 1, pf))
    {
        if (pf == NULL)
            return 1;

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] && 0xf0 == 0xe0)
        {

            if (img != NULL)
            {
                fclose(img);
                ct += 1;
            }

            sprintf(fname,"%03i.jpg", ct);
            img = fopen(fname,"w");
            fwrite(buffer, sizeof(buffer), 1, img);
        }
        else if (img != NULL)
            fwrite(buffer, sizeof(buffer), 1, img);
    }

    fclose(pf);
    fclose(img);
    return 0;
}