#include <iostream>

int get_r(int a,int b){
    if(a==0)
        return b;
    else if(b==0)
        return a;
    else
        return a>b?a%b:b%a;
}

int gcd(int a, int b){
    int t,r;
    if(a>b)
        t = b;
    else
        t = a;
    r= get_r(a,b);
    while(r){
        int tmp = get_r(t,r);
        t = r;
        r = tmp;
    }
    return t;
}

int get_reverse(int num, int mod){    // num < mod
    //                              a
    //  prev_s      prev_t          b
    //  s           t       tmp     r
    //
    if(gcd(num,mod)!=1){
        return -1;
    }
    int prev_s = 1, prev_t = 0, s = 0, t = 1, prev_r = 0, a = mod, b = num, tmp = a/b, r = get_r(a,b);
    while(r){
        int temp = s;
        s = prev_s-s*tmp;
        prev_s = temp;
        temp = t;
        t = prev_t-t*tmp;
        prev_t = temp;
        tmp = b/r;
        temp = r;
        r = get_r(b,r);
        b = temp;
    }
    if(t<0)
        t = t + mod;
    return t;


}

int main(void){
    int a,b,max,min;
    printf("input two numbers:\n");
    std::cin>>a>>b;
    max = b>a?b:a;
    min = a<b?a:b;
    int rev = get_reverse(min,max);
    if(rev==-1){
        printf("the gcd of them is %d, and the reverse of %d mod %d does not exists.\n",gcd(a,b),min,max);
    }
    else{
        printf("the gcd of them is %d, and the reverse of %d mod %d is %d\n",gcd(a,b),min,max,rev); 
    }
    return 0;
}


// 扩展欧几里得算法