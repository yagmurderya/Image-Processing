/**********************************************************
 * Image.cpp - the image library which implements
 *             the member functions defined in Image.h
 **********************************************************/

#include "Image.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

/**
 * Default constructor.
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
 * verilen ilk piksel degerine göre satir ve sutunlari birer artirarak doldurur.
 * bu sekilde sag asagiya dogru giderek acilan gri tonlu gradyan goruntu elde edilir.
 */
void Image::fillPix(int value) {
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

  float min = getMinimum(); // olceklenecek goruntunun maksimum piksel degeri
  float max = getMaximum(); // olceklenecek goruntunun minimum piksel degeri
  float fm_max = max - min; // minimum deger sifira esitlendikten sonraki maksimum deger

  Image temp; 
  temp.createImage(nrows, ncols); // yeni goruntu olusturuldu

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
Image Image::logTrans(int bit, float c) {

  float r, s;                                        // piksel degerleri
  int rangeMax = pow(2, bit) - 1;                    // L-1
  float normalize = rangeMax/log10(1+getMaximum());  // piksel degerlerini araliga göre normalize etmek icin
  
  Image temp;
  temp.createImage(nrows, ncols);  // gri tonlu goruntu


  for(int rows = 0; rows < nrows; rows ++)
    for(int cols = 0; cols < ncols; cols ++) {
      r = getPix(rows, cols);             // ilk piksel degerleri
      s = c * log10(1.0 + r)* normalize;  // log donusumunden sonra piksel degerleri
      temp.setPix(rows, cols, s);         // donusturulmus goruntunun piksel degerleri ayarlandi
    }

  return temp;
}

/**
 * Goruntunun gama donusumunu alir.
 * girilen parametreler pozitif sabitlerdir.
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
 * center: maskenin merkezindeki pikselin degeri
 * center degiskenine gore kullanilacak maske ayarlanir
 */
Image Image::Laplacian_unscaled(int center) {

  float value, tempVal; // piksel degeri ayarlamak icin degisken
  
  float w[9];
  float w_4[9] = {0, 1, 0, 1, -4, 1, 0, 1, 0}; 
  float w_8[9] = {1, 1, 1, 1, -8, 1, 1, 1, 1};

  if (center == 4) { // Fig 3.37(a) maskesi kullanilacak
    for(int i = 0; i < 9; i++){
      w[i] = w_4[i];
    }
  }
  
  else if (center == 8) { // Fig 3.37(b) maskesi kullanilacak
    for(int i = 0; i < 9; i++){
      w[i] = w_8[i];
    }
  }
  else {  // hatali input durumu
    cout<<"Laplace maskesi merkez degeri hatali girildi\n";
    exit(1);
  }

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
 * girilen center degiskenine gore hangi maskenin kullanilacagi ayarlanir
 */
Image Image::LaplacianMask(int center) {

  float value, g_val; // piksel degeri ayarlamak icin degisken

  Image temp = Laplacian_unscaled(center); // goruntunun laplace'i icin yeni goruntu olusturuldu

  for(int rows = 0; rows < nrows; rows ++) {
    for(int cols = 0; cols < ncols; cols ++) {
      value = temp.getPix(rows, cols);     // laplace goruntusunun piksel degerleri alindi
      g_val = getPix(rows, cols) - value;  // yeni goruntunun piksel degerleri alindi (f - f_laplace)
      temp.setPix(rows, cols, g_val);     // degerler goruntuye aktarildi
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

// END OF MY FUNCTIONS //
