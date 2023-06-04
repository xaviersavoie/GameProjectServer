#include <Perlin3D.hpp>
#include <Vec3d.hpp>
#include <cmath>
#include <iostream>
#include <fstream> //For tester

        int Perlin3D::p[512] = { 151,160,137,91,90,15,                              
            131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
            190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
            88,237,149,56,87,174,20,125,136,171,168,68,175,74,165,71,134,139,48,27,166,
            77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
            102,143,54, 65,25,63,161,1,216,80,73,209,76,132,187,208,89,18,169,200,196,
            135,130,116,188,159,86,164,100,109,198,173,186,3,64,52,217,226,250,124,123,
            5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
            223,183,170,213,119,248,152,2,44,154,163,70,221,153,101,155,167,43,172,9,
            129,22,39,253,19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
            251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
            49,192,214, 31,181,199,106,157,184,84,204,176,115,121,50,45,127,4,150,254,
            138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,151,160,137,91,90,15,    
            131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,    
            190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,    
            88,237,149,56,87,174,20,125,136,171,168,68,175,74,165,71,134,139,48,27,166,     
            77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,    
            102,143,54, 65,25,63,161,1,216,80,73,209,76,132,187,208,89,18,169,200,196,      
            135,130,116,188,159,86,164,100,109,198,173,186,3,64,52,217,226,250,124,123,     
            5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,    
            223,183,170,213,119,248,152,2,44,154,163,70,221,153,101,155,167,43,172,9,             
            129,22,39,253,19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,     
            251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,    
            49,192,214, 31,181,199,106,157,184,84,204,176,115,121,50,45,127,4,150,254,      
            138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
            };

        Vec3d Perlin3D::getGradientVector(int v) {
            int hash = v % 8;

            //std::cout << "Hash: " << hash << std::endl;

            switch(hash) {
                case 0:
                    return Vec3d(1.0, 1.0, 1.0); 
                case 1:
                    return Vec3d(-1.0, 1.0, 1.0);
                case 2:
                    return Vec3d(-1.0, -1.0, 1.0);
                case 3:
                    return Vec3d(-1.0, -1.0, -1.0);
                case 4:
                    return Vec3d(1.0, -1.0, 1.0);
                case 5:
                    return Vec3d(1.0, -1.0, -1.0);
                case 6:
                    return Vec3d(1.0, 1.0, -1.0);
                case 7:
                    return Vec3d(-1.0, 1.0, -1.0);
                default:
                    return Vec3d(0.0, 0.0, 0.0);
            }
        }

    double Perlin3D::grad(int hash, double x, double y, double z) {
        switch(hash & 0xF)
        {
            case 0x0: return  x + y;
            case 0x1: return -x + y;
            case 0x2: return  x - y;
            case 0x3: return -x - y;
            case 0x4: return  x + z;
            case 0x5: return -x + z;
            case 0x6: return  x - z;
            case 0x7: return -x - z;
            case 0x8: return  y + z;
            case 0x9: return -y + z;
            case 0xA: return  y - z;
            case 0xB: return -y - z;
            case 0xC: return  y + x;
            case 0xD: return -y + z;
            case 0xE: return  y - x;
            case 0xF: return -y - z;
            default: return 0; // never happens
        }
    }

        double Perlin3D::generatePerlin(double x, double y, double z) {
            int X = (int)std::floor(x) & 255;
	    int Y = (int)std::floor(y) & 255;
	    int Z = (int)std::floor(z) & 255;

            //std::cout << "X Y Z  " << X << " " << Y << " " << Z << std::endl; 

            double xf = x-std::floor(x);
            double yf = y-std::floor(y);
            double zf = z-std::floor(z);

            int aaa, aba, aab, abb, baa, bba, bab, bbb;
            aaa = p[p[p[    X ]+    Y ]+    Z ];
            aba = p[p[p[    X ]+Y + 1]+    Z ];
            aab = p[p[p[    X ]+    Y ] + Z + 1];
            abb = p[p[p[    X ]+Y + 1]+ Z + 1];
            baa = p[p[p[X + 1]+    Y ]+    Z ];
            bba = p[p[p[X + 1]+ Y + 1]+    Z ];
            bab = p[p[p[X + 1]+ Y ]+Z + 1];
            bbb = p[p[p[X + 1]+Y + 1] + Z + 1];

            double valueAAA = grad(aaa, xf, yf, zf);
            double valueBAA = grad(baa, xf-1, yf, zf);
            double valueBBA = grad(aba, xf, yf-1, zf);
            double valueBBB = grad(bba, xf-1, yf-1, zf);
            double valueABB = grad(aab, xf, yf, zf-1);
            double valueAAB = grad(bab, xf-1, yf, zf-1);
            double valueBAB = grad(abb, xf, yf-1, zf-1);
            double valueABA = grad(bbb, xf-1, yf-1, zf-1);
            /*
            std::cout << "valueAAA: " << valueAAA << std::endl;
            std::cout << "valueBAA: " << valueBAA << std::endl;
            std::cout << "valueBBA: " << valueBBA << std::endl;
            std::cout << "valueBBB: " << valueBBB << std::endl;
            std::cout << "valueABB: " << valueABB << std::endl;
            std::cout << "valueAAB: " << valueAAB << std::endl;
            std::cout << "valueBAB: " << valueBAB << std::endl;
            std::cout << "valueABA: " << valueABA << std::endl;
            */
            double u = fade(xf);
            double v = fade(yf);
            double w = fade(zf);

            double firstLerp = lerp(u, valueAAA, valueBAA);
            //std::cout << "firstLerp : " << firstLerp << std::endl;
            double secondLerp = lerp(u, valueBBA, valueBBB);
            //std::cout << "secondLerp : " << secondLerp << std::endl;
            double thirdLerp = lerp(u, valueABB, valueAAB);
            //std::cout << "thirdLerp : " << thirdLerp << std::endl;
            double fourthLerp = lerp(u, valueBAB, valueABA);
            //std::cout << "fourthLerp : " << fourthLerp << std::endl;
            
            double fifthLerp = lerp(v, firstLerp, secondLerp);
            //std::cout << "fifthLerp : " << fifthLerp << std::endl;
            double sixthLerp = lerp(v, thirdLerp, fourthLerp);
            //std::cout << "sixthLerp : " << sixthLerp << std::endl;

            double returnLerp = lerp(w, fifthLerp, sixthLerp);
            //std::cout << "OUTPUT: " << returnLerp << std::endl;

            return returnLerp;

        }

        double Perlin3D::fade(double t) {
            return t * t * t * (t * (t * 6 - 15) + 10);         // 6t^5 - 15t^4 + 10t^3
        }

        double Perlin3D::lerp(double t, double a1, double a2) {
            return a1 + t*(a2-a1);
        }




//to image.ppm
 void Perlin3D::IMAGETEST() {
   size_t SIZE = 512 * 512 * 3;
   unsigned char * image_data = (unsigned char * ) malloc(SIZE);
   memset(image_data, 255, SIZE);
   std::ofstream myImage;
   myImage.open("image.ppm");
   const int width = 512,
     height = 512; {
     myImage << "P3" << std::endl;
     myImage << width << " " << height << std::endl;
     myImage << "255" << std::endl;
   }
   int pixel = 0; {
     for (int i = 0; i < width; i++) {
       for (int j = 0; j < height; j++) {
         double perl1 = Perlin3D::generatePerlin(i * 0.01, 67 * 0.01, j * 0.01);
         perl1 = (perl1 + 1) / 2;
         perl1 = perl1 * 255;

         int color = (int) perl1;
         image_data[pixel * 3] = color;
         image_data[pixel * 3 + 1] = color;
         image_data[pixel * 3 + 2] = color;
         pixel++;
       }
     }
   } {
     for (int x = 0; x < SIZE; x++) {
       int value = image_data[x];
       myImage << value << " " << std::endl;
     }
   }
   myImage.close();
   free(image_data);
   image_data = NULL;
 }
