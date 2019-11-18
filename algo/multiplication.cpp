#include <iostream>

using namespace std;

const int N = 70;

int split(char a[], int la, char a1[], char a2[]){
    int la1 = la / 2;
    for (int i = 0; i < la; i ++)
        if (i < la1)
            a1[i] = a[i];
        else
            a2[i - la1] = a[i];
    return la1;
}


void pad_zeros_first(char a[], int la, int n){
    for (int i = n + la - 1; i >= 0; i--)
        if (i - n >= 0) a[i] = a[i - n]; else a[i] = '0';
    return;
}

int char_sum(char a[], char b[], int la, int lb, char c[]){
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
    return m + shift;
}

int char_subtract(char a[], char b[], int la, int lb, char c[]){
    c[0] = 0;
    int diff;
    int minus_one = 0;
    char bi;
    for (int i = 0; i < la; i++){
        if (i < lb) bi = b[lb - i - 1]; else bi = '0';
        diff = 10 + a[la - i - 1] - bi - minus_one;
        c[la - i - 1] = static_cast<char>((diff % 10) + '0');
        minus_one = static_cast<int>(diff / 10);
    };
    return la;
}

int pad_zeros_last(char a[], int la, int n){
    for (int i = la; i < n + la; i++)
        a[i] = '0';
    a[n + la] = '\0';
    return la + n;
}

// char * char_subtract()


int recursive_mul(char A[], char B[], char C[], int lA=N, int lB=N){
    if ((lA < 2) && (lB < 2)){
        int v = (A[0] - '0') * (B[0] - '0');
        C[0] = static_cast<char>((v / 10) + '0');
        C[1] = static_cast<char>((v % 10) + '0');
        return 2;
    }
    if (lA < lB){
        pad_zeros_first(A, lA, lB - lA);
        lA = lB;
    }
    if (lB > lA){
        pad_zeros_first(B, lB, lB - lA);
        lB = lA;
    }
    char a[N], b[N];
    int la = split(A, lA, a, b);
    char c[N], d[N];
    int lb = split(B, lB, c, d);
    char ac[N];
    int lac = recursive_mul(a, c, ac, la, lb);
    char bd[N];
    int lbd = recursive_mul(b, d, bd, lA - la, lB - lb);
    char ab[N];
    int lab = char_sum(a, b, la, lb, ab);   // tochar(toint(a, la) + toint(b, lb), ab);
    char cd[N];
    int lcd = char_sum(c, d, lA - la, lB - lb, cd);
    char abcd[N];
    int labcd = recursive_mul(ab, cd, abcd, lab, lcd);
    char acbd[N];
    int lacbd = char_sum(ac, bd, lac, lbd, acbd);
    char abcd_acbd[N];
    int labcd_acbd = char_subtract(abcd, acbd, labcd, lacbd, abcd_acbd);
    char first[N];
    int lfirst = pad_zeros_last(ac, lac, lA - la + lB - lb);
    char second[N];
    int lsecond = pad_zeros_last(abcd_acbd, labcd_acbd, lA - la);
    char first_second[N];
    int lfirst_second = char_sum(first, second, lfirst, lsecond, first_second);
    int lC = char_sum(first_second, bd, lfirst_second, lbd, C);
    return lC;   // revrite with char_subtract
}

int main()
{
    char a[N], b[N], c[N];
    scanf("%s %s", &a, &b);

    int lc = recursive_mul(a, b, c, 4, 4);
    for (int i = 0; i < lc; i++)
        cout << c[i];
    cout << endl;
    return 0;
}