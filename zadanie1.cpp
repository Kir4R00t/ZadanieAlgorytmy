#include <iostream>
using namespace std;

// Zadanie 1: Stos (listowy) - odwracanie stosu
struct Node {
    int data;
    Node* next;
};

class ListStack {
    Node* topNode;
public:
    ListStack() : topNode(nullptr) {}

    void push(int val) {
        Node* newNode = new Node{val, topNode};
        topNode = newNode;
    }

    void pop() {
        if (topNode) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    int top() const {
        return topNode ? topNode->data : -1;
    }

    bool empty() const {
        return topNode == nullptr;
    }

    void reverse() {
        Node* prev = nullptr;
        Node* curr = topNode;
        while (curr) {
            Node* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        topNode = prev;
    }

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
class ArrayStack {
    int data[100];
    int size;
public:
    ArrayStack() : size(0) {}

    void push(int val) {
        if (size < 100) data[size++] = val;
    }

    void pop() {
        if (size > 0) --size;
    }

    int top() const {
        return size > 0 ? data[size - 1] : -1;
    }

    bool empty() const {
        return size == 0;
    }

    int getSize() const { return size; }

    int get(int i) const { return data[i]; }

    void clear() { size = 0; }

    void print() const {
        for (int i = size - 1; i >= 0; --i)
            cout << data[i] << " ";
        cout << endl;
    }
};

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

ArrayStack mergeStacks(ArrayStack& a, ArrayStack& b) {
    int merged[200];
    int n = 0;

    while (!a.empty()) { merged[n++] = a.top(); a.pop(); }
    while (!b.empty()) { merged[n++] = b.top(); b.pop(); }

    sortArray(merged, n);

    ArrayStack c;
    for (int i = 0; i < n; ++i) {
        c.push(merged[i]);
    }
    return c;
}

// Zadanie 3: Kolejka (tablicowa) liczb rzeczywistych
class FloatQueue {
    float data[100];
    int frontIndex, rearIndex;
public:
    FloatQueue() : frontIndex(0), rearIndex(0) {}

    void enqueue(float val) {
        if (rearIndex < 100) data[rearIndex++] = val;
    }

    void dequeue() {
        if (frontIndex < rearIndex) ++frontIndex;
    }

    float front() const {
        return frontIndex < rearIndex ? data[frontIndex] : -1;
    }

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
struct StringNode {
    char str[100];
    StringNode* next;
};

class StringQueue {
    StringNode* frontNode;
    StringNode* rearNode;
public:
    StringQueue() : frontNode(nullptr), rearNode(nullptr) {}

    void enqueue(const char* s) {
        StringNode* newNode = new StringNode;
        int i = 0;
        for (; s[i] != '\0'; ++i) newNode->str[i] = s[i];
        newNode->str[i] = '\0';
        newNode->next = nullptr;

        if (!rearNode) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
    }

    void dequeue() {
        if (frontNode) {
            StringNode* temp = frontNode;
            frontNode = frontNode->next;
            if (!frontNode) rearNode = nullptr;
            delete temp;
        }
    }

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

    return 0;
}
