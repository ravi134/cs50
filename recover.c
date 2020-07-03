#include <stdio.h>
#include <stdlib.h>

#define BLOCK 512

int main(int argc, char *argv[])
{

    //check to make sure image is in command line
    if (argc != 2)
    {
        printf("Usage: ./recover file\n");
        return 1;
    }

    //open image and check to make sure image is valid
    FILE *cardraw = fopen(argv[1], "r");

    //exit with error if invalid
    if (cardraw == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }

    //establish the buffer
    unsigned char buffer[BLOCK];

    //image counter
    int counter = 0;

    //file pointer to write the JPEGS too
    FILE *jpegs;

    //array to hold file name
    char imagename[8];

    //repeat until end of card
    while (fread(buffer, 1, BLOCK, cardraw) == BLOCK)
    {
        //read 512 Bytes into a buffer and check if its the start of a jpeg
        if (buffer[0] == 0xff
            && buffer[1] == 0xd8
            && buffer[2] == 0xff
            && (buffer[3] & 0xf0) == 0xe0)
        {
            //if first jpeg
            if (counter == 0)
            {
                //make the first file
                sprintf(imagename, "%03i.jpg", counter);
                counter ++;

                //open newfile for writing
                jpegs = fopen(imagename, "w");

                // Write to outfile
                fwrite(buffer, 1, BLOCK, jpegs);
            }
            else if (counter > 0)
            {
                //close the last file we were writing to
                fclose(jpegs);

                //make the next file
                sprintf(imagename, "%03i.jpg", counter);
                counter ++;

                //open newfile for writing
                jpegs = fopen(imagename, "w");

                // Write to outfile
                fwrite(buffer, 1, BLOCK, jpegs);

            }

        }

        else if (counter > 0)
        {
            fwrite(buffer, 1, BLOCK, jpegs);
        }
    }
    fclose(jpegs);
    fclose(cardraw);
    return 0;
}