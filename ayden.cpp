/*************************************************************************//**
 * @file
 * @brief Functions done by Ayden Drabek
 *****************************************************************************/
#include "image.h"

/**************************************************************************//**
 * @author Ayden Drabek
 *
 * @par Description: The salt_pepper function goes through the image randomly
 *  putting white and black pixels in. The next black or white pixel will be
 *  a random number between 1 and 51 from the last black or white pixel.
 *
 *
 *****************************************************************************/

void image::salt_pepper()
{
    int x = 0;
    int y = 0;
    srand ( (unsigned int)time ( NULL ) );
    
    //randomly counts up for the rows
    for ( x = 0; x < rows; x += rand() % 50  )
    {
        //randomly counts up for the columns
        for ( y = 0; y < cols; y += rand() % 50 + 1 )
        {
            //sets that random pixel to black
            redgray[x][y] = 0;
            green[x][y] = 0;
            blue[x][y] = 0;
            
            
        }
        
    }
    
    //rando counts up for the rows
    for ( x = 0; x < rows; x += rand() % 50 + 1  )
    {
        //randomly counts up for the columns
        for ( y = 0; y < cols; y += rand() % 50 + 1 )
        {
            //sets the random pixel to white
            redgray[x][y] = 255;
            green[x][y] = 255;
            blue[x][y] = 255;
            
            
        }
        
    }
}

/**************************************************************************//**
 * @author Ayden Drabek
 *
 * @par Description:  The median function walks through the image checking to
 *  see if there are any black or white pixels. If there is it takes the 
 *  average of all the pixels around it to fill the pixel. Its main use is to
 *  undo the salt_pepper function.
 *
 *
 *****************************************************************************/
void image::median ( )
{
    int x = 1, y = 1;
    //walks through the color arrays
    for ( x = 1; x < ( rows - 1 ); x++ )
    {
        for ( y = 1; y < ( cols - 1 ); y++ )
        {
            //checks to see if the pixel is white or black
            if ( ( redgray[x][y] == 0 && green[x][y] == 0 && blue[x][y] == 0 ) ||
                  ( redgray[x][y] == 255 && green[x][y] == 255 
                      && blue[x][y] == 255 ) )
            {
            //takes the average of all the pixels around the pixel under 
            //question and sets it the that average. Does this for the redgray
            //green and blue.
                redgray[x][y]  = pixel ( max ( ( long ) 0, min ( ( long ) 255,
                                       long ( ( ( long ) redgray[x - 1][y - 1] +
                                       ( long ) redgray[x - 1][y] +
                                       ( long ) redgray[x - 1][y + 1] +
                                       ( long ) redgray[x][y - 1] +
                                       ( long ) redgray[x][y + 1] +
                                       ( long ) redgray[x + 1][y - 1] +
                                       ( long ) redgray[x + 1][y] +
                                       ( long ) redgray[x + 1][y + 1] ) /
                                        8.0 ) ) ) );
                green[x][y]  = pixel ( max ( ( long ) 0, min ( ( long ) 255,
                                           long ( ( ( long ) green[x - 1][y - 1]
                                             + ( long ) green[x - 1][y] +
                                             ( long ) green[x - 1][y + 1] +
                                             ( long ) green[x][y - 1] +
                                             ( long ) green[x][y + 1] +
                                             ( long ) green[x + 1][y - 1] +
                                             ( long ) green[x + 1][y] +
                                             ( long ) green[x + 1][y + 1] ) /
                                                    8.0 ) ) ) );
                blue[x][y]  = pixel ( max ( ( long ) 0, min ( ( long ) 255,
                                            long ( ( ( long ) blue[x - 1][y - 1] 
                                            + ( long ) blue[x - 1][y] +
                                            ( long ) blue[x - 1][y + 1] +
                                            ( long ) blue[x][y - 1] +
                                            ( long ) blue[x][y + 1] +
                                            ( long ) blue[x + 1][y - 1] +
                                            ( long ) blue[x + 1][y] +
                                            ( long ) blue[x + 1][y + 1] ) /
                                                   8.0 ) ) ) );
            }
        }
    }
}
/**************************************************************************//**
 * @author Ayden Drabek
 *
 * @par Description: The filter function simply lets the user chose which filter
 *  they would like to apply then sets the other 2 color arrays to 0
 *
 *
 *****************************************************************************/
void image::filters()
{
    char filter;
    int x = 0, y = 0;
    //gets the users filter choice
    cout << "Enter filter choice(r-red, b-blue, g-green): ";
    cin >> filter;
    //checks the users choice
    switch ( filter )
    {
        case 'r':
            //sets all values in the green and blue arrays to 0
            for ( x = 0; x < rows; x++ )
            {
            
                for ( y = 0; y < cols; y++ )
                {
                    green[x][y] = 0;
                    blue[x][y] = 0;
                    
                    
                }
                
            }
            
            break;
            
            
        case 'g':
            //sets all values in the red and blue arrays to 0
            for ( x = 0; x < rows; x++ )
            {
            
                for ( y = 0; y < cols; y++ )
                {
                    redgray[x][y] = 0;
                    blue[x][y] = 0;
                    
                    
                }
                
            }
            
            break;
            
        case 'b':
            //sets all values in the green and red arrays to 0
            for ( x = 0; x < rows; x++ )
            {
            
                for ( y = 0; y < cols; y++ )
                {
                    redgray[x][y] = 0;
                    green[x][y] = 0;
                    
                    
                }
                
            }
            
            break;
            
        default:
            cout << "Please choose valid choice"<<endl;
    }
}



/**************************************************************************//**
 * @author Ayden Drabek
 *
 * @par Description: The emphasis function walks through the different color
 *  arrays and finds which one has the highest value for each pixel.
 *  Then it sets the other 2 color arrays to 0. Thus emphasising the main color
 *  in each pixel
 *
 *
 *****************************************************************************/
void image::emphasis()
{
    int x = 0, y = 0;
    
    //walks though the color arrays
    for ( x = 0; x < rows; x++ )
    {
        for ( y = 0; y < cols; y++ )
        {
            //check to see if red is the greatest value.
            if ( redgray[x][y] > green[x][y] && redgray[x][y] > blue[x][y] )
            {
                //sets other 2 arrays to 0.
                green[x][y] = 0;
                blue[x][y] = 0;
            }
            
            //check to see if green is the greatest value
            if ( redgray[x][y] < green[x][y] && green[x][y] > blue[x][y] )
            {
                //sets other 2 arrays to 0.
                redgray[x][y] = 0;
                blue[x][y] = 0;
            }
            //checks to see if blue is the greatest value.
            if ( blue[x][y] > redgray[x][y] && green[x][y] < blue[x][y] )
            {
                //sets other 2 arrays to 0.
                redgray[x][y] = 0;
                green[x][y] = 0;
            }
        }
    }
    
}


/**************************************************************************//**
 * @author Ayden Drabek
 *
 * @par Description: The pixelate function walks though the arrays putting 
 *  either a white or black pixel in all the even columns and rows. It determines
 *  which color by taking the average of the 3 color arrays if it is greater 
 *  then 128 it sets the pixel to white if not it sets it to black.
 *
 *
 *****************************************************************************/
void image::pixelate()
{
    int x = 0, y = 0;
    int average = 0;
    //walks through the array.
    for ( x = 0; x < rows; x += 2 )
    {
        for ( y = 0; y < cols; y += 2 )
        {
            //find the average of the pixel in question
            average = ( redgray[x][y] + green[x][y] + blue[x][y] ) / 3;
            //check to see if the average is less the 128
            if ( average < 128 )
            {
                //sets the pixel to black
                redgray[x][y] = 0;
                green[x][y] = 0;
                blue[x][y] = 0;
            }
            //if the average is greater then 128 it sets the pixel to white.
            else
            {
            
                redgray[x][y] = 255;
                green[x][y] = 255;
                blue[x][y] = 255;
                
            }
            
            
        }
        
        
        
    }
    
    
}


/**************************************************************************//**
 * @author Ayden Drabek
 *
 * @par Description: The box is the main function to seperate the image out 
 *  into 9 different boxes. Once it does this it can rearrenge the boxes if 
 *  need be. If the image is not divisable by 3 it calls a function that changes
 *  the size of the image to be divisable by 3.
 *
 *
 *****************************************************************************/
void image::box()
{
    int box_rows = 0, box_cols = 0;
    //calls check_size which makes sure the image is divisable by 3 and if not 
    // changes the size so it is.
    check_size();
    box_rows = rows / 3;
    box_cols = cols / 3;

    //initializs 27 new arrays. a red, blue and green for each of the 9 boxes
    pixel **boxr1 = nullptr, **boxr2 = nullptr, **boxr3 = nullptr,
            **boxr4 = nullptr , **boxr5 = nullptr, **boxr6 = nullptr,
            **boxr7 = nullptr, **boxr8 = nullptr, **boxr9 = nullptr;
    pixel **boxg1 = nullptr, **boxg2 = nullptr, **boxg3 = nullptr,
            **boxg4 = nullptr, **boxg5 = nullptr, **boxg6 = nullptr,
            **boxg7 = nullptr, **boxg8 = nullptr, **boxg9 = nullptr;
    pixel **boxb1 = nullptr, **boxb2 = nullptr, **boxb3 = nullptr,
            **boxb4 = nullptr, **boxb5 = nullptr, **boxb6 = nullptr,
            **boxb7 = nullptr, **boxb8 = nullptr, **boxb9 = nullptr;
    //calls a function that allocates each of the new arrays            
    box_allocate ( boxr1, boxg1, boxb1, box_rows, box_cols );
    box_allocate ( boxr2, boxg2, boxb2, box_rows, box_cols );
    box_allocate ( boxr3, boxg3, boxb3, box_rows, box_cols );
    box_allocate ( boxr4, boxg4, boxb4, box_rows, box_cols );
    box_allocate ( boxr5, boxg5, boxb5, box_rows, box_cols );
    box_allocate ( boxr6, boxg6, boxb6, box_rows, box_cols );
    box_allocate ( boxr7, boxg7, boxb7, box_rows, box_cols );
    box_allocate ( boxr8, boxg8, boxb8, box_rows, box_cols );
    box_allocate ( boxr9, boxg9, boxb9, box_rows, box_cols );

    //fills each box with the corresponding values from the original color arrays.
    box_fill ( boxr1, boxg1, boxb1, box_rows, box_cols,
               box_rows, box_cols, 0, 0 );
    box_fill ( boxr2, boxg2, boxb2, box_rows, box_cols * 2,
               box_rows, box_cols, 0, box_cols );
    box_fill ( boxr3, boxg3, boxb3, box_rows, box_cols * 3,
               box_rows, box_cols, 0, box_cols * 2 );
    box_fill ( boxr4, boxg4, boxb4, box_rows * 2, box_cols,
               box_rows, box_cols, box_rows, 0 );
    box_fill ( boxr5, boxg5, boxb5, box_rows * 2, box_cols * 2,
               box_rows, box_cols, box_rows, box_cols );
    box_fill ( boxr6, boxg6, boxb6, box_rows * 2, box_cols * 3,
               box_rows, box_cols, box_rows, box_cols * 2 );
    box_fill ( boxr7, boxg7, boxb7, box_rows * 3, box_cols,
               box_rows, box_cols, box_rows * 2, 0 );
    box_fill ( boxr8, boxg8, boxb8, box_rows * 3, box_cols * 2,
               box_rows, box_cols, box_rows * 2, box_cols );
    box_fill ( boxr9, boxg9, boxb9, box_rows * 3, box_cols * 3,
               box_rows, box_cols, box_rows * 2, box_cols * 2 );
               
               cout<<"did fill"<<endl;
    //puts the data from the new arrays back into the original arrays. 
    //By changing th box number in each call you can move the boxes around.
    box_back ( boxr3, boxg3, boxb3, box_rows, box_cols,
               box_rows, box_cols, 0, 0 );
    box_back ( boxr6, boxg6, boxb6, box_rows, box_cols * 2,
               box_rows, box_cols, 0, box_cols - 1 );
    box_back ( boxr9, boxg9, boxb9, box_rows, box_cols * 3,
               box_rows, box_cols, 0, box_cols * 2 - 2 );
    box_back ( boxr2, boxg2, boxb2, box_rows * 2, box_cols,
               box_rows, box_cols, box_rows - 1, 0 );
    box_back ( boxr5, boxg5, boxb5, box_rows * 2, box_cols * 2,
               box_rows, box_cols, box_rows - 1, box_cols - 1 );
    box_back ( boxr8, boxg8, boxb8, box_rows * 2, box_cols * 3,
               box_rows, box_cols, box_rows - 1, box_cols * 2 - 2 );
    box_back ( boxr1, boxg1, boxb1, box_rows * 3, box_cols,
               box_rows, box_cols, box_rows * 2 - 2, 0 );
    box_back ( boxr4, boxg4, boxb4, box_rows * 3, box_cols * 2,
               box_rows, box_cols, box_rows * 2 - 2, box_cols - 1 );
    box_back ( boxr7, boxg7, boxb7, box_rows * 3, box_cols * 3,
               box_rows, box_cols, box_rows * 2 - 2, box_cols * 2 - 2 );
               cout<<"did refill";
    //calls a function to free up the 27 box arrays.
    box_freeing ( box_rows, boxr1, boxg1, boxb1 );
    box_freeing ( box_rows, boxr2, boxg2, boxb2 );
    box_freeing ( box_rows, boxr3, boxg3, boxb3 );
    box_freeing ( box_rows, boxr4, boxg4, boxb4 );
    box_freeing ( box_rows, boxr5, boxg5, boxb5 );
    box_freeing ( box_rows, boxr6, boxg6, boxb6 );
    box_freeing ( box_rows, boxr7, boxg7, boxb7 );
    box_freeing ( box_rows, boxr8, boxg8, boxb8 );
    box_freeing ( box_rows, boxr9, boxg9, boxb9 );
}

/**************************************************************************//**
 * @author Ayden Drabek
 *
 * @par Description: The check size function check to see if the image passed
 *  in has a size that is divisable by 3. If it is not then it fills 3 temp
 *  arrays with the data from the original color arrays and the frees them up.
 *  after it does this it then reallocates those original arrays to the new 
 *  size that is divisable by 3. Once they are allocated it copys the data 
 *   back into them from the temp arrays.
 *
 *
 *****************************************************************************/
void image::check_size()
{
    //find the new size of the arrays
    int temprows=rows, tempcols=cols;
    int tolong_rows = rows - rows % 3;
    int tolong_cols = cols - cols % 3;
    //if the new size and old size are not equal it means the old size is not 
    //divisable by 3
    if ( tolong_rows != rows || tolong_cols != cols )
    {
        //initalizes 3 temp arrays
        pixel **tempred = nullptr, **tempgreen = nullptr, **tempblue = nullptr;
        //allocates the temp arrays
        tempred = getArray ( tolong_rows, tolong_cols );
        tempgreen = getArray ( tolong_rows, tolong_cols );
        tempblue = getArray ( tolong_rows, tolong_cols );
        

        //walks through the arrays copying the original data into the temp 
        //arryas
        for ( int x = 0; x < tolong_rows; x++ )
        {
            for ( int y = 0; y < tolong_cols; y++ )
            {
                tempred[x][y] = redgray[x][y];
                tempgreen[x][y] = green[x][y];
                tempblue[x][y] = blue[x][y] ;
            }
            
        }
        //frees up the original arrays
        freeArray ( redgray, rows  );
        freeArray (  green, rows );
        freeArray ( blue, rows );
        //changes the size of the image
        rows = tolong_rows;
        cols = tolong_cols;
        //reallocates the original arrays as the new size
        redgray = getArray ( rows, cols );
        green = getArray ( rows, cols );
        blue = getArray ( rows, cols );
        
        //copys the data back into the original arrays
        for ( int x = 0; x < tolong_rows; x++ )
        {
            for ( int y = 0; y < tolong_cols; y++ )
            {
                redgray[x][y] = tempred[x][y];
                green[x][y] = tempgreen[x][y];
                blue[x][y] = tempblue[x][y];
            }
            
        }
        //frees up the temp arrays
        freeArray ( tempred, rows  );
        freeArray ( tempgreen, rows  );
        freeArray ( tempblue, rows  );
    }
}
/**************************************************************************//**
 * @author Ayden Drabek
 *
 * @par Description: The box_allocate fncton is just a helper function to 
 *  decrease the number of lines in box. It simply calls the getArray function
 *  for each of array for the passes in box
 *
 * @param[in]   boxr - is the red array for each box that is passed in.
 * @param[in]   boxg - is the gren array for each box that is passed in.
 * @param[in]   boxb - is the blue array for each box that is passed in.
 * @param[in]   box_rows - is the number of rows in each of the new box arrays.
 * @param[in]   box_cols - is the number of columns in each of the new box arrays.
 *
 *
 *****************************************************************************/
void image::box_allocate ( pixel ** &boxr, pixel ** &boxg, pixel ** &boxb,
                           int box_rows, int box_cols )
{
    //allocates memory for each of the new color arrays.
    boxr = getArray ( box_rows, box_cols );
    boxg = getArray ( box_rows, box_cols );
    boxb = getArray ( box_rows, box_cols );
    
}
/**************************************************************************//**
 * @author Ayden Drabek
 *
 * @par Description: The box_fill function takes in the parameters for each of 
 *  the new boxes and fills each box with the appropriate data from the original
 *  color arrays.
 *
 * @param[in]   boxr - is the red array for each box that is passed in.
 * @param[in]   boxg - is the gren array for each box that is passed in.
 * @param[in]   boxb - is the blue array for each box that is passed in.
 * @param[in]   box_rows - is the row where in the original array the copying 
 *                  should stop
 * @param[in]   box_cols - is the column where in the original array the copying 
 *                 should stop
 * @param[in]   boxrow - is the row where the data being copied to the new 
 *                  box array should stop
 * @param[in]   boxcol - is the column where the data being copied to the new 
 *                  box array should stop
 * @param[in]   spotx - is the row in the original color arrays the copying 
 *                  should start
 * @param[in]   spoty - is the column in the original color arrays the copying 
 *                  should start
 *
 *
 *****************************************************************************/
void image::box_fill ( pixel **boxr, pixel **boxg, pixel **boxb,
                       int box_rows, int box_cols,int boxrow, int boxcol, 
                       int spotx, int spoty )
{
    int r = 0, c = 0, x = 0, y = 0;
    
    for ( r = 0, x = spotx; r < boxrow && x < box_rows - 1; r++, x++ )
    {
        for ( c = 0, y = spoty; c < boxcol && y < box_cols - 1; c++, y++ )
        {
        
            boxr[r][c] = redgray[x][y];
            boxg[r][c] = green[x][y];
            boxb[r][c] = blue[x][y];
            
        }
        
    }
    
    
}


/**************************************************************************//**
 * @author Ayden Drabek
 *
 * @par Description: The box_back function copies the data from each of the
 *  box arrays back into the original color arrays. By changing the order you 
 *  pass in the boxes you can change which box goes where.
 *
 *
 * @param[in]   boxr - is the red array for each box that is passed in.
 * @param[in]   boxg - is the gren array for each box that is passed in.
 * @param[in]   boxb - is the blue array for each box that is passed in.
 * @param[in]   box_rows - is the row where in the original array the copying 
 *                  should stop
 * @param[in]   box_cols - is the column where in the original array the copying 
 *                  should stop
 * @param[in]   boxrow - is the row where the data being copied should stop
 * @param[in]   boxcol - is the column where the data being copied should stop
 * @param[in]   spotx - is the row in the original color arrays the copying 
 *                  should start
 * @param[in]   spoty - is the column in the original color arrays the copying 
 *                  should start
 *
 *****************************************************************************/
void image::box_back ( pixel **boxr, pixel **boxg, pixel **boxb,
                       int box_rows, int box_cols,
                       int boxrow, int boxcol, int spotx, int spoty )
{
    int r = 0, c = 0, x = 0, y = 0;
    
    for ( r = 0, x = spotx; r < boxrow && x < box_rows; r++, x++ )
    {
        for ( c = 0, y = spoty; c < boxcol && y < box_cols; c++, y++ )
        {
        
            redgray[x][y] = boxr[r][c];
            green[x][y] = boxg[r][c];
            blue[x][y] = boxb[r][c];
            
        }
        
    }
    
    
}


/**************************************************************************//**
 * @author Ayden Drabek
 *
 * @par Description: The box_freeing fncton is just a helper function to 
 *  decrease the number of lines in box. It simply calls the freeArray function
 *  for each of array for the passes in box
 *
 * @param[in]   box_rows - is the number of rows in each of the new box arrays.
 * @param[in]   boxr - is the red array for each box that is passed in.
 * @param[in]   boxg - is the gren array for each box that is passed in.
 * @param[in]   boxb - is the blue array for each box that is passed in.

 *
 *****************************************************************************/
void image::box_freeing ( int box_rows, pixel **boxr, pixel **boxg,
                          pixel **boxb )
{
    freeArray ( boxr, box_rows );
    freeArray ( boxg, box_rows );
    freeArray ( boxb, box_rows );
    
}


