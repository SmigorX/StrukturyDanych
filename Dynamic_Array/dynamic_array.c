#include "dynamic_array.h"

/* Inicjalizuje dynamiczną tablicę ustawiając pojemność na 1 i przechowując rozmiar elementu */
void initArray(DynamicArray *arr, size_t elementSize) {
    arr->A = malloc(elementSize); // początkowo miejsce na 1 element
    if (arr->A == NULL) {
        fprintf(stderr, "Błąd alokacji pamięci!\n");
        exit(EXIT_FAILURE);
    }
    arr->currSize = 0;
    arr->capacity = 1;
    arr->elementSize = elementSize;
}

/* Powiększa tablicę, jeżeli jest pełna */
void reSizeArray(DynamicArray *arr) {
    if (arr->currSize == arr->capacity) {
        int newCapacity = arr->capacity * 2;
        void *temp = malloc(newCapacity * arr->elementSize);
        if (temp == NULL) {
            fprintf(stderr, "Błąd alokacji pamięci przy rozszerzaniu tablicy!\n");
            exit(EXIT_FAILURE);
        }
        /* Przenosimy istniejące elementy do nowo zaalokowanego obszaru */
        memcpy(temp, arr->A, arr->currSize * arr->elementSize);
        free(arr->A);
        arr->A = temp;
        arr->capacity = newCapacity;
    }
}

/* Zmniejsza tablicę, gdy liczba elementów spada do 1/4 pojemności */
void shrinkArray(DynamicArray *arr) {
    if (arr->currSize <= arr->capacity / 4 && arr->capacity > 1) {
        int newCapacity = arr->capacity / 2;
        void *temp = malloc(newCapacity * arr->elementSize);
        if (temp == NULL) {
            fprintf(stderr, "Błąd alokacji pamięci przy zmniejszaniu tablicy!\n");
            exit(EXIT_FAILURE);
        }
        memcpy(temp, arr->A, arr->currSize * arr->elementSize);
        free(arr->A);
        arr->A = temp;
        arr->capacity = newCapacity;
    }
}

/* Wstawia element na końcu tablicy */
void insertAtEnd(DynamicArray *arr, void *x) {
    if (arr->currSize == arr->capacity) {
        reSizeArray(arr);
    }
    /* Kopiujemy zawartość x do odpowiedniego miejsca w tablicy */
    memcpy((char*)arr->A + arr->currSize * arr->elementSize, x, arr->elementSize);
    arr->currSize++;
}

/* Wstawia element pod wskazanym indeksem (w środek) */
void insertAtMiddle(DynamicArray *arr, int index, void *x) {
    if (index < 0 || index > arr->currSize) {
        fprintf(stderr, "Błędny indeks!\n");
        return;
    }
    if (arr->currSize == arr->capacity) {
        reSizeArray(arr);
    }
    /* Przesuwamy elementy w prawo, by zrobić miejsce */
    memmove((char*)arr->A + (index + 1) * arr->elementSize,
            (char*)arr->A + index * arr->elementSize,
            (arr->currSize - index) * arr->elementSize);
    memcpy((char*)arr->A + index * arr->elementSize, x, arr->elementSize);
    arr->currSize++;
}

/* Usuwa ostatni element tablicy */
void deleteAtEnd(DynamicArray *arr) {
    if (arr->currSize == 0) {
        printf("Dynamic array is empty!\n");
        return;
    }
    arr->currSize--;
    /* Opcjonalnie: wyzerowanie obszaru usuwanego elementu (np. memset) */
    if (arr->currSize <= arr->capacity / 4) {
        shrinkArray(arr);
    }
}

/* Usuwa element znajdujący się pod indeksem */
void deleteAtMiddle(DynamicArray *arr, int index) {
    if (arr->currSize == 0) {
        printf("Dynamic array is empty!\n");
        return;
    }
    if (index < 0 || index >= arr->currSize) {
        fprintf(stderr, "Błędny indeks!\n");
        return;
    }
    /* Przesuwamy elementy w lewo, by nadpisać usuwany element */
    memmove((char*)arr->A + index * arr->elementSize,
            (char*)arr->A + (index + 1) * arr->elementSize,
            (arr->currSize - index - 1) * arr->elementSize);
    arr->currSize--;
    if (arr->currSize <= arr->capacity / 4) {
        shrinkArray(arr);
    }
}
