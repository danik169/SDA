#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Whiskey {
    char *denumire;
    int varsta;
    char *aroma;
    int pret;
    struct Whiskey *next;
} Whiskey;

// Input
Whiskey* citireWhiskey() {
    Whiskey *s = (Whiskey*)malloc(sizeof(Whiskey));
    s->denumire=malloc(sizeof(Whiskey)*20);
    s->aroma=malloc(sizeof(Whiskey)*20);

    printf("Introduceti denumirea de whiskey: ");
    scanf("%s", s->denumire);
    printf("Introduceti varsta bauturii: ");
    scanf("%d", &s->varsta);
    printf("Introduceti aroma: ");
    scanf("%s", s->aroma);
    printf("Introduceti pretul unei sticle: ");
    scanf("%d", &s->pret);
    s->next = NULL;
    return s;
}

void afisareLista(Whiskey *head) {
    Whiskey *current = head; 
    int st=1;
    printf("\nLista de whiskey:\n");
    while (current != NULL) {
    printf("Whiskey nr.%d\n",st);
        printf("Denumire: %s\n Varsta: %d\n Aroma: %s\n Pretul: %d\n\n\n",
               current->denumire, current->varsta, current->aroma, current->pret);
        current = current->next;
        st++;
    }
}

int cautareNume(Whiskey *head, char numeCautat[]) {
    Whiskey *current = head;
    int pozitie = 1;
    while (current != NULL) {
        if (strcmp(current->denumire, numeCautat) == 0) {
            return pozitie;
        }
        current = current->next;
        pozitie++;
    }
    return -1; // Numele nu a fost găsit
}

// curatarea listei
void eliberareLista(Whiskey *head) {
    Whiskey *current = head;
    while (current != NULL) {
        Whiskey *temp = current;
        current = current->next;
        free(temp);
    }
}


void sortareVarsta(Whiskey **head) {
    if (*head == NULL || (*head)->next == NULL) {
        // Lista este goală sau conține un singur element, deja sortată
        return;
    }

    Whiskey *i, *j;
    for (i = *head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->varsta > j->varsta) {
                int tempVarsta = i->varsta;
                i->varsta = j->varsta;
                j->varsta = tempVarsta;

                char *tempDenumire = i->denumire;
                i->denumire = j->denumire;
                j->denumire = tempDenumire;

                char *tempAroma = i->aroma;
                i->aroma = j->aroma;
                j->aroma = tempAroma;

                int tempPret = i->pret;
                i->pret = j->pret;
                j->pret = tempPret;
            }
        }
    }
}



// Funcție pentru inserarea la începutul listei
void inserareInceput(Whiskey **head, Whiskey *nou) {
    nou->next = *head;
    *head = nou;
}

// Funcție pentru inserarea la sfârșitul listei
void inserareSfarsit(Whiskey **head, Whiskey *nou) {
    if (*head == NULL) {
        *head = nou;
    } else {
        Whiskey *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = nou;
    }
}

// Funcție pentru inserarea la o anumită poziție în listă
void inserareLaPozitie(Whiskey **head, Whiskey *nou, int pozitie) {
    if (pozitie <= 0) {
        printf("Pozitie invalida.\n");
        return;
    }
    if (pozitie == 1) {
        inserareInceput(head, nou);
    } else {
        Whiskey *current = *head;
        int i = 1;
        while (current != NULL && i < pozitie - 1) {
            current = current->next;
            i++;
        }
        if (current == NULL) {
            printf("Pozitie invalida.\n");
            return;
        }
        nou->next = current->next;
        current->next = nou;
    }
}

// Funcție pentru ștergerea de pe o anumită poziție din listă
void stergereDeLaPozitie(Whiskey **head, int pozitie) {
    if (*head == NULL) {
        printf("Lista este goala.\n");
        return;
    }
    if (pozitie <= 0) {
        printf("Pozitie invalida.\n");
        return;
    }
    Whiskey *temp = *head;
    if (pozitie == 1) {
        *head = (*head)->next;
        free(temp);
    } else {
        int i = 1;
        Whiskey *prev = NULL;
        while (temp != NULL && i < pozitie) {
            prev = temp;
            temp = temp->next;
            i++;
        }
        if (temp == NULL) {
            printf("Pozitie invalida.\n");
            return;
        }
        prev->next = temp->next;
        free(temp);
    }
}

// Funcție pentru inversarea ordinii elementelor din listă
void inversareLista(Whiskey **head) {
    Whiskey *prev = NULL, *current = *head, *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

void curatareLista(Whiskey **head) {
    eliberareLista(*head);
    *head = NULL;
}



int main() {
    Whiskey *head = NULL;
    int choice, pozitie;
    char numeCautat[50];
    do {
        printf("\n");
        printf("1. Citire whiskey\n");
        printf("2. Afișare lista\n");
        printf("3. Cautare whiskey după nume\n");
        printf("4. Eliberare memorie lista\n");
        printf("5. Sortare lista după varsta\n");
        printf("6. Inserare whiskey la începutul listei\n");
        printf("7. Inserare whiskey la sfârșitul listei\n");
        printf("8. Inserare whiskey la o anumită poziție\n");
        printf("9. Ștergere whiskey de pe o anumită poziție\n");
        printf("10. Inversare lista\n");
        printf("11. Curățare lista\n");
        printf("0. Iesire\n");
        printf("Alegerea dvs: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inserareSfarsit(&head, citireWhiskey());
                break;
            case 2:
                afisareLista(head);
                break;
            case 3:
                printf("Introduceti numele whiskey-lui cautat: ");
                scanf("%s", numeCautat);
                pozitie = cautareNume(head, numeCautat);
                if (pozitie != -1) {
                    printf("Whiskey cu numele '%s' se afla pe pozitia %d in lista.\n", numeCautat, pozitie);
                } else {
                    printf("Whiskey cu numele '%s' nu a fost gasit in lista.\n", numeCautat);
                }
                break;
            case 4:
                eliberareLista(head);
                head = NULL;
                printf("Lista a fost eliberata.\n");
                break;
            case 5:
                sortareVarsta(&head);
                printf("Lista a fost sortata dupa varsta.\n");
                break;      
            case 6:
                inserareInceput(&head, citireWhiskey());
                break;
            case 7:
                inserareSfarsit(&head, citireWhiskey());
                break;
            case 8:
                printf("Introduceti pozitia la care sa fie inserat Whiskey: ");
                scanf("%d", &pozitie);
                inserareLaPozitie(&head, citireWhiskey(), pozitie);
                break;
            case 9:
                printf("Introduceti pozitia de pe care sa fie sters Whiskey: ");
                scanf("%d", &pozitie);
                stergereDeLaPozitie(&head, pozitie);
                break;
            case 10:
                inversareLista(&head);
                printf("Lista a fost inversata.\n");
                break;
            case 11:
                curatareLista(&head);
                printf("Lista a fost curatata.\n");
                break;
            case 0:
                printf("Iesire din program.\n");
                break;
            default:
                printf("Optiune invalida. Va rugam sa incercati din nou.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}