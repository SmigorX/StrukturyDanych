#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Struktura dynamicznej tablicy, działającej dla dowolnego typu danych */
typedef struct DynamicArray {
    void *A;            // Wskaźnik do blokowego obszaru pamięci
    int currSize;       // Aktualna liczba elementów
    int capacity;       // Aktualna pojemność (ilość zaalokowanych elementów)
    size_t elementSize; // Rozmiar pojedynczego elementu w bajtach
} DynamicArray;

/* Inicjalizacja dynamicznej tablicy dla danych o rozmiarze elementSize */
void initArray(DynamicArray *arr, size_t elementSize);

/* Zwiększenie tablicy – jeśli tablica jest pełna, podwajamy jej rozmiar */
void reSizeArray(DynamicArray *arr);

/* Zmniejszenie tablicy – jeżeli wykorzystanie spadnie do 1/4, zmniejszamy
 * pojemność o połowę */
void shrinkArray(DynamicArray *arr);

/* Wstawienie nowego elementu na końcu tablicy */
void insertAtEnd(DynamicArray *arr, void *x);

/* Wstawienie elementu w środek tablicy pod danym indeksem */
void insertAtMiddle(DynamicArray *arr, int index, void *x);

/* Usunięcie ostatniego elementu tablicy */
int deleteAtEnd(DynamicArray *arr);

/* Usunięcie elementu znajdującego się pod wskazanym indeksem */
int deleteAtMiddle(DynamicArray *arr, int index);

#endif
