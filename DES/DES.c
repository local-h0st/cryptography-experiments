#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool debugMode = false;

int IP[8][8] = {
    {58,50,42,34,26,18,10,2},
    {60,52,44,36,28,20,12,4},
    {62,54,46,38,30,22,14,6},
    {64,56,48,40,32,24,16,8},
    {57,49,41,33,25,17,9,1},
    {59,51,43,35,27,19,11,3},
    {61,53,45,37,29,21,13,5},
    {63,55,47,39,31,23,15,7},
};
int PC1[8][7] = {
    {57,49,41,33,25,17,9},
    {1,58,50,42,34,26,18},
    {10,2,59,51,43,35,27},
    {19,11,3,60,52,44,36},
    {63,55,47,39,31,23,15},
    {7,62,54,46,38,30,22},
    {14,6,61,53,45,37,29},
    {21,13,5,28,20,12,4},
};
int PC2[8][6] = {
    {14,17,11,24,1,5},
    {3,28,15,6,21,10},
    {23,19,12,4,26,8},
    {16,7,27,20,13,2},
    {41,52,31,37,47,55},
    {30,40,51,45,33,48},
    {44,49,39,56,34,53},
    {46,42,50,36,29,32},
};
int E[8][6] = {
    {32,1,2,3,4,5},
    {4,5,6,7,8,9},
    {8,9,10,11,12,13},
    {12,13,14,15,16,17},
    {16,17,18,19,20,21},
    {20,21,22,23,24,25},
    {24,25,26,27,28,29},
    {28,29,30,31,32,1},
};
int P[8][4] = {
    {16,7,20,21},
    {29,12,28,17},
    {1,15,23,26},
    {5,18,31,10},
    {2,8,24,14},
    {32,27,3,9},
    {19,13,30,6},
    {22,11,4,25},
};
int S[8][4][16] = {
    {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8}, 
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0}, 
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13},
    },
    {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15}, 
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9},
    },
    {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8}, 
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12},
    },
    {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9}, 
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14},
    },
    {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3},
    },
    {
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11}, 
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8}, 
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6}, 
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13},
    },
    {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6}, 
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2}, 
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12},
    },
    {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2}, 
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11},
    },
};
char K[65] = "0000000100100011010001010110011110001001101010111100110111101111";

void printinfo(const char *str, char *arr, int len, int break_lines){
    printf(str);
    for(int i=0;i<len;i++){
        if(i==len/2){
            printf(" ");
        }
        printf("%c",arr[i]);
    }
    for(int i = 0;i<break_lines+1;i++){
        printf("\n");
    }
}

void reverseIP(int IP[8][8],int IP_rev_recv[8][8]){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            IP_rev_recv[IP[i][j]/8][IP[i][j]%8-1] = i*8+j+1;
        }
    }
}   // pass

void moveLeftOnce(char pc1[57]){
    char temp=pc1[0];
    for(int i=0;i<27;i++){
        pc1[i]=pc1[i+1];
    }
    pc1[27] = temp;
    temp = pc1[28];
    for(int i=28;i<54;i++){
        pc1[i]=pc1[i+1];
    }
    pc1[55] = temp;
}   // pass

void generateKs(char K[65], int PC1[8][7], int PC2[8][6], char Keys_receive[16][49]){ // 
    // 依照PC1填原始表
    char T[57];
    for(int line=0;line<8;line++){
        for(int row=0;row<7;row++){
            T[line*7+row] = K[PC1[line][row]-1];
        }
    }
    T[56] = '\0';   // TODO     T[56] = '\n';
    if(debugMode){
        printinfo("T <- PC1(K):\t\t",T,56,0);
    }

    for(int i=1;i<=16;i++){
        if(debugMode){
            printf("generating key %d:\n",i);
        }
        // 循环移位
        moveLeftOnce(T);
        if(i!=1&&i!=2&&i!=9&&i!=16){
            moveLeftOnce(T);
        }
        if(debugMode){
            printinfo("  after move left\t",T,56,0);
        }

        // 对照PC2生成本次Ki并写入Keys_reveive
        for(int line=0;line<8;line++){
            for(int row=0;row<6;row++){
                Keys_receive[i-1][line*6+row] = T[PC2[line][row]-1];
            }
        }
        Keys_receive[i-1][48] = '\0';
        if(debugMode){
            printinfo("  key<-PC2(T)\t\t",Keys_receive[i-1],48,0);
        }
    }
    if(debugMode){
        printf("All 16 keys generated correctly.\n\n");
    }
}   // pass

void replacement(char data[65], int IP[8][8]){  // 用于始末的置换
    char temp[65];
    for(int line=0;line<8;line++){
        for(int row=0;row<8;row++){
            temp[line*8+row] = data[IP[line][row]-1];
        }
    }
    temp[64] = '\0';
    strcpy(data,temp);
}   // pass

void doOnce(char data[65], char Ki[49], int E[8][6], int P[8][4] ,int S[8][4][16]){
    char L[33];
    char R[33];
    for(int i=0;i<32;i++){
        L[i] = data[i];
        R[i] = data[i+32];
    }
    L[32] = '\0';
    R[32] = '\0';
    // R经过E扩展到48位
    char extendedR[49];
    for(int line=0;line<8;line++){
        for(int row=0;row<6;row++){
            extendedR[line*6+row] = R[E[line][row]-1];
        }
    }
    extendedR[48] = '\0';
    if(debugMode){
        printinfo("  extendedR\t\t",extendedR,48,0);
    }


    // 和Ki做xor
    for(int i=0;i<48;i++){
        if(extendedR[i]==Ki[i]){
            extendedR[i] = '0';
        }
        else{
            extendedR[i] = '1';
        }
    }
    if(debugMode){
        printinfo("  Ki xor extR(48 bit)\t",extendedR,48,0);
    }

    // 分8组
    char replaced[33];
    for(int i=0;i<8;i++){
        // 注意直接拿出来的是char，要ascii减掉48才是数字0和1
        int line = 2*(extendedR[i*6]-48)+(extendedR[i*6+5]-48);
        int row = 8*(extendedR[i*6+1]-48)+4*(extendedR[i*6+2]-48)+2*(extendedR[i*6+3]-48)+(extendedR[i*6+4]-48);
        int decimo = S[i][line][row];
        if(debugMode){
            printf("  line/row/decimo:\t%d/%d/%d\n",line+1,row+1,decimo);
        }
        for(int j=3;j>=0;j--){
            int n = decimo%2;
            if(n==0){
                replaced[i*4+j] = '0';
            }
            else{
                replaced[i*4+j] = '1';
            }
            decimo = decimo/2;
        }
        replaced[i*4+4] = '\0';
        if(debugMode){
            printf("  replaced(32 bit):\t");
            printf(replaced);
            printf("\n");
        }
    }

    char fOut[33];
    for(int line=0;line<8;line++){
        for(int row=0;row<4;row++){
            fOut[line*4+row] = replaced[P[line][row]-1];
        }
    }
    fOut[32] = '\0';
    if(debugMode){
        printf("  fout<-P(repl):\t");
        printf(fOut);
        printf("\n");
    }


    // 和L做xor
    char RNext[33];
    for(int i=0;i<48;i++){
        if(L[i]==fOut[i]){
            RNext[i] = '0';
        }
        else{
            RNext[i] = '1';
        }
    }
    RNext[32] = '\0';
    if(debugMode){
        printf("  L xor fout\t\t");
        printf(RNext);
        printf("\n");
    }


    for(int i=0;i<32;i++){
        data[i] = R[i];
    }
    for(int i=0;i<32;i++){
        data[i+32] = RNext[i];
    }
    data[64] = '\0';
}   // pass

void swapLR(char data[65]){
    char L[33];
    char R[33];
    for(int i=0;i<32;i++){
        L[i] = data[i];
        R[i] = data[i+32];
    }
    L[32] = '\0';
    R[32] = '\0';
    for(int i=0;i<32;i++){
        data[i] = R[i];
    }
    for(int i=0;i<32;i++){
        data[i+32] = L[i];
    }
    data[64] = '\0';
}   // pass

void handleBlock(
        char block[65],
        char K[65],
        bool encryptMode,
        int IP[8][8],
        int PC1[8][7],
        int PC2[8][6],
        int E[8][6],
        int P[8][4],
        int S[8][4][16]
    ){
        char keys[16][49];
        int IP_rev[8][8];
        generateKs(K, PC1, PC2, keys);
        reverseIP(IP,IP_rev);

        if(debugMode){
            if(encryptMode){
                printf("---------- encrypt ----------\n");
            }
            else{
                printf("---------- decrypt ----------\n");
            }    
            printinfo("orig\t\t\t",block,64,0);        
        }


        replacement(block,IP);
        if(debugMode){
            if(encryptMode){
                printinfo("L0/R0\t\t\t",block,64,0);
            }
            else{
                printinfo("R16/L16\t\t\t",block,64,0);
            }            
        }

        for(int i=0;i<16;i++){
            if(debugMode){
                printf("doing %d time(s):\n",i+1);
            }
            
            if(encryptMode){
                doOnce(block,keys[i],E,P,S);
                if(debugMode){
                    printf("L%d/R%d\t\t\t",i+1,i+1);
                }
            }
            else{
                doOnce(block,keys[15-i],E,P,S);
                if(debugMode){
                    printf("R%d/L%d\t\t\t",15-i,15-i);
                }
            }
            if(debugMode){
                printinfo("",block,64,0);
            }
        }
        swapLR(block);
        if(debugMode){
            if(encryptMode){
                printinfo("R16/L16\t\t\t",block,64,0);
            }
            else{
                printinfo("L0/R0\t\t\t",block,64,0);
            }            
        }

        replacement(block,IP_rev);
        if(debugMode){
            if(encryptMode){
                printinfo("encrypted\t\t",block,64,0);
            }
            else{
                printinfo("decrypted\t\t",block,64,0);
            }            
        }

}   // pass

void devideBlock(char *strr, char blocks[][65], int size){
    for(int i=0;i<size;i++){
        for(int j=0;j<65;j++){
            blocks[i][j] = '0';
        }
    }   // 不够长度填充0
    int i=0;
    while(i<size*64&&strr[i]!='\0'){
        blocks[i/64][i%64] = strr[i];
        if(i%64==63){
            blocks[i/64][64] = '\0';
        }
        i++;
    }
    blocks[i/64][64] = '\0';
    for(int j=i/64+1;j<size;j++){
        blocks[j][0] = '\0';  // 第一个如果是'\0'代表此行为空
    }
}   // pass

void mergeBlock(char blocks[][65],int size, char *bindata){
    int pos = 0;
    for(int i=0;i<size;i++){
        for(int j=0;blocks[i][j]!='\0';j++){
            bindata[pos] = blocks[i][j];
            pos++;
        }
    }
    bindata[pos] = '\0';
}   // pass

void encodeStr2bin(char *strr, char *data){
    int i=0;
    while(strr[i]!='\0'){
        int ascii = strr[i];
        for(int j=0;j<8;j++){
            data[i*8+7-j] = 48+ascii%2;
            ascii = ascii/2;
        }
        i++;
    }
    data[i*8] = '\0';
}   // pass

void decodeBin2str(char *data, char*strr){
    int i=0;
    while(data[i*8]!='\0'){
        strr[i] = 128*(data[i*8]-48)+64*(data[i*8+1]-48)+32*(data[i*8+2]-48)+16*(data[i*8+3]-48)+8*(data[i*8+4]-48)+4*(data[i*8+5]-48)+2*(data[i*8+6]-48)+1*(data[i*8+7]-48);
        i++;
    }
    strr[i] = '\0';
}   // pass

void bin2hex(char *bindata, char *hex_recv){
    if(debugMode){
        printf("--------- converting bin to hex. ----------\n");
    }
    int i=0;
    while(bindata[i*4]!='\0'){
        // 第i组四个数下标是i*4到i*4+3
        int decimo = 8*(bindata[i*4]-48)+4*(bindata[i*4+1]-48)+2*(bindata[i*4+2]-48)+(bindata[i*4+3]-48);
        if(decimo<10){
            hex_recv[i] = decimo+48;
        }
        else{
            hex_recv[i] = decimo+87;
        }
        if(debugMode){
            printf("group %d: %c%c%c%c decimo/hex: %d/%c\n",i+1,bindata[i*4],bindata[i*4+1],bindata[i*4+2],bindata[i*4+3],decimo,hex_recv[i]);
        }
        i++;
    }
    hex_recv[i] = '\0';
}   // pass

void hex2bin(char *hexdata, char *bin_recv){
    int i=0;
    while(hexdata[i]!='\0'){
        int decimo = hexdata[i]-48;
        if(decimo>9){
            decimo = decimo-39;
        }
        for(int j=0;j<4;j++){
            bin_recv[i*4+3-j] = 48+decimo%2;
            decimo = decimo/2;
        }
        i++;
    }
    bin_recv[i*4] = '\0';
}   // pass


void handldStr(
    char *strr,
    char *result_recv,
    bool encryptMode,
    char K[65],
    int IP[8][8],
    int PC1[8][7],
    int PC2[8][6],
    int E[8][6],
    int P[8][4],
    int S[8][4][16]
){
    char strrBin[2000000];
    const int size = 512;
    char blocks[size][65];
    if(encryptMode){
        encodeStr2bin(strr,strrBin);
        devideBlock(strrBin,blocks,size);
        for(int i=0;i<size;i++){
            if(blocks[i][0]!='\0'){
                handleBlock(blocks[i],K,true,IP,PC1,PC2,E,P,S);
            }
        }
        mergeBlock(blocks,size,strrBin);
        bin2hex(strrBin,result_recv);
    }
    else{
        hex2bin(strr,strrBin);
        devideBlock(strrBin,blocks,size);
        for(int i=0;i<size;i++){
            if(blocks[i][0]!='\0'){
                handleBlock(blocks[i],K,false,IP,PC1,PC2,E,P,S);
            }
        }
        mergeBlock(blocks,size,strrBin);
        decodeBin2str(strrBin,result_recv);
    }
}

int main(void){


    char result[100000];
    char str[100000];

    // encrypt
    printf("input the string you want to encrypt: ");
    gets(str);
    handldStr(str,result,true,K,IP,PC1,PC2,E,P,S);
    printf("result ==> ");
    printf(result);
    printf("\n\n");

    // decrypt
    printf("input the hex you want to decrypt: ");
    gets(str);
    handldStr(str,result,false,K,IP,PC1,PC2,E,P,S);
    printf("result ==> ");
    printf(result);
    printf("\n");

    // for test
    // char s[65] = "0000000100100011010001010110011110001001101010111100110111101111";
    // handleBlock(s,K,true,IP,PC1,PC2,E,P,S);
    // printf(s);
    // return 0;
}

// DES
