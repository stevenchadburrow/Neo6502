// Neon6502-Combiner.c

// Combines the sync signals .bin file with a program .bin file, into a single .bin file to be flashed with minipro

#include <stdio.h>
#include <stdlib.h>

int main(const int argc, const char **argv)
{
	if (argc < 4)
	{
		printf("Arguments: <signals-64kb.bin> <program-32kb.bin> <output-128kb.bin>\n");
		return 0;
	}

	FILE *input = NULL, *output = NULL;

	output = fopen(argv[3], "wb");
	if (!output)
	{
		printf("Error!\n");
		return 0;
	}

	int bytes = 1;
	unsigned char buffer;
	unsigned long counter = 0;

	input = NULL;

	input = fopen(argv[1], "rb");
	if (!input)
	{
		printf("Error!\n");
		return 0;
	}

	bytes = 1;

	counter = 0;

	while (bytes > 0 && counter < 0x10000)
	{
		bytes = fscanf(input, "%c", &buffer);
		
		if (bytes > 0)
		{
			fprintf(output, "%c", buffer);

			counter++;
		}
	}

	fclose(input);

	for (int i=0; i<32768; i++)
	{
		fprintf(output, "%c", 0xFF);
	}

	input = NULL;

	input = fopen(argv[2], "rb");
	if (!input)
	{
		printf("Error!\n");
		return 0;
	}

	bytes = 1;

	counter = 0;

	while (bytes > 0 && counter < 0x8000)
	{
		bytes = fscanf(input, "%c", &buffer);

		if (bytes > 0)
		{
			fprintf(output, "%c", buffer);

			counter++;
		}
	}
	
	fclose(input);

	fclose(output);

	return 1;
}
