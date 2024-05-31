#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct flower {
    char* name;
    int price;
};

void menu() {
    printf("MENIU PRINCIPAL\n");
    printf("1.Afisarea listei curente\n");
    printf("2.Sortarea elementelor dupa un camp al structurii\n");
    printf("3.Inserarea unui element la o pozitie X in cadrul tabloului\n");
    printf("4.Stergerea elementului de pe o pozitie X\n");
    printf("5.Exit\n");
    printf("Alege o varianta conform meniului\n");
}

// functia va afisa lista curenta
void sarcina_1(struct flower* flowers) {
    for (int i = 0; i < 4; i++) {
        printf("Floarea %d:\n", i + 1);
        printf("Numele: %s\n", flowers[i].name);
        printf("pret: %d\n", flowers[i].price);
        printf("-------------\n");
    }
}

// sortarea dupa nume
int compare_by_name(const void* a, const void* b) {
    const struct flower* flower_a = (const struct flower*)a;
    const struct flower* flower_b = (const struct flower*)b;

    return strcmp(flower_a->name, flower_b->name);
}

void sarcina_2(struct flower* flowers) {
    printf("Sortarea dupa nume:\n");
    qsort(flowers, 4, sizeof(struct flower), compare_by_name);
    sarcina_1(flowers);
}

// Inserarea unui element
void sarcina_3(struct flower* flowers) {
    int poz;
    printf("Introdu pe ce pozitie sa fie noua floare(intre 1-4): ");
    scanf("%d", &poz);

    if (poz < 1 || poz > 4) {
        printf("Pozitie invalida.");
    }

    struct flower new_fl;
    new_fl.name = (char*)malloc(50 * sizeof(char));
    printf("Introdu numele: ");
    scanf("%s", new_fl.name);

    printf("Introdu pretul:");
    scanf("%d", &new_fl.price);

    for (int i = 2; i >= poz - 1; i--) {
        flowers[i + 1] = flowers[i];
    }
    flowers[poz - 1] = new_fl;

    printf("Lista noua: \n");
    printf("-------------\n");
    for (int i = 0; i < 4; i++) {
        printf("Floarea %d: \n", i + 1);
        printf("Numele: %s\n", flowers[i].name);
        printf("Pretul: %d\n", flowers[i].price);
        printf("-------------\n");
    }
}

// Stergerea unui element
void sarcina_4(struct flower* flowers) {
    int poz2;
    printf("\nIntrodu pozitia din lista care se va sterge(intre 1-4): ");
    scanf("%d", &poz2);

    if (poz2 < 1 || poz2 > 4) {
        printf("Pozitie invalida\n");
    }

    for (int i = poz2 - 1; i < 3; i++) {
        flowers[i] = flowers[i + 1];
    }

    printf("\nLista noua:\n");
    printf("-------------\n");
    for (int i = 0; i < 3; i++) {
        printf("Floarea %d: \n", i + 1);
        printf("Numele: %s\n", flowers[i].name);
        printf("Pretul: %d\n", flowers[i].price);
        printf("-------------\n");
    }
}

int main() {
    int poz, poz2, i;
    int op = 0;
    struct flower* flowers = (struct flower*)malloc(4 * sizeof(struct flower));

    // Alocarea memoriei 
    for (int i = 0; i < 4; i++) {
        flowers[i].name = (char*)malloc(50 * sizeof(char));
    }

    strcpy(flowers[0].name, "Trandafir");
    flowers[0].price = 50;

    strcpy(flowers[1].name, "Crin");
    flowers[1].price = 35;

    strcpy(flowers[2].name, "Lalea");
    flowers[2].price = 25;

    while (op != 5) {
        menu();
        scanf("%d", &op);

        switch (op) {
        case 1:
            sarcina_1(flowers);
            break;

        case 2:
            sarcina_2(flowers);
            break;

        case 3:
            sarcina_3(flowers);
            break;

        case 4:
            sarcina_4(flowers);
            break;

        case 5:
            printf("Exiting program...\n");
            break;

        default:
            printf("Invalid choice, please try again.\n");
            break;
        }
    }

    // Eliberarea memoriei
    for (int i = 0; i < 4; i++) {
        free(flowers[i].name);
    }
    free(flowers);

    return 0;
}
