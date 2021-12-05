/********************************************************************
 * Note:
 *   This is a simple C++ library for image processing.
 *   The purpose is not high performance, but to show how
 *   the algorithm works through programming.
 *   This library can only read in PGM/PPM format images.
 *
 ********************************************************************/

#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

class Image {
  friend ostream & operator<<(ostream &, Image &);
  friend Image operator/(Image &, double);    // image divided by a scalar
  friend Image operator*(Image &, double);    // image multiplied by a scalar
  friend Image operator+(Image &, double);    // image add a scalar
  friend Image operator-(Image &, double);    // image subtract a scalar

 public:
  // constructors and destructor
  Image();                             // default constructor
  Image(int, int);                     // constructor with row & column
  Image(const Image &);                // copy constructor
  ~Image();                            // destructor


  // create an image
  void createImage();                 	// create an image, parameters all set
  void createImage(int,        		      // create an image with row
		   int c=1            			// column (default 1, a column vector)
           );
  void initImage(float init=0.0);       // initiate the pixel value of an img
										// the default is 0.0
  // get and set functions
  int getRow() const;                  	// get row # / the height of the img
  int getCol() const;                  	// get col # / the width of the image
  float getMaximum() const;            	// get the maximum pixel value
  float getMinimum() const;            	// get the mininum pixel value
  float getPix(int rows, int cols);		  // get pixel value at (rows, cols)
  Image getImage() const;              	// get the image

  void setRow(int);                    // set row number
  void setCol(int);                    // set column number
  void setPix(int rows, int cols, float value);	// set Pixel value at (rows, cols)
  void setImage(Image &);              // set the image,

  // operator overloading functions
  float & operator()(int, int c = 0) const; // operator overloading (i,j), when c = 0, a column vector
  const Image operator=(const Image &);     // = operator overloading
  Image operator+(const Image &) const;     // overloading + operator
  Image operator-(const Image &) const;     // overloading - operator
  Image operator*(const Image &) const;     // overloading pixelwise *
  Image operator/(const Image &) const;     // overloading pixelwise division

  bool IsEmpty() const { return (image==NULL); }

  void readImage(char *fname);
  void writeImage(char *fname, bool flag = false);

  // YOUR MEMBER FUNCTIONS //
  
  Image thresholdImage(float threshold = 127.0, float lowValue = 0.0, float highValue = 255.0);

  // END OF YOUR MEMBER FUNCTIONS//

  //--------------------------------------------------- MY FUNCTIONS - YAGMUR DERYA ----------------------------------------------------------//
  
  void fillPix(int);          // verilen ilk degere gore, pikselleri sagdan sola ve yukaridan asagiya birer artirarak doldurma
  float Median(float[], int); // medyani bulan fonksiyon
  
  Image scale(int);        // piksel degerlerini olcekeme
  Image upScale(int);      // goruntunun enini ve boyunu aynı oranda kucultme
  Image downScale(int);    // goruntunun enini ve boyunu aynı oranda buyutme
  
  // Intensity Transformation Functions
  Image Negative(int);                 // goruntunun negatifini alma
  Image logTrans(int, float);          // goruntunun log donusumu
  Image gammaTrans(int, float, float); // goruntunun gama donusumu

  // Spatial Filters
  Image SqrAvgFilter(int, int);          // square average filtre (m x n)
  Image MedianFilter(int, int);          // median filtre (m x n)
  Image GaussianFilter(int, int, float); // Gauss filtre (m x n, standart sapma)
  // sharpening spatial filters
  Image UnsharpMask(int, int, float);         // unsharp maskesi (m x n, standart sapma)
  Image SharpenImage(int, int, float, float); // goruntu keskinlestirme (unsharp, highboost)
  Image Laplacian_unscaled(int);              // olceklenmemis laplace
  Image LaplacianMask(int);                   // laplace maskesi

  // Histogram
  Image HistogramEqualization(int); // goruntunun histogramini esitleme
  

  // END OF MY FUNCTIONS //
  


  private:
    int nrows;		// number of rows / height
    int ncols;		// number of columns / width
    int maximum;	// the maximum pixel value
    float *image;	// image buffer
};


////////////////////////////////////
// image I/O
  Image readImage(char *);             // read image
  void writeImage(Image &,             // write an image
                char *,
                int flag = 0);         // flag for rescale, rescale when == 1


#endif
