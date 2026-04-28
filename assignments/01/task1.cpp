// Aufgabe 01: Verwenden Sie einen Stack vom Typ stack<char> zur Auswertung 
// vollständig geklammerter arithmetischer Ausdrücke mit Werten aus {0, . . . , 9}.
#include <iostream>
#include <LEDA/core/string.h>
#include <LEDA/core/stack.h>

using leda::string;
using leda::stack;

int read_int_from_stack(stack<char>& st) {
    int value = 0;
    int multiplier = 1;

    while (!st.empty() && st.top() >= '0' && st.top() <= '9') {
        value += (st.top() - '0') * multiplier;
        multiplier *= 10;
        st.pop();
    }

    return value;
}

void write_int_to_stack(stack<char>& st, int value) {
    if (value == 0) {
        st.push('0');
        return;
    }

    stack<char> tempStack;
    while (value > 0) {
        tempStack.push((value % 10) + '0');
        value /= 10;
    }

    while (!tempStack.empty()) {
        st.push(tempStack.top());
        tempStack.pop();
    }
}

int main() {
    string s;
    int stringLength;
    stack<char> st;

    int operand1, operand2, result;
    char op;

    // Einlesen eines arithmetischen Ausdrucks
    cout << "Arithmetischer Ausdruck: ";
    s.read_line();
    stringLength = s.length();

    // Über String iterieren und Ausdruck auswerten
    for (int i = 0; i < stringLength; i++) {
        char c = s[i];

        // Default-Fall: Zeichen einfach auf den Stack legen
        if (c == '(' || (c >= '0' && c <= '9') || c == '+' || c == '-' || c == '*' || c == '/') {
            st.push(c);
        
        // Sonderfall: Schließende Klammer gefunden, dann Operation ausführen
        } else if (c == ')') {
            if (st.empty()) {
                cout << "Ungültiger Ausdruck: Zu viele schließende Klammern." << endl;
                return 1;
            }

            // Operanden und Operator vom Stack lesen
            operand2 = read_int_from_stack(st);
            op = st.pop();
            operand1 = read_int_from_stack(st);
            st.pop();

            // Operation ausführen
            switch (op) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0) {
                        cout << "Ungültiger Ausdruck: Division durch Null." << endl;
                        return 1;
                    }
                    result = operand1 / operand2;
                    break;
                default:
                    cout << "Ungültiger Ausdruck: Unbekannter Operator '" << op << "'." << endl;
                    return 1;
            }

            // Ergebnis zurück auf den Stack legen
            write_int_to_stack(st, result);
        } 
        else {
            cout << "Ungültiger Ausdruck: Unbekanntes Zeichen '" << c << "'." << endl;
            return 1;
        }
            
    }
        


    result = read_int_from_stack(st);
    if (!st.empty()) {
        cout << "Auswertung fehlgeschlagen." << endl;
    } else {
        cout << "Ergebnis: " << result << endl;
    }

    return 0;
}