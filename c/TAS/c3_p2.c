// aranjamente de n luate cate p

#include <stdio.h>

#define MAX_SIZE 256

static int v[MAX_SIZE] = {0};
static int n = 0;
static int p = 0;

void Init(int k) { // k – vârful stivei
    v[k] = 0; // iniţializează/resetează, valoarea din vârful stivei
}

int Succesor(int k) {
    if (v[k] < n) { // se poate creşte valoarea din vârf
        v[k]++; // se incrementează valoarea din vârf
        return 1;  // funcţia a avut success
    }
    return 0; // nu se poate creşte valoarea din vârf
}

int Valid(int k) {
    for (int i = 1; i < k; ++i) // verifică dacă elementul din
        if (v[i] == v[k]) // vârf este diferit de 
            return 0; // elementele precedente din stivă
    return 1;
}

int Solution(int k) {
    return (k == p); 
}

void Print(int k) {
    static int m = 0;
    printf("%d : ", ++m);
    for (int i = 1; i <= k; ++i)
        printf("%d ", v[i]);
    printf("\n");
}

void Back(int n) {
    int k = 1, isS, isV;
    Init(k);
    while (k > 0){ // cât timp stiva nu e vidă
        isS = isV = 0;
        if (k <= n) { // nu are sens depăşirea nivelului n în stivă
            do { // repetă cât timp...
                isS = Succesor(k);
                if (isS) 
                    isV = Valid(k);
            } while (isS && !isV); // ...există succesor dar nu este valid
        }
        if (isS) { //este succesor si este valid
            if (Solution(k)) { // verifică candidatul la soluţie
                Print(k); // afişează soluţia
            } else { // dacă nu este soluţie
                k++; 
                Init(k); // creşte vârful stivei şi iniţializează
            }
        } else { // nu există succesor pt. valoarea curentă din stivă
            k--; // -> se coboară o poziţie în stivă
        }
    }
}

int main(void) {
    n = 10;
    p = 3;
    Back(n);
    return 0;
}