// Aufgabe 3: Schreiben Sie eine Spezifikation für den Datentyp int queue (Schlange von ganzen
// Zahlen) an und schreiben Sie eine enstprechende Klasse in C++ oder JAVA.

// Spezifikation: Siehe task3_spec.md

// Implementierung mithilfe von linked list:

#include <stdexcept>
#include <iostream>

class element {
    public:
        int value;
        element* next;

        element(int val) : value(val), next(nullptr) {}
};

class int_queue {
    private:
        element* front; // Zeiger auf das vorderste Element
        element* rear;  // Zeiger auf das hinterste Element
        int size;       // Anzahl der Elemente in der Queue

    public:
        int_queue() : front(nullptr), rear(nullptr), size(0) {}

        ~int_queue() {
            while (front != nullptr) {
                element* temp = front;
                front = front->next;
                delete temp;
            }
        }

        void enqueue(int value) {
            element* newElement = new element(value);
            if (rear == nullptr) { // Queue ist leer
                front = rear = newElement;
            } else {
                rear->next = newElement;
                rear = newElement;
            }
            size++;
        }

        int dequeue() {
            if (front == nullptr) { // Queue ist leer
                throw std::underflow_error("Queue underflow: Queue ist leer.");
            }
            int value = front->value;
            element* temp = front;
            front = front->next;
            if (front == nullptr) {
                rear = nullptr;
            }
            delete temp;
            size--;
            return value;
        }

        bool is_empty() const {
            return size == 0;
        }

        int get_size() const {
            return size;
        }
};

int main() {
    // Lese Werte ein und füge sie zur Queue hinzu, bis der Benutzer -1 eingibt
    int_queue queue;
    int value;
    std::cout << "Geben Sie Werte ein (beenden mit -1): ";
    while (std::cin >> value && value != -1) {
        queue.enqueue(value);
    }

    // Dequeue und Ausgabe der Werte, bis die Queue leer ist
    std::cout << "Dequeue Werte: ";
    while (!queue.is_empty()) {
        try {
            std::cout << queue.dequeue() << " ";
        } catch (const std::underflow_error& e) {
            std::cerr << e.what() << std::endl;
            break;
        }
    }
    std::cout << std::endl;
    return 0;
}