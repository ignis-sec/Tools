#include <stdio.h>
#include <stdlib.h>

//	Name: isolate text

//	Author: Ata Hakcil
//	Description:


int main(void)
{
	char filename[] = "io.bmp";                    //filename
	FILE * ioftp;

	int red, green, blue;
	int i = 0;
	char ch;

	ioftp = fopen(filename, "ab+");

	red = 0;
	green = 0;
	blue = 0;
	fseek(ioftp, 54, 0);
	while ((ch = getc(ioftp)) != EOF)
	{
		switch (i % 3)
		{
		case 0:
			blue = ch;
			break;

		case 1:
			green = ch;
			break;

		case 2:
			red = ch;
			break;
		}
		i++;
	}
	if (blue == 196 && green == 196 && red == 196)
	{
	}
	else {
		fseek(ioftp, -3, 0);
		fprintf(ioftp, 0);
		fprintf(ioftp, 0);
		fprintf(ioftp, 0);
	}





	fclose(ioftp);
	return 0;
}


