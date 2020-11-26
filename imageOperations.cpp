/*************************************************************************//**
 * @file 
 * @brief All image operation functions are handled here.
 *****************************************************************************/
#include "image.h"
/*************************************************************************//**
 * @author Samuel Coffin
 * 
 * @par Description: 
 * This function preform the negate function.  It takes each element in the 
 * stored arrays and subtracts it from 255.  No boundry checking is required.
 * 
 * 
 * 
 ****************************************************************************/
void image::negate()
{
	// loop vairables
	int i = 0;
	int j = 0;
	// loop to negate the file
	while (i < rows)
	{
		for (j = 0; j < cols; j++)
		{
			redgray[i][j] = 255 - redgray[i][j];
			green[i][j] = 255 - green[i][j];
			blue[i][j] = 255 - blue[i][j];
		}
		i++;
	}
}
/*************************************************************************//**
 * @author Samuel Coffin
 * 
 * @par Description: 
 * This function preform the brighten function.  It takes each element in the 
 * stored arrays and adds the amount specified in the incominimumg value parameter.
 * It adds the value specifed to each element in the array.  It will then do
 * a boundry check to make sure vales are not above 255 or below 0.
 * 
 * @param[in]  value - The amount to brighten or darken the image.
 * 
 ****************************************************************************/
void image::brighten( int value)
{
	// loop vairables
	int i = 0;
	int j = 0;
	// temp varaible used for boundry control
	int newvalue = 0;

	// loop used to brighten image
	while (i < rows)
	{
		for (j = 0; j < cols; j++)
		{
			newvalue = redgray[i][j] + value;
			if (newvalue < 0)
				redgray[i][j] = 0;
			else if (newvalue > 255)
				redgray[i][j] = 255;
			else
				redgray[i][j] = newvalue;
			newvalue = green[i][j] + value;
			if (newvalue < 0)
				green[i][j] = 0;
			else if (newvalue > 255)
				green[i][j] = 255;
			else
				green[i][j] = newvalue;
			newvalue = blue[i][j] + value;
			if (newvalue < 0)
				blue[i][j] = 0;
			else if (newvalue > 255)
				blue[i][j] = 255;
			else
				blue[i][j] = newvalue;
		}
		i++;
	}
}
/*************************************************************************//**
 * @author Samuel Coffin
 * 
 * @par Description: 
 * This function preform the grayscale option.  It multiples the each value in 
 * the red, green, and blue arrays by 0.3, 0.6 and 0.1 respectively.  It then
 * adds the three arrays together and stores the value into a temp grayscale 
 * array.  This function also determinimumes the minimum and
 * maximum values that are used in the contrast funciton.  The temp grayscale array
 * is then put back into the redgray parameter defined in the structure.
 *
 * 
 * 
 ****************************************************************************/
void image::grayscale()
{
	// loop vairables
	int i = 0;
	int j = 0;
	// variable used for boundry checks
	int number;
	// numbers needed for contrast funciton
	maximum = 0;
	minimum = 255;
	// temp array needed to hold the image math cleared at end of funciton
	pixel **grayscale;
	// tempory array needed
	grayscale = getArray(rows, cols);
	
	while (i < rows)
	{
		for (j = 0; j < cols; j++)
		{
			number = int(.3 * redgray[i][j]) + int(0.6 * green[i][j])
				+ int(0.1 * blue[i][j]);
			
			grayscale[i][j] = number;
			
			if (grayscale[i][j] < minimum)
				minimum = grayscale[i][j];
			
			if (grayscale[i][j] > maximum)
				maximum = grayscale[i][j];
		}
		i++;
	}

	i = 0;

	while (i < rows)
	{
		for (j = 0; j < cols; j++)
		{
			redgray[i][j] = grayscale[i][j];
		}
		i++;
	}
	// frees temp array
	freeArray(grayscale, rows);
}
/*************************************************************************//**
 * @author Samuel Coffin
 * 
 * @par Description: 
 * This function preform the contrast option. It determinimums a scale value by 
 * dividing 255 by the maximum-minimum determinimumed in the grayscale function.  It then 
 * multiplies each element by the above scale and stores the value back into the
 * redgray array structure.
 *
 * 
 * 
 ****************************************************************************/
void image::contrast()
{
	// loop varaibls
	int i = 0;
	int j = 0;
	// temp varaible used for boundry checks
	int number;
	// varaible needed for contrast maths
	double scale = 0;
	scale = 255.0 / (maximum - minimum);
	while (i < rows)
	{
		for (j = 0; j < cols; j++)
		{
			number = int(scale * (redgray[i][j] - minimum));
			redgray[i][j] = number;
		}
		i++;
	}
}
/*************************************************************************//**
 * @author Samuel Coffin
 * 
 * @par Description: 
 * This function preform the sharpen option. It accomplishes this task by 
 * multipling the center 3x3 element in and array and subtracting the top, 
 * bottom, left, and right values from the center value. IT checks the boudries
 * of this variable to make sure it is not above 255 or below 0.
 * It stores this in a temp array. It is then put back into the origional array
 * and the function finally cleans up the temp arrays.
 *
 * 
 * 
 ****************************************************************************/
void image::sharpen()
{
	// loop variables
	int i = 1;
	int j = 1;
	// temp number used for boundry checks
	int number;
	// needed temp arrays so that the math does not compound on self
	pixel **tempArray1;
	pixel **tempArray2;
	pixel **tempArray3;

	tempArray1 = getArray(rows, cols);
	tempArray2 = getArray(rows, cols);
	tempArray3 = getArray(rows, cols);
	// does the math requried for sharpen.  stores value in tmep arrays
	while (i < rows - 1)
	{
		for (j = 1; j < cols - 1; j++)
		{
			number = int(5.0 * redgray[i][j]) - redgray[i - 1][j] -
				redgray[i + 1][j] - redgray[i][j - 1] - redgray[i][j + 1];
			if (number < 0)
				number = 0;
			if (number > 255)
				number = 255;
			tempArray1[i][j] = number;
			number = int(5.0 * green[i][j]) - green[i - 1][j] - 
				green[i + 1][j] - green[i][j - 1] -	green[i][j + 1];
			if (number < 0)
				number = 0;
			if (number > 255)
				number = 255;
			tempArray2[i][j] = number;
			number = int(5.0 * blue[i][j]) - blue[i - 1][j] - 
				blue[i + 1][j] - blue[i][j - 1] - blue[i][j + 1];
			if (number < 0)
				number = 0;
			if (number > 255)
				number = 255;
			tempArray3[i][j] = number;
		}

		i++;
	}
	i = 0;
	// used to load temp array back into perm arrays
	while (i < rows)
	{
		for (j = 0; j < cols; j++)
		{
			redgray[i][j] = tempArray1[i][j];
			green[i][j] = tempArray2[i][j];
			blue[i][j] = tempArray3[i][j];
		}
		i++;

	}
	// free temp arrays
	freeArray(tempArray1, rows);
	freeArray(tempArray2, rows);
	freeArray(tempArray3, rows);
}
/*************************************************************************//**
 * @author Samuel Coffin
 * 
 * @par Description: 
 * This function preform the smooth option. It accomplishes this task by 
 * taking each element in a 3x3 matrix and subtrackting them. It then divides
 * this number by 9. It assinges this value to an int and checks the boudries
 * of this variable to make sure it is not above 255 or below 0.
 * It stores this in a temp array. It is then put back into the origional array
 * and the function finally cleans up the temp arrays.
 *
 * 
 * 
 ****************************************************************************/
void image::smooth()
{
	// loop varaibles
	int i = 1;
	int j = 1;
	// used to temp store number for boundry checking
	int number;
	// temp arrays needed so that smooth does not compound on self
	pixel **tempArray1;
	pixel **tempArray2;
	pixel **tempArray3;

	tempArray1 = getArray(rows, cols);
	tempArray2 = getArray(rows, cols);
	tempArray3 = getArray(rows, cols);

	// fills temp arrays after math and does error checks
	while (i < rows - 1)
	{
		for (j = 1; j < cols - 1; j++)
		{
			number = int((redgray[i - 1][j - 1] + redgray[i - 1][j]
				+ redgray[i - 1][j + 1] + redgray[i][j - 1] + redgray[i][j]
				+ redgray[i][j + 1] + redgray[i + 1][j - 1]
				+ redgray[i + 1][j] + redgray[i + 1][j + 1]) / 9.0);
			
			if (number < 0)
				number = 0;
			
			if (number > 255)
				number = 255;
			
			tempArray1[i][j] = number;
			
			number = int((green[i - 1][j - 1] + green[i - 1][j] 
				+ green[i - 1][j + 1] + green[i][j - 1]	+green[i][j]
				+ green[i][j + 1] + green[i + 1][j - 1]
				+ green[i + 1][j] + green[i + 1][j + 1]) / 9.0);
			
			if (number < 0)
				number = 0;
			
			if (number > 255)
				number = 255;
			
			tempArray2[i][j] = number;
			
			number = int((blue[i - 1][j - 1] + blue[i - 1][j] 
				+ blue[i - 1][j + 1] + blue[i][j - 1] + blue[i][j] 
				+ blue[i][j + 1] + blue[i + 1][j - 1] +	blue[i + 1][j] 
				+ blue[i + 1][j + 1]) / 9.0);
			
			if (number < 0)
				number = 0;
			
			if (number > 255)
				number = 255;
			
			tempArray3[i][j] = number;
		}
		i++;
	}
	i = 0;
	// fills structure arrays with temp array info
	while (i < rows)
	{
		for (j = 0; j < cols; j++)
		{
			redgray[i][j] = tempArray1[i][j];
			green[i][j] = tempArray2[i][j];
			blue[i][j] = tempArray3[i][j];
		}
		i++;
	}
	// free up temp arrays
	freeArray(tempArray1, rows);
	freeArray(tempArray2, rows);
	freeArray(tempArray3, rows);
}
