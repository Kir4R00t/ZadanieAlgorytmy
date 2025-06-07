# Zadanie na algorytmy
Implementacje stosów i kolejek bez użycia STL w języku C++

## Kompilacja
Do kompilacji programu skorzystałem z kompilatora g++ <br>
Ver: ```g++.exe (Rev4, Built by MSYS2 project) 15.1.0```
<br>

```bash
g++ -o zadanie zadanie.cpp
./zadanie
```

## Jak korzystać z funkcjonalności
W pliku `zadanie.cpp` znajdują się cztery osobne klasy odpowiadające za:

1. **Listowy stos (`ListStack`)** – można dodać elementy, wypisać je oraz odwrócić stos.
2. **Tablicowy stos (`ArrayStack`)** – umożliwia scalanie dwóch rosnących stosów.
3. **Tablicowa kolejka (`FloatQueue`)** – implementacja FIFO dla liczb rzeczywistych.
4. **Listowa kolejka napisów (`StringQueue`)** – można dodać napisy oraz przeszukiwać kolejkę.