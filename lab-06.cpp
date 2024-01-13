/*
Autor: Dominik Kaczmarek
Grupa: Pn/P 13:15
Temat: Laboratorium 6, zadania 1, 2
Data: 13.01.2024 r.
*/

#include <stdio.h>
#include <stdlib.h>

struct Towar {
    char nazwa[20] = {NULL};
    float cena{};
    int ilosc{};
};

// Inicjalizacja dynamicznej tablicy struktur o podanym rozmiarze
void InitTab(Towar *&Tab, unsigned int &Rozmiar);

// Wypisanie elementow tablicy
void PrintTab(Towar *Tab, unsigned int Rozmiar);

// Dodanie nowego rekordu na koncu tablicy
void AddRecord(Towar *&Tab, unsigned int &Rozmiar);

// Usuniecie danego rekordu z tablicy
void RemoveRecord(Towar *&Tab, unsigned int &Rozmiar);

// Usuniecie z pamieci tablicy dynamicznej
void RemoveTab(Towar *&Tab, unsigned int &Rozmiar);


int main() {
    printf("Autor: Dominik Kaczmarek Pn/P 13:15\n");

    Towar (*Tab)[] = NULL;
    unsigned int Rozmiar = 0;

    // TODO menu

    return 0;
}

void InitTab(Towar *&Tab, unsigned int &Rozmiar) {
    printf("Podaj rozmiar tablicy:");
    scanf("%u", &Rozmiar);
    Tab = (Towar*) calloc(Rozmiar,sizeof(Towar));
    printf("\nTablica o rozmiarze %u zostala utworzona.\n", Rozmiar);
}

void PrintTab(Towar *Tab, unsigned int Rozmiar) {
    printf("\n\n");
    printf("  Lp.  |         Nazwa         |     Cena     |  Ilosc  |   Wartosc   \n");
    printf("______________________________________________________________________\n");
    for (int i = 0; i < Rozmiar; i++) {
        printf("%-5d | %20s | %-12f | %-7d | %-11.3f",
            i+1, Tab[i].nazwa, Tab[i].cena, Tab[i].ilosc, Tab[i].cena*Tab[i].ilosc);
    }
    printf("______________________________________________________________________\n");
    printf("\n\n\n");
}

void AddRecord(Towar *&Tab, unsigned &Rozmiar) {
    unsigned int pozycja;
    for (pozycja = 0; pozycja < Rozmiar; pozycja++) {
        if (Tab[pozycja].nazwa == NULL) break;
    }
    if (!pozycja < Rozmiar) {
        Rozmiar += 1;
        Tab = (Towar*) realloc(Tab,sizeof(Towar)*Rozmiar);
        pozycja = Rozmiar - 1;
    }
    printf("\nPodaj imie: ");
    fgets(Tab[pozycja].nazwa, 20, stdin);
    printf("\nPodaj cene:");
    scanf("%f", &Tab[pozycja].cena);
    printf("\nPodaj ilosc:");
    scanf("%d", &Tab[pozycja].ilosc);
}

void RemoveRecord(Towar *&Tab, unsigned &Rozmiar) {

}

void RemoveTab(Towar *&Tab, unsigned &Rozmiar) {

}
