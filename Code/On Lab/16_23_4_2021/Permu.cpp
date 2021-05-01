#ifndef SORTINGAPPLICATION_H
#define SORTINGAPPLICATION_H
#include <iostream>
#include <string>
using namespace std;
bool isPermutation(string a, string b);

void bubbleSortString(string& a) {
    for (int i = 0; i < (int)a.length() - 1; i++) {               //neu xet tu vi tri dau sang ben phai, thi cau chi muon no lap lai a.length() - 1 lan
        for (int j = 0; j < (int)a.length() - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                char temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

/* Your helping functions go here */
bool isPermutation(string a, string b) {
    //TODO
    if (a.length() != b.length()) return false;
    bubbleSortString(a);
    bubbleSortString(b);
    for (int i = 0; i < (int)a.length(); i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

int main() {
    string a = "abba";
    string b = "baba";
    cout << isPermutation(a, b);
    return 0;
}
#endif /* SORTINGAPPLICATION_H */