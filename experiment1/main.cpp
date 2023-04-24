#include <iostream>
using namespace std;

int main(){
    char encrypted[256] = "UZQSOVUOHXMOPVGPOZPEVSGZWSZOPFPESXUDBMETSXAIZVUEPHZHMDZSHZOWSFPAPPDTSVPQUZWYMXUZUHSXEPYEPOPDZSZUFPOMBZWPFUPZHMDJUDTMOHMQ";
    int count = 0;
    float probability[26] = {8.04,1.54,3.06,3.99,12.51,2.3,1.96,5.49,7.26,0.16,0.67,4.14,2.53,7.09,7.6,2,0.11,6.12,6.54,9.25,2.71,0.99,1.92,0.19,1.73,0.09};
    int frequency[26];
    for(int i = 0;i<26;i++){
        frequency[i] = 0;
    }
    for(int i=0;encrypted[i]!='\0';i++){
        frequency[encrypted[i]-65]++;
        // printf("[%c:%d]%d\n",encrypted[i],encrypted[i]-65,frequency[encrypted[i]-65]);
        count++;
    }
    /*
    for(int i = 0;i<26;i++){
        // printf("%.2f\t",((float)frequency[i])/((float)count));
        printf("%d\t",frequency[i]);
    }
    cout<<endl;
    for(int i = 0;i<26;i++){
        printf("%.2f\t",probability[i]*count/100);
    }
    cout<<endl;
    */

    int fake2truth[26];
    for(int i = 0;i<26;i++){
        fake2truth[i] = -1;
    }
    fake2truth[15] = 4;
    fake2truth[25] = 19;
    fake2truth[20] = 8;
    fake2truth[16] = 22;
    fake2truth[18] = 0;
    fake2truth[14] = 18;
    fake2truth[21] = 3;
    fake2truth[7] = 2;
    fake2truth[23] = 11;
    fake2truth[12] = 14;
    fake2truth[6] = 24;
    fake2truth[4] = 17;
    fake2truth[22] = 7;
    fake2truth[5] = 21;
    fake2truth[3] = 13;
    fake2truth[1] = 5;
    fake2truth[19] = 12;
    fake2truth[0] = 1;
    fake2truth[8] = 20;
    fake2truth[24] = 15;

    cout<<encrypted<<endl;
    cout<<"依照单字符出现的统计概率配合双字符出现的概率可得对应为："<<endl;
    for(int i=0;encrypted[i]!='\0';i++){
        if(fake2truth[encrypted[i]-65]!=-1){
            printf("%c",fake2truth[encrypted[i]-65]+65);
        }
        else{
            printf("%c",encrypted[i]);
        }
    }
    cout<<endl;
}