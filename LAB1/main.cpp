#include "Image.h"

using namespace std;

int main(int argc, char **argv)
{
// SORU 1

// Fig 3.4

  Image inputImg3_4, outputImg3_4_b;

  char inputFig3_4[] = "Fig0304(a)(breast_digital_Xray).pgm";  // orijinal goruntunun adi
  char outputFig3_4_b[] = "Fig0304(b).pgm";                    // yeni goruntunun adi

  inputImg3_4.readImage(inputFig3_4);           // orijinal goruntu okundu

  outputImg3_4_b = inputImg3_4.Negative(8);     // goruntunun negatifi alindi
  outputImg3_4_b.writeImage(outputFig3_4_b);    // negatif goruntu yazdirildi
  

// Fig 3.5

  Image inputImg3_5, outputImg3_5_b;

  char inputFig3_5[] = "Fig0305(a)(DFT_no_log).pgm";  // orijinal goruntunun adi
  char outputFig3_5_b[] = "Fig0305(b).pgm";           // yeni goruntunun adi

  inputImg3_5.readImage(inputFig3_5);           // orijinal goruntu okundu
  
  outputImg3_5_b = inputImg3_5.logTrans(8, 1);  // goruntunun log donusumu alindi
  outputImg3_5_b.writeImage(outputFig3_5_b);    // donusturulen goruntu yazdirildi


// Fig 3.8

  Image inputImg3_8, outputImg3_8_b, outputImg3_8_c, outputImg3_8_d;

  char inputFig3_8[] = "Fig0308(a)(fractured_spine).pgm";      // orijinal goruntunun adi
  char outputFig3_8_b[] = "Fig0308(b).pgm";                    // b goruntusunun adi
  char outputFig3_8_c[] = "Fig0308(c).pgm";                    // c goruntusunun adi
  char outputFig3_8_d[] = "Fig0308(d).pgm";                    // d goruntusunun adi

  inputImg3_8.readImage(inputFig3_8);  // orijinal goruntu okundu

  // verilen c ve gamma sabitlerine gore b, c, d goruntuleri olusturuldu
  outputImg3_8_b = inputImg3_8.gammaTrans(8, 1, 0.6); 
  outputImg3_8_c = inputImg3_8.gammaTrans(8, 1, 0.4);
  outputImg3_8_d = inputImg3_8.gammaTrans(8, 1, 0.3);
  
  // olusturulan goruntuler yazdirildi
  outputImg3_8_b.writeImage(outputFig3_8_b);
  outputImg3_8_c.writeImage(outputFig3_8_c);
  outputImg3_8_d.writeImage(outputFig3_8_d);


// Fig 3.9
  
  Image inputImg3_9, outputImg3_9_b, outputImg3_9_c, outputImg3_9_d;

  char inputFig3_9[] = "Fig0309(a)(washed_out_aerial_image).pgm";  // orijinal goruntunun adi
  char outputFig3_9_b[] = "Fig0309(b).pgm";                        // b goruntusunun adi
  char outputFig3_9_c[] = "Fig0309(c).pgm";                        // c goruntusunun adi
  char outputFig3_9_d[] = "Fig0309(d).pgm";                        // d goruntusunun adi

  inputImg3_9.readImage(inputFig3_9);   // orijinal goruntu okundu

  // verilen c ve gamma sabitlerine gore b, c, d goruntuleri olusturuldu
  outputImg3_9_b = inputImg3_9.gammaTrans(8, 1, 3.0); 
  outputImg3_9_c = inputImg3_9.gammaTrans(8, 1, 4.0);
  outputImg3_9_d = inputImg3_9.gammaTrans(8, 1, 5.0);
  
  // olusturulan goruntuler yazdirildi
  outputImg3_9_b.writeImage(outputFig3_9_b);
  outputImg3_9_c.writeImage(outputFig3_9_c);
  outputImg3_9_d.writeImage(outputFig3_9_d);


// Fig 3.33

  Image inputImg3_33, outputImg3_33_b, outputImg3_33_c, outputImg3_33_d, outputImg3_33_e, outputImg3_33_f;

  char inputFig3_33[] = "Fig0333(a)(test_pattern_blurring_orig).pgm"; // orijinal goruntunun adi
  char outputFig3_33_b[] = "Fig0333(b).pgm";                          // b goruntusunun adi
  char outputFig3_33_c[] = "Fig0333(c).pgm";                          // c goruntusunun adi
  char outputFig3_33_d[] = "Fig0333(d).pgm";                          // d goruntusunun adi
  char outputFig3_33_e[] = "Fig0333(e).pgm";                          // e goruntusunun adi
  char outputFig3_33_f[] = "Fig0333(f).pgm";                          // f goruntusunun adi

  inputImg3_33.readImage(inputFig3_33);           // orijinal goruntu okundu

  // m x n degerlerine gore square average filter uygulanarak b, c, d, e, f goruntuleri olusturuldu
  outputImg3_33_b = inputImg3_33.SqrAvgFilter(3, 3);
  outputImg3_33_c = inputImg3_33.SqrAvgFilter(5, 5);
  outputImg3_33_d = inputImg3_33.SqrAvgFilter(9, 9);
  outputImg3_33_e = inputImg3_33.SqrAvgFilter(15, 15);
  outputImg3_33_f = inputImg3_33.SqrAvgFilter(35, 35);
  
  // olusturulan goruntuler yazdirildi
  outputImg3_33_b.writeImage(outputFig3_33_b);
  outputImg3_33_c.writeImage(outputFig3_33_c);
  outputImg3_33_d.writeImage(outputFig3_33_d);
  outputImg3_33_e.writeImage(outputFig3_33_e);
  outputImg3_33_f.writeImage(outputFig3_33_f);


// Fig 3.35

  Image inputImg3_35, outputImg3_35_b, outputImg3_35_c;

  char inputFig3_35[] = "Fig0335(a)(ckt_board_saltpep_prob_pt05).pgm"; // orijinal goruntunun adi
  char outputFig3_35_b[] = "Fig0335(b).pgm";                           // b goruntusunun adi
  char outputFig3_35_c[] = "Fig0335(c).pgm";                           // c goruntusunun adi

  inputImg3_35.readImage(inputFig3_35);              // orijinal goruntu okundu

  // m x n degerlerine gore square average filter ve median filter uygulanarak b ve c goruntuleri olusturuldu
  outputImg3_35_b = inputImg3_35.SqrAvgFilter(3,3);
  outputImg3_35_c = inputImg3_35.MedianFilter(3,3);

  // olusturulan goruntuler yazdirildi
  outputImg3_35_b.writeImage(outputFig3_35_b);
  outputImg3_35_c.writeImage(outputFig3_35_c);

  // SORU 1 SONU


  // SORU 2

  Image inputImg1, inputImg2, inputImg3, outputImg1, outputImg2, outputImg3;

  char inputFile1[] = "Soru2_woman.pgm";
  char inputFile2[] = "Soru2_skull.pgm";
  char inputFile3[] = "Soru2_way.pgm";

  char outputFile1[] = "new_woman.pgm";
  char outputFile2[] = "new_skull.pgm";
  char outputFile3[] = "new_way.pgm";

  // giris goruntuleri okundu
  inputImg1.readImage(inputFile1);
  inputImg2.readImage(inputFile2);
  inputImg3.readImage(inputFile3);

  // goruntuler duzeltildi
  outputImg1 = inputImg1.gammaTrans(8, 1, 3);
  outputImg2 = inputImg2.gammaTrans(8, 1, 0.5);
  outputImg3 = inputImg3.gammaTrans(8, 1, 2.5);


  // olusturulan yeni goruntuler yazdirildi
  outputImg1.writeImage(outputFile1);
  outputImg2.writeImage(outputFile2);
  outputImg3.writeImage(outputFile3);

  // SORU 2 SONU
  
}