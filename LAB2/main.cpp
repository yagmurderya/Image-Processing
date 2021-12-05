#include "Image.h"

using namespace std;

int main(int argc, char **argv)
{

// SORU 1 

// Fig 3.16(1)
  Image inputImg3_16_1, outputImg3_16_1;

  char inputFig3_16_1[] = "Fig0316(1)(top_left).pgm";
  char outputFig3_16_1[] = "Fig0316(1)_out.pgm";

  inputImg3_16_1.readImage(inputFig3_16_1);

  outputImg3_16_1 = inputImg3_16_1.HistogramEqualization(8); // 8 goruntunun bit bilgisidir
  outputImg3_16_1.writeImage(outputFig3_16_1);

// Fig 3.16(2)
  Image inputImg3_16_2, outputImg3_16_2;

  char inputFig3_16_2[] = "Fig0316(2)(2nd_from_top).pgm";
  char outputFig3_16_2[] = "Fig0316(2)_out.pgm";

  inputImg3_16_2.readImage(inputFig3_16_2);
  
  outputImg3_16_2 = inputImg3_16_2.HistogramEqualization(8);
  outputImg3_16_2.writeImage(outputFig3_16_2);

// Fig 3.16(3)
  Image inputImg3_16_3, outputImg3_16_3;

  char inputFig3_16_3[] = "Fig0316(3)(third_from_top).pgm";
  char outputFig3_16_3[] = "Fig0316(3)_out.pgm";

  inputImg3_16_3.readImage(inputFig3_16_3);
  
  outputImg3_16_3 = inputImg3_16_3.HistogramEqualization(8);
  outputImg3_16_3.writeImage(outputFig3_16_3);

// Fig 3.16(4)
  Image inputImg3_16_4, outputImg3_16_4;

  char inputFig3_16_4[] = "Fig0316(4)(bottom_left).pgm";
  char outputFig3_16_4[] = "Fig0316(4)_out.pgm";

  inputImg3_16_4.readImage(inputFig3_16_4);
  
  outputImg3_16_4 = inputImg3_16_4.HistogramEqualization(8);
  outputImg3_16_4.writeImage(outputFig3_16_4);

// SORU 1 SONU 

// SORU 2

// Soru2(light) - parlak goruntu
  Image inputImg_light, outputImg_light;

  char inputFig_light[] = "Soru2(light).pgm";
  char outputFig_light[] = "Soru2(light)_out.pgm";

  inputImg_light.readImage(inputFig_light);

  outputImg_light = inputImg_light.HistogramEqualization(8);
  outputImg_light.writeImage(outputFig_light);

// Soru2(dark) - karanlik goruntu
  Image inputImg_dark, outputImg_dark;

  char inputFig_dark[] = "Soru2(dark).pgm";
  char outputFig_dark[] = "Soru2(dark)_out.pgm";

  inputImg_dark.readImage(inputFig_dark);

  outputImg_dark = inputImg_dark.HistogramEqualization(8);
  outputImg_dark.writeImage(outputFig_dark);
  
// Soru2(low_contrast) - dusuk kontrastlı goruntu
  Image inputImg_lowContrast, outputImg_lowContrast;
  
  char inputFig_lowContrast[] = "Soru2(low_contrast).pgm";
  char outputFig_lowContrast[] = "Soru2(low_contrast)_out.pgm";

  inputImg_lowContrast.readImage(inputFig_lowContrast);

  outputImg_lowContrast = inputImg_lowContrast.HistogramEqualization(8);
  outputImg_lowContrast.writeImage(outputFig_lowContrast);

// SORU 2 SONU

// SORU 3

// Fig 3.38

  Image inputImg3_38a;
  
  char inputFig3_38a[] = "Fig0338(a)(blurry_moon).pgm";
  inputImg3_38a.readImage(inputFig3_38a);

  // b
  Image outputImg3_38b;
  
  char outputFig3_38b[] = "Fig0338(b).pgm";

  outputImg3_38b = inputImg3_38a.Laplacian_unscaled(4); // olceklenmemis laplace goruntusu
  outputImg3_38b.writeImage(outputFig3_38b);

  // c
  Image outputImg3_38c;
  
  char outputFig3_38c[] = "Fig0338(c).pgm";

  outputImg3_38c = inputImg3_38a.Laplacian_unscaled(4);
  outputImg3_38c = outputImg3_38c.scale(8);  // goruntu olceklendi 
  outputImg3_38c.writeImage(outputFig3_38c);

  // d
  Image outputImg3_38d;

  char outputFig3_38d[] = "Fig0338(d).pgm";

  outputImg3_38d = inputImg3_38a.LaplacianMask(4); // laplace maskesiyle keskinlestirilmis goruntu (merkezi 4 olan)
  outputImg3_38d.writeImage(outputFig3_38d);

  // e
  Image outputImg3_38e;

  char outputFig3_38e[] = "Fig0338(e).pgm";

  outputImg3_38e = inputImg3_38a.LaplacianMask(8); // laplace maskesiyle keskinlestirilmis goruntu (merkezi 8 olan)
  outputImg3_38e.writeImage(outputFig3_38e);


// Fig 3.40
 
 Image inputImg3_40a;

 char inputFig3_40a[] = "Fig0340(a)(dipxe_text).pgm";
 inputImg3_40a.readImage(inputFig3_40a);

 // b
 Image outputImg3_40b;

 char outputFig3_40b[] = "Fig0340(b).pgm";

 outputImg3_40b = inputImg3_40a.GaussianFilter(5, 5, 3); // 5x5, standart sapma 3 
 outputImg3_40b.writeImage(outputFig3_40b);

 // c
 Image outputImg3_40c;

 char outputFig3_40c[] = "Fig0340(c).pgm";
 outputImg3_40c = inputImg3_40a.UnsharpMask(5, 5, 3); // unsharp maskesi olusturuldu
 outputImg3_40c.writeImage(outputFig3_40c);

 // d
 Image outputImg3_40d;

 char outputFig3_40d[] = "Fig0340(d).pgm";

 outputImg3_40d = inputImg3_40a.SharpenImage(5, 5, 3, 1); // k = 1, unsharp masking
 outputImg3_40d.writeImage(outputFig3_40d);

 // e 
 Image outputImg3_40e;

 char outputFig3_40e[] = "Fig0340(e).pgm";

 outputImg3_40e = inputImg3_40a.SharpenImage(5, 5, 3, 4.5); // k = 4.5, highboost filtering
 outputImg3_40e.writeImage(outputFig3_40e);

// SORU 3 SONU
}