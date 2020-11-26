/*************************************************************************//**
 * @file
 *
 * @mainpage Program 4 - Image Class
 *
 * @section course_section Course Information
 *
 * @authors Samuel Coffin
 * @authors Ayden Drabek
 * @authors Dillon Roller
 *
 * @date December 5, 2017
 *
 * @par Professor:
 *          Roger Schrader
 *
 * @par Course:
 *         CSC 215 - Section 1 -  1:00 pm
 *
 * @par Location:
 *         ECE -  Room 254
 *
 * @section program_section Program Information
 *
 * @details The below information was taken from the program write up provided
 * by Professor Schrader.
 *
 * This programming assignment is to help you get a firm understanding
 * of 2d arrays, dynamic memory allocation, ascii data files and binary data
 * files and the use of classes and overload operators.
 * Data files with a .ppm extension are color images and files with a
 *.pgm extension are grayscale. Color and grayscale images can be used for input.
 *
 * PPM image types are the only type used for input. For a file to be a ppm
 * image it must have a magic number of P3 or P6.  The magic number is found by
 * reading the first two bytes of the file.  Those bytes must match a P3 or a
 * P6 and are case sensitive.  The next line can be a comment.  If it starts
 * with a # symbol, the line is considered to be a comment.  Multiple lines can
 * be comments so line 3 could be a comment if the line starts with the symbol
 * #.  For our purpose, you will only have one comment line and if one exists
 * and it must be preserved and copied to the new.  After the comment line come
 *  the width and height of the image, in that order.  A whitespace separates
 * these two values.  The next line contains the maximum value that can be in a
 *  pixel.  For the images that we use, this value will always be 255 or less.
 *  If it is greater than 255, you would be dealing with 16 bit pixels; we will
 * only deal with 8 bit pixels.  So far all the data is in ascii format.  What
 * follows the maximum number is a single white space (endl will not work in
 * binary mode for outputting an image) and then the data that makes up the
 * image.  If the magic number was P3, the data will be in ascii format.  If
 * the magic number was P6, the data will be in binary format.
 *
 * The program must use overload operators.  The following operators are used
 * throughout the program:\n\n
 * '<<' Will read an image in\n
 * '>>' Will output an image\n
 * '=' Will set two images equal to each other\n
 * '==' Tests if two images are equal\n
 * '!=' Tests if two images are not equal\n\n
 *
 * The program will be run from the command line and will have to trap errors
 * such as too many arguments or not enough.  A minimal run of the program must
 * have 3 arguments supplied. The first argument in this example specifies how
 * the final image will be stored.  If a -oa is specified, the data is to bein
 * ascii format.  If a -ob is supplied, the data is to be in binary format.The
 * following argument is just the new name for the file. The user could specify
 * and option to be applied to the original image prior to output.  Only one
 * option can be specified at a time to keep things simple.  The options are
 * specified between the program name and the -o[ab].
 *
 * Only the following options are allowed:
 * -n Negate
 * -b # Brighten
 * -p Sharpen
 * -s Smooth
 * -g Grayscale
 * -c Contrast
 *
 * Lastely you can run the program using -m.  -m will bring up a menu that
 * allows you to enter the menu.  The menu will give you the ability to 
 * run the above image operations along with the following:
 *
 * salt and pepper - this will change random pixels to either black or white
 * median - this will undo the salt in pepper. 
 * image grid - this will allow you to put your image into a grid.
 * Filters - put a red, green, or blue tint to image.
 * Test Overload operators - This will prove the use of overload operators
 * emphasis - this will emphasis/brighten all of the main colors
 * pixelate - as said it will make your image grainy.
 * edge detection - will emphasis the edges in an image and darken the rest of it
 * flip - this will reorinate the image
 * Mirror Vertically - will mirror image along axis
 * Mirror Horizontally - will mirror image along axis
 * Box image - will seperate image into nine boxes and rotate them around
 * 
 * All of the above image operations with the exception of grid will output
 * the origional image along with the operations preformed on it after exiting 
 * the program.
 *
 * @par Compiling Instructions:
 *      None
 *
 * @par Usage:
 * C:\>program4.exe [option]   -o[ab]    basename      image.ppm
 * C:\>program4.exe -m
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @bug There are no bugs in the program # Making EE Great Again One Program
 * at a time.
 *
 *
 * @todo 
 *
 *
 * @par Modifications and Development Timeline:
 * <a href = "https://gitlab.mcs.sdsmt.edu/csc215f17prog4/team09/commits/master"> 
 * commit log available here </a>
 ****************************************************************************/

#include "image.h"
#include "functions.h"

/*************************************************************************//**
 * @author Samuel Coffin
 *
 * @par Description:
 * The main function.  This portion of the program will handel the command line
 * arguments.  It will produce an error message if the amount of arguments is
 * below 3 or above 6. Main also declares fin and fout variables.  Main will
 * also call the open file function, close file function and select option
 * function. At the end of main both the input and output file will be closed
 * and any dynamically allocated arrays will be cleaned up.
 *
 *
 * @param[in,out] argc - The amount of arguments coming into the program.
 * @param[in,out] argv - The arguments coming into the program. A 2D array char
 *
 * @returns 0 program ran successful.
 * @returns 1 To few or to many arguments input.
 *
 ****************************************************************************/
int main ( int argc, char **argv )
{
    ifstream fin;
    ofstream fout;
    image img1;
    int grayCheck = 0;
    int brightness = 0;
    string outputName;
	
	string inputName;
	
	string file;

    // Checks to make sure min and max arguments are within specs
    if ( argc < 4 || argc > 6 )
    {
		
		if (strcmp(argv[1], "-m") == 0)
		{
			printMenu();
			return 1;
		}

        cout << "The program requires 1, 4, 5 or 6 arguments to run" << endl;
        return 1;
    }
    
	outputName = argv[argc - 2];
	inputName = argv[argc-1];
	file = argv[argc-3];
	cout << inputName << endl;
    // Does the bear minimum.  Simply reads the file and outputs it in the
    // selected format.
    if ( argc == 4 )
    {
    
        grayCheck = img1.openFile( inputName, fin );
        img1.outputFile( outputName, inputName, file, grayCheck, fin );
    }
    
    // will open file and do the appropriate option selected.  Then output the
    // request format.
    if ( argc == 5 || argc == 6 )
    {
    
        grayCheck = img1.openFile( inputName, fin );
        
        if ( argc == 6 )
        {
            brightness = stoi ( argv[2] );
        }
		
        image pic(img1);
        grayCheck = img1.selectedOption ( argc, argv, fin, grayCheck, brightness);
        img1.outputFile( outputName, inputName, file, grayCheck, fin );

    }
    
    // will free all arrays and close the output and input file
    fin.close();
    fout.close();

    return 0;
}

/*************************************************************************//**
 * @author Samuel Coffin
 *
 * @par Description:
 * This function will call the getArray function.  It is help allocate the
 * redgray, green, and blue arrays that are used throughout the rest of the
 * program.  If an array cannot be allocated it will output and error message
 * and exit the program.
 *
 * @param[in,out]  fin - This is the input file. It is closed if allocation fail
 *
 ****************************************************************************/
void image::allocateArrays ( ifstream &fin )
{
    // allocates the arrays for the red, green, and blue arrays
    redgray = getArray ( rows, cols );
    green = getArray ( rows, cols );
    blue = getArray ( rows, cols );
    
    //simple error check for nullptr.  Will close the input file and free the
    // Allocated arrays.
    if ( redgray == nullptr || green == nullptr || blue == nullptr )
    {
        cout << "Not enough Memory" << endl;
        fin.close();
    }
    
}
/*************************************************************************//**
 * @author Samuel Coffin
 *
 * @par Description:
 * THis funciton handles the allocation and fulfillment of the output file. It
 * will create the output file and append either a .ppm or .pgm accordingly.
 * It will then call the appropriate output file type.  A grayscale, color,
 * binary, or ascii type. Will free arrays and close files if -oa or -ob not
 * seleceted for output type.
 *
 * @param[in]      outputName - name of output file
 * @param[in]      inputName - name of imput file
 * @param[in]      file - file type
 * @param[in]      grayCheck - A check to see if grayscale file needed
 * @param[in]      fin - passed in case of failure can close the file
 *
 ****************************************************************************/

void image::outputFile ( string outputName, string inputName, string file, int grayCheck,
                  ifstream &fin )
{

    ofstream fout;

    string str;
    // output name of file

    
    // used for ascii grayscale files
    if ( file == "-oa"  && grayCheck == 1 )
    {
        fileType[0] = 'P';
		fileType[1] = '2';
		str = ".pgm";
        outputName += str;
        openOutputAsciiFile ( fout, outputName );
        fout << *this;
    }
    
    // used for binay grayscale files
    else if ( file == "-ob"  && grayCheck == 1 )
    {
		fileType[0] = 'P';
		fileType[1] = '5';
        str = ".pgm";
        outputName += str;
        openOutputBinaryFile ( fout, outputName );
        fout << *this;
    }
    
    // used for ascii output files
    else if ( file == "-oa"  )
    {
        fileType[0] = 'P';
		fileType[1] = '3';
		str = ".ppm";
        outputName += str;
        openOutputAsciiFile ( fout, outputName );
        fout << *this;
    }
    
    // used for binary output files
    else if ( file == "-ob" )
    {
        fileType[0] = 'P';
		fileType[1] = '6';
		str = ".ppm";
        outputName += str;
        openOutputBinaryFile ( fout, outputName );
        fout << *this;
    }
    
    // error check for -o[ab] files if not error and close file and quit
    else
    {
        cout << "argument must be -oa or -ob" << endl;
        fin.close();
    }
}

/*************************************************************************//**
 * @author Samuel Coffin
 *
 * @par Description:
 * THis funciton handles the opening of the input file. It will open the file in
 * ascii format first to determine the file type and get the header information.
 * It will then close and reopen the file in binary format if P6 is selected.
 * If the magic number is not P3 or P6 the function will output and error
 * message and quit.
 *
 * @param[in]      inputName - the input file name
 * @param[in]      fin - passed in case of failure can close the file
 *
 * @returns 0 - wrong file type
 ****************************************************************************/

int image::openFile ( string inputName, ifstream &fin )
{
   cout << inputName << endl;
	openInputFile ( fin, inputName );
    getHeader ( fin );
	fin.close();
    
    // checks for binary file type and fills arrays
    if ( strcmp ( fileType, "P6" ) == 0 )
    {
        
        openBinaryFile ( fin, inputName );
        fin >> *this;
    }
    
    // checks for ascii file type and fills arrays
    else if ( strcmp ( fileType, "P3" ) == 0 )
    {
        openInputFile(fin, inputName);
		fin >> *this;
    }
    else if ( strcmp ( fileType, "P2" ) == 0 )
    {
        openInputFile(fin, inputName);
		fin >> *this;
		return 1;
    }
	    else if ( strcmp ( fileType, "P5" ) == 0 )
    {
        openInputFile(fin, inputName);
		fin >> *this;
		return 1;
    }
    
	
	// error checking for wrong file type
   	else
    {
        cout << "Magic Number is not P2, P3, P5 or P6" << endl;
        fin.close();
        exit ( 0 );
    }
	return 0;
}

/*************************************************************************//**
 * @author Samuel Coffin
 *
 * @par Description:
 * THis funciton handles the option that was selected.  It will call the
 * appropriate function to handle the option seleced.  It will also call an
 * error message if an appropriate option was not selected.  It will then free
 * the allocated arrays, close the input file and exit the program.
 *
 * @param[in]      argc - used to determine the placement of argv arguments
 * @param[in]      argv - The input arguments used to determine file parameters
 * @param[in,out]  fin - passed in case of failure can close the file
 * @param[in]      grayCheck - A check to see if grayscale file needed
 * @param[in]      brightness - gets the option for argv for amount to brighten.
 *
 * @returns grayCheck - Tells weather a funciton is a grayscale value.
 ****************************************************************************/

int image::selectedOption ( int argc, char **argv, ifstream &fin, 
                     int grayCheck, int brightness)
{

    string option;
    // sets option to the selected type
    option = argv[1];
    
    // option = negate
    if ( option == "-n" )
    {
        negate ( );
    }
    
    // option = sharpen
    else if ( option == "-p" )
    {
        sharpen ();
    }
    
    // option = smooth
    else if ( option == "-s" )
    {
        smooth ( );
    }
    
    // option = grayscale
    else if ( option == "-g" )
    {
        grayscale ();
        grayCheck = 1;
    }
    
    // option = contrast
    else if ( option == "-c" )
    {
        grayscale ();
        contrast ();
        grayCheck = 1;
    }
    
    // option = brighten
    else if ( option == "-b" )
    {
        brighten (brightness );
    }
    
	else if (option == "-y" )
	{
		grayscale ();
		grayCheck = 1;
	}

    // option error check output message and free arrays/ close files
    else
    {
        cout << "option specified needs to be a -n, -b #, -p, -s, -c, -g" << endl;
        fin.close();
    }
    
    // retruns if grayscale file required
    return grayCheck;
}

