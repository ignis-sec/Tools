#include <stdio.h>
#include <stdlib.h>
#define SHADE 196
//	Name: Isolate Text

//	Author: Ata Hakcil
//	Description:Isolate unicolor text from background


//BMP architecture
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//



int main(void)
{
	char filename[] = "io.bmp";						//filename
	FILE * ioftp;									//pointer to the file

	int red, green, blue;							//variables
	int i = 54;										//iterator; starting from 54 because the first 54 bytes are reserved for bitmap headers
	unsigned short int ch=0;						//char variable to catch bytes from filestream
	int nc = 0;										//required for end of file (nullcount)
	ioftp = fopen(filename, "rb+");					//open file for read and write
	
	red = 0;										//initializing variables
	green = 0;										//
	blue = 0;										//

	fseek(ioftp, 54, SEEK_SET);						//seek for 54th byte from start:: SEEK_SET->From Start
	while ((ch = getc(ioftp)) != EOF)				//get char as long as it is	   :: SEEK_CUR->Current
	{												//not end of file              :: SEEK_END->From End
		switch (i % 3)								//switch on i%3 to check if it is r,g or b
		{
		case 0:										//case blue
			blue = ch;
			break;

		case 1:										//case green
			green = ch;
			break;

		case 2:										//case red; color cells in bmp end with red, so logic is applied here. 
			red = ch;								//If last cell has our SHADE,SHADE,SHADE grey, then we ignore (it is a text pixel)
			if (red == 0 && blue == 0 && green == 0) nc++;
			if (nc == 2) return 0;
			if (blue == SHADE && green == SHADE && red == SHADE)			
			{
				nc = 0;
				printf("%d %d %d\n", blue, green, red);
				fseek(ioftp, -3, SEEK_CUR);				//so we seek 3 btyes behind
				fprintf(ioftp, "%c", 0);				//overwrite them with 0,0,0 (black) 
				fprintf(ioftp, "%c", 0);
				fprintf(ioftp, "%c", 0);
				fseek(ioftp, 0, SEEK_CUR);				//doesn't work without SEEK_CUR to itself(fuck C)
			}
			else {									//if it is SHADE,SHADE,SHADE; it is part of the background, 
				nc = 0;
				printf("This isnt text:%d %d %d\n", blue, green, red);
				fseek(ioftp, -3, SEEK_CUR);			//so we seek 3 btyes behind
				fprintf(ioftp, "%c", 255);			//overwrite them with 255,255,255 (white) 
				fprintf(ioftp, "%c", 255);
				fprintf(ioftp, "%c", 255);
				fseek(ioftp, 0, SEEK_CUR);			//doesn't work without SEEK_CUR to itself(fuck C)
			}
			break;
		}i++;										//iterate i
	}
	fclose(ioftp);									//close file
	return 0;										//gtfo
}



