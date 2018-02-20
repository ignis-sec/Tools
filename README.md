# Code-for-isolating-white-text
Fast c script for reading through a 24 bit .BMP file and isolating the text inside

It reads the BMP headers index 18-19-20 and calculates row size and null byte counts from it. 
Then it reads through the color cells and checks if it is within the tolerance of the text color. if so, sets the pixel to COLOR_TEXT
If not, sets it to COLOR_BG
