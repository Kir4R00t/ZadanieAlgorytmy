#include <iostream>
using namespace std;

// Zadanie 1: Stos (listowy) - odwracanie stosu
// LIFO - Last In First Out
struct Node {
    int data;
    Node* next;
};

class ListStack {
    Node* topNode; // pointer na górę stosu

public:
    ListStack() : topNode(nullptr) {} // inicjacja pustego stosu

    // 'wepchnięcie' elementu na stos -> stworzenie nowego node'a
    //   wskazującego na aktualny topNode,
    //   nowy węzeł idzie na góre
    void push(int val) {
        Node* newNode = new Node{val, topNode}; 
        topNode = newNode;
    }

    // usnięcie top Node -> następny node stosu staje się topNode
    void pop() {
        if (topNode) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    // zwraca wartość topNode'a, lub zwraca 0 jeśli stos jest pusty
    int top() const {
        return topNode ? topNode->data : -1;
    }

    // sprawdza czy stos jest pusty
    bool empty() const {
        return topNode == nullptr;
    }

    // aglorytm odwracania stosu (wizualizacja)
    void reverse() {
        Node* prev = nullptr; // do 'śledzenia' poprzedniego node'a w odwróconym stosie
        Node* curr = topNode; // aktualny top node na którym pracujemy
        while (curr) {
            Node* next = curr->next;
            curr->next = prev; // odwrócenie kierunku wskaźnika
            prev = curr;
            curr = next;
        }
        topNode = prev;
    }

    // wypisanie stosu
    void print() const {
        Node* curr = topNode;
        while (curr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }
};

// Zadanie 2: Stos (tablicowy) - scalanie dwóch stosów rosnących
// LIFO - Last In First Out
class ArrayStack {
    int data[100];
    int size;
public:
    ArrayStack() : size(0) {} // zainicjowanie pustego stosu

    void push(int val) {
        if (size < 100) data[size++] = val; // wstawienie elem o ile nie przekracza rozmiaru
    }

    void pop() {
        if (size > 0) --size;
    }

    // zwraca elem z góry stosu lub '-1' jeśli pusty
    int top() const {
        return size > 0 ? data[size - 1] : -1;
    }

    // sprawdzenie czy stos jest pusty
    bool empty() const {
        return size == 0;
    }

    // funkcje pomocnicze
    int getSize() const { return size; } // liczba elem
    int get(int i) const { return data[i]; } // zwróć 'i-ty' elem stosu
    void clear() { size = 0; } // zeruj stos

    void print() const {
        for (int i = size - 1; i >= 0; --i)
            cout << data[i] << " ";
        cout << endl;
    }
};

// funkcja sortująca stos - klasyczny Bubble sort
void sortArray(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Mergowanie stosów
ArrayStack mergeStacks(ArrayStack& a, ArrayStack& b) {
    int merged[200]; // pomocnicza tablica na 2 stosy
    int n = 0;       // licznik elem w merged

    // wrzucamy wsio do merged & sortujemy
    while (!a.empty()) { merged[n++] = a.top(); a.pop(); }
    while (!b.empty()) { merged[n++] = b.top(); b.pop(); }
    sortArray(merged, n);

    // tworzymy stos "c" i wrzucamy posortowane elem
    ArrayStack c;
    for (int i = 0; i < n; ++i) {
        c.push(merged[i]);
    }
    return c;
}

// Zadanie 3: Kolejka (tablicowa) liczb rzeczywistych
// FIFO - First In First Out
class FloatQueue {
    float data[100];
    int frontIndex, rearIndex;
public:
    FloatQueue() : frontIndex(0), rearIndex(0) {} // ustaw oba indexy na 0 - kolejka pusta

    // dodaj na koniec kolejki -> inkrementuj rearIndex, aby wskazywał następny wolny slot
    void enqueue(float val) {
        if (rearIndex < 100) data[rearIndex++] = val;
    }

    // usuń pierwszy element z kolejki (na frontIndex) -> przesuń frontIndex do przodu
    void dequeue() {
        if (frontIndex < rearIndex) ++frontIndex;
    }

    // sprawdź pierwszy element
    float front() const {
        return frontIndex < rearIndex ? data[frontIndex] : -1;
    }

    // sprawdź czy kolejka jest pusta
    bool empty() const {
        return frontIndex == rearIndex;
    }

    void print() const {
        for (int i = frontIndex; i < rearIndex; ++i)
            cout << data[i] << " ";
        cout << endl;
    }
};

// Zadanie 4: Kolejka napisów (listowa) + wyszukiwanie
// FIFO - First In First Out
struct StringNode {
    char str[100];
    StringNode* next;
};

class StringQueue {
    // pointer na początek i koniec kolejki
    StringNode* frontNode;
    StringNode* rearNode;
public:
    StringQueue() : frontNode(nullptr), rearNode(nullptr) {}

    // Stworzenie nowego węzła 'newNode'
    void enqueue(const char* s) {
        StringNode* newNode = new StringNode;
        int i = 0;
        for (; s[i] != '\0'; ++i) newNode->str[i] = s[i]; // kopiujemy znak po znaku ciąg 's' do newNode
        newNode->str[i] = '\0'; // dodanie znaku końca żeby utworzyć poprawny string
        newNode->next = nullptr; // ustaw ostatni elem jako nullptr

        // jeśli kolejka jest pusta (rearNode == nullptr), ustawiamy oba wskaźniki na newNode
        if (!rearNode) {
            frontNode = rearNode = newNode;
        } else { // w przeciwnym razie dodajemy elemnt na koniec & aktualizujemy rearNode
            rearNode->next = newNode;
            rearNode = newNode;
        }
    }

    // usuwamy pierwszy element z kolejki
    // przesuwamy frontNode na następny w kolejce -> next
    void dequeue() {
        if (frontNode) {
            StringNode* temp = frontNode;
            frontNode = frontNode->next;
            if (!frontNode) rearNode = nullptr;     // jesli po przesunięciu nie ma żadnych elem -> zeruj rearNode
            delete temp;                            // zwolnienie pamięci
        }
    }

    // funkcja sprawdzająca czy wyszukiwane hasło znajdude się w stringu
    
    // przechodzimy znak po znaku jak trafimy na 'match' ustawiamy flage na true, jeśli nie to na false
    // jak znajdziemy pełne dopasowanie to zwracamy True
    bool find(const char* target) const {
        for (StringNode* curr = frontNode; curr; curr = curr->next) {
            bool match = true;
            for (int i = 0; target[i] != '\0' || curr->str[i] != '\0'; ++i) {
                if (target[i] != curr->str[i]) {
                    match = false;
                    break;
                }
            }
            if (match) return true;
        }
        return false;
    }

    void print() const {
        for (StringNode* curr = frontNode; curr; curr = curr->next)
            cout << curr->str << " ";
        cout << endl;
    }
};

int main() {
    cout << "ZADANIE 1: " << endl;
    ListStack s;
    s.push(1);
    s.push(2);
    s.push(3);
    cout << "Stos przed odwroceniem: "; s.print();
    s.reverse();
    cout << "Stos po odwroceniu:     "; s.print();

    cout << "\nZADANIE 2: " << endl;
    ArrayStack a, b;
    a.push(10); a.push(3); a.push(5);
    b.push(2); b.push(4); b.push(6);
    ArrayStack c = mergeStacks(a, b);
    cout << "Scalony stos: "; c.print();

    cout << "\nZADANIE 3: " << endl;
    FloatQueue fq;
    fq.enqueue(1.1);
    fq.enqueue(2.2);
    fq.enqueue(3.3);
    cout << "Zawartosc kolejki: "; fq.print();
    fq.dequeue();
    cout << "Po usunieciu pierwszego: "; fq.print();

    cout << "\nZADANIE 4: Kolejka napisow (listowa)" << endl;
    StringQueue sq;
    sq.enqueue("hello");
    sq.enqueue("world");
    sq.enqueue("algorytm");
    cout << "Zawartosc kolejki: "; sq.print();
    cout << "Czy zawiera 'world'? " << (sq.find("world") ? "tak" : "nie") << endl;
    cout << "Czy zawiera 'test'?  " << (sq.find("test") ? "tak" : "nie") << endl;

    return 0;
}
