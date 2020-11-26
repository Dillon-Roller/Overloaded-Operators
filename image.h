/*************************************************************************//**
 * @file
 * @brief Overview of the structure file
 *****************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <stdlib.h>   
#include <time.h>
#include <algorithm>

using namespace std;

#ifndef IMAGE_H_
#define IMAGE_H_
/*!
* @brief pixel contains all of the image arrays
*/
typedef unsigned char pixel;

/*!
* @brief allows easy manipulation to of image
*/
class image
{
    public:
        image();
        image ( image &pic );
        ~image();
        
		void allocateArrays ( ifstream &fin );
		void outputFile (  string outputName, string inputName, string file, int grayCheck,
                  ifstream &fin );
        int openFile (  string inputName, ifstream &fin);
		int selectedOption (  int argc, char **argv, ifstream &fin, 
			 int grayCheck, int brightness);
		
        image &operator = ( image rhs );
        bool operator == ( const image& rhs ) const;
        bool operator != ( const image& rhs ) const;
        void brighten( int value );
		void smooth();
		void sharpen();
		void contrast();
		void grayscale();
		void printTwo( image &pic );
		void grid ();
		void getNewArrays( int row, int col );
		void pixelate();
		void emphasis();
		void filters();
		void median ( );
		void negate();
        void salt_pepper();
        void box();
        void check_size();
        void box_allocate( pixel **&boxr,pixel **&boxg,pixel **&boxb,
            int box_rows, int box_cols );
        void box_fill( pixel**boxr,pixel **boxg,pixel **boxb,int box_rows, 
            int box_cols, int boxrow,int boxcol,int spotx,int spoty );
        void box_back( pixel**boxr,pixel **boxg,pixel **boxb,int box_rows, 
            int box_cols, int boxrow,int boxcol,int spotx,int spoty );
        void box_freeing ( int box_rows, pixel**boxr,pixel **boxg,pixel **boxb);
        

        friend ofstream &operator << ( ofstream &fout, image &img );
        friend ifstream &operator >> ( ifstream &fin, image &img );
        void mirrorUpDown();
        void mirrorLeftRight();
        void flip();
        friend void swapImage( image& img1, image& img2 );
        void testOperators();
        void testInputOutput( ifstream& fin, ofstream& fout, image& img1 );
        void testEquality( const image& img1, image& img2, ifstream& fin );
        void testAssignment( ifstream& fin, ofstream& fout, string& name,
            string& extension, image& img1, image& img2 );
        bool testName( const string& name );
		void edgeDetect();


    protected:
        unsigned char **getArray(int rows, int col);
		void freeArray( unsigned char **&ptr, int rows);
		void openOutputAsciiFile(ofstream &fout, string fileName);
		void openOutputBinaryFile(ofstream &fout, string fileName);
		void outASCII( ofstream &fout);
		void outBinary(ofstream &fout);
		void grayAsciiOutput(ofstream &fout);
		void grayBinaryOutput(ofstream &fout);
		void openInputFile(ifstream &fin, string fileName);
		void openBinaryFile(ifstream &fin, string fileName);
		void getHeader(ifstream &fin);
		void fillASCII(ifstream &fin);
		void fillBinary( ifstream &fin);


    private:
    
        int rows;   /*!< Number of rows in input file*/
        int cols;   /*!< Numer of cols in input file*/
        int colorBand;  /*!< Max number of colors allowed in input file*/
        int minimum;  /*!< Holds minimum value of pixel in an image */
        int maximum; /*!< Holds maximum value of pixel in an image */
        char fileType[3];   /*!< determines weather binary or ascii or grayscale*/
        char comment[81] = "";  /*!< allocates room if there is comment in input*/
        
        pixel **redgray; /*!< redgray array */
        pixel **green;    /*!< green array */
        pixel **blue;       /*!< blue array */
        
        
};

#endif

