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
        printf("Usage: program inputfile outputfile\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    char *infile = argv[1];
    FILE *inputr = fopen(infile, "r");

    if (inputr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    int sizeHeader = sizeof(WAVHEADER);
    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header, sizeHeader, 1, inputr);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(header) == 0)
    {
        printf("Not a WAV file format.\n");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    char *outfile = argv[2];
    FILE *outputw = fopen(outfile, "w");

    if (outputw == NULL)
    {
        printf("Could not open %s.\n", outfile);
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&header, sizeHeader, 1, outputw);

    // Use get_block_size to calculate size of block
    // TODO #7
    int size = get_block_size(header);

    // Write reversed audio to file
    // TODO #8
    if (fseek(inputr, size, SEEK_END))
    {
        return 1;
    }
    BYTE buffer[size];
    while(ftell(inputr) - size > sizeHeader)
    {
        if (fseek(inputr, - 2 * size, SEEK_CUR))
        {
            return 1;
        }
        fread(buffer, size, 1, inputr);
        fwrite(buffer, size, 1, outputw);
    }

    // Close infile
    fclose(inputr);

    // Close outfile
    fclose(outputw);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    BYTE tempformat[] = {'W', 'A', 'V', 'E'};
    BYTE tempSubchunk1ID[] = {'f', 'm', 't', ' '};
    BYTE tempSubchunk2ID[] = {'d', 'a', 't', 'a'};

    for (int letter = 0; letter < 4; letter ++)
    {
        // A WAVE file is often just a RIFF file with a single "WAVE" chunk which consists of two sub-chunks:
        // a "fmt " chunk specifying the data format (subchunk1ID = "fmt ")
        // and a "data" chunk containing the actual sample data (subchunk2ID = "data")
        if (header.format[letter] == tempformat[letter] && header.subchunk1ID[letter] == tempSubchunk1ID[letter] && header.subchunk2ID[letter] == tempSubchunk2ID[letter])
        {
            return 1;
        }
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int size = header.numChannels * (header.bitsPerSample / 8);
    return size;
}