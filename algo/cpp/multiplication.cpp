#include <iostream>

using namespace std;

const int N = 70;

int len(char a[]){
    int l = 0;
    while ((a[l] != '\0') && (l < N))
        l++;
    return l;
} 

void print(char a[]){
    for (int i = 0; i < len(a); i ++) cout << a[i];
    cout << endl;
}

void split(char a[], char a1[], char a2[]){
    int la = len(a);
    int la1 = static_cast<int>(la / 2);
    for (int i = 0; i < la; i ++)
        if (i < la1)
            a1[i] = a[i];
        else
            a2[i - la1] = a[i];
    a1[la1] = '\0';
    a2[la - la1] = '\0';
    return;
}


void pad_zeros_first(char a[], int n){
    int la = len(a);
    for (int i = n + la - 1; i >= 0; i--)
        if (i - n >= 0) a[i] = a[i - n]; else a[i] = '0';
    a[la + n] = '\0';
    return;
}

void char_sum(char a[], char b[], char c[]){
    int la = len(a);
    int lb = len(b);
    c[0] = '0';
    int m = la > lb ? la : lb;
    int prev = 0;
    int ai, bi;
    int shift = static_cast<int>((a[0] + b[0] - '0' - '0') / 10);
    for (int i = 0; i < m; i ++){
        if (i < la) ai = static_cast<int>(a[la - i - 1] - '0'); else ai = 0;
        if (i < lb) bi = static_cast<int>(b[lb - i - 1] - '0'); else bi = 0;
        c[m + shift - i - 1] = static_cast<char>((ai + bi + prev) % 10 + '0');
        prev = static_cast<int>((ai + bi + prev) / 10);
    }
    if (prev > 0) c[0] = static_cast<char>(prev + '0');
    c[m + shift] = '\0';
    return;
}

void char_subtract(char a[], char b[], char c[]){
    int la = len(a);
    int lb = len(b);
    c[0] = 0;
    int diff;
    int minus_one = 0;
    char bi;
    for (int i = 0; i < la; i++){
        if (i < lb) bi = b[lb - i - 1]; else bi = '0';
        diff = 10 + a[la - i - 1] - bi - minus_one;
        c[la - i - 1] = static_cast<char>((diff % 10) + '0');
        minus_one = 1 - static_cast<int>(diff / 10);
    };
    c[la] = '\0';
    return;
}

int pad_zeros_last(char a[], int n){
    int la = len(a);
    for (int i = la; i < n + la; i++)
        a[i] = '0';
    a[n + la] = '\0';
    return la + n;
}

void cut_zeros_first(char a[]){
    int la = len(a);
    int z = 0;
    for (int i = 0; i < la; i++)
        if ((i == z) && (a[i] == '0'))
            z++;
        else
            a[i - z] = a[i];
    if (z < la)
        a[la - z] = '\0';
        return;
    a[0] = '0';
    a[1] = '\0';
    return;

}


void recursive_mul(char A[], char B[], char C[]){
    int lA = len(A);
    int lB = len(B);
    if ((lA < 2) && (lB < 2)){
        int v = (A[0] - '0') * (B[0] - '0');
        C[0] = static_cast<char>((v / 10) + '0');
        C[1] = static_cast<char>((v % 10) + '0');
        C[2] = '\0';
        return;
    }
    if (lA < lB){
        pad_zeros_first(A, lB - lA);
        lA = lB;
    }
    if (lB < lA){
        pad_zeros_first(B, lA - lB);
        lB = lA;
    }
    char a[N], b[N];
    split(A, a, b);
    char c[N], d[N];
    split(B, c, d);
    char ac[N];
    recursive_mul(a, c, ac);
    char bd[N];
    recursive_mul(b, d, bd);
    char ab[N];
    char_sum(a, b, ab);   // tochar(toint(a, la) + toint(b, lb), ab);
    char cd[N];
    char_sum(c, d, cd);
    char abcd[N];
    recursive_mul(ab, cd, abcd);
    char acbd[N];
    char_sum(ac, bd, acbd);
    char abcd_acbd[N];
    char_subtract(abcd, acbd, abcd_acbd);
    pad_zeros_last(ac, lA - len(a) + lB - len(b));
    pad_zeros_last(abcd_acbd, lA - len(a));
    char first_second[N];
    char_sum(ac, abcd_acbd, first_second);
    char_sum(first_second, bd, C);
    cut_zeros_first(C);
    return;   // revrite with char_subtract
}

int main()
{
    char a[N], b[N], c[N];
    scanf("%s %s", &a, &b);
    a[len(a)] = '\0';
    b[len(b)] = '\0';

    recursive_mul(a, b, c);
    for (int i = 0; i < len(c); i++)
        cout << c[i];
    cout << endl;
    return 0;
}