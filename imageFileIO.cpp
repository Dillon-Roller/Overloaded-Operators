/*************************************************************************//**
 * @file 
 * @brief All Input and Output Functions are handled here.
 *****************************************************************************/

#include "image.h"
/*************************************************************************//**
 * @author Samuel Coffin
 * 
 * @par Description: 
 * This function will open the input file. IF the file does not open the program
 * will send out error message and exit.
 * 
 * 
 * @param[in,out]  fin - This is the input file. It is closed if allocation fail
 * @param[in]  fileName - This contains the .file name to open 
 * 
 ****************************************************************************/
void image::openInputFile(ifstream &fin, string fileName)
{
	fin.open(fileName);
	if (!fin)
	{
		cout << "File did not open" << endl;
		exit(0);
	}
}
/*************************************************************************//**
 * @author Samuel Coffin
 * 
 * @par Description: 
 * This function will open the input file. If the file does not open the program
 * will send out error message and exit.
 * 
 * @param[in,out]  fin - This is the input file. It is closed if allocation fail
 * @param[in,out]  fileName - This contains the .file name to open 
 * 
 ****************************************************************************/
void image::openBinaryFile(ifstream &fin, string fileName)
{
	fin.open(fileName, ios::in | ios::binary);

	if (!fin)
	{
		cout << "File did not open" << endl;
	}

}
/*************************************************************************//**
 * @author Samuel Coffin
 * 
 * @par Description: 
 * This function will open the input file. IF the file does not open the program
 * will send out error message and exit.
 * 
 * 
 * @param[in,out]  fout - This is the input file. It is closed if allocation fail
 * @param[in,out]  fileName - This contains the .file name to open 
 * 
 ****************************************************************************/
void image::openOutputAsciiFile(ofstream &fout, string fileName)
{
	fout.open(fileName);
	if (!fout)
	{
		cout << "ASCII output File did not open" << endl;
	}
}
/*************************************************************************//**
 * @author Samuel Coffin
 * 
 * @par Description: 
 * This function will open the input file. IF the file does not open the program
 * will send out error message and exit.
 * 
 * 
 * @param[in,out]  fout - This is the input file. It is closed if allocation fail
 * @param[in,out]  fileName - This contains the .file name to open 
 * 
 ****************************************************************************/
void image::openOutputBinaryFile(ofstream &fout, string fileName)
{
	
//	fout.open("Ballonsout.ppm");
	
	fout.open(fileName, ios::out | ios::trunc | ios::binary);


	if (!fout)
	{
		cout << " Binary File did not open" << endl;
	}

}
/*************************************************************************//**
 * @author Samuel Coffin
 * 
 * @par Description: 
 * This function will fill the output file in ASCII.  It will put in a new 
 * header and fill in the information from the arrays that are recieved from the
 * picture structure.
 * 
 * @param[in]  fout - This is the output file that will be filled with info
 * 
 ****************************************************************************/
void image::outASCII(ofstream &fout)
{
	// loop variables
	int i = 0;
	int j = 0;
	// these are requried to get whole ascii number out
	int r = 0;
	int g = 0;
	int b = 0;
	// header information
	fout << "P3" << endl;
	fout << comment << endl;
	fout << cols << " " << rows << endl;
	fout << colorBand << endl;

	// fills the file with information from arrays
	while (i < rows)
	{
		for (j = 0; j < cols; j++)
		{
			r = redgray[i][j];
			fout << r << endl; 
			g = green[i][j];
			fout << g << endl;
			b = blue[i][j];
			fout << b << endl;
		}
		i++;
	}
}
/*************************************************************************//**
 * @author Samuel Coffin
 * 
 * @par Description: 
 * This function will fill the output file in Binary.  It will put in a new 
 * header and fill in the information from the arrays that are recieved from the
 * picture structure.
 * 
 * @param[in]  fout - This is the output file that will be filled with info
 * 
 ****************************************************************************/
void image::outBinary(ofstream &fout)
{
	// loop vairables
	int i = 0;
	int j = 0;
	// header information
	fout << "P6" << endl;
	fout << comment << endl;
	fout << cols << " " << rows << endl;
	fout << colorBand << '\n';
	// fills file with binary information
	while (i < rows)
	{
		for (j = 0; j < cols; j++)
		{
			fout.write((char *)&redgray[i][j], sizeof(pixel));
			fout.write((char *)&green[i][j], sizeof(pixel));
			fout.write((char *)&blue[i][j], sizeof(pixel));

		}
		i++;
	}

}
/*************************************************************************//**
 * @author Samuel Coffin
 * 
 * @par Description: 
 * This function will fill the output file in grayscale ascii. It will put in a 
 * new header and fill in the information from the arrays that are recieved from
 * the picture structure.
 * 
 * @param[in]  fout - This is the output file that will be filled with info
 * 
 * 
 ****************************************************************************/
void image::grayAsciiOutput(ofstream &fout)
{
	// loop vairables
	int i = 0;
	int j = 0;
	// requried to output whole int and not single characters 
	int r = 0;
	// header information
	fout << "P2" << endl;
	fout << comment << endl;
	fout << cols << " " << rows << endl;
	fout << colorBand << endl;

	// loop to fill file with information from array
	while (i < rows)
	{
		for (j = 0; j < cols; j++)
		{
			r = redgray[i][j];
			fout << r << endl;
		}
		i++;
	}
}
/*************************************************************************//**
 * @author Samuel Coffin
 * 
 * @par Description: 
 * This function will fill the output file in grayscale binary. It will put in a 
 * new header and fill in the information from the arrays that are recieved from
 * the picture structure.
 * 
 * @param[in]  fout - This is the output file that will be filled with info
 * 
 * 
 ****************************************************************************/
void image::grayBinaryOutput(ofstream &fout)
{
	// loop varaibles
	int i = 0;
	int j = 0;
	// header information
	fout << "P5" << endl;
	fout << comment << endl;
	fout << cols << " " << rows << endl;
	fout << colorBand << '\n';
	// loop to fill informaiton
	while (i < rows)
	{
		for (j = 0; j < cols; j++)
		{
			fout.write((char *)&redgray[i][j], sizeof(pixel));
		}
		i++;
	}

}
/*************************************************************************//**
 * @author Samuel Coffin
 * 
 * @par Description: 
 * This function will fill get the header information from the input file. It
 * will store this information in the picture structure.  It ignores the last
 * white space for the binary files.
 * 
 * @param[in]  fin - This is the input file that contains the header info
 * 
 * 
 ****************************************************************************/
void image::getHeader(ifstream &fin)
{
	// used to check if a comment is in input file
	char commentCheck[2];
	fin.getline(fileType, 3);
	// actually checks to see if comment is there
	commentCheck[1] = fin.peek();
	if (commentCheck[1] == '#')
	{
		fin.getline(comment, 81);
	}
	// fills header information
	fin >> cols;
	fin >> rows;
	fin >> colorBand;
	// used to ignore whitespace for binary files
	fin.ignore();
}
/*************************************************************************//**
 * @author Samuel Coffin
 * 
 * @par Description: 
 * This function will fill the arrays stored in the picture structure from the
 * input ascii file.
 * 
 * @param[in]  fin - This is the intput file that contains the information
 * 
 * 
 ****************************************************************************/
void image::fillASCII(ifstream &fin)
{
	// loop vairables
	int i = 0;
	int j = 0;
	// used to get whole int from file
	int r = 0;
	int g = 0;
	int b = 0;
	// loop to retrieve info from file and save in allocated arrays
	while (i < rows)
	{

		for (j = 0; j < cols; j++)
		{
		
			if (strcmp(fileType, "P2") == 0)
			{
				fin >> r;
				redgray[i][j] = r;
			}
			else
			{
			fin >> r;
			redgray[i][j] = r;
			fin >> g;
			green[i][j] = g;
			fin >> b;
			blue[i][j] = b;
			}
		}
		i++;
	}
}
/*************************************************************************//**
 * @author Samuel Coffin
 * 
 * @par Description: 
 * This function will fill the arrays stored in the picture structure from the
 * input binary file.
 * 
 * @param[in]  fin - This is the intput file that contains the information
 * 
 * 
 ****************************************************************************/
void image::fillBinary( ifstream &fin)
{
	// loop vairables
	int i = 0;
	int j = 0;
	// retrieves binary info from file
	while (i < rows)
	{
		for (j = 0; j < cols; j++)
		{
			if (strcmp(fileType, "P5") == 0)
				fin.read((char *)&redgray[i][j], sizeof(pixel));
			else
				fin.read((char *)&redgray[i][j], sizeof(pixel));
				fin.read((char *)&green[i][j], sizeof(pixel));
				fin.read((char *)&blue[i][j], sizeof(pixel));
		}
		i++;
	}


}


