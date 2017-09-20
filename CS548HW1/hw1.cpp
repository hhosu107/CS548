/*
 * CS548 Assignment #1
 * September 21, 2017
 * 20173245 Chansu Park
 * c++11 with g++-5.4.0
 *
 * make: make a result binary
 * make result: generate output.txt
 * make clean: delete a result binary and output.txt
 *
 * Problem 1. Construct 8 XDTs using 8 DES S-Boxes.
 * Problem 2. Why ~=1/234 is the best iterative characteristic of DES?
 *
 * S-Boxes are in S-Boxes.txt.
 */

#include<cstdio>
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>

using namespace std;

//int SBox[8][4][16]; // Contains 8 S-Boxes(4x16).
int SBox[8][4][16] =
 {{{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7}, {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8}, {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0}, {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},
  {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10}, {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5}, {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15}, {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},
  {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8}, {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1}, {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7}, {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},
  {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15}, {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9}, {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4}, {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},
  {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9}, {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6}, {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14}, {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},
  {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11}, {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8}, {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6}, {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},
  {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1}, {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6}, {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2}, {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},
  {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7}, {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2}, {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8}, {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}};
int XDT[8][64][16]; /* Each XDT[i] takes input XOR X'(6-bit)
                       and output XOR Y'(4-bit) and then return XDT[i][X'][Y']. */

void FillSBox(){
  FILE *in;
  in = fopen("S-Boxes.txt", "r");
 // printf("DES 8 S-Boxes:\n");
  for(int i=0; i<8; i++){
   // printf("S%d:\n", i+1);
    for(int j=0; j<4; j++){
      for(int k=0; k<16; k++){
        fscanf(in, "%d", &SBox[i][j][k]);
        //printf("%3d ", SBox[i][j][k]);
      }
      //printf("\n");
    }
  }
  fcloseall();
}

int SBoxEval(int k, int x){
  /* Decide S_k using input k.
   * Each S-Box S_k takes 6-bit integer(b1b2b3b4b5b6)
   * and return S_k[b1b6][b2b3b4b5]. */
  int i = x/32 * 2 + (x%2);
  int j = (x%32)/2;
  return SBox[k][i][j];
}

int main(){
  printf("CS548 Assignment #1\n");
  printf("20173245 Chansu Park\n");

//  FillSBox();

  /* Construct XDT */
  for(int k=0; k<8; k++){
    for(int i=0; i<64; i++){
      for(int j=0; j<64; j++){
        /*i, j: two inputs of S_k Box */
        int x = i^j;
        /* increase the corresponding cell */
        XDT[k][x][SBoxEval(k, i) ^ SBoxEval(k, j)] += 1;
      }
    }
  }

  printf("\nProblem 1: 8 XDTs of DES 8 S-Boxes\n");
  // printf("See S-Boxes.txt containing DES S-Boxes.\n");
  printf("These tables follow the format in Slide 27.\n\n");
  for(int k=0; k<8; k++){
    printf("XDT %d:\n", k+1);
    printf("+-----+----------------------------------------------------------------+\n");
    printf("|INPUT|                           Output XOR                           |\n");
    printf("| XOR |");
    for(int i=0; i<16; i++) printf("%2Xx ", i);
    printf("|\n+-----+----------------------------------------------------------------+\n");
    for(int i=0; i<64; i++){
      printf("| %2Xx |", i);
      for(int j=0; j<16; j++){
        printf("%3d ", XDT[k][i][j]);
      }
      printf("|\n");
    }
    printf("+-----+----------------------------------------------------------------+\n\n");

  }
  printf("Problem 2: Verify that 1/234 is the best iterative characteristic of DES.\n(i.e., put proper values into 2-round characteristic, display intermediate values and then obtain the probability which is 1/234.)\n\n");
  printf("Definition of 2-round characteristic:\n");
  printf("A 2-round characteristic is a tuple Om = (Op, Or, Ot) \nwhere Op, Ot are m-nit numbers and Or is a list of 2 elements Or = (r_1, r_2)\nwhere r_i = (rIi, rOi) where rIi and rOi are m/2 bit numbers \nand m is the block size of the cryptosystem.\nHere, any characteristis satisfies following rules: \nrI1 = the right half of Op\nrI2 = the left half of Op XOR rO1\nrI2 = the right half of Ot\nrI1 = the left half of Ot XOR rO2.\n\n");
  printf("It is well known that 1/234 is the best iterative characteristic of DES \nwhen Op = 0x1960000000000000, Ot = 0000000019600000.\n");
  printf("Given that Op and Ot, \nrI1 = 0x00000000 by first rule and rI2 = 0x19600000 by third rule.\nThus rO1 = 0x00000000 by second rule and rO2 = 0x00000000 by fourth rule.\n");
  printf("Here, rI1/rI2 will be used as inputs of the first/second F-function of DES after extension\nand rO1/rO2 are the outputs of the first/second F-function of DES.\n\n");
  unsigned long long int eI1 = 0, eI2 = 0;
  unsigned int rI1[8] = {0,0,0,0,0,0,0,0}, rI2[8] = {1,9,6,0,0,0,0,0}, rO1[8] = {0,0,0,0,0,0,0,0}, rO2[8] = {0,0,0,0,0,0,0,0};
  int erI1[8], erI2[8];
  for(int i=0; i<8; i++){
    erI1[i] = (rI1[(i+7)%8]%2)*32 + rI1[i]*2 + rI1[(i+1)%8]/8;
    erI2[i] = (rI2[(i+7)%8]%2)*32 + rI2[i]*2 + rI2[(i+1)%8]/8;
  }
  for(int i=0; i<8; i++){
    eI1 = 64 * eI1 + erI1[i];
    eI2 = 64 * eI2 + erI2[i];
  }
  printf("Extended rI1 = 0x %X %X %X %X %X %X %X %X, Extended rI2 = 0x %X %X %X %X %X %X %X %X.\n\n", erI1[0], erI1[1], erI1[2], erI1[3], erI1[4], erI1[5], erI1[6], erI1[7], erI2[0], erI2[1], erI2[2], erI2[3], erI2[4], erI2[5], erI2[6], erI2[7]);
  printf("In the first step, all S-block will make 0x0 as output\n and every 6-bit input also equals to 0x0.");
  printf("According to each XDTs, probability of each tuple (input 6-bit, output 4-bit) is:\n");
  for(int i=0; i<8; i++){
    printf("Extended rI1[%d] = %#X, rO1[%d] = %#X : XDT %d[%d][%d] = %d/64\n", i+1, erI1[i], i+1, rO1[i], i+1, erI1[i], rO1[i], XDT[i][erI1[i]][rO1[i]]);
  }
  printf("Thus, probability of given (input, output) tuple is:\n");
  for(int i=0; i<7; i++){
    printf("%d/64 * ", XDT[i][erI1[i]][rO1[i]]);
  }
  printf("%d/64 = ", XDT[7][erI1[7]][rO1[7]]);
  double p1 = 1.0f;
  for(int i=0; i<8; i++){
    p1 *= (double)XDT[i][erI1[i]][rO1[i]] / (double)64;
  }
  printf("%.6lf\n\n", p1);
  printf("In the second step, still all S-block will make 0x0 as output\n whereas first three extended inputs are %#X, %#X, %#X.\n", erI2[0], erI2[1], erI2[2]);
  printf("According to each XDTs, probability of each tuple (input 6-bit, output 4-bit) is:\n");
  for(int i=0; i<8; i++){
    printf("Extended rI2[%d] = %#X, rO2[%d] = %#X : XDT %d[%d][%d] = %d/64\n", i+1, erI2[i], i+1, rO2[i], i+1, erI2[i], rO2[i], XDT[i][erI2[i]][rO2[i]]);
  }
  printf("Thus, probability of given (input, output) tuple is:\n");
  for(int i=0; i<7; i++){
    printf("%d/64 * ", XDT[i][erI2[i]][rO2[i]]);
  }
  printf("%d/64 = ", XDT[7][erI2[7]][rO2[7]]);
  double p2 = 1.0f;
  for(int i=0; i<8; i++){
    p2 *= (double)XDT[i][erI2[i]][rO2[i]] / (double)64;
  }
  printf("%.6lf\n\n", p2);
  printf("Therefore the probability of this iterative characteristic is %.6lf * %.6lf = %.6lf.\n", p1, p2, p1*p2);
  printf("It is almost same as 1/234 = %.6lf, thus we succesfully verified that the best iterative characteristic of DES is 1/234.\n", (double)1/(double)234);
  return 0;
}
