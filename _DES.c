#include<stdio.h>
#include<string.h>
#include<math.h>

void Subkey_Gen();
void hexToBin(char master_Key64[]);
void hexToBin_Text(char plain_Text64[]);
void Perm_Divide(int permuted_Master[]);
void Perm_C1(int binary_Master_Key64[]);
void IP_Text(int binary_Plain_Text64[]);
void Perm_C2(int subKeys[][57]);
void Text_Perm_Divide(int permuted_Text[]);
int RightSideFunction(int R[][32],int permuted_Subkeys[][48],int ED_MODE);
int getRow(int x,int y);
int getColumn(char *str);
void int_to_bin_digit(int in[], int out);
void finalPerm(int* sbx,int out);
void TheFinalStage();
void toHex(int arr[]);

int permuted_Master[56]={0};
int ED_MODE=0;
int permuted_Text[64]={0};
int permuted_Subkeys[16][48]={0};
char plain_Text64[17]={0};
char master_Key64[17]={0};
int binary_Master_Key64[64]={0};
int binary_Plain_Text64[64]={0};
int key_left_Half[28]={0};
int key_right_Half[28]={0};
int leftSub[17][28]={0};
int rightSub[17][28]={0};
int subKeys[16][57]={0};
int L[17][32]={0};
int R[17][32]={0};
int SBoxVal[16][32]={0};
int SBoxPerm[16][32]={0};
int ReversedLR[64]={0};
int invRLR[64]={0};


int PC1[56]={
 57,   49,    41,   33,    25,    17,   9,
  1,   58,    50,   42,    34,    26,   18,
 10,    2,    59,   51,    43,    35,   27,
 19,   11,     3,   60,    52,    44,   36,
 63,   55,    47,   39,    31,    23,   15,
  7,   62,    54,   46,    38,    30,   22,
 14,    6,    61,   53,    45,    37,   29,
 21,   13,     5,   28,    20,    12,    4};
  int PC2[48]={
 14,    17,   11,    24,     1,    5,
  3,    28,   15,     6,    21,   10,
 23,    19,   12,     4,    26,    8,
 16,     7,   27,    20,    13,    2,
 41,    52,   31,    37,    47,   55,
 30,    40,   51,    45,    33,   48,
 44,    49,   39,    56,    34,   53,
 46,    42,   50,    36,    29,   32};
int Left_Shift[16]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
int IP[64]={
  58,    50,   42,    34,    26,   18,    10,    2,
  60,    52,   44,    36,    28,   20,    12,    4,
  62,    54,   46,    38,    30,   22,    14,    6,
  64,    56,   48,    40,    32,   24,    16,    8,
  57,    49,   41,    33,    25,   17,     9,    1,
  59,    51,   43,    35,    27,   19,    11,    3,
  61,    53,   45,    37,    29,   21,    13,    5,
  63,    55,   47,    39,    31,   23,    15,    7
};
int EBit[]={
 32,     1,    2,     3,     4,    5,
  4,     5,    6,     7,     8,    9,
  8,    9,    10,    11,    12,   13,
 12,    13,   14,    15,    16,   17,
 16,    17,   18,    19,    20,   21,
 20,    21,   22,    23,    24,   25,
 24,    25,   26,    27,    28,   29,
 28,    29,   30,    31,    32,    1
};
int S1[] = {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
			 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
			 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
			15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13};

int S2[] = {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
			 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
			 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
			13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9};

int S3[] = {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
			13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
			13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
			 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12};

int S4[] = { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
			13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
			10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
			 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14};

int S5[] = { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
			14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
			 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
			11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3};

int S6[] = {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
			10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
			 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
			 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13};

int S7[] = { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
			13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
			 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
			 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12};

int S8[] = {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
			 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
			 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
      2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11};

int IPLast[]={
  16,  7,  20,  21,
  29,  12,  28,  17,
  1,  15,  23,  26,
  5,  18,  31,  10,
  2,   8,  24,  14,
 32 , 27,   3 ,  9,
 19,  13,  30,   6,
 22,  11,   4,  25};

int invIP[]={ 40 ,    8,   48 ,   16 ,   56 ,  24 ,   64 ,  32,
           39,     7,   47,    15,    55,   23,    63,   31,
           38,     6,   46,    14,    54,   22,    62,   30,
           37,     5,   45,    13,    53,   21,    61,   29,
           36,     4,   44,    12,    52,   20,    60,   28,
           35,     3,   43,    11,    51,   19,    59,   27,
           34,     2,   42,    10,    50,   18,    58,   26,
           33,     1,   41,     9,    49,   17,    57,   25};

int main(){
  //Master Key and Sub Key Generation
  int *perm;
  int i,j;
  printf("\n-----------------DEScrypto-----------------\n\t\t\tAuthor:P5N4PPZ\n\n");
  printf("1.Encrypt\n2.Decrypt\n Your Choice: ");
  scanf("%d",&ED_MODE);

  printf("Enter 64bit Master Key\n");
  scanf("%s",master_Key64);
  hexToBin(master_Key64);
  Perm_C1(binary_Master_Key64);
  Perm_Divide(permuted_Master);
  for(i=0;i<28;i++){
    leftSub[0][i]=key_left_Half[i];
    rightSub[0][i]=key_right_Half[i];
  }
  Subkey_Gen();

  //Plain Text to Cipher
  if(ED_MODE==1){
    printf("Enter 64bit Plain Text\n");
  }
  else{
    printf("Enter Cipher Text\n");
  }
  scanf("%s",plain_Text64);
  hexToBin_Text(plain_Text64);
  IP_Text(binary_Plain_Text64);
  Text_Perm_Divide(permuted_Text);
  RightSideFunction(R,permuted_Subkeys,ED_MODE);
  TheFinalStage();
  return 0;
}

//Applying PC-1 to Binary Binary_Plain_Text64
void Perm_C1(int binary_Master_Key64[]){

  int i=0,perm=0;
  for(i=0;i<56;i++){
    perm = PC1[i];
    permuted_Master[i]=binary_Master_Key64[perm-1];
  }
  printf("Permuted Master Key\n");
  for(i=0;i<56;i++){
    printf("%d",permuted_Master[i]);
  }
  printf("\n");

}

//Divide the Permuted Master Key into 2(28 bit each)
void Perm_Divide(int permuted_Master[]){
  int i=0;
  for(i=0;i<28;i++){
    key_left_Half[i]=permuted_Master[i];
  }
  for(i=0;i<28;i++){
    key_right_Half[i]=permuted_Master[i+28];
  }

}

void Subkey_Gen(){
  int i,j,k,shifts=0,last,seclast;
  {//Sub Key Left
  for(i=1;i<=16;i++){
    shifts=Left_Shift[i-1];
    last=leftSub[i-1][shifts-1];
    for(k=0;k<shifts;k++){
      for(j=0;j<28;j++){
        leftSub[i][j]=leftSub[i-1][j+shifts];
      }
    }
    leftSub[i][27]=last;
    if(shifts==2){
      seclast=leftSub[i-1][0];
      leftSub[i][26]=seclast;
    }
    shifts=shifts-1;
  }
  }
  {//Sub Key right
  for(i=1;i<=16;i++){
    shifts=Left_Shift[i-1];
    last=rightSub[i-1][shifts-1];
    for(k=0;k<shifts;k++){
    for(j=0;j<28;j++){
      rightSub[i][j]=rightSub[i-1][j+shifts];
    }
  }
    rightSub[i][27]=last;
    if(shifts==2){
      seclast=rightSub[i-1][shifts-2];
      rightSub[i][26]=seclast;
    }
    shifts=shifts-1;
  }
  }
  {//Subkey Merged
    for(i=1;i<=16;i++){
      for(j=0;j<28;j++){
      subKeys[i-1][j]=leftSub[i][j];
      subKeys[i-1][j+28]=rightSub[i][j];
    }
    }
    Perm_C2(subKeys);
  }
}

//Applying PC-1 to Binary Binary_Plain_Text64
void Perm_C2(int subKeys[][57]){

  int i=0,perm=0,j;
  for(i=0;i<48;i++){
    for(j=0;j<48;j++){
    perm = PC2[j];
    permuted_Subkeys[i][j]=subKeys[i][perm-1];
  }
  }
  printf("\nSub Keys After Permutation\n");
  for(i=0;i<16;i++){
    printf("\n");
    for(j=0;j<48;j++)
    printf("%d",permuted_Subkeys[i][j]);
  }
  printf("\n");

}

//Hex Value to Binary
void hexToBin(char master_Key64[]){
  int k;
  int hexDigitToBinary[16][4] = {{0,0,0,0}, {0,0,0,1}, {0,0,1,0}, {0,0,1,1}, {0,1,0,0}, {0,1,0,1},
  {0,1,1,0}, {0,1,1,1}, {1,0,0,0}, {1,0,0,1}, {1,0,1,0}, {1,0,1,1}, {1,1,0,0}, {1,1,0,1}, {1,1,1,0},
   {1,1,1,1}};
  char hexDigits[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8',
   '9', 'A', 'B', 'C', 'D', 'E', 'F'};
   char hexadecimal[17]={};
   int i,j,index=0;
   strcpy(hexadecimal,master_Key64);
   for(i=0; i<16; i++){
      for(j = 0; j < 16; j++){
          if(hexadecimal[i] == hexDigits[j]){
            for(k=0;k<4;k++){
              binary_Master_Key64[index++]= hexDigitToBinary[j][k];
            }
          }
      }
    }
    printf("Master Key Binary\n");
    for(i=0;i<64;i++){
      printf("%d",binary_Master_Key64[i]);
    }

    printf("\n");
}


//Hex Value to Binary
void hexToBin_Text(char plain_Text64[]){
  int k;
  int hexDigitToBinary[16][4] = {{0,0,0,0}, {0,0,0,1}, {0,0,1,0}, {0,0,1,1}, {0,1,0,0}, {0,1,0,1},
  {0,1,1,0}, {0,1,1,1}, {1,0,0,0}, {1,0,0,1}, {1,0,1,0}, {1,0,1,1}, {1,1,0,0}, {1,1,0,1}, {1,1,1,0},
   {1,1,1,1}};
  char hexDigits[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8',
   '9', 'A', 'B', 'C', 'D', 'E', 'F'};
   char hexadecimal[17]={};
   int i,j,index=0;
   strcpy(hexadecimal,plain_Text64);
   for(i=0; i<16; i++){
      for(j = 0; j < 16; j++){
          if(hexadecimal[i] == hexDigits[j]){
            for(k=0;k<4;k++){
              binary_Plain_Text64[index++]= hexDigitToBinary[j][k];
            }
          }
      }
    }
    printf("Plain Text Binary\n");
    for(i=0;i<64;i++){
      printf("%d",binary_Plain_Text64[i]);
    }

    printf("\n");
}
//Applying PC-1 to Binary Binary_Plain_Text64
void IP_Text(int binary_Plain_Text64[]){

  int i=0,perm=0;
  for(i=0;i<64;i++){
    perm = IP[i];
    permuted_Text[i]=binary_Plain_Text64[perm-1];
  }
  printf("Permuted Plain Text\n");
  for(i=0;i<64;i++){
    printf("%d",permuted_Text[i]);
  }
  printf("\n");

}
//Divide the Permuted Plain Text into 2(32 bit each)
void Text_Perm_Divide(int permuted_Text[]){
  int i=0,row,column;
  for(i=0;i<32;i++){
    L[0][i]=permuted_Text[i];
  }
  for(i=0;i<32;i++){
    R[0][i]=permuted_Text[i+32];
  }
  printf("\n Left and right half\n");
  for(i=0;i<32;i++){
    printf("%d",L[0][i]);
  }
  printf("\n");
  for(i=0;i<32;i++){
    printf("%d",R[0][i]);
  }

}

//RightSideFunction

int RightSideFunction(int R[][32],int permuted_Subkeys[][48],int ED_MODE){
  int EbitRight[16][48]={0};
  int XoREbitRight[16][48]={0};
  char str[5]={0};
  int i,j,k,l,x,y,z,box,pos,bit=0;
  int row[8]={};
  int column[8]={};
  int rpos[16][16]={0};
  int newpos[16][8]={0};
  for(i=0;i<16;i++){
    for(j=0;j<48;j++){
      bit=EBit[j];
      EbitRight[i][j]=R[i][bit-1];
      if(ED_MODE==1){
        XoREbitRight[i][j]=permuted_Subkeys[i][j]^EbitRight[i][j];
      }else{
        XoREbitRight[i][j]=permuted_Subkeys[15-i][j]^EbitRight[i][j];
      }
    }

        rpos[i][0]=XoREbitRight[i][0];
        rpos[i][1]=XoREbitRight[i][5];

        rpos[i][2]=XoREbitRight[i][6];
        rpos[i][3]=XoREbitRight[i][11];

        rpos[i][4]=XoREbitRight[i][12];
        rpos[i][5]=XoREbitRight[i][17];

        rpos[i][6]=XoREbitRight[i][18];
        rpos[i][7]=XoREbitRight[i][23];

        rpos[i][8]=XoREbitRight[i][24];
        rpos[i][9]=XoREbitRight[i][29];

        rpos[i][10]=XoREbitRight[i][30];
        rpos[i][11]=XoREbitRight[i][35];

        rpos[i][12]=XoREbitRight[i][36];
        rpos[i][13]=XoREbitRight[i][41];

        rpos[i][14]=XoREbitRight[i][42];
        rpos[i][15]=XoREbitRight[i][47];
        for(z=0;z<8;z++){
          row[z]=getRow(rpos[i][2*z],rpos[i][2*z+1]);
          str[0]='0'+XoREbitRight[i][6*z+1];
          str[1]='0'+XoREbitRight[i][6*z+2];
          str[2]='0'+XoREbitRight[i][6*z+3];
          str[3]='0'+XoREbitRight[i][6*z+4];
          str[4]='\0';
          column[z]=getColumn(str);
        }
          pos=16* row[0]+column[0];
          newpos[i][0]=S1[pos];
          pos=16* row[1]+column[1];
          newpos[i][1]=S2[pos];
          pos=16* row[2]+column[2];
          newpos[i][2]=S3[pos];
          pos=16* row[3]+column[3];
          newpos[i][3]=S4[pos];
          pos=16* row[4]+column[4];
          newpos[i][4]=S5[pos];
          pos=16* row[5]+column[5];
          newpos[i][5]=S6[pos];
          pos=16* row[6]+column[6];
          newpos[i][6]=S7[pos];
          pos=16* row[7]+column[7];
          newpos[i][7]=S8[pos];
          int_to_bin_digit(newpos[i],i);
          finalPerm(SBoxVal[i],i);
          for(z=0;z<32;z++){
            L[i+1][z]=R[i][z];
            R[i+1][z]=L[i][z]^SBoxPerm[i][z];
          }
}

  return 0;
}
void finalPerm(int* sbx,int out){

  int z,bit;
  for(z=0;z<32;z++){
    bit=IPLast[z];
    SBoxPerm[out][z]=sbx[bit-1];
  }
}
void int_to_bin_digit(int in[], int out)
{
    unsigned int mask = 1U << (4-1);
    int i,j,k=0;
    for(i=0;i<8;i++){
    for (j = 0; j < 4; j++) {
        SBoxVal[out][k] = (in[i] & mask) ? 1 : 0;
        in[i] <<= 1;
        k++;
    }
  }
}

int getRow(int x,int y)
{
    int n;
    int powe = 10;
    while(y >= powe)
        powe *= 10;
    n =  x * powe + y;
    int row = 0, i = 0, remainder;
    while (n!=0)
    {
        remainder = n%10;
        n /= 10;
        row += remainder*pow(2,i);
        ++i;
    }
    return row;
}
int getColumn(char * str){
  int n = 0;
 int size = strlen(str) - 1;
        int count = 0;
 while ( *str != '\0' ) {
  if ( *str == '1' )
      n = n + pow(2, size - count );
  count++;
  str++;
 }
 return n;
}
void TheFinalStage(){
  int i,val=0,b,num=0;
  for(i=0;i<32;i++){
    ReversedLR[i]=R[16][i];
  }
  for(i=0;i<32;i++){
    ReversedLR[i+32]=L[16][i];
  }
  for(i=0;i<64;i++){
    val=invIP[i];
    invRLR[i]=ReversedLR[val-1];
  }
  printf("\n");
  for(i=0;i<64;i++){
    printf("%d",invRLR[i]);
  }
  toHex(invRLR);
}
void toHex(int arr[]){

int i;
long long int num=0;
char a[65]={};
for(i=0;i<64;i++){
  a[i] =arr[i]+'0';
}
a[64]='\0';
for(i=0;i<64;i++){
    int b = a[i]=='1'?1:0;
    num = (num<<1)|b;
}
printf("\n Cipher Text: ");
printf("%llX\n", num);
}
