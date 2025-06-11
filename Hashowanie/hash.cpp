// Zadanie 1: Hashowanie łańcuchowe
#include <iostream>
#include <list>
#include <vector>
using namespace std;

class HashTableChaining {
    int size;
    vector<list<int>> table;

public:
    HashTableChaining(int m) : size(m), table(m) {}

    int hash(int x) {
        return x % size;
    }

    void insert(int x) {
        int h = hash(x);
        table[h].push_back(x);
    }

    void print() {
        for (int i = 0; i < size; ++i) {
            cout << i << ": ";
            for (int x : table[i])
                cout << x << " ";
            cout << endl;
        }
    }
};

// Zadanie 2: Hashowanie rozproszone (adresowanie uniwersalne)
class HashTableUniversal {
    int size, a, b;
    vector<int> table;

public:
    HashTableUniversal(int m, int a_, int b_) : size(m), a(a_), b(b_), table(m, -1) {}

    int hash(int x) {
        return (a * x + b) % size;
    }

    void insert(int x) {
        int h = hash(x);
        if (table[h] == -1)
            table[h] = x;
        else
            cout << "Collision at " << h << " for " << x << endl;
    }

    void print() {
        for (int i = 0; i < size; ++i)
            cout << i << ": " << table[i] << endl;
    }
};

// Zadanie 3: Hashowanie otwarte (adresowanie otwarte)
#include <cmath>

class HashTableOpenAddressing {
    int size;
    vector<int> table;
    const double alpha = (sqrt(5.0) - 1) / 2;

public:
    HashTableOpenAddressing(int m) : size(m), table(m, -1) {}

    int hash(int x, int i) {
        double frac = alpha * x - floor(alpha * x);
        int h1 = int(size * frac);
        return (h1 + i) % size;
    }

    void insert(int x) {
        for (int i = 0; i < size; ++i) {
            int h = hash(x, i);
            if (table[h] == -1) {
                table[h] = x;
                return;
            }
        }
        cout << "Table full for " << x << endl;
    }

    void print() {
        for (int i = 0; i < size; ++i)
            cout << i << ": " << table[i] << endl;
    }
};

// Przykładowe użycie
int main() {
    HashTableChaining h1(10);
    for (int x : {10, 22, 31, 4, 15, 28, 17, 88, 59}) h1.insert(x);
    cout << "Chaining:\n"; h1.print();

    HashTableUniversal h2(13, 5, 7);
    for (int x : {10, 25, 7}) h2.insert(x);
    cout << "\nUniversal Hashing:\n"; h2.print();

    HashTableOpenAddressing h3(11);
    for (int x : {10, 22, 31, 4, 15, 28, 17, 88, 59}) h3.insert(x);
    cout << "\nOpen Addressing:\n"; h3.print();

    return 0;
}
