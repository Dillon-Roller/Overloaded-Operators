/*************************************************************************//**
 * @file
 * @brief Functions done by Samuel Coffin
 *****************************************************************************/

#include "image.h"
#include "functions.h"


/*************************************************************************//**
 * @author Samuel Coffin
 *
 * @par Description:
 * This funciton is the menu for program 4.  It handles the user input file
 * calling the image class and using the overload operator to copy an image.
 * It will prompt the user first for the input file name. Then output file name.
 * It will then prompt for the output file type -oa or -ob.  Once the above 
 * information is recieved it will the attempt to open up the appropriate files.
 * At this point the menu will prompt the user with the available image operations
 * It will continue to do this until the user is satisfied.  Once the user chooses
 * to exit the program it will then output the appropriate file.
 *
 *
 ****************************************************************************/

void printMenu ()
{

	image pic, img1;
	ifstream fin;
	ofstream fout;
	string inputName;
	string outputName;
	string file;
	int choice;
	int greyCheck = 0;
	int exempt = 0;
	int bright = 0;
	cout << "Input File Name: ";
	getline(cin, inputName);


	cout << "Output File Name: ";
	getline(cin, outputName);


	cout << "Enter output file type (-oa or -ob): ";
	getline(cin, file);
	cout << endl;
	cout << endl;



	greyCheck = img1.openFile(inputName, fin);
	
	
	pic = img1;
   
    do
    {
        cout << "Menu: " << endl;
        cout << "1. median" << endl;
        cout << "2. Salt and Pepper" << endl;
		cout << "3. Image Grid" << endl;
		cout << "4. Filters" << endl;
        cout << "5. Test Overloaded Operators" << endl;
        cout << "6. emphasis" << endl;
		cout << "7. pixelate" << endl;
		cout << "8. edge detection" << endl;
        cout << "9. Flip" << endl;
        cout << "10. Mirror (vertically)" << endl;
        cout << "11. Mirror (horizontally)" << endl;
		cout << "12. Box image" << endl;
		cout << "13. Sharpen" << endl;
		cout << "14. Smooth" << endl;
		cout << "15. Greyscale" << endl;
		cout << "16. Brighten" << endl;
		cout << "17. Negate" << endl;
		cout << "18. Contrast" << endl;
		cout << "19. Exit Program" << endl;
		cout << "Choice: ";
        cin >> choice;
        cout << endl;
        
        switch ( choice )
        {
            case 1:
				pic.median();

				break;
                
            case 2:
				pic.salt_pepper();
				
				break;
                
            case 3:
				pic.grid();
				exempt = 1;	
				break;
                
			case 4:
				pic.filters();
				
				break;

			case 5:
	            pic.testOperators();
				
				break ;

			case 6:
				pic.emphasis();
				
				break;

			case 7:
				pic.pixelate();
				
				break;

			case 8:
				
				if (greyCheck == 0)
				{
					pic.grayscale();
					img1.grayscale();
					pic.edgeDetect();
					greyCheck = 1;
				}
				else
				pic.edgeDetect();
				
				break;

			case 9:
                pic.flip();
                
				break;
            case 10:
                pic.mirrorUpDown();
                
                break;
            case 11:
                pic.mirrorLeftRight();
				img1.printTwo(pic);
				break;

			case 12:
				pic.box();

				break;

			case 13:
				pic.sharpen();
				break;

			case 14:
				pic.smooth();
				break;

			case 15:
				pic.grayscale();
				greyCheck = 1;

				break;

			case 16: 
				cout << "Enter brighten amount: ";
				cin >> bright;
				cout << endl;
				pic.brighten(bright);
				break;

			case 17:
				pic.negate();
				break;

			case 18:
				if (greyCheck != 1)
				{
					pic.grayscale();
					greyCheck = 1;
				}
				pic.contrast();
				break;

			case 19:
				

				if (exempt == 0)
				img1.printTwo(pic);

				break;
			
			default:
                cout << "Not a proper choice. Please try again" << endl;
                break;
        }
    }
    while ( choice != 19 );
	if (exempt == 1)
	pic.outputFile(outputName, inputName, file, greyCheck, fin);
	else	
	img1.outputFile(outputName, inputName, file, greyCheck, fin);
	return;
    
    
}

/*************************************************************************//**
 * @author Samuel Coffin
 *
 * @par Description:
 * THis funciton takes the input origional image and combines the duplicate that
 * the image operations were preformed on. This works for all of the images 
 * except for the grid.
 *
 * @param[in,out]  pic - this is the duplicate image with the preformed image ops
 *
 ****************************************************************************/
void image::printTwo(image &pic)
{

	int i = 0;
	int j = 0;
	int k = 0;
	int col = cols + pic.cols + 1 ;
	int row = rows + 1;
	if (pic.rows != rows)
	{
	row = row + abs(rows-pic.rows);
	}

	pixel **finalImageRed;
	pixel **finalImageGreen;
	pixel **finalImageBlue;
		
	finalImageRed = getArray(row, col);
	finalImageGreen = getArray(row, col);
	finalImageBlue = getArray(row, col);

	// still need to do cleanup if not available memory
	if ( finalImageRed == nullptr || finalImageGreen == nullptr || finalImageBlue == nullptr )
    {
        cout << "Not enough Memory available to do print origional and modified image." << endl;
    }
	
	while (i < row)
	{
		
		for (j = 0; j < col; j++ )
		{

			if (j <= pic.cols && i < pic.rows)
			{
			
			k = 0;
			finalImageRed[i][j] = redgray[i][j];
			finalImageGreen[i][j] = green[i][j];
			finalImageBlue[i][j] = blue[i][j];
			}
			else if (j <= pic.cols && i > pic.rows)
			{
			finalImageRed[i][j] = 0;
			finalImageGreen[i][j] = 0;
			finalImageBlue[i][j] = 0;
			}
			else if (j > pic.cols && i < pic.rows)
			{
			finalImageRed[i][j] = pic.redgray[i][k];
			finalImageGreen[i][j] = pic.green[i][k];
			finalImageBlue[i][j] = pic.blue[i][k];
			k++;
			}
			else
			{
			finalImageRed[i][j] = 0;
			finalImageGreen[i][j] = 0;
			finalImageBlue[i][j] = 0;
			k++;
			}

		}
		i++;
	}

	getNewArrays(row, col);
    rows = row;
	cols = col;
	i = 0;
	while (i < rows)
	{
		for (j = 0; j < cols; j++)
		{
			redgray[i][j] = finalImageRed[i][j];
			green[i][j] = finalImageGreen[i][j];
			blue[i][j] = finalImageBlue[i][j];
		}
		i++;

	}
	// free temp arrays
	freeArray(finalImageRed, rows);
	freeArray(finalImageGreen, rows);
	freeArray(finalImageBlue, rows);

}

/*************************************************************************//**
 * @author Samuel Coffin
 *
 * @par Description:
 * THis funciton will create a number of duplicates that the user requests. It
 * asks the user for the amount of images for rows and columns. It then allocates
 * an appropriate sized array and copys the requested amount of images.  It will
 * then resize the origional arrays and copy in the temp arrays.  lastly it cleans
 * up the temp arrays used.  This idea was provided by Professor Schrader.
 *
 *
 ****************************************************************************/
void image::grid ()
{
		
	int i = 0;
	int j = 0;
	int count1 = 0;
	int count2 = 0;
	int r = 0;
	int b = 0;
	int g = 0;
	int row;
	int col;

	int rowNumber;
	int colNumber;

	pixel **finalImageRed;
	pixel **finalImageGreen;
	pixel **finalImageBlue;
	cout << "Note:  The more images in the grid require more time to process.  For example a 9x9 image could take a half hour to process." << endl << endl;
	cout << "Enter the amount of image rows: " ;
	cin >> rowNumber;
	cout << endl;
	cout << "Enter the amount of image columns: ";
	cin >> colNumber;
	cout << endl;
	row = rowNumber * rows;
	col = colNumber * cols;

	finalImageRed = getArray(rows * rowNumber, cols * colNumber);
	finalImageGreen = getArray(rows * rowNumber, cols * colNumber);
	finalImageBlue = getArray(rows * rowNumber, cols * colNumber);

	if ( finalImageRed == nullptr || finalImageGreen == nullptr || finalImageBlue == nullptr )
    {
        cout << "Not enough Memory available to do this operation" << endl;
		return;

    }

	while (i < rowNumber * rows)
	{
		for (j = 0; j < colNumber * cols; j++)
		{
			if (count2 == cols)
				count2 = 0;
			finalImageRed[i][j] = redgray[count1][count2];
			finalImageGreen[i][j] = green[count1][count2];
			finalImageBlue[i][j] = blue[count1][count2];
			count2++;
		}
		i++;
		count1++;
		if (count1 == rows)
			count1 = 0;
		
	}

	getNewArrays(row, col);
    rows = row;
	cols = col;
	i = 0;
		while (i < rows)
	{
		for (j = 0; j < cols; j++)
		{
			redgray[i][j] = finalImageRed[i][j];
			green[i][j] = finalImageGreen[i][j];
			blue[i][j] = finalImageBlue[i][j];
		}
		i++;

	}
	// free temp arrays
	freeArray(finalImageRed, rows);
	freeArray(finalImageGreen, rows);
	freeArray(finalImageBlue, rows);

}

/*************************************************************************//**
 * @author Samuel Coffin
 *
 * @par Description:
 * THis funciton simply reallocates the origional array sizes so it can handle
 * the new size of image needed.
 
 *
 * @param[in]      row - the amount of rows needed
 * @param[in]      col - the amount of cols needed
 *
 ****************************************************************************/
void image::getNewArrays(int row, int col)
{
	freeArray(redgray, rows);
	freeArray(green, rows);
	freeArray(blue, rows);

	redgray = getArray ( row, col );
    green = getArray ( row, col );
    blue = getArray ( row, col );
    
    //simple error check for nullptr.  Will close the input file and free the
    // Allocated arrays.
    if ( redgray == nullptr || green == nullptr || blue == nullptr )
    {
        cout << "Not enough Memory" << endl;
		exit (0);
    }

}

/*************************************************************************//**
 * @author Samuel Coffin
 *
 * @par Description:
 * THis funciton detects the edges in a greyscale image. It uses the sobel edge
 * detection method and the idea was provided by Professor Schrader.  
 *
 *
 ****************************************************************************/
void image::edgeDetect()
{
	int i = 1;
	int j = 1;
	int Gx = 0;
	int Gy = 0;
	double Gfinal = 0;
	pixel **temp;

	temp = getArray(rows, cols);

	
	
	while (i < rows-1)
	{
		
		for (j=1; j < cols-1; j++)
		{
		Gx = int(redgray[i-1][j-1] * -1 + redgray[i][j-1] * -2 + redgray[i+1][j-1] * -1 + redgray[i+1][j+1] * 1 + redgray[i][j+1] * 2 + redgray[i+1][j+1] * 1);
		Gy = int(redgray[i-1][j-1] * -1 + redgray[i-1][j] * -2 + redgray[i-1][j+1] * -1 + redgray[i+1][j-1] * 1 + redgray[i+1][j] * 2 + redgray[i+1][j+1] * 1);
		Gfinal = sqrt(Gx*Gx+Gy*Gy);
		if (Gfinal < 0)
			Gfinal = 0;
		if (Gfinal > 255)
			Gfinal = 255;
		temp[i][j] = int(Gfinal);
		}
	i++;
	}

	for (i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			redgray[i][j] = temp[i][j];
		}
	}
	freeArray(temp, rows);
}
