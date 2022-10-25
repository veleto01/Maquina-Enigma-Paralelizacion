//cd /D M:\UNI\URJC\3º\CAP\LAB\Debug
//mpiexec -n 4 ./LAB.exe
#include <iostream>
#include <mpi.h>
int  rank, size, status,lin;


#define nLines 9			//Número de filas de los textos cifrados
#define nCharsPerLine 33	//Número de caracteres en cada fila de los textos cifrados
#define nRotors 2			//Número de rotores de enigma para cifrar y descifrar

int ciphered[nLines][nCharsPerLine] = { //[9][33] - 2 rotores
	{65,63,59,89,50,117,131,56,142,132,131,64,153,133,154,139,146,145,160,80,161,162,86,172,162,161,94,183,163,176,178,187,120},
	{57,65,57,87,48,115,129,54,140,130,129,62,134,139,150,139,72,158,148,143,164,82,150,171,170,168,175,94,161,169,165,175,182},
	{53,57,53,125,128,46,132,122,121,54,123,137,136,130,76,66,152,142,141,74,152,151,151,154,168,86,172,162,157,178,96,164,182},
	{61,70,60,122,129,124,138,57,143,133,132,65,135,134,158,151,87,77,163,153,152,85,159,168,173,171,95,181,171,166,187,105,194},
	{55,58,54,108,120,116,132,51,137,127,126,59,144,139,134,136,149,140,155,158,89,79,165,155,154,87,172,163,166,164,173,167,101},
	{61,58,56,129,119,114,135,53,126,142,124,143,131,148,67,153,143,142,75,159,148,146,159,162,170,89,170,163,95,174,168,179,117},
	{57,65,57,87,48,130,128,123,124,129,129,62,141,155,68,146,145,144,145,78,145,160,152,86,160,169,170,173,178,98,184,181,104},
	{67,64,60,133,123,122,55,103,132,132,135,149,8252,152,71,128,140,161,146,153,95,85,157,168,173,93,179,169,172,184,103,183,180},
	{57,56,54,114,117,131,49,116,131,123,57,124,137,139,65,151,141,140,73,153,150,150,153,167,168,87,173,170,93,162,176,176,170},
};

/*int ciphered[nLines][nCharsPerLine] = { //[8][93] - 5 rotores
	{75,76,88,85,98,92,134,158,174,175,169,176,187,197,195,129,218,211,213,149,230,228,248,253,243,261,267,189,259,282,204,281,283,219,296,294,302,239,314,328,339,337,332,269,358,351,353,366,306,299,337,375,392,388,406,329,379,404,426,432,426,359,446,448,457,448,384,454,472,467,404,486,493,505,493,497,434,504,510,528,539,543,464,553,546,548,484,556,559,565,577,587,526},
	{72,82,87,90,97,93,161,169,174,175,178,188,186,120,195,209,217,140,228,229,232,229,249,242,248,258,256,190,264,276,288,279,227,220,308,309,312,309,329,322,328,338,336,270,359,359,285,359,373,376,378,381,387,404,394,408,335,412,418,427,369,360,405,439,375,450,464,475,473,468,405,488,494,504,497,503,513,511,472,450,522,536,544,554,547,553,563,561,495,573,583,510,599},
	{73,80,90,91,100,94,158,160,96,169,188,176,203,190,208,214,148,141,203,230,238,236,8351,254,176,267,259,267,265,214,290,276,299,305,299,309,307,241,314,333,329,339,341,271,349,359,286,375,368,370,306,398,389,399,395,331,418,406,413,426,368,361,449,456,449,465,469,391,468,466,484,482,416,494,504,431,520,513,515,451,523,537,545,554,545,565,498,491,562,580,585,586,599},
	{71,78,77,84,94,89,150,172,160,178,190,193,183,185,203,195,145,181,206,228,234,228,161,233,243,245,248,261,260,264,201,290,283,285,221,310,304,320,317,315,334,256,340,336,271,360,353,355,291,382,380,382,396,393,390,409,331,402,430,346,408,435,443,441,8556,459,381,452,460,464,401,489,484,484,490,453,431,515,519,515,451,543,526,549,471,541,481,552,570,575,576,506,590},
	{84,90,87,100,97,98,160,95,180,184,179,199,202,214,130,201,229,145,201,227,229,241,246,244,269,197,190,279,272,274,210,294,304,297,299,317,240,328,329,332,329,265,353,354,362,369,290,374,370,305,387,384,388,398,397,400,416,345,416,434,439,440,370,447,449,385,457,474,485,481,478,415,503,492,495,517,507,514,526,544,460,550,548,543,549,567,573,579,565,583,578,515,585},
	{90,95,96,103,104,103,171,173,183,179,115,199,195,144,187,212,214,150,239,225,241,246,175,246,264,269,270,267,270,293,284,220,304,300,305,309,327,319,323,260,342,349,357,349,285,369,365,300,389,382,384,320,408,395,412,409,372,350,432,445,432,442,375,450,458,457,479,473,484,488,415,485,503,498,435,520,524,519,539,542,554,482,475,545,485,560,560,573,587,510,580,597,604},
	{80,80,87,96,97,95,172,170,181,102,186,182,117,194,200,215,221,221,229,241,169,162,233,251,256,257,270,192,276,280,207,289,286,290,300,299,310,320,316,252,322,340,335,272,357,354,360,368,376,385,386,392,389,411,327,397,415,410,347,430,422,446,452,454,442,458,387,475,464,475,476,490,484,491,439,432,502,442,515,537,540,546,556,472,556,558,555,492,581,581,584,581,517},
	{89,95,96,106,108,104,175,179,106,176,192,188,198,200,213,230,158,151,221,239,166,240,254,265,259,273,265,201,289,283,285,297,296,231,315,311,246,317,335,340,341,354,276,354,364,291,366,380,388,380,389,392,404,331,412,406,424,422,441,426,437,440,459,395,399,404,409,414,419,424,429,434,439,444,449,454,459,464,469,474,479,484,489,494,499,504,509,514,519,524,529,534,539},
};*/

int descifrada[nLines][nCharsPerLine];
int deciphered[nCharsPerLine];
int lineas[nLines];
int Phijos = size - 1;




void printNumbersAsString(int lin, int texto[nLines][nCharsPerLine])
{
	
		char line[nCharsPerLine + 1];
		for (int idx2 = 0; idx2 < nCharsPerLine; idx2++)
		{
			line[idx2] = texto[lin][idx2];
		}
		line[nCharsPerLine] = '\0';
		printf("%s\n", line);
	
}

int* decipher(int line[], int key)
{
	int rawData[nCharsPerLine];

	for (int idx = 0; idx < nCharsPerLine; idx++)
	{
		rawData[idx] = line[idx];
	}

	int* rotorKeys = (int*)malloc(sizeof(int) * nRotors);
	int remainder = key;
	for (int idx = 0; idx < nRotors; idx++)
	{
		int divisor = pow(10, (nRotors - (1 + idx)));
		rotorKeys[idx] = (int)(remainder / divisor);
		remainder = (int)(remainder % divisor);
	}


	for (int rotorIdx = 0; rotorIdx < nRotors; rotorIdx++)
	{
		int displacement = rotorKeys[rotorIdx];
		for (int idx = 0; idx < nCharsPerLine; idx++)
		{
			rawData[idx] = rawData[idx] - displacement++;
		}
	}

	free(rotorKeys);
	return rawData;
}

void enigma(int lin)
{
	printf("ESTO ES LA ENTRADA: \n");
	printNumbersAsString(lin, ciphered);
	printf("\n");

	printf("DESCIFRANDO...: \n");
	printf("\n");
	
	for (int i = 0; i < nCharsPerLine; i++)
	{
		deciphered[i] = i;
	}

	for (int lineKey = (int)pow(10, nRotors - 1); lineKey < (int)pow(10, nRotors); lineKey++)
	{
		int* p_deciphered = decipher(ciphered[lin], lineKey);

		char decipheredLine[nCharsPerLine];
		for (int i = 0; i < nCharsPerLine; i++)
		{
			decipheredLine[i] = p_deciphered[i];
		}

		char stringKey[nRotors + 1];
		sprintf_s(stringKey, "%d", lineKey);
		if (!strncmp(stringKey, decipheredLine, nRotors))
		{
			for (int idx2 = 0; idx2 < nCharsPerLine; idx2++)
			{
			deciphered[idx2] = decipheredLine[idx2];
			}
			printf("Descifrada linea %d con clave %d\n\n\n", lin, lineKey);
			break;
			
		}
	}

	for (int i = 0; i < nCharsPerLine; i++)
	{
		descifrada[lin][i] = deciphered[i];
	}
}

int main(int argc, char* argv[])
{

	MPI_Status status;
	MPI_Request request;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	
	

	if (rank == 0)
	{
		
		for (int i = 0; i < nLines; i++)
		{
			lineas[i] = (i % Phijos) + 1;
			
		}

		MPI_Bcast(&lineas, nLines, MPI_INT, 0, MPI_COMM_WORLD);

		for (int i = 0; i < nLines; i++)
		{
			MPI_Recv(&descifrada[i][0], nCharsPerLine, MPI_INT, lineas[i], 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			
		}
		
	}

	if (rank != 0)
	{
		MPI_Bcast(&lineas, nLines, MPI_INT, 0, MPI_COMM_WORLD);

		for (int lin = 0; lin < nLines; lin++)
		{
			if (rank == lineas[lin])
			{
				enigma(lin);
			}
		}
		for (int i = 0; i < nLines; i++)
		{
			if (rank == lineas[lin]) {

				MPI_Send(&descifrada[i][0], nCharsPerLine, MPI_INT, 0, 0, MPI_COMM_WORLD);
				
			}
		}
	}

	
	if (rank == 0)
	{
		printf("ESTO ES LA SALIDA:\n");
		for (int i = 0; i < nLines; i++)
		{
			printNumbersAsString(i, descifrada);
		}
		printf("\n");
		printf("\n");

		
	}
	
	MPI_Finalize();

	return 0;
}