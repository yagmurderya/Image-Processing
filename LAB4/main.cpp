#include "Image.h"

using namespace std;

int main(int argc, char **argv)
{

// SORU 1
    Image inputImg3_43a;
    char inputFig3_43a[] = "Fig0343(a)(skeleton_orig).pgm";

    inputImg3_43a.readImage(inputFig3_43a); // giris goruntusu okundu

    // Fig 3.43(b) - Fig 3.43(a)'un olceklenmis Laplace'ı
    Image outputImg3_43b, outputImg3_43b_scaled;
    char outputFig3_43b[] = "Fig0343(b)_1.pgm";


    int w[] = {-1, -1, -1, -1, 8, -1, -1, -1, -1};  // kullanilacak maske tanimlandi

    outputImg3_43b = inputImg3_43a.Laplacian_unscaled(w); // olceklenmemis laplace hesaplandi
    outputImg3_43b_scaled = outputImg3_43b.scale(8);      // [0- 255] araliginda olceklendirildi

    outputImg3_43b_scaled.writeImage(outputFig3_43b);

    // Fig 3.43(c) - Fig 3.43(a) ve (b)yi toplayınca elde edilen keskinlestirilmis goruntu
    Image outputImg3_43c;
    char outputFig3_43c[] = "Fig0343(c)_1.pgm";
    
    outputImg3_43c = inputImg3_43a + outputImg3_43b; // giris goruntusuyle laplace toplandi
    outputImg3_43c.writeImage(outputFig3_43c); 

    // Fig 3.43(d) - (a)'nın Sobel gradienti
    Image outputImg3_43d, outputImg3_43d_scaled;
    char outputFig3_43d[] = "Fig0343(d)_1.pgm";

    outputImg3_43d = inputImg3_43a.SobelGradient(); 
    outputImg3_43d_scaled = outputImg3_43d.scale(8);

    outputImg3_43d_scaled.writeImage(outputFig3_43d);

    // Fig 3.43(e) - 5x5 ortalama filtresiyle yumusatilmis Sobel goruntusu
    Image outputImg3_43e, outputImg3_43e_scaled;
    char outputFig3_43e[] = "Fig0343(e)_1.pgm";

    outputImg3_43e = outputImg3_43d.SqrAvgFilter(5, 5);
    outputImg3_43e_scaled = outputImg3_43e.scale(8);

    outputImg3_43e_scaled.writeImage(outputFig3_43e);

    // Fig 3.43(f) - (c) ve (e) goruntulerinin carpimiyla olusturulan maske goruntusu
    Image outputImg3_43f, outputImg3_43f_scaled, inputImg3_43c;
    
    char inputFig3_43c[] = "Fig0343(c)_1.pgm";
    char outputFig3_43f[] = "Fig0343(f)_1.pgm";

    inputImg3_43c.readImage(inputFig3_43c); // negatif degerleri sifir almak icin olusturulan goruntu geri okunarak elde edildi

    outputImg3_43f = inputImg3_43c * outputImg3_43e; // goruntuler carpildi
    outputImg3_43f_scaled = outputImg3_43f.scale(8);

    outputImg3_43f_scaled.writeImage(outputFig3_43f);

    // Fig 3.43(g) - (a) ve (f)nin toplami
    Image outputImg3_43g;
    char outputFig3_43g[] = "Fig0343(g)_1.pgm";

    outputImg3_43g = inputImg3_43a + outputImg3_43f_scaled; // olceklenmis f degeriyle toplandi ki giris goruntusuyle araligi ayni olsun

    outputImg3_43g.writeImage(outputFig3_43g);

    // Fig 3.43(h) - g'nin iyilestirilmis hali
    Image outputImg3_43h;
    char outputFig3_43h[] = "Fig0343(h)_1.pgm";

    outputImg3_43h = outputImg3_43g.gammaTrans(8, 1, 0.5); 

    outputImg3_43h.writeImage(outputFig3_43h);

// SORU 1 SONU

// SORU 2
    Image inputImg3_43a_2;
    char inputFig3_43a_2[] = "Fig0343(a)(skeleton_orig).pgm";

    inputImg3_43a_2.readImage(inputFig3_43a_2); // giris goruntusu okundu

    // Fig 3.43(b) - frekans domaini
    Image outputImg3_43b_2, outputImg3_43b_scaled_2, inputImg3_43a_2_scaled;
    char outputFig3_43b_2[] = "Fig0343(b)_2.pgm";

    Complex** Fourier;     // Fourier sonrasi elde edilen karmasik piksel degerleri icin degisken
    Complex** Laplacian;   // frekansta elde edilen laplace icin degisken

    inputImg3_43a_2_scaled = inputImg3_43a_2.scale(1);  // a goruntusu [0-1] araliginda normalize edildi

    inputImg3_43a_2_scaled.ftshift();          // DC merkeze alindi
    Fourier = inputImg3_43a_2_scaled.dft2();   // goruntunun fourieri alindi

    Laplacian = inputImg3_43a_2_scaled.Laplace_freq(Fourier);    // goruntunun fourieri ile laplace filtresi carpildi
    
    outputImg3_43b_2 = inputImg3_43a_2_scaled.idft2(Laplacian);           // ters fourieri alinarak goruntunun laplace'i elde edildi
    outputImg3_43b_2 = outputImg3_43b_2/(3*inputImg3_43a_2.getMaximum()); // laplace normalize edildi
    outputImg3_43b_2.ftshift();
    
    outputImg3_43b_scaled_2 = outputImg3_43b_2.scale(8);  // olusturulan laplace [0, 255] araliginda olceklendirildi

    outputImg3_43b_scaled_2.writeImage(outputFig3_43b_2); 

    // Fig 3.43(c) - Fig 3.43(a) ve (b)yi toplayınca elde edilen keskinlestirilmis goruntu
    Image outputImg3_43c_2, outputImg3_43c_scaled_2;
    char outputFig3_43c_2[] = "Fig0343(c)_2.pgm";
    
    outputImg3_43c_2 = inputImg3_43a_2 - outputImg3_43b_2; // c = -1

    outputImg3_43c_2.writeImage(outputFig3_43c_2);

    // Fig 3.43(d) - (a)'nın Sobel gradienti
    Image outputImg3_43d_2, outputImg3_43d_scaled_2;
    char outputFig3_43d_2[] = "Fig0343(d)_2.pgm";

    outputImg3_43d_2 = inputImg3_43a_2.SobelGradient();
    outputImg3_43d_scaled_2 = outputImg3_43d_2.scale(8);

    outputImg3_43d_scaled_2.writeImage(outputFig3_43d_2);

    // Fig 3.43(e) - 5x5 ortalama filtresiyle yumusatilmis Sobel goruntusu
    Image outputImg3_43e_2, outputImg3_43e_scaled_2;
    char outputFig3_43e_2[] = "Fig0343(e)_2.pgm";

    outputImg3_43e_2 = outputImg3_43d_2.SqrAvgFilter(5, 5);
    outputImg3_43e_scaled_2 = outputImg3_43e_2.scale(8);

    outputImg3_43e_scaled_2.writeImage(outputFig3_43e_2);

    // Fig 3.43(f) - (c) ve (e) goruntulerinin carpimiyla olusturulan maske goruntusu
    Image outputImg3_43f_2, outputImg3_43f_scaled_2, inputImg3_43c_2;
    
    char inputFig3_43c_2[] = "Fig0343(c)_2.pgm";
    char outputFig3_43f_2[] = "Fig0343(f)_2.pgm";

    inputImg3_43c_2.readImage(inputFig3_43c_2);

    outputImg3_43f_2 = inputImg3_43c_2 * outputImg3_43e_2;
    outputImg3_43f_scaled_2 = outputImg3_43f_2.scale(8);

    outputImg3_43f_scaled_2.writeImage(outputFig3_43f_2);

    // Fig 3.43(g) - (a) ve (f)nin toplami
    Image outputImg3_43g_2;
    char outputFig3_43g_2[] = "Fig0343(g)_2.pgm";

    outputImg3_43g_2 = inputImg3_43a_2 + outputImg3_43f_scaled_2;

    outputImg3_43g_2.writeImage(outputFig3_43g_2);

    // Fig 3.43(h) 
    Image outputImg3_43h_2;
    char outputFig3_43h_2[] = "Fig0343(h)_2.pgm";

    outputImg3_43h_2 = outputImg3_43g_2.gammaTrans(8, 1, 0.5);

    outputImg3_43h_2.writeImage(outputFig3_43h_2); 

}