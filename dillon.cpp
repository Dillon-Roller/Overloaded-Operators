/*************************************************************************//**
 * @file 
 * @brief All functions done by Dillon Roller 
 *****************************************************************************/
#include "image.h"
#include <algorithm>

/**************************************************************************//**
 * @author Dillon Roller
 *
 * @par Description: Tests all of the overloaded operator and shows the user
 * that they work. 
 *
 *****************************************************************************/
void image::testOperators()
{
    //variables used to test the operators
    image img1, img2;
    ifstream fin;
    ofstream fout;
    string name, extension;
    int choice = 0;

    cout << "Tests overloaded operators for this program. Use binary images"
        << " for speed and simplicity.\n\n"
        << "Enter image name to input from your directory(binary): ";
    cin >> name;

    //checks if it has proper name
    if ( !testName(name ) )
        return;

    extension = name.substr( name.size() - 4 );
    openBinaryFile( fin, name );

    //checks if file opened
    if ( !fin ) 
        return;

    openOutputBinaryFile( fout, "TestInputOutput" + extension );

    //checks if output file opened
    if ( !fout )
    {
        fin.close();
        return;
    }

    testInputOutput( fin, fout, img1 );

    cout << "Enter name of another image to compare to the first (can be "
        << "the same image): ";
    cin >> name;

    openBinaryFile( fin, name ); 
    //checks if input file opened
    if ( !fin ) 
        return;
    testEquality( img1, img2, fin );
    
    testAssignment( fin, fout, name, extension, img1, img2 );
}
/**************************************************************************//**
 * @author Dillon Roller
 *
 * @par Description: Helper function that verifies that the output file name
 * has the correct extension, being either '.ppm' or '.pgm'. 
 *
 * @param[in] name - string holding output file name
 * 
 * @returns true - name has correct extension
 * @returns false - name has incorrect extension
 *****************************************************************************/
bool image::testName( const string& name )
{
    if ( name.size() > 4 && ( name.substr( name.size() - 4 ) == ".ppm" ||
        name.substr( name.size() - 4 ) == ".pgm" ) )
    {
        return true;
    }
    else
    {
        cout << "Invalid file extension type\n" << endl;
        return false;
    }
}
/**************************************************************************//**
 * @author Dillon Roller
 *
 * @par Description: Inputs and outputs image using '>>'. Previews the code
 * to the user as it's being used.
 *
 * @param[in] fin - ifstream to input image
 * @param[in] fout - ofstream to output image
 * @param[in] img1 - stores the image
 *
 *****************************************************************************/
void image::testInputOutput( ifstream& fin, ofstream& fout, image& img1 )
{
    fin >> img1;
    fout << img1;
    cout << "\nfin >> img1;" << endl;
    cout << "fout << img1;\n" << endl;
    cout << "A file named \"TestInputOutput\" has been outputted to your "
        << "directory using the operators\n" << endl;
    fin.close();
    fout.close();
}
/**************************************************************************//**
 * @author Dillon Roller
 *
 * @par Description: Tests for equalities between images for testOperator 
 * menu. Previews actual code to the user that are being used in the program.
 *
 * @param[in] img1 - image on lhs
 * @param[in] img2 - image on rhs
 * @param[in] fin - file stream to handle input
 *
 *****************************************************************************/
void image::testEquality( const image& img1, image& img2, ifstream& fin )
{
    fin >> img2;
    cout << "\nfin >> img2;\n" << endl;
    cout << "Using '==' and '!=' to compare the two images, the following"
        << " logic statement is true:\n\n";

    if ( img1 == img2 )
        cout << "img1 == img2" << endl;
    if ( img1 != img2 )
        cout << "img1 != img2" << endl;
    cout << endl;
    fin.close();
}
/**************************************************************************//**
 * @author Dillon Roller
 *
 * @par Description: Previews to the user the code actually used to assign
 * one image to another. Basically tests that the assignment operator '=' is 
 * working for the image class. It returns out early if there is an error 
 * reading an image 
 *
 * @param[in] fin - ifstream holding input image
 * @param[in] fout - ofstream holding output image
 * @param[in] name - name of output image
 * @param[in] extension - the extension of the output file (.ppm / .pgm)
 * @param[in] img1 - image on the lhs
 * @param[in] img2 - image on the rhs
 * 
 * @returns none
 *
 *****************************************************************************/
void image::testAssignment( ifstream& fin, ofstream& fout, string& name, 
    string& extension, image& img1, image& img2 )
{
    cout << "Assignment test: img1 = img2\n"
        << "Enter name of img1 (binary): ";
    cin >> name;
    openBinaryFile( fin, name );
    if ( !fin ) 
        return;
    fin >> img1;
    fin.close();

    cout << "Enter name of img2 (binary): ";
    cin >> name;
    if ( !testName( name ) )
        return;
    extension = name.substr( name.size() - 4 );
    openBinaryFile( fin, name );
    if ( !fin ) 
        return;
    fin >> img2;
    fin.close();

    img1 = img2;
    openOutputBinaryFile( fout, "TestAssignment" + extension );
    fout << img1;
    cout << "\nfin >> img1;\n"
        << "fin2 >> img2;\n"
        << "img1 = img2\n"
        << "fout << img1\n" << endl;
    cout << "A file named \"TestAssignment\" has been outputted to your "
        << "directory.\nIt should contain all data img2 has.\n" << endl;
    fout.close();
}
/**************************************************************************//**
 * @author Dillon Roller
 *
 * @par Description: Outputs an image to an ofstream by calling the appropriate
 * output function depending on what type of image it is.
 *
 * @param[in] fout - ofstream to write file to
 * @param[in] img - image to output with fout
 *
 * @returns fout - returns a reference to this (for chaining)
 *
 *****************************************************************************/
ofstream &operator << ( ofstream &fout, image &img )
{
    //outputs image depending on its type
    if ( strcmp( img.fileType, "P3" ) == 0 )
        img.outASCII( fout );

    if ( strcmp( img.fileType, "P2" ) == 0 )
        img.grayAsciiOutput( fout );

    if ( strcmp( img.fileType, "P6" ) == 0 )
        img.outBinary( fout );

    if ( strcmp( img.fileType, "P5" ) == 0 )
        img.grayBinaryOutput( fout );

    return fout;
}
/**************************************************************************//**
 * @author Dillon Roller
 *
 * @par Description: Reads an image into a file handle using the fillASCII
 * and fillBinary functions, depending on image type. This functions
 * returns a reference to the ifstream so that you can chain multiple 
 * statements together.
 *
 * @param[in] fin - ifstream to read image into
 * @param[in] img - image to be read into ifstream
 *
 * @returns a reference to fin
 *
 *****************************************************************************/
ifstream &operator >> ( ifstream &fin, image &img )
{
    //grabs header info and allocated arrays to hold pixel values
    img.getHeader( fin );
    img.allocateArrays( fin );

    //fills pixel values depending on image type
    if ( strcmp( img.fileType, "P3" ) == 0 || 
         strcmp( img.fileType, "P2" ) == 0 )
        img.fillASCII( fin );
    else
        img.fillBinary( fin );
    return fin;
}

/**************************************************************************//**
 * @author Dillon Roller
 *
 * @par Description: Assignment operator for images. This function assigns the 
 * images on the rhs to the one of the lhs. It does this using the copy-and-
 * swap idiom. Passing in the rhs image by value calls the copy constructor 
 * and passed a copy of rhs into the function. The swapImage function then
 * swaps the contents of the copy of rhs with that of the lhs (current instance
 * of image '*this'). After function finishes, the destructor is called
 * and destroys the copy of the rhs, leaving only the new contents inside lhs.
 * This function returns a reference to the current instance of the object 
 * (This allows you to chain multiple '=' statements)
 * 
 * @param[in] rhs - image on rhs
 *
 * @returns a reference to the current image
 *****************************************************************************/
image& image::operator = ( image rhs )
{
    swapImage( *this, rhs );
    return *this;
}

/**************************************************************************//**
 * @author Dillon Roller
 *
 * @par Description: Determines whether or not two images are equal. It does 
 * this by going through each item individually inside the image file and 
 * checking that they are equal. If an item is found to not be equal, this
 * function returns false. If it makes it to the end of the function, this 
 * means that all items compared equal and it returns true
 *
 * @param[in] rhs - image on rhs being compared
 * 
 * @returns true - Both images are equal
 * @returns false - Both images are not equal
 *****************************************************************************/
bool image::operator == ( const image& rhs ) const 
{
    //compares file types
    if ( strcmp( fileType, rhs.fileType ) != 0 )
    {
        return false;
    }
    //compares header info
    if ( rows != rhs.rows || cols != rhs.cols || colorBand != rhs.colorBand ||
        minimum != rhs.minimum || maximum != rhs.maximum )
    {
        return false;
    }
    //compares each individual pixel value
    int i, j;
    for ( i = 0; i < rows; i++ )
        for ( j = 0; j < cols; j++ )
        {
            if ( redgray[i][j] != rhs.redgray[i][j] ||
                green[i][j] != rhs.green[i][j] ||
                blue[i][j] != rhs.blue[i][j] )
            {
                return false;
            }
        }
    //if all are equal, they are equal
    return true;
}
/**************************************************************************//**
 * @author Dillon Roller
 *
 * @par Description: Determines whether or not two images are equal to each 
 * other. It does this by using the previously implemented overloaded operator
 * '==' and checks if it returns false. If it returns false, it is not equal,
 * and this function returns true. If the '==' function returns true, it is 
 * equal, and this function returns false
 *
 * @param[in] rhs - image on rhs being compared
 *
 * @returns true - two images are not equal
 * @returns false - two images are equal
 *****************************************************************************/
bool image::operator != ( const image &rhs ) const
{
    return !( *this == rhs );
}
/**************************************************************************//**
 * @author Dillon Roller
 *
 * @par Description: Mirrors an image about the x-axis
 *
 *****************************************************************************/
void image::mirrorUpDown()
{
    int i, j;
    for ( i = 0; i < rows / 2; i++ )
    {
        for ( j = 0; j < cols; j++ )
        {
            redgray[rows - i - 1][j] = redgray[i][j];
            green[rows - i - 1][j] = green[i][j];
            blue[rows - i - 1][j] = blue[i][j];
        }
    }
}
/**************************************************************************//**
 * @author Dillon Roller
 *
 * @par Description: Mirrors an image about the y-axis
 *
 *****************************************************************************/
void image::mirrorLeftRight()
{
    int i, j;
    for ( i = 0; i < rows; i++ )
    {
        for ( j = 0; j < cols / 2; j++ )
        {
            redgray[i][cols - j - 1] = redgray[i][j];
            green[i][cols - j - 1] = green[i][j];
            blue[i][cols - j - 1] = blue[i][j];
        }
    }
}
/**************************************************************************//**
 * @author Dillon Roller
 *
 * @par Description: Flips an image about the x-axis
 *
 *****************************************************************************/
void image::flip()
{ 

    int i, j;
    for ( i = 0; i < rows / 2; i++ )
    {
        for ( j = 0; j < cols; j++ )
        {
            swap( redgray[i][j], redgray[rows - i - 1][j] );
            swap( green[i][j], green[rows - i - 1][j] );
            swap( blue[i][j], blue[rows - i - 1][j] );
        }
    }
}
/**************************************************************************//**
 * @author Dillon Roller
 *
 * @par Description: This function swaps each item in the file with the other.
 * Can be used to swap the contents of two image files. 
 * This program utilizes this swap function to efficiently assign one image to 
 * another using the overloaded '=' operator. 
 *
 * @param[in] img1 - image whose contents are being swapped with img2
 * @param[in] img2 - image whose contents are being swapped with img1
 *
 *****************************************************************************/
void swapImage( image &img1, image &img2 )
{
    swap( img1.rows, img2.rows );
    swap( img1.cols, img2.cols );
    swap( img1.colorBand, img2.colorBand );
    swap( img1.minimum, img2.minimum );
    swap( img1.maximum, img2.maximum );
    swap( img1.fileType, img2.fileType );
    swap( img1.comment, img2.comment );
    swap( img1.redgray, img2.redgray );
    swap( img1.green, img2.green );
    swap( img1.blue, img2.blue );
}