//	Name: Isolate Text From 24 bit BMP

//	Author: Ata Hakcil 
//	Description:Isolate text inside BMP image from the background
/// ///////////////////////////////////////////////////////////////////////////////////////IMPORTANT NULL BYTE COUNTER NOT IMPLEMENTED 
#include <stdio.h>																		///MAKE SURE IMAGE WIDTH IS 4N until it is implemented
#include <stdlib.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define FILENAME "io.bmp"																											//
																																	//
#define HEADERSIZE 54																												//																																	
																																	//
#define SHADE 196																													//
#define SHADE_RED SHADE								//if color is grayscale keep SHADERED/GREEN/BLUE defined as SHADE; change SHADE	//
#define SHADE_BLUE SHADE																											//
#define SHADE_GREEN SHADE																											//
																																	//
#define TOLERANCE 0									//change below if you want custom tolerance on each color						//
#define TOLERANCE_RED TOLERANCE						//just keep it positive															//
#define TOLERANCE_BLUE TOLERANCE																									//
#define TOLERANCE_GREEN TOLERANCE																									//
																																	//
#define COLOR_TEXT 0								//color of your text															//
#define COLOR_TEXT_RED	COLOR_TEXT																									//
#define COLOR_TEXT_GREEN COLOR_TEXT																									//
#define COLOR_TEXT_BLUE COLOR_TEXT																									//
																																	//
#define COLOR_BG 255								//color of your background														//
#define COLOR_BG_RED	COLOR_BG																									//
#define COLOR_BG_GREEN COLOR_BG																										//
#define COLOR_BG_BLUE COLOR_BG																										//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
//BMP architecture
// 54 bytes of header for 24 bit image 
// BM tag image sizes colors definition etc
// *****************VERY IMPORTANT NULL BYTES**********************
//If a line of pixels is not size of 4n, file will be filled with 000 pixels until its size of 4n
//BMP extension has no end file, it instead declares size at the start. Instead i declared 0,255,0 (green) as my EOF
//

int main(void)
{

	FILE * ioftp;								//pointer to the file

	int red, green, blue;					//variables
	int i = 0;						//iterator; starting from 54 because the first 54 bytes are reserved for bitmap headers
	///int width;
	int nullCount=0;
	int ch=0;						//char variable to catch bytes from filestream
	ioftp = fopen(FILENAME, "rb+");				//open file for read and write
	
	red = 0;										//initializing variables
	green = 0;										// 
	blue = 0;										//

	fseek(ioftp, -3, SEEK_END);						//set the last pixel as green and hope there are no other 1,255,1's
	fprintf(ioftp, "%c", 1);						
	fprintf(ioftp, "%c", 255);
	fprintf(ioftp, "%c", 1);
	fseek(ioftp, 0, SEEK_CUR);						//doesn't work without SEEK_CUR to itself(fuck C)

	///fseek(ioftp, 19, SEEK_SET);                  //null byte counter not implemented
	///width = getc(ioftp) + getc(ioftp) * 16 * 16;
	///fseek(ioftp, 0, SEEK_CUR);
	///if (width % 4) nullCount = 4 - width % 4; else nullCount = 0;
	fseek(ioftp, HEADERSIZE, SEEK_SET);						//seek for 54th byte from start   :: SEEK_SET->From Start
	while ((ch = getc(ioftp)) != EOF)				//get char as long as it is	      :: SEEK_CUR->Current	     Also EOF doesn't do anything 
	{												//not end of file                 :: SEEK_END->From End	     here, but might as well stay
		switch (i % 3)				//switch on i%3 to check if it is r,g or b
		{
		case 0:										
			blue = ch;
			break;

		case 1:										
			green = ch;
			break;

		case 2:										//Color cells in bmp end with red, so logic is applied here. 
			red = ch;
			if (red == 1 && blue == 1 && green == 255) return 0;		//stop if cell is absolute green(1,255,1)		

			if (((blue >= SHADE_BLUE-TOLERANCE_BLUE)&&(blue <= SHADE_BLUE + TOLERANCE_BLUE))			//if each color is 
				&&((green >= SHADE_GREEN - TOLERANCE_GREEN)&&(green <= SHADE_GREEN + TOLERANCE_GREEN))	//in range of SHADE +- TOLERANCE
				&&((red >= SHADE_RED - TOLERANCE_RED)&&(red <= SHADE_RED + TOLERANCE_RED)))
			{
				///printf("%x %x %x\n", blue, green, red);							//print statement slows down the code 100x times only for debug
				fseek(ioftp, -3, SEEK_CUR);							//we seek 3 btyes behind
				fprintf(ioftp, "%c", COLOR_TEXT_BLUE);				//overwrite them with text color
				fprintf(ioftp, "%c", COLOR_TEXT_GREEN);
				fprintf(ioftp, "%c", COLOR_TEXT_RED);
				fseek(ioftp, 0, SEEK_CUR);				//doesn't work without SEEK_CUR to itself(fuck C)
			}
			else {									
				///printf("This isnt text:%x %x %x\n", blue, green, red);			//print statement slows down the code 100x times only for debug
				fseek(ioftp, -3, SEEK_CUR);						//so we seek 3 btyes behind
				fprintf(ioftp, "%c", COLOR_BG_BLUE);			//overwrite them with background color
				fprintf(ioftp, "%c", COLOR_BG_GREEN);
				fprintf(ioftp, "%c", COLOR_BG_RED);
				fseek(ioftp, 0, SEEK_CUR);			//doesn't work without SEEK_CUR to itself(fuck C)
			}
			break;
		}
		///if (i == width)
		///{
		///	fseek(ioftp, nullCount, SEEK_CUR);             /null byte counter not yet implemented
		///} 
		i++;												//iterate i
	}
	fclose(ioftp);									//close file
	return 0;										//gtfo
}