
// Aufgabe 2: Geben Sie eine Implementierung für den Datentyp int stack aus der Vorlesung an,
// bei der die maximale Größe des Stacks im Konstruktur angegeben wird.

#include <stdexcept>
#include <iostream>

class int_stack {
    private:
        int* data;      // Array zur Speicherung der Stack-Elemente
        int top;        // Index des obersten Elements
        int capacity;   // Maximale Kapazität des Stacks 

    public:
        int_stack(int max_capacity) {
            data = new int[max_capacity];
            top = -1; // Stack ist anfangs leer
            capacity = max_capacity;
        };
        ~int_stack() {
            delete[] data;
        };
        void push(int value) {
            if (top < capacity - 1) {
                data[++top] = value;
            } else {
                throw std::overflow_error("Stack overflow: Maximale Kapazität erreicht.");
            }
        };
        int pop() {
            if (top >= 0) {
                return data[top--];
            } else {
                throw std::underflow_error("Stack underflow: Stack ist leer.");
            }
        };
        bool is_empty() const {
            return top == -1;
        };
        bool is_full() const {
            return top == capacity - 1;
        };
};

int main() {
    // Lese maximale Kapazität des Stacks ein
    int max_capacity;
    std::cout << "Maximale Kapazität des Stacks: ";
    std::cin >> max_capacity;
    int_stack stack(max_capacity);

    // Lese Werte ein und füge sie zum Stack hinzu, bis der Benutzer -1 eingibt oder der Stack voll ist
    int value;
    std::cout << "Geben Sie Werte ein (beenden mit -1): ";
    while (!stack.is_full() && std::cin >> value && value != -1) {
        try {
            stack.push(value);
        } catch (const std::overflow_error& e) {
            std::cerr << e.what() << std::endl;
            break; 
        }
    }

    // Pop alle Werte vom Stack und gebe sie aus
    std::cout << "Werte im Stack (LIFO-Reihenfolge): ";
    while (!stack.is_empty()) {
        try {
            std::cout << stack.pop() << " ";
        } catch (const std::underflow_error& e) {
            std::cerr << e.what() << std::endl;
            break; 
        }
    }

    std::cout << std::endl;
}