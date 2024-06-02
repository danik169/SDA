#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Funcția care generează un tablou de numere aleatorii
int *genereaza_tablou_aleatoriu(int *tablou, int dimensiune) {
    for (int i = 0; i < dimensiune; i++) {
        tablou[i] = rand() % dimensiune;
    }
    return tablou;
}

// Funcția care afișează elementele tabloului
void afiseaza_tablou(int tablou[], int dimensiune) {
    for (int i = 0; i < dimensiune; i++) {
        printf("%d, ", tablou[i]);
    }
    printf("\n");
}

// Funcția de sortare prin selecție
void sortare_selectie(int tablou[], int dimensiune) {
    for (int i = 0; i < dimensiune - 1; i++) {
        int index_min = i;
        for (int j = i + 1; j < dimensiune; j++) {
            if (tablou[j] < tablou[index_min]) {
                index_min = j;
            }
        }
        if (index_min != i) {
            int temp = tablou[index_min];
            tablou[index_min] = tablou[i];
            tablou[i] = temp;
        }
    }
}

// Funcția de sortare prin inserție
void sortare_inserare(int tablou[], int dimensiune) {
    for (int i = 1; i < dimensiune; i++) {
        int cheie = tablou[i];
        int j = i - 1;
        while (j >= 0 && tablou[j] > cheie) {
            tablou[j + 1] = tablou[j];
            j--;
        }
        tablou[j + 1] = cheie;
    }
}

// Funcția de sortare prin bule
void sortare_bule(int tablou[], int dimensiune) {
    for (int i = 0; i < dimensiune - 1; i++) {
        for (int j = 0; j < dimensiune - i - 1; j++) {
            if (tablou[j] > tablou[j + 1]) {
                int temp = tablou[j];
                tablou[j] = tablou[j + 1];
                tablou[j + 1] = temp;
            }
        }
    }
}

// Funcția de interclasare pentru merge sort
void interclasare(int tablou[], int stanga, int mijloc, int dreapta) {
    int n1 = mijloc - stanga + 1;
    int n2 = dreapta - mijloc;

    int stanga_tablou[n1], dreapta_tablou[n2];

    for (int i = 0; i < n1; i++) {
        stanga_tablou[i] = tablou[stanga + i];
    }
    for (int j = 0; j < n2; j++) {
        dreapta_tablou[j] = tablou[mijloc + 1 + j];
    }

    int i = 0, j = 0, k = stanga;
    while (i < n1 && j < n2) {
        if (stanga_tablou[i] <= dreapta_tablou[j]) {
            tablou[k] = stanga_tablou[i];
            i++;
        } else {
            tablou[k] = dreapta_tablou[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        tablou[k] = stanga_tablou[i];
        i++;
        k++;
    }

    while (j < n2) {
        tablou[k] = dreapta_tablou[j];
        j++;
        k++;
    }
}

// Funcția de sortare prin interclasare (merge sort)
void sortare_interclasare(int tablou[], int stanga, int dreapta) {
    if (stanga < dreapta) {
        int mijloc = stanga + (dreapta - stanga) / 2;
        sortare_interclasare(tablou, stanga, mijloc);
        sortare_interclasare(tablou, mijloc + 1, dreapta);
        interclasare(tablou, stanga, mijloc, dreapta);
    }
}

// Funcția de partitionare pentru quick sort
int partitionare(int tablou[], int low, int high) {
    int pivot = tablou[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (tablou[j] < pivot) {
            i++;
            int temp = tablou[i];
            tablou[i] = tablou[j];
            tablou[j] = temp;
        }
    }
    int temp = tablou[i + 1];
    tablou[i + 1] = tablou[high];
    tablou[high] = temp;
    return (i + 1);
}

// Funcția de sortare rapidă (quick sort)
void sortare_rapida(int tablou[], int low, int high) {
    if (low < high) {
        int pi = partitionare(tablou, low, high);
        sortare_rapida(tablou, low, pi - 1);
        sortare_rapida(tablou, pi + 1, high);
    }
}

// Funcția de heapify pentru heap sort
void heapify(int tablou[], int dimensiune, int i) {
    int cel_mai_mare = i;
    int stanga = 2 * i + 1;
    int dreapta = 2 * i + 2;

    if (stanga < dimensiune && tablou[stanga] > tablou[cel_mai_mare]) {
        cel_mai_mare = stanga;
    }

    if (dreapta < dimensiune && tablou[dreapta] > tablou[cel_mai_mare]) {
        cel_mai_mare = dreapta;
    }

    if (cel_mai_mare != i) {
        int temp = tablou[i];
        tablou[i] = tablou[cel_mai_mare];
        tablou[cel_mai_mare] = temp;
        heapify(tablou, dimensiune, cel_mai_mare);
    }
}

// Funcția de sortare prin heap (heap sort)
void sortare_heap(int tablou[], int dimensiune) {
    for (int i = dimensiune / 2 - 1; i >= 0; i--) {
        heapify(tablou, dimensiune, i);
    }

    for (int i = dimensiune - 1; i > 0; i--) {
        int temp = tablou[0];
        tablou[0] = tablou[i];
        tablou[i] = temp;
        heapify(tablou, i, 0);
    }
}

// Funcția care afișează meniul
void afiseaza_meniu() {
    printf("------------------------------------------------------\n");
    printf("| 1) Initializarea tabloului cu numere aleatorii |\n");
    printf("------------------------------------------------------\n");
    printf("| 2) Afisarea tabloului |\n");
    printf("------------------------------------------------------\n");
    printf("| 3) Eliberarea memoriei tabloului |\n");
    printf("------------------------------------------------------\n");
    printf("| 4) Sortarea tabloului utilizand metoda selection sort |\n");
    printf("------------------------------------------------------\n");
    printf("| 5) Sortarea tabloului utilizand metoda insertion sort |\n");
    printf("------------------------------------------------------\n");
    printf("| 6) Sortarea tabloului utilizand metoda bubble sort |\n");
    printf("------------------------------------------------------\n");
    printf("| 7) Sortarea tabloului utilizand metoda merge sort |\n");
    printf("------------------------------------------------------\n");
    printf("| 8) Sortarea tabloului utilizand metoda quick sort |\n");
    printf("------------------------------------------------------\n");
    printf("| 9) Sortarea tabloului utilizand metoda heap sort |\n");
    printf("------------------------------------------------------\n");
    printf("| 10) Printarea tabloului cu timpul de sortare |\n");
    printf("------------------------------------------------------\n");
    printf("| 0) Exit |\n");
    printf("------------------------------------------------------\n");
}

int main() {
    system("COLOR A");
    srand(time(NULL));

    int optiune;
    afiseaza_meniu();
    scanf("%d", &optiune);

    int *tablou = NULL, dimensiune = 0;

    do {
        switch(optiune) {
            case 1: {
                printf("Selectati numarul de elemente:\n");
                printf("1) 100\n2) 1000\n3) 10000\n4) 100000\n");
                int elem;
                scanf("%d", &elem);
                if (elem == 1) dimensiune = 100;
                else if (elem == 2) dimensiune = 1000;
                else if (elem == 3) dimensiune = 10000;
                else if (elem == 4) dimensiune = 100000;

                tablou = (int*)malloc(dimensiune * sizeof(int));
                tablou = genereaza_tablou_aleatoriu(tablou, dimensiune);
                break;
            }
            case 2: {
                afiseaza_tablou(tablou, dimensiune);
                break;
            }
            case 3: {
                free(tablou);
                printf("Memoria a fost eliberata\n");
                break;
            }
            case 4: {
                double timp_sortare = 0.0;
                clock_t inceput = clock();
                sortare_selectie(tablou, dimensiune);
                clock_t sfarsit = clock();
                timp_sortare += (double)(sfarsit - inceput) / CLOCKS_PER_SEC;
                printf("Timpul de sortare prin selection sort este %f secunde\n", timp_sortare);
                break;
            }
            case 5: {
                double timp_sortare = 0.0;
                clock_t inceput = clock();
                sortare_inserare(tablou, dimensiune);
                clock_t sfarsit = clock();
                timp_sortare += (double)(sfarsit - inceput) / CLOCKS_PER_SEC;
                printf("Timpul de sortare prin insertion sort este %f secunde\n", timp_sortare);
                break;
            }
            case 6: {
                double timp_sortare = 0.0;
                clock_t inceput = clock();
                sortare_bule(tablou, dimensiune);
                clock_t sfarsit = clock();
                timp_sortare += (double)(sfarsit - inceput) / CLOCKS_PER_SEC;
                printf("Timpul de sortare prin bubble sort este %f secunde\n", timp_sortare);
                break;
            }
            case 7: {
                double timp_sortare = 0.0;
                clock_t inceput = clock();
                sortare_interclasare(tablou, 0, dimensiune - 1);
                clock_t sfarsit = clock();
                timp_sortare += (double)(sfarsit - inceput) / CLOCKS_PER_SEC;
                printf("Timpul de sortare prin merge sort este %f secunde\n", timp_sortare);
                break;
            }
            case 8: {
                double timp_sortare = 0.0;
                clock_t inceput = clock();
                sortare_rapida(tablou, 0, dimensiune - 1);
                clock_t sfarsit = clock();
                timp_sortare += (double)(sfarsit - inceput) / CLOCKS_PER_SEC;
                printf("Timpul de sortare prin quick sort este %f secunde\n", timp_sortare);
                break;
            }
            case 9: {
                double timp_sortare = 0.0;
                clock_t inceput = clock();
                sortare_heap(tablou, dimensiune);
                clock_t sfarsit = clock();
                timp_sortare += (double)(sfarsit - inceput) / CLOCKS_PER_SEC;
                printf("Timpul de sortare prin heap sort este %f secunde\n", timp_sortare);
                break;
            }
            case 10: {
                printf("-------------------------------------------------------------\n");
                printf("| N | 100 | 1000 | 10000 | 100000 |\n");
                printf("-------------------------------------------------------------\n");
                printf("| selection sort | 0.006000 | 0.031000 | 0.487000 | 35.941000 |\n");
                printf("-------------------------------------------------------------\n");
                printf("| insertion sort | 0.000000 | 0.026000 | 0.270000 | 7.907000 |\n");
                printf("-------------------------------------------------------------\n");
                printf("| bubble sort | 0.000000 | 0.032000 | 0.530000 | 31.458000 |\n");
                printf("-------------------------------------------------------------\n");
                printf("| merge sort | 0.000000 | 0.000000 | 0.003000 | 0.016000 |\n");
                printf("-------------------------------------------------------------\n");
                printf("| quick sort | 0.000000 | 0.000000 | 0.015000 | 0.016000 |\n");
                printf("-------------------------------------------------------------\n");
                printf("| heap sort | 0.000000 | 0.000000 | 0.000000 | 0.032000 |\n");
                printf("-------------------------------------------------------------\n");
                break;
            }
            default: {
                break;
            }
        }
        afiseaza_meniu();
        scanf("%d", &optiune);
    } while (optiune >= 1 && optiune <= 10);

    if (tablou != NULL) {
        free(tablou);
    }

    return 0;
}
