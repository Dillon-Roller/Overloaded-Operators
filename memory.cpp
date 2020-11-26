/*************************************************************************//**
 * @file 
 * @brief memory allocation and freeing Functions are handled here.
 *****************************************************************************/
#include "image.h"

/*************************************************************************//**
 * @author Samuel Coffin
 * 
 * @par Description: 
 * This function allocates one 2D array.  It will return the null pointer if
 * the allocation fails.  IF it succeds it will return the pointer.
 * 
 * @param[in]      rows - amount of rows in array
 * @param[in]     col - amount of cols in array
 * 
 * @return nullptr - Retruns nullpointer if the allocation of memory failed
 * @return ptr - Returns pointer if the allocation of memory was successful
 ****************************************************************************/
unsigned char **image::getArray(int rows, int col)
{
	int i = 0;
	unsigned char **ptr = nullptr;
	ptr = new (nothrow) unsigned char * [rows];
	if (ptr == nullptr)
	{
		return nullptr;
	}
	for (i = 0; i < rows; i++)
	{
		ptr[i] = new unsigned char[col];
		if (ptr[i] == nullptr)
		{
			return nullptr;
		}

	}
	return ptr;
}

/*************************************************************************//**
 * @author Samuel Coffin
 * 
 * @par Description: 
 * This function is used to free up any array that has been allocated in memory
 * this fulfills the requirements of freeing the array.
 * 
 * @param[in]      ptr - pointer to 2D array to freed back to system memory
 * @param[in]      rows - amount of rows in above pointer
 ****************************************************************************/
void image::freeArray( unsigned char **&ptr, int rows)
{
	int i = 0;
	if (ptr == nullptr)
		return;

	for (i = 0; i < rows; i++)
		delete[] ptr[i];

	delete[] ptr;

}

