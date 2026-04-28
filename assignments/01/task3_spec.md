# Aufgabe 3: Spezifikation für `int_queue`

- Name: `int_queue`
- Objekte: Integer

## Operationen
- `create`: Erzeugt leere Schlange
- `enqueue`: int_queue $\times$ Integer $\to$ int_queue</br>
Semantik: Füge element hinten an die Schlange an
- `dequeue`: int_queue $\to$ int_queue $\times$ Integer</br>
Semantik: Entferne vorderstes Element und gib es zurück
- `get_size`: int_queue $\to$ Integer</br>
Semantik: Gib die Größe der Schlange, also die Anzahl der enthaltenen Elemente, zurück
- `is_empty`: int_queue $\to$ Boolean</br>
Semantik: True, falls size == 0, False sonst
