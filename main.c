#include <stdio.h>

void displayCorrectUsage();

int main(int argc, char* argv[])
{
	int inFlag, outFlag;
	char* inFile;
	char* outFile;

	inFlag = 0;
	outFlag = 0;

	if (argc != 5)
	{
		/* Invalid number of arguments to function correctly */
		printf("Invalid number of arguments\n");
		displayCorrectUsage();
	}
	else
	{
		/* Correct number of arguments. Store arguments */
		if (*argv[1] == 'i')
		{
			inFlag = 1;
			inFile = argv[2];
		}
		else if (*argv[3] == 'i')
		{
			inFlag = 1;
			inFile = argv[4];
		}

		if (*argv[1] == 'o')
		{
			outFlag = 1;
			outFile = argv[2];
		}
		else if (*argv[3] == 'o')
		{
			outFlag = 1;
			outFile = argv[4];
		}

		/* Hanlde the error detection with the flags */
		if (inFlag == 0)
		{
			printf("No input file argument detected\n");
			displayCorrectUsage();
		}
		if (outFlag == 0)
		{
			printf("No outfile file argument detected\n");
			displayCorrectUsage();
		}

		if (outFlag == 1 && inFlag == 1)
		{
			printf("%s, %s\n", inFile, outFile);
		}

	}
}

void displayCorrectUsage()
{
	printf("Correct Usage:\nsortingAssignment i inFile o outfile\n");
}
