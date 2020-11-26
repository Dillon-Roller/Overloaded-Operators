/*************************************************************************//**
 * @file 
 * @brief Includes the constructor, copy constructor, and destructor
 * for the image class.
 *****************************************************************************/
#include "image.h"

/**************************************************************************//**
 * @author Samuel Coffin
 *
 * @par Description: Constructor: Initializes all variables that are part of
 * the image
 *
 *****************************************************************************/
image::image()
{
	rows = 0;	/*!< Number of rows in input file*/
	cols = 0;	/*!< Numer of cols in input file*/
	colorBand = 0;  /*!< Max number of colors allowed in input file*/
	
	minimum = 0;
	maximum = 0;
	 
	fileType[0] = ' ';	/*!< determines weather binary or ascii or grayscale*/
	comment[0] = ' ';	/*!< allocates room if there is comment in input*/

	redgray = 0; /*!< redgray array */
	green = 0;    /*!< green array */
	blue = 0;		/*!< blue array */

}

/**************************************************************************//**
 * @author Samuel Coffin
 *
 * @par Description: Copy constructor. Creates an image that is a copy of the
 * one passed in. Basically copies each individual item of the image that is
 * passed in over to the image being constructed.
 *
 * @param pic - image to be copied
 *
 *****************************************************************************/
image::image (image &pic)
{
	int i = 0;
	int j = 0;
	rows = pic.rows;
	cols = pic.cols;
	colorBand = pic.colorBand;
    minimum = pic.minimum;
	maximum = pic.maximum;

	if (rows == 0 && cols == 0 )
		return;
	
	
	for (i = 0; i < 3; i++)
		fileType[i] = pic.fileType[i];

	for (i = 0; i < 81; i++)
		comment[i] = pic.comment[i];
	i = 0;


	redgray = pic.getArray(rows, cols);
	green = pic.getArray(rows, cols);
	blue = pic.getArray(rows, cols);

	while(i < rows)
	{
		for (j=0; j< cols; j++)
		{
			redgray[i][j] = pic.redgray[i][j];
			green[i][j] = pic.green[i][j];
			blue[i][j] = pic.blue[i][j];
		}
		i++;
	}


}

/**************************************************************************//**
 * @author Samuel Coffin
 *
 * @par Description: Image destructor: Cleans up all dynamically allocated 
 * memory involved with arrays for holding image pixel values.
 *
 *****************************************************************************/
image::~image()
{
	freeArray ( redgray, rows );
    freeArray ( green, rows );
    freeArray ( blue, rows );
}

