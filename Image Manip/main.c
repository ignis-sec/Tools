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
	int i = 54;
	char ch=0;

	ioftp = fopen(filename, "rb+");
	
	red = 0;
	green = 0;
	blue = 0;
	fseek(ioftp, 54, SEEK_SET);
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
			printf("%x %x %x\n", blue, green, red);
			if (blue == 196 && green == 196 && red == 196)
			{
				printf("This is text");
			}
			else {
				fseek(ioftp, i-3, SEEK_SET);
				fprintf(ioftp, 0);
				fprintf(ioftp, 0);
				fprintf(ioftp, 0);
				fseek(ioftp, i, SEEK_SET);
			}
			break;
		}i++;
	}
	fclose(ioftp);
	return 0;
}


