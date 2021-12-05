/**********************************************************
 The original copy of the code can be found at http://web.eecs.utk.edu/~mkarakay/courses_files/testfiles.zip 
 and it is modified for ELM463/667
 
 * Image.cpp - the image library which implements
 *             the member functions defined in Image.h
 *
 * Author: Hairong Qi, ECE, University of Tennessee
 *
 * Created: 02/05/02
 *
 * Copyright (C) hqi@utk.edu
 **********************************************************/

#include "Image.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Complex class

/**
 * Default constructor
 */
Complex::Complex() {
  real = 0.0;
  imag = 0.0;
}

/**
 * Constructor for complex numbers
 */
Complex::Complex(float re, float im) {
  real = re;
  imag = im;
}

/**
 * Copy constructor
 * complex: kopyalanacak karmasik sayi
 */
Complex::Complex(const Complex &complex) {
  real = complex.real;
  imag = complex.imag;
}

/**
 * karmasik sayi toplama islemi
 */
Complex operator+(Complex a, Complex b) {
  return Complex(a.real+b.real, a.imag+b.imag);
}

/**
 * karmasik sayi cikarma islemi
 */
Complex operator-(Complex a, Complex b) {
  return Complex(a.real-b.real, a.imag-b.imag);
}

/**
 * karmasik sayi carpma islemi
 */
Complex operator*(Complex a, Complex b) {
  return Complex(a.real*b.real - a.imag*b.imag, a.imag*b.real + a.real*b.imag);
}

/**
 * gercek sayiyla karmasik sayi carpma islemi
 * operatorun sol tarafindaki gercek sayi, sag tarafindaki karmasik sayidir
 */
Complex operator*(float a, Complex b) {
  return Complex(a*b.real, a*b.imag);
}

/**
 * karmasik sayi bolme islemi
 */
Complex operator/(Complex a, Complex b) {
  float r = (a.real*b.real + a.imag*b.imag)/(pow(b.real, 2) + pow(b.imag, 2)); // gercek kisim
  float i = (a.imag*b.real - a.real*b.imag)/(pow(b.real, 2) + pow(b.imag, 2)); // sanal kisim
  
  return Complex(r, i);
}

/**
 * karmasik sayiyi gercek sayiya bolme islemi
 * operatorun sol tarafindaki karmasik sayi, sag tarafindaki gercek sayidir
 */
Complex operator/(Complex a, float b){
  return Complex(a.real/b, a.imag/b);
}

/**
 * Karmasik sayinin genligini alma fonksiyonu
 */
float Complex::abs() {
  return (sqrt(pow(real, 2) + pow(imag, 2))); // (real^2 + imag^2)^(1/2)
}

/**
 * Karmasik sayinin fazini alma fonksiyonu
 */
float Complex::pha() {
  return atan2(imag, real);  // arctan(imag/real)
}

// Image class

/**
 * Default constructor
 */ 
Image::Image() {
  image = NULL;
  nrows = 0;
  ncols = 0;
  maximum = 255;
  //createImage(0, 0);
}

/**
 * Constructor for grayscale images.
 * @param nrows Numbers of rows (height).
 * @param ncols Number of columns (width).
 * @return The created image.
 */
Image::Image(int nRows, int nCols) {
  if (nRows<=0 || nCols<=0) {
    cout << "Image: Index out of range.\n";
    exit(3);
  }
  image = NULL;
  createImage(nRows, nCols);
}

/**
 * Copy constructor. 
 * @param img Copy image.
 * @return The created image.
 */
Image::Image(const Image &img) {
  int rows, cols;

  image = NULL;
  nrows = img.getRow();
  ncols = img.getCol();
  createImage(nrows, ncols);             // allocate memory
  
  for (rows=0; rows < nrows; rows++)
    for (cols=0; cols < ncols; cols++)
		image[rows * ncols + cols] = img(rows, cols);
}

/**
 * Destructor.  Frees memory.
 */
Image::~Image() {
  if (image)
    delete [] image;       // free the image buffer
}

/**
 * Allocate memory for the image and initialize the content to be 0.
 */
void Image::createImage() {

  if (image != NULL)
    delete [] image;

  maximum = 255;

  image = (float *) new float [nrows * ncols];
  if (!image) {
    cout << "CREATEIMAGE: Out of memory.\n";
    exit(1);
  }

  initImage();
}


/**
 * Allocate memory for the image and initialize the content to be zero.
 * @param r Numbers of rows (height).
 * @param c Number of columns (width).
 */
void Image::createImage(int numberOfRows, int numberOfColumns) {
  
  if (image != NULL)
    delete [] image;

  nrows = numberOfRows;
  ncols = numberOfColumns;
  maximum = 255;

  image = (float *) new float [nrows * ncols];
  if (!image) {
    cout << "CREATEIMAGE: Out of memory.\n";
    exit(1);
  }

  initImage();
}

/**
 * Initialize the image.
 * @para init The value the image is initialized to. Default is 0.0.
 */
void Image::initImage(float initialValue) {
  int i;

  for (i = 0; i < nrows * ncols; i++)
    image[i] = initialValue;
}

/**
 * Returns the total number of rows in the image.
 * @return Total number of rows.
 * \ingroup getset
 */
int Image::getRow() const {
  return nrows;
}

/**
 * Returns the total number of columns in the image.
 * @return Total number of columns.
 * \ingroup getset
 */
int Image::getCol() const {
  return ncols;
}

/**
 * Returns the maximum pixel value of a gray-level image. 
 * @return The intensity of that pixel.
 * \ingroup getset
 */
float Image::getMaximum() const {
  int i, j;
  float maxi=-10000;

 
  for (i=0; i<nrows; i++)
    for (j=0; j<ncols; j++)
      if (maxi < image[i*ncols+j])
	maxi = image[i*ncols+j];
  
  return maxi;
}


/**
 * Returns the minimum pixel value of the image.
 * @return The minimum pixel value.
 * \ingroup getset
 */
float Image::getMinimum() const {
  int i, j;
  float mini=10000; 

  for (i=0; i<nrows; i++)
    for (j=0; j<ncols; j++)
      if (mini > image[i*ncols+j])
	mini = image[i*ncols+j];

  return mini;
}



/**
 * Returns the pixel value at rows, cols
 * @return The pixel value
 * \ingroup getset
 */
float Image::getPix(int rows, int cols) {
  return image[rows * ncols + cols];
}


/**
 * Returns the image. 
 * @return a gray-scale image
 * \ingroup getset
 */
Image Image::getImage() const {
  Image temp;
  int rows, cols;
  
  temp.createImage(nrows, ncols);   // temp is a gray-scale image
  for (rows = 0; rows < nrows; rows++)
    for (cols = 0; cols < ncols; cols++)
      temp(rows, cols) = image[rows * ncols + cols];
      
  return temp;
}

/**
 * Sets the total number of rows in an image.
 * @param r Total number of rows.
 * \ingroup getset
 */
void Image::setRow(int numberOfRows) {
  nrows = numberOfRows;
}

/**
 * Sets the total number of columns in an image.
 * @param c Total number of columns.
 * \ingroup getset
 */
void Image::setCol(int numberOfColumns) {
  ncols = numberOfColumns;
}


/**
 * Sets the pixel value at rows,cols.
 * @param row and col index.
 * \ingroup getset
 */
void Image::setPix(int rows, int cols, float value) {
  image[rows * ncols + cols] = value;
}

/**
 * Sets the image given a grayscale image. 
 * \ingroup getset
 */
void Image::setImage(Image &img) {
  int rows, cols;

  for (rows = 0; rows < nrows; rows++)
    for (cols = 0; cols < ncols; cols++)
      image[rows * ncols + cols] = img(rows, cols);
}

/**
 * Overloading () operator
 * \ingroup overload
 * @param i Row
 * @param j Column
 */
float & Image::operator()(int rows, int cols) const {
  return image[rows * ncols + cols];
}

/**
 * Overloading = operator.
 * \ingroup overload
 * @param img Image to copy.
 * @return Newly copied image.
 */
const Image Image::operator=(const Image& img) {
  int rows, cols;

  if (this == &img)
    return *this;

  nrows = img.getRow();
  ncols = img.getCol();
  createImage(nrows, ncols);             

  for (rows = 0; rows < nrows; rows++)
    for (cols = 0; cols < ncols; cols++)
	(*this)(rows, cols) = img(rows, cols);

  return *this;
}

/**
 * Overloading + operator.
 * \ingroup overload
 * @param img Image to add to specified image.
 * @return Addition of the two images.
 */
Image Image::operator+(const Image& img) const {
  int i, j, nr, nc;
  Image temp;

  nr = img.getRow();
  nc = img.getCol();

  if (nr != nrows || nc != ncols) {
    cout << "operator+: "
         << "Images are not of the same size or type, can't do addition\n";
    exit(3);
  }
  temp.createImage(nrows, ncols);
  
  for (i=0; i<nrows; i++)
    for (j=0; j<ncols; j++)
        temp(i,j) = image[i*ncols+j] + img(i,j);

  return temp;
}

/**
 * Overloading - operator.
 * \ingroup overload
 * @param img Image to subtract from specified image.
 * @return Subtraction of the two images.
 */
Image Image::operator-(const Image &img) const {
   int i, j, nr, nc;
  Image temp;

  nr = img.getRow();
  nc = img.getCol();

  if (nr != nrows || nc != ncols) {
    cout << "operator-: "
         << "Images are not of the same size or type, can't do subtraction\n";
    exit(3);
  }
  temp.createImage(nrows, ncols);             
  
  for (i=0; i<nrows; i++)
    for (j=0; j<ncols; j++)
        temp(i,j) = image[i*ncols+j] - img(i,j);

  return temp;
}

/**
 * Overloading * operator.  This function does pixel by pixel multiplication.
 * \ingroup overload
 * @param img Image to multiply with specified image.
 * @return Multiplication of the two images.
 */
Image Image::operator*(const Image &img) const {
  int i, j, nr, nc;
  Image temp;

  nr = img.getRow();
  nc = img.getCol();

  if (nr != nrows || nc != ncols) {
    cout << "operator*: "
         << "Images are not of the same size or type, can't do multiplication\n";
    exit(3);
  }
  temp.createImage(nrows, ncols);             
  
  for (i=0; i<nrows; i++)
    for (j=0; j<ncols; j++)
        temp(i,j) = image[i*ncols+j] * img(i,j);

  return temp;
}

/**
 * Overloading / operator.  This function does pixel by pixel division.
 * Specified image is the dividend.
 * \ingroup overload
 * @param img Image to be divided (divisor).
 * @return Quotient of the two images.
 */
Image Image::operator/(const Image &img) const {
  int i, j, nr, nc;
  Image temp;

  nr = img.getRow();
  nc = img.getCol();

  if (nr != nrows || nc != ncols) {
    cout << "operator/: "
         << "Images are not of the same size or type, can't do division\n";
    exit(3);
  }
  temp.createImage(nrows, ncols);             
  
  for (i=0; i<nrows; i++)
    for (j=0; j<ncols; j++)
        temp(i,j) = image[i*ncols+j] / ( img(i,j) + 0.001 );

  return temp;
}


/**
 * Overloading << operator.  Output the image to the specified destination.
 * \ingroup overload
 * @param out The specified output stream (or output destination).
 * @param img Image to be output.
 * @result Output image to the specified file destination.
 */
ostream & operator<<(ostream &out, Image &img) {
  int rows, cols;
  

    for (rows = 0; rows < img.getRow(); rows++) {
      for (cols = 0; cols < img.getCol(); cols++)
        out << setw(4) << img(rows, cols) << ' ';
      out << endl;
    }

  return out; 
}

/**
 * Overloading / operator.  The left operand is the image and the right
 * is the dividend (a double point number). Each pixel in the image is 
 * divided by the double point number.
 * \ingroup overload
 * @param img Image as the left operand.
 * @param val A double point number as the right operand.
 * @result Image divided by a double point number.
 */
Image operator/(Image &img, double val) {
  int i, j, nr, nc;
  Image temp;
  
  nr = img.getRow();
  nc = img.getCol();
  temp.createImage(nr, nc);
  
  for (i=0; i<nr; i++)
    for (j=0; j<nc; j++)
        temp(i,j) = img(i,j) / val;
  
  return temp;
}

/**
 * Overloading * operator.  The left operand is the image and the right
 * is a double point number. Each pixel in the image is multiplied by the
 * double point number.
 * \ingroup overload
 * @param img Image as the left operand.
 * @param s A double point number as the right operand.
 * @result Image multiplied by a double point scalar.
 */
Image operator*(Image &img, double s) {
  int i, j, nr, nc;
  Image temp;
  
  nr = img.getRow();
  nc = img.getCol();
  temp.createImage(nr, nc);
  
  for (i=0; i<nr; i++)
    for (j=0; j<nc; j++)
        temp(i,j) = img(i,j) * s;
  
  return temp;
}


/**
 * Overloading + operator.  The left operand is the image and the right
 * is a double point number. Each pixel in the image is added by the
 * double point number.
 * \ingroup overload
 * @param img Image as the left operand.
 * @param s A double point number as the right operand.
 * @result Image add a double point scalar.
 */
Image operator+(Image &img, double s) {
  int i, j, nr, nc;
  Image temp;
  
  nr = img.getRow();
  nc = img.getCol();
  temp.createImage(nr, nc);
  
  for (i=0; i<nr; i++)
    for (j=0; j<nc; j++)
        temp(i,j) = img(i,j) + s;
  
  return temp;
}  
  
/**
 * Overloading - operator.  The left operand is the image and the right
 * is a double point number. Each pixel in the image is subtracted by the
 * double point number.
 * \ingroup overload
 * @param img Image as the left operand.
 * @param s A double point number as the right operand.
 * @result Image subtract a double point scalar.
 */
Image operator-(Image &img, double s) {
  int i, j, nr, nc;
  Image temp;
  
  nr = img.getRow();
  nc = img.getCol();
  temp.createImage(nr, nc);
  
  for (i=0; i<nr; i++)
    for (j=0; j<nc; j++)
        temp(i,j) = img(i,j) - s;
  
  return temp;
} 

/**
 * Read image from a file                     
 * @param fname The name of the file 
 * @return An Image object
 */
  void Image::readImage(char *fname) {
  ifstream ifp;
  char dummy[80];
  unsigned char *img;
  int rows, cols;
  int nRows, nCols, nt, maxi;

  ifp.open(fname, ios::in | ios::binary);

  if (!ifp) {
    cout << "readImage: Can't read image: " << fname << endl;
    exit(1);
  }

  // identify image format
  ifp.getline(dummy, 80, '\n');

  if (dummy[0] == 'P' && dummy[1] == '5') 
     ;
  else {
    cout << "readImage: Can't identify image format." << endl;
    exit(1);
  }

  // skip the comments
  ifp.getline(dummy, 80, '\n');

  while (dummy[0] == '#') {
    ifp.getline(dummy, 80, '\n');
  }

  // read the row number and column number
  sscanf(dummy, "%d %d", &nCols, &nRows);

  // read the maximum pixel value
  ifp.getline(dummy, 80, '\n');
  sscanf(dummy, "%d", &maxi); 
  if (maxi > 255) {
    cout << "Don't know what to do: maximum value is over 255.\n";
    exit(1);
  }

  if (image != NULL)
  delete [] image;
  
  nrows = nRows;
  ncols = nCols;
  maximum = 255;
  
  // read the image data
  img = (unsigned char *) new unsigned char [nRows * nCols];
  if (!img) {
    cout << "READIMAGE: Out of memory.\n";
    exit(1);
  }
  image = (float *) new float [nRows * nCols];
  if (!image) {
    cout << "READIMAGE: Out of memory.\n";
    exit(1);
  }

    ifp.read((char *)img, (nRows * nCols * sizeof(unsigned char)));
    
    for (rows = 0; rows < nRows; rows++)
      for (cols = 0; cols < nCols; cols++)
          image[rows * nCols + cols] = (float) img[rows * nCols + cols];
      
  ifp.close();
  
  delete [] img;
}


/**
 * Write image buffer to a file.
 * @param fname The output file name.
 */
void Image::writeImage(char *fname, bool flag) {
  ofstream ofp;
  int i, j;
  int nRows, nCols, nt;
  unsigned char *img;

  ofp.open(fname, ios::out | ios::binary);

  if (!ofp) {
    cout << "writeImage: Can't write image: " << fname << endl;
    exit(1);
  }


  ofp << "P5" << endl;
  ofp << ncols << " " << nrows << endl;

 
  ofp << 255 << endl;
  
  

  // convert the image data type back to unsigned char
  img = (unsigned char *) new unsigned char [nrows * ncols];
  if (!img) {
    cout << "WRITEIMAGE: Out of memory.\n";
    exit(1);
  }

  float maxi = getMaximum();
  float mini = getMinimum();
  
  
    for (i = 0; i< nrows; i++)
      for (j = 0; j < ncols; j++) {
	  // rescale if the flag is set
	  if ((maxi != mini) && flag == true)
	    img[i * ncols + j] = (unsigned char)  ((image[i * ncols + j]-mini)/(float)(maxi-mini)*255.0); 
	  // any intensity that is larger than the maximum would be set as maximum
	  else if (image[i * ncols + j] > 255)
	    img[i * ncols + j] = 255;
	  else if (image[i * ncols + j] < 0)
	    img[i * ncols + j] = 0;
	  else
	    img[i * ncols + j] = (unsigned char)  image[i * ncols + j]; 
      }
      
    ofp.write((char *)img, (nrows * ncols * sizeof(unsigned char)));


  ofp.close();
  delete [] img;
}


// YOUR FUNCTIONS

/**
 * Returns the image. 
 * @return a gray-scale image
 * \ingroup getset
 */
Image Image::thresholdImage(float thresholdValue, float lowValue, float highValue) {
  Image temp;
  int rows, cols;
  
  temp.createImage(nrows, ncols);   // temp is a gray-scale image
  for (rows = 0; rows < nrows; rows++)
    for (cols = 0; cols < ncols; cols++)
      if (image[rows * ncols + cols] <= thresholdValue) 
	temp(rows, cols) = lowValue;
      else
	temp(rows, cols) = highValue;
      
      
  return temp;
}
  //END OF YOUR FUNCTIONS //

//---------------------------------------------------- MY FUNCTIONS - YAGMUR DERYA -----------------------------------------------------------//

/**
 * verilen ilk piksel degerine gore piksel degerlerini birer artirarak doldurur.
 */
void Image::fillPix(int value) {
  for(int rows = 0; rows < nrows; rows++) 
    for(int cols = 0; cols < ncols; cols++) {
      setPix(rows, cols, value);              // piksel degeri ayarlandi
      value ++;                               // iksel degeri bir artirildi
    }
}

/**
 * verilen ilk piksel degerine gore satir ve sutunlari birer artirarak doldurur.
 * bu sekilde sag asagiya dogru giderek acilan gri tonlu gradyan goruntu elde edilir.
 */
void Image::fillPix_gradient(int value) {
  for(int rows = 0; rows < nrows; rows++) {    
    int temp = value;                        // birinci sutundaki piksel degerleri temp degiskenine atandi
    for(int cols = 0; cols < ncols; cols++) {
      setPix(rows, cols, temp);              // piksel degeri ayarlandi
      temp++;                                // ayni satirdaki sutunlarin piksel degeri birer artirildi
    }
    value ++;                                // birinci sutundaki satirlarin piksel degeri birer artirildi
  }
}


/**
 * arrayin medyanini bulan fonksiyon
 * giris parametreleri arrayin kendisi ve boyutu
 */
float Image::Median(float value[], int n) {
  // bubble sort  
  float temp;

  for (int i = 0; i < n-1; i++) {
    for (int j = 0; j < n-i-1; j++) {
      if (value[j] > value[j+1]){
        // swap
        temp = value[j];
        value[j] = value[j+1];
        value[j+1] = temp;
      }
    }
  }
  
  return value[(n-1)/2]; // siralandiginda ortada kalan deger gonderildi
}

/**
 * araligi olceklemek icin fonksiyon
 * giris parametresi olarak goruntunun bit bilgisini alir
 */

Image Image::scale(int bit) {

  int L = pow(2, bit);  // piksel araligi [0, L-1]
  float value, scaled_val;

  Image temp;
  temp.createImage(nrows, ncols);

  float min = getMinimum(); // olceklenecek goruntunun maksimum piksel degeri
  float max = getMaximum(); // olceklenecek goruntunun minimum piksel degeri
  float fm_max = max - min; // minimum deger sifira esitlendikten sonraki maksimum deger

  for(int rows = 0; rows < nrows; rows ++) {
    for(int cols = 0; cols < ncols; cols ++) {
      value = getPix(rows, cols) - min;     // minimum degeri sifira esitlemek icin
      scaled_val = (L-1) * value / fm_max;  // [0, fm_max] araligi [0, L-1] araligina getirildi
      temp.setPix(rows, cols, scaled_val);  // goruntunun piksel degerleri ayarlandi
    }
  }

  return temp;
}

/**
 * goruntunun enini ve boyunu aynı oranda kucultur.
 * h x w boyutundaki bir goruntuden (h/size) x (w/size) boyutuna dusurulmus goruntu uretir. 
 */
Image Image::upScale(int size) {

  int value;    // piksel degeri

  Image temp;   // kucultulmus goruntu
  temp.createImage(nrows/size, ncols/size);  // istenen oranda kucultulmus yeni goruntu olusturuldu

  for(int rows = 0; rows < nrows/size; rows ++)
    for(int cols = 0; cols < ncols/size; cols ++) {
      value = getPix(rows*size, cols*size);  // orijinal goruntunun piksel degerleri (size-1) aralikla alindi (seyrek ornekleme gibi)
      temp.setPix(rows, cols, value);        // kucultulmus goruntunun piksel degeri ayarlandi
    }

  return temp;
}

/**
 * goruntunun enini ve boyunu aynı oranda buyutur.
 * h x w boyutundaki bir goruntuden (h*size) x (w*size) boyutunda bir goruntu uretir. 
 */
Image Image::downScale(int size) {

  float value;  // piksel degeri
  
  Image temp;   // buyutulmus goruntu
  temp.createImage(nrows*size, ncols*size);  // istenen oranda buyutulmus yeni goruntu olusturuldu

  for(int rows = 0; rows < nrows*size; rows ++)
    for(int cols = 0; cols < ncols*size; cols ++) {
      value = getPix(rows/size, cols/size);  // orijinal goruntunun piksel degerleri alindi
      /**
       * rows, cols ve size degiskenleri int olduklari icin sadece virgulden onceki tam sayilik kisim alinacagindan
       * her n*size adimda bir piksel degeri degisecektir
       * (size = k => 0/k, 1/k, .., (k-1)/k      = 0  -> (k-1)inci indekse kadar orijinal goruntunun 0. indeksine esitlenecek
       *              k/k, (k+1)/k, .., (2k-1)/k = 1  -> (2k-1)inci indekse kadar orijinal goruntunun 1. indeksine esitlenecek
       *              2k/k,..., (3k-1)/k         = 2
       *              .                          = .
       *              .                          = . )
       */ 

      temp.setPix(rows, cols, value);        // buyutulmus goruntunun piksel degeri ayarlandi
    }

  return temp;
}

/**
 * Goruntunun negatifini alir.
 * Girilen parametre, goruntunun bit sayisidir.
 */
Image Image::Negative(int bit) {
 
  float r, s; // piksel degerleri
  
  Image temp;
  temp.createImage(nrows, ncols); // gri tonlu goruntu

  for(int rows = 0; rows < nrows; rows ++)
    for(int cols = 0; cols < ncols; cols ++) {
      r = getPix(rows, cols);     // ilk piksel degeri
      s = pow(2, bit) - 1 - r;    // negatifini aldiktan sonraki piksel degeri
      temp.setPix(rows, cols, s); // negatif goruntunun piksel degerleri ayarlandi
    }

  return temp;
}

/**
 * Goruntunun log donusumunu alir.
 * c sabit sayidir. 
 */
void Image::logTrans(int bit, float c) {

  float r, s;                                        // piksel degerleri
  int rangeMax = pow(2, bit) - 1;                    // L-1
  float normalize = rangeMax/log10(1+getMaximum());  // piksel degerlerini araliga göre normalize etmek icin

  for(int rows = 0; rows < nrows; rows ++)
    for(int cols = 0; cols < ncols; cols ++) {
      r = getPix(rows, cols);             // ilk piksel degerleri
      s = c * log10(1.0 + r)* normalize;  // log donusumunden sonra piksel degerleri
      setPix(rows, cols, s);              // donusturulmus goruntu icin piksel degerleri ayarlandi
    }

}

/**
 * Goruntunun gama donusumunu alir.
 * girilen parametreler bit, c ve gama pozitif sabitlerdir.
 */
Image Image::gammaTrans(int bit, float c, float gamma) {
 
  float r, s; // piksel degerleri
  
  Image temp;
  temp.createImage(nrows, ncols); // gri tonlu goruntu

  for(int rows = 0; rows < nrows; rows ++)
    for(int cols = 0; cols < ncols; cols ++) {
      r = getPix(rows, cols);     // ilk piksel degeri
      s = c * pow(r, gamma);      // yeni piksel degeri
      temp.setPix(rows, cols, s); // negatif goruntunun piksel degerleri ayarlandi
    }
    
  float normalize, s_new;
  normalize = temp.getMaximum() - temp.getMinimum(); // degerleri normalize etmek icin aralik hesaplandi
  
  for(int rows = 0; rows < nrows; rows ++)
    for(int cols = 0; cols < ncols; cols ++) {
      s_new = ((pow(2, bit)-1) * temp.getPix(rows, cols)) / normalize; // normalize edilmis piksel degeri
      temp.setPix(rows, cols, s_new) ;                     // normalize negatif goruntu elde edildi
    }

  return temp;
}

/**
 * Square Average Filter
 * maskenin satir sutun bilgisini alir
 */
Image Image::SqrAvgFilter(int m, int n) {

  int a = (m-1)/2;      // a siniri ayarlandi
  int b = (n-1)/2;      // b siniri ayarlandi
  float value, tempVal; // piksel degeri ayarlamak icin degisken

  Image temp;
  temp.createImage(nrows, ncols); // goruntu olusturuldu

  for(int f_rows = 0; f_rows < nrows; f_rows ++) {
    for(int f_cols = 0; f_cols < ncols; f_cols ++) {
      value = 0.0;

      // mask loops
      for(int w_rows = -a; w_rows <= a; w_rows ++) {
        for(int w_cols = -b; w_cols <= b; w_cols ++) {
          if((f_rows + w_rows) < 0 || (f_cols + w_cols) < 0 || (f_rows + w_rows) >= nrows || (f_cols + w_cols) >= ncols)
            tempVal = 0.0;  // zero padding
          else
            tempVal = getPix((f_rows + w_rows), (f_cols + w_cols))/(float)(m*n); // (piksel degeri)/(m x n) hesaplandi

          value = value + tempVal; // tum degerler toplandi
        }
      }
    
      temp.setPix(f_rows, f_cols, value);  // yeni goruntunun piksel degerleri ayarlandi
    } 
  }
    
  return temp;
}

/**
 * medyan fitre
 * maskenin satir sutun bilgisini alir
 */
Image Image::MedianFilter(int m, int n) {

  int a = (m-1)/2;            // a siniri ayarlandi
  int b = (n-1)/2;            // b siniri ayarlandi
  float values[m*n], tempVal; // piksel degeri ayarlamak icin degisken

  Image temp;
  temp.createImage(nrows, ncols); // goruntu olusturuldu

  for(int f_rows = 0; f_rows < nrows; f_rows ++) {
    for(int f_cols = 0; f_cols < ncols; f_cols ++) {
      int i = 0;

      // mask loops
      for(int w_rows = -a; w_rows <= a; w_rows ++) {
        for(int w_cols = -b; w_cols <= b; w_cols ++) {
          if((f_rows + w_rows) < 0 || (f_cols + w_cols) < 0 || (f_rows + w_rows) >= nrows || (f_cols + w_cols) >= ncols)
            tempVal = 0.0;  // zero padding
          else
            tempVal = getPix((f_rows + w_rows), (f_cols + w_cols)); // piksel degeri alindi

          values[i] = tempVal; // tum degerler values arrayine alindi
          i++;
        }
      }

      temp.setPix(f_rows, f_cols, Median(values, (m * n) )); // values arrayinin medyani piksel degeri olarak ayarlandi
    }
  }
    
  return temp;
}

/**
 * Gaussian Filter
 * maskenin satir sutun bilgisini alir
 * dev: standart sapmasini alir
 */
Image Image::GaussianFilter(int m, int n, float dev) {

  int a = (m-1)/2;           // a siniri ayarlandi
  int b = (n-1)/2;           // b siniri ayarlandi
  float value, tempVal, sum; // piksel degeri ayarlamak icin degiskenler
  float h;                   // maskenin fonksiyonu

  Image temp;
  temp.createImage(nrows, ncols); // goruntu olusturuldu

  for(int f_rows = 0; f_rows < nrows; f_rows ++) {
    for(int f_cols = 0; f_cols < ncols; f_cols ++) {
      // toplamada kulanilacak degerler baslangicta sifirlandi
      value = 0.0;
      sum = 0.0;

      // mask loops
      for(int w_rows = -a; w_rows <= a; w_rows ++) {
        for(int w_cols = -b; w_cols <= b; w_cols ++) {
          h = exp(-(pow((w_rows), 2) + pow((w_cols), 2)) / (2 * pow(dev, 2)) ); // maskenin fonksiyonu tanimlandi
          sum = sum + h; // h degerlerinin toplami hesaplandi
          
          if((f_rows + w_rows) < 0 || (f_cols + w_cols) < 0 || (f_rows + w_rows) >= nrows || (f_cols + w_cols) >= ncols)
            tempVal = 0.0;  // zero padding
          else
            tempVal = h * getPix((f_rows + w_rows), (f_cols + w_cols)); // h(s, t) x f(x+s, y+t)

          value = value + tempVal; // degerler toplandi [sum (h(s, t) x f(x+s, y+t))]
        }
      }
    
      temp.setPix(f_rows, f_cols, value/sum);  // yeni goruntunun piksel degerleri ayarlandi
    } 
  }
    
  return temp;
}

/**
 * Unsharp Maskesi
 * Orijinal goruntuyle gauss filtresinden gecmis goruntunun farkini alir
 * giris parametreleri olarak maskenin satir sutun bilgisini ve standart sapma degerini alir
 */
Image Image::UnsharpMask(int m, int n, float dev) {

  float blurred_val, mask_val; // piksel degerleri icin degiskenler atandi

  Image temp = GaussianFilter(m, n, dev); // gauss filtresinden gecen goruntu

  for(int rows = 0; rows < nrows; rows++) {
    for (int cols = 0; cols < ncols; cols++) {
      blurred_val = temp.getPix(rows, cols);       // bulaniklastirilmis goruntunun piksel degerleri alindi
      mask_val = getPix(rows, cols) - blurred_val; // orijinal goruntuden bulaniklastirilmis goruntu cikarildi
      temp.setPix(rows, cols, mask_val);           // maskenin goruntusu olusturuldu
    }
  }
  
  return temp;
}

/**
 * Goruntu keskinlestirme filtresi
 * giris parametreleri olarak maskenin satir sutun bilgisini standart sapma ve k degerini alir
 * k = 1 => unsharp mask
 * k > 1 => highboost filtering
 */
Image Image::SharpenImage(int m, int n, float dev, float k) {
  
  float mask_val, sharpened_val; // piksel degerleri icin degiskenler

  Image temp = UnsharpMask(m, n, dev); // unsharp maskesini goruntusu

  for(int rows = 0; rows < nrows; rows++) {
    for (int cols = 0; cols < ncols; cols++) {
      mask_val = temp.getPix(rows, cols);                // maskenin piksel degerleri alindi
      sharpened_val = getPix(rows, cols) + k * mask_val; // orijinal goruntuye maske eklendi
      temp.setPix(rows, cols, sharpened_val);            // keskinlestirilmis goruntu olusturuldu
    }
  }
  
  return temp; 
}

/**
 * Olceklenmemis laplace goruntusu
 * giris parametresi olarak maskenin degerlerini alir
 */
Image Image::Laplacian_unscaled(int *w) {

  float value, tempVal; // piksel degeri ayarlamak icin degisken

  Image temp;
  temp.createImage(nrows, ncols);

  for(int f_rows = 0; f_rows < nrows; f_rows ++) {
    for(int f_cols = 0; f_cols < ncols; f_cols ++) {
      value = 0.0; // laplace hesabi icin baslangic degeri 0 alindi
      int i = 0;   // maskenin ilk elemanindan baslamak icin

      // mask loops
      for(int w_rows = -1; w_rows <= 1; w_rows ++) {
        for(int w_cols = -1; w_cols <= 1; w_cols ++) {
          if((f_rows + w_rows) < 0 || (f_cols + w_cols) < 0 || (f_rows + w_rows) >= nrows || (f_cols + w_cols) >= ncols)
            tempVal = 0.0;  // zero padding
          else
            tempVal = w[i] * getPix((f_rows + w_rows), (f_cols + w_cols)); // laplace icin piksel degerleri hesaplandi

          value = value + tempVal;  // laplace alindi 
          i++; // maskenin elemanlarini gezmek icin
        }
      }
      temp.setPix(f_rows, f_cols, value); // yeni piksel degerleri atandi
    }
  }

  return temp;
}

/**
 * Laplace maskesi
 * center: maskenin merkezindeki pikselin degeri
 * w maskenin elemanlarinin degeri
 * sign 1 ise toplama, 0 ise cikartma islemi
 */
Image Image::LaplacianMask(int *w, int sign) {

  float value, g_val; // piksel degeri ayarlamak icin degisken

  Image temp = Laplacian_unscaled(w); // goruntunun laplace'i icin yeni goruntu olusturuldu

  for(int rows = 0; rows < nrows; rows ++) {
    for(int cols = 0; cols < ncols; cols ++) {
      value = temp.getPix(rows, cols);     // laplace goruntusunun piksel degerleri alindi
      if(sign = 1){
        g_val = getPix(rows, cols) + value;  // yeni goruntunun piksel degerleri alindi (f + f_laplace)
      }
      else if(sign = 0) {
        g_val = getPix(rows, cols) - value;  // yeni goruntunun piksel degerleri alindi (f - f_laplace)
        if(g_val<0){
        }
      }
      temp.setPix(rows, cols, g_val);     // degerler goruntuye aktarildi
    }
  }

  return temp;
}

/**
 * Goruntunun kenarlarini bulmak icin
 * Sobel Gradient
 * cikista kenarlari bulunmus goruntuyu dondurur
 */
Image Image::SobelGradient() {

  float value; //piksel degeri icin degisken
  float g_x, g_y;
  int w_x[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1}; // x ekseni icin sobel operatoru
  int w_y[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1}; // y ekseni icin sobel operatoru

  Image temp;
  temp.createImage(nrows, ncols);

  for(int f_rows = 0; f_rows < nrows; f_rows ++) {
    for(int f_cols = 0; f_cols < ncols; f_cols ++) {
      int i = 0; // operatorlerin ilk elemanindan baslamak icin
      // toplama yapilirken kullanilacaklari icin degiskenlerin baslangic degerleri sifirlandi
      g_x = 0;
      g_y = 0;

      // mask loops
      for(int w_rows = -1; w_rows <= 1; w_rows ++) {
        for(int w_cols = -1; w_cols <= 1; w_cols ++) {
          if((f_rows + w_rows) < 0 || (f_cols + w_cols) < 0 || (f_rows + w_rows) >= nrows || (f_cols + w_cols) >= ncols){
            g_x = 0;  // zero padding
            g_y = 0;  // zero padding
          }
          else{
            g_x = g_x + w_x[i] * getPix((f_rows + w_rows), (f_cols + w_cols)); // x ekseni icin piksel degerleri hesaplandi
            g_y = g_y + w_y[i] * getPix((f_rows + w_rows), (f_cols + w_cols)); // y ekseni icin piksel degerleri hesaplandi
          }
          i++; // operatorlerin elemanlarini gezmek icin
        }
      }
      
      value = abs(g_x) + abs(g_y);  // M(x, y) = |g_x| + |g_y|
      temp.setPix(f_rows, f_cols, value); // yeni piksel degerleri atandi
    }
  }

  return temp;
}

/**
 * Histogram Equalization 
 * bit: goruntunun bit bilgisidir
 */
Image Image::HistogramEqualization(int bit) {

  int L = pow(2, bit);            // piksel araligi
  float P[L+1], T[L+1], s[L+1];   // pdf, cdf ve scale edilmis cdf

  Image temp;
  temp.createImage(nrows, ncols); // yeni goruntu olusturuldu

  int size = nrows*ncols; // toplam piksel sayisi

// pdf ve cdf baslangicta sifirlandi
  P[0] = 0.0; 
  T[0] = 0.0;

// cdf hesaplanirken baslangicta gecmis degeri kullanabilmek icin array eleman sayisi 1 fazla alinip, 0 yerine 1. elemandan baslandi
  for(int i = 1; i < (L + 1); i++) {
    int count = 0;   // piksel deger miktarini tutmak icin counter

    // piksel degerinin satir sutun gezilerek bulunmasi icin 
    for(int rows = 0; rows < nrows; rows++) {
      for(int cols = 0; cols < ncols; cols ++) {
        if(getPix(rows, cols) == (i-1)) {  // i = 1 icin 0 degerli pikseller, 2 için 1 degerli..., n icin n-1 degerli
          count ++;                        // i-1 degerli piksel miktari hesaplandi
        }
      }
    }
    
    P[i] = (float)count/size; // pdf hesaplandi
    T[i] = T[i-1] + P[i];     // cdf hesaplanirken onceki T degeri ile P degeri toplandi
    s[i] = (L-1) * T[i];        // araligi scale etmek icin cdf L ile carpildi ([0,1] -> [0,L])

    // piksele yeni degerinin atanmasi icin
    for(int rows = 0; rows < nrows; rows++) {
      for(int cols = 0; cols < ncols; cols ++) {
        if(getPix(rows, cols) == (i-1)) { 
          temp.setPix(rows, cols, round(s[i]));  // hesaplanan s degerleri ilgili piksellere aktarildi
        }
      }
    }
  }
  
  return temp;
}

/**
 * Goruntunun iki boyutlu Fourier donusumunu alma fonksiyonu
 * cikis parametresi fourier donusumu sonrasi elde edilen 2 boyutlu kompleks arraydir
 * olusturulan Complex class'i ve fonksiyonlari kullanilarak islemler yapildi
 */
Complex** Image::dft2() {  
  // satir ve sutun bilgileri degiskenlere atandi
  int M = nrows;
  int N = ncols;
  // satirlarin Fourier donusumunu atamak icin c complex matrisi olusturuldu
  // eleman sayisi buyudugunde sikinti olmamasi icin hafizada malloc ile yer ayirildi
  Complex** c = (Complex**)malloc(M*sizeof(Complex*)); 
  for(int i = 0; i < M; i++){
    c[i] = (Complex*)malloc(N*sizeof(Complex));
  }

  // 2 boyutlu Fourier donusumu tamamlandiktan sonra elde edilen kompleks degerleri tutmak icin 2 boyutlu complex arrayi
  Complex** ft2D_complex = (Complex**)malloc(M*sizeof(Complex*)); 
  for(int i = 0; i < M; i++){
    ft2D_complex[i] = (Complex*)malloc(N*sizeof(Complex));
  }

  // F(x, v) - satirlarin Fourier donusumu
  for(int v = 0; v < N; v++) {
    for(int x = 0; x < M; x++) {
      Complex complex_val;  // complex piksel degerleri icin degisken tanimlandi, default constructor oldugu icin (0+0i)'ye esit
      for(int y = 0; y < N; y++) {
        // 1D Fourier donusumu hesaplandi
        // cmath kutuphanesinde pi degeri M_PI olarak tanimli, cos ve sin radyan aliyor
        // sum( f(x, y)e^(-j*2pi*v*y/N) )
        complex_val = complex_val + getPix(x, y) * Complex(cos(2 * M_PI * v * y / N), -sin(2 * M_PI * v * y / N));
      }
      c[x][v] = complex_val; // F(x, v) degerleri c matrisine tanimlandi, tek boyutlu fourier donusumu degerleri
    }
  }

  // F(u, v) - sutunlarin Fourier donusumu
  for(int u = 0; u < M; u++) {
    for(int v = 0; v < N; v++) {
      Complex complex_val;  // complex_val = 0+0i (default constructor), karmasik piksel degerlerini tutmak icin tanimlandi
      for(int x = 0; x < M; x++) {
        // 1D Fourier donusumu hesaplandi
        // sum( F(x, v)e^(-j*2pi*u*x/M) )
        complex_val = complex_val + c[x][v] * Complex(cos(2 * M_PI * u * x / M), -sin(2 * M_PI * u * x / M));
      }
      ft2D_complex[u][v] = complex_val; // ft2D_complex[u][v] = F(u, v), 2D fourier sonrasi piksellerin kompleks degerleri
    }
  }
  return ft2D_complex; // F(u, v)
}

/**
 * goruntunun ters Fourier donusumunu alma fonksiyonu
 * cikista ters Fourieri alinmis goruntuyu dondurur
 */

Image Image::idft2(Complex** F) {
  // satir ve sutun bilgileri degiskenlere atandi
  int M = nrows;
  int N = ncols;    

  Image temp;
  temp.createImage(M, N);   // ters Fourieri alinmis goruntu icin olusturuldu

  // tek boyutlu ters fourieri atamak icin c complex matrisi olusturuldu
  // eleman sayisi buyudugunde sikinti olmamasi icin hafizada malloc ile yer ayirildi
  Complex** c = (Complex**)malloc(M*sizeof(Complex*)); 
  for(int i = 0; i < M; i++){
    c[i] = (Complex*)malloc(N*sizeof(Complex));
  }

  // f(u, y) - satirlarin ters Fourier donusumu
  for(int y = 0; y < N; y++) { 
    for(int u = 0; u < M; u++) {
      Complex complex_val;
      for(int v = 0; v < N; v++) {
        // 1D ters Fourier donusumu hesaplandi
        // sum( F(u, v)e^(j*2pi*v*y/N) )
        complex_val = complex_val + F[u][v] * Complex(cos(2 * M_PI * v * y / N), sin(2 * M_PI * v * y / N));
      }
      // complex_val burada N*f(u, y)'ye esit
      c[u][y] = complex_val/N; // f(u, y) degerleri c matrisine tanimlandi
    }
  }

  // f(x, y) - sutunlarin ters Fourier donusumu
  for(int x = 0; x < M; x++) {
    for(int y = 0; y < N; y++) {
      Complex complex_val;
      for(int u = 0; u < M; u++) {
        // sum( f(x, y)e^(j*2pi*u*x/M) )
        complex_val = complex_val + c[u][y] * Complex(cos(2 * M_PI * u * x / M), sin(2 * M_PI * u * x / M));
      }
      // complex_val burada M*f(x, y)'ye esit
      complex_val = complex_val/M;
      temp.setPix(x, y, complex_val.real); // olusturulan goruntuye complex f(x, y) degerlerinin genligi atandi
    }
  }

  return temp; // f(x, y)
}

/**
 * Fourier donusumunun genlik spektrumunu elde etme fonksiyonu
 * giris parametresi karmasik sayi matrisidir 
 */
void Image::dft2_abs(Complex** F) {

  for (int u = 0; u < nrows; u++) {
    for (int v = 0; v < ncols; v++) {
      setPix(u, v, F[u][v].abs()); // F[u][v].abs() = |F(u, v)|
    }
  }
}

/**
 * Fourier donusumunde DC'yi merkeze almak icin fonksiyon
 * f(x, y)(-1)^(x+y) <=> F(u-M/2, v-N/2)
 */
void Image::ftshift() {

  float value; // piksel degerlerini atamak icin degisken tanimlandi

  for(int rows = 0; rows < nrows; rows++) 
    for(int cols = 0; cols < ncols; cols++) {
      value = getPix(rows, cols) * pow(-1, rows + cols); // f(x, y)(-1)^(x+y)
      setPix(rows, cols, value); // carpilan piksel degeri goruntuye aktarildi
    }
}

/**
 * Frekans domaininde goruntunun laplace'ini alir
 * giris parametresi olarak DFT sonucunda elde edilen kompleks arrayi alir
 * cikista H(u,v)*F(u,v) dondurulur
 */
Complex** Image::Laplace_freq(Complex** F) {

  Complex** H = (Complex**)malloc(nrows*sizeof(Complex*)); // filtre ile goruntunun fourierinin carpimini atamak icin array
  for(int i = 0; i < nrows; i++){
    H[i] = (Complex*)malloc(ncols*sizeof(Complex));
  }

  for(int u = 0; u < nrows; u++) {
    for(int v = 0; v < ncols; v++) {
      H[u][v] = -4 * M_PI*M_PI * ((u - nrows/2)*(u - nrows/2) + (v - ncols/2)*(v - ncols/2)) * F[u][v]; // H(u,v) * F(u,v)
    }
  }

  return H; // laplace'in fourieri
}

// END OF MY FUNCTIONS //