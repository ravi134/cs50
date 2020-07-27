#include <stdio.h>
#include <stdlib.h>
#define BLOCK 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover file\n");
        return 1;
    }

    FILE *cardraw = fopen(argv[1], "r");
    if (cardraw == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }

    unsigned char buf[BLOCK];
    int cnt = 0;
    FILE *jpegs;
    char in[8];

    while (fread(buf, 1, BLOCK, cardraw) == BLOCK)
    {
        if (buf[0] == 0xff && buf[1] == 0xd8 &&
            buf[2] == 0xff && (buf[3] & 0xf0) == 0xe0)
        {
            if (cnt == 0)
            {
                sprintf(in, "%03i.jpg", cnt);
                cnt ++;
                jpegs = fopen(in, "w");
                fwrite(buf, 1, BLOCK, jpegs);
            }
            else if (cnt > 0)
            {
                fclose(jpegs);
                sprintf(in, "%03i.jpg", cnt);
                cnt ++;
                jpegs = fopen(in, "w");
                fwrite(buf, 1, BLOCK, jpegs);
            }
        }
        else if (cnt > 0)
            fwrite(buf, 1, BLOCK, jpegs);
    }
    fclose(jpegs);
    fclose(cardraw);
    return 0;
}