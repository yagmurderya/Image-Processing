#include "Image.h"

using namespace std;

int main(int argc, char **argv)
{

// SORU 0______________________________________________________________________________________________________________________________
    
    Image Img0, FourierImg0, inverseFourierImg0;  // goruntu degiskenleri olusturuldu

    char outputImg0[] = "Soru0_image.pgm";            // olusturulan goruntunun adi
    char outputFT[] = "Soru0_Fourier.pgm";            // Fourieri alinmis goruntunun adi
    char outputInverseFT[] = "Soru0_inverseFT.pgm";   // ters Fourieri alinmis goruntunun adi

    Img0.createImage(3, 3); // 3x3'luk goruntu olusturuldu
    Img0.fillPix(1);        // goruntu piksel degerleri birer artacak sekilde dolduruldu

    Img0.writeImage(outputImg0);

    // 2D DFT
    Complex** C_Fourier0 = Img0.dft2();  // goruntunun 2D Fourier donusumu alindi 
    
    FourierImg0.createImage(Img0.getRow(), Img0.getCol()); // Fourier icin giris goruntusuyle ayni boyda goruntu olusturuldu
    
    FourierImg0.dft2_abs(C_Fourier0);   // 2D Fourierin genligi alindi
    FourierImg0.writeImage(outputFT);   // goruntu yazdirildi

    // 2D IDFT
    inverseFourierImg0 = FourierImg0.idft2(C_Fourier0); // elde edilen kompleks fourier degerlerinden ters fourier donusumu alindi
    inverseFourierImg0.writeImage(outputInverseFT);     // ters fourier donusumunden elde edilen goruntu yazdirildi

// SORU 0 SONU_________________________________________________________________________________________________________________________

// SORU 1______________________________________________________________________________________________________________________________

    // Fig 4.25(a)
    Image inputImg4_25a, outputImg4_25b; // giris ve cikis goruntuleri tanimlandi
    Complex** C_Fourier4_25b;            // Fourier sonrasi elde edilen karmasik piksel degerleri icin degisken

    char inputFig4_25a[] = "Fig0425(a)(translated_rectangle).pgm"; // giris goruntusunun adi tanimlandi
    char outputFig4_25b[] = "Fig0425(b).pgm";                      // cikis goruntusunun adi tanimlandi

    inputImg4_25a.readImage(inputFig4_25a);
    outputImg4_25b.createImage(inputImg4_25a.getRow(), inputImg4_25a.getCol());

    inputImg4_25a.ftshift();                 // DC'yi merkeze almak icin
    C_Fourier4_25b = inputImg4_25a.dft2();   // goruntunun fourieri alindi
    outputImg4_25b.dft2_abs(C_Fourier4_25b); // spektrum goruntusu olusturuldu

    outputImg4_25b.logTrans(8, 1);             // detaylari gorebilmek icin log transform (c = 1) alindi
    outputImg4_25b.writeImage(outputFig4_25b); // olusturulan goruntu yazdirildi

    // Fig 4.25(c)
    Image inputImg4_25c, outputImg4_25d;
    Complex** C_Fourier4_25d;   // Fourier sonrasi elde edilen karmasik piksel degerleri icin degisken

    char inputFig4_25c[] = "Fig0425(c)(rotated_rectangle).pgm";
    char outputFig4_25d[] = "Fig0425(d).pgm";

    inputImg4_25c.readImage(inputFig4_25c);
    outputImg4_25d.createImage(inputImg4_25c.getRow(), inputImg4_25c.getCol());

    inputImg4_25c.ftshift();                 // DC'yi merkeze almak icin
    C_Fourier4_25d = inputImg4_25c.dft2();   // goruntunun fourieri alindi
    outputImg4_25d.dft2_abs(C_Fourier4_25d); // spektrum goruntusu olusturuldu

    outputImg4_25d.logTrans(8, 1);             // detaylari gorebilmek icin log transform (c = 1) alindi
    outputImg4_25d.writeImage(outputFig4_25d); // olusturulan goruntu yazdirildi

    // Fig 4.29a
    Image inputImg4_29a, outputImg4_29b;
    Complex** C_Fourier4_29b;  // Fourier sonrasi elde edilen karmasik piksel degerleri icin degisken

    char inputFig4_29a[] = "Fig0429(a)(blown_ic).pgm";
    char outputFig4_29b[] = "Fig0429(b).pgm";

    inputImg4_29a.readImage(inputFig4_29a);
    outputImg4_29b.createImage(inputImg4_29a.getRow(), inputImg4_29a.getCol());

    inputImg4_29a.ftshift();                 // DC'yi merkeze almak icin
    C_Fourier4_29b = inputImg4_29a.dft2();   // goruntunun fourieri alindi
    outputImg4_29b.dft2_abs(C_Fourier4_29b); // spektrum goruntusu olusturuldu

    outputImg4_29b.logTrans(8, 7);             // detaylari gorebilmek icin log transform (c = 7) alindi
    outputImg4_29b.writeImage(outputFig4_29b); // olusturulan goruntu yazdirildi

// SORU 1 SONU_________________________________________________________________________________________________________________________

// SORU 2______________________________________________________________________________________________________________________________
/** 
 * SORU 1'de olusturulan fourieri alinan outputImg4_x degiskenleri ve
 * elde edilen kompleks Fourier degerleri kullanilarak ters fourier islemi yapildi
 */
    // 4.25(b)

    Image outputImg4_25a; // ters fourier donusumu icin

    char outputFig4_25a[] = "Fig0425(a)_inverseFT.pgm";

    outputImg4_25a = outputImg4_25b.idft2(C_Fourier4_25b); // 1. soruda elde edilen DFT'nin ters donusumu alindi
                                                           // C_Fourier4_25b: DFT'de elde edilen kompleks degerler
                                                           // outputImg4_25b: DFT goruntusu 
    outputImg4_25a.writeImage(outputFig4_25a);             // goruntu yazdirildi

    // 4.25(d)
    Image outputImg4_25c;

    char outputFig4_25c[] = "Fig0425(c)_inverseFT.pgm";

    outputImg4_25c = outputImg4_25b.idft2(C_Fourier4_25d);
    outputImg4_25c.writeImage(outputFig4_25c);

    // 4.29(b)
    Image outputImg4_29a;

    char outputFig4_29a[] = "Fig0429(a)_inverseFT.pgm";

    outputImg4_29a = outputImg4_29b.idft2(C_Fourier4_29b);
    outputImg4_29a.writeImage(outputFig4_29a);

// SORU 2 SONU_________________________________________________________________________________________________________________________
}