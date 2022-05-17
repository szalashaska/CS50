#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t BYTE;

//Number of bytes units that camara uses to write JPEG
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    //check for proper usage
    char *card_name = "card.raw";
    if (argc != 2 || strcmp(argv[1], card_name) != 0)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    char filename[8];
    int counter = 0;

    BYTE buffer[BLOCK_SIZE];
    // fread(...) == 1 assures that loop will when it will rech the end of memory to read
    // function reads size "size" (here BLOCK_SIZE = 512) number of times "number" (here "1"). If it read whole chunk of size "size", it returns number of times "times".
    //if it didnt read a whole chunk of size "size" (for example at the end of a file) it returns number lesser than "times" or 0, hence the condition.
    while (fread(buffer, BLOCK_SIZE, 1, inptr) == 1)
    {
        //check for beginging of the JPEG
        // (buffer[3] & 0xf0) == 0xe0 checks condition 0xe0, 0xe1, 0xe2, ... , 0xef
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // checks if it is a firts jpeg
            if (counter == 0)
            {
                // "%03i" means, that it prints an integer as 3 digits, even if it just 1, or 10
                sprintf(filename, "%03i.jpg", counter);
                //opens a file in writing mode
                FILE *outptr = fopen(filename, "w");
                if (outptr == NULL)
                {
                    return 1;
                }
                fwrite(buffer, BLOCK_SIZE, 1, outptr);
                //keeps count of jpegs
                counter++;
                fclose(outptr);
            }
            else
            {
                sprintf(filename, "%03i.jpg", counter);
                //opens a file in write mode
                FILE *outptr = fopen(filename, "w");
                if (outptr == NULL)
                {
                    return 1;
                }
                fwrite(buffer, BLOCK_SIZE, 1, outptr);
                //keeps count
                counter++;
                fclose(outptr);
            }
        }
        else
        {
            //if the firt photo was alredy found
            if (counter != 0)
            {
                //opens a file in append mode
                FILE *outptr = fopen(filename, "a");
                if (outptr == NULL)
                {
                    return 1;
                }
                fwrite(buffer, BLOCK_SIZE, 1, outptr);
                fclose(outptr);
            }
        }
    }
    //ends reading card
    fclose(inptr);
}