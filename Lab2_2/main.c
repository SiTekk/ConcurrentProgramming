#include <stdio.h>
#include <stdlib.h>

static const unsigned int delta = 0x9e3779b9;
static const unsigned int key[] = { 128, 129, 130, 131 };

void decrypt(unsigned int values[2])
{
    unsigned int sum = 0xC6EF3720;

    for (int i = 0; i < 32; i++)
    {
        values[1] = values[1] - (((values[0] << 4) + key[2]) ^ (values[0] + sum) ^ ((values[0] >> 5) + key[3]));

        values[0] = values[0] - (((values[1] << 4) + key[0]) ^ (values[1] + sum) ^ ((values[1] >> 5) + key[1]));

        sum -= delta;
    }
}

int main(int argc, const char* argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Please provide all arguments\n");
        return -1;
    }
    fprintf(stdout, "%s\n%s\n", argv[1], argv[2]);


    FILE* sourceFile = NULL, *destinationFile = NULL;
    fopen_s(&sourceFile, argv[1], "rb");

    if(sourceFile == NULL)
    {
        fprintf(stderr, "Could not open source File\n");
        return -1;
    }

    unsigned int length;
    fread(&length, sizeof(unsigned int), 1, sourceFile);
    unsigned int* pValues = (unsigned int*)malloc(length);

    if (pValues == NULL)
    {
        fprintf(stderr, "Could not allocate memory.");
        return -1;
    }

    fread(pValues, sizeof(unsigned int), length / 4, sourceFile);
    fclose(sourceFile);

    unsigned int numberOfBlocks = length / 8;

    for (unsigned int i = 0; i < numberOfBlocks; i++)
    {
        decrypt(pValues + 2 * i);
    }

    fopen_s(&destinationFile, argv[2], "wb");

    if (destinationFile == NULL)
    {
        fprintf(stderr, "Could not open destination File.");
        return -1;
    }

    fwrite(pValues, 1, length, destinationFile);

    fclose(destinationFile);
    free(pValues);

    return 0;
}
