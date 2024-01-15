/*
Autor: Dominik Kaczmarek
Grupa: Pn/P 13:15
Temat: Laboratorium 6, zadania 1, 2
Data: 13.01.2024 r.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Towar {
    char nazwa[20] = "\0";
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

    Towar (*Tab) = NULL;
    unsigned int Rozmiar = 0;

    // TODO menu
    int wybranaOpcja;
    do {
        printf("\n\n");
        printf("\n=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=\n");
        printf("|| Aktualny adres tablicy: %p.       Rozmiar tablicy: %3u. ||\n", Tab, Rozmiar);
        printf("=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=\n");
        printf("||                  Wybierz funkcje do uruchomienia                      ||\n");
        printf("|| *1* Utworzenie tablicy o danym rozmiarze                              ||\n");
        printf("|| *2* Dodanie rekordu do tablicy                                        ||\n");
        printf("|| *3* Usuniecie danego rekordu z tablicy                                ||\n");
        printf("|| *4* Wypisanie zawartosci tablicy                                      ||\n");
        printf("|| *5* Usuniecie tablicy                                                 ||\n");
        //printf("|| *5* Wypisanie wszystkich imion zaczynajacych sie dana litera          ||\n");
        //printf("|| *6* Sortowanie imion alfabetycznie                                    ||\n");
        //printf("|| *7* Sortowanie imion wedlug dlugosci                                  ||\n");
        printf("|| *8* Zakoncz dzialanie programu                                        ||\n");
        printf("=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=\n");
        printf("Wprowadz numer wybranej opcji: ");
        scanf("%i", &wybranaOpcja);
        system("cls");
        fflush(stdin); // wyczyszczenie bufora klawiatury
        switch (wybranaOpcja) {
            case 1: InitTab(Tab, Rozmiar); break;
            case 2: AddRecord(Tab, Rozmiar); break;
            case 3: RemoveRecord(Tab, Rozmiar); break;
            case 4: PrintTab(Tab, Rozmiar); break;
            case 5: RemoveTab(Tab, Rozmiar); break;

            default: printf("Niepoprawna liczba.");
        }
    } while (wybranaOpcja != 8);
    // TODO wyszukiwanie i wyświetlanie danych dotyczących zakupów spełniających wybrane
    //  kryteria, np. cena jednostkowa mniejsza niż podana


    return 0;
}

void InitTab(Towar *&Tab, unsigned int &Rozmiar) {
    if (Tab != NULL) {
        printf("\nTablica zostala wczesniej utworzona. Czy chcesz \n");
    }
    printf("Podaj rozmiar tablicy:");
    scanf("%u", &Rozmiar);
    Tab = (Towar*) calloc(Rozmiar,sizeof(Towar));
    printf("\nTablica o rozmiarze %u zostala utworzona.\n", Rozmiar);
}

void PrintTab(Towar *Tab, unsigned int Rozmiar) {
    if (Tab == NULL) {
        printf("Tablica nie zostala jeszcze utworzona.");
    }
    else if (Rozmiar == 0) {
        printf("W tablicy nie znajduja sie jeszcze zadne rekordy.");
    }
    else {
        printf("\n\n");
        printf("  Lp.  |         Nazwa         |     Cena     |  Ilosc  |   Wartosc   \n");
        printf("----------------------------------------------------------------------\n");
        for (int i = 0; i < Rozmiar; i++) {
            printf(" %5d | %-20s  | %12.2f | %7d | %11.3f \n",
                i+1, Tab[i].nazwa, Tab[i].cena, Tab[i].ilosc, Tab[i].cena*Tab[i].ilosc);
        }
        printf("----------------------------------------------------------------------\n");
        printf("\n\n\n");
    }
}

void AddRecord(Towar *&Tab, unsigned &Rozmiar) {
    if (Tab == NULL) {
        printf("Tablica nie zostala jeszcze utworzona.");
    }
    else {
        unsigned int pozycja;
        printf("%d\n", Rozmiar);
        for (pozycja = 0; pozycja < Rozmiar; pozycja++) {
            if (Tab[pozycja].nazwa[0] == '\0') {
                printf("NULL! %d\n", pozycja);
                break;
            }
        }
        if (pozycja >= Rozmiar) {
            printf("Zmieniono pozycje");
            Rozmiar += 1;
            Tab = (Towar*) realloc(Tab,sizeof(Towar)*Rozmiar);
            pozycja = Rozmiar - 1;
        }
        printf("\nPodaj nazwe: ");
        fgets(Tab[pozycja].nazwa, 20, stdin);
        Tab[pozycja].nazwa[strlen(Tab[pozycja].nazwa)-1] = 0; // usuwa znak nowej linii \n
        printf("\nPodaj cene:");
        scanf("%f", &Tab[pozycja].cena);
        printf("\nPodaj ilosc:");
        scanf("%d", &Tab[pozycja].ilosc);
    }
}

void RemoveRecord(Towar *&Tab, unsigned &Rozmiar) {
    if (Tab == NULL) {
        printf("Tablica nie zostala jeszcze utworzona.");
    }
    else {
        unsigned int pozycja;
        printf("Podaj numer rekordu do usuniecia: ");
        scanf("%u", &pozycja);
        while (pozycja > Rozmiar) {
            printf("Podany rekord nie istnieje.");
            printf("Podaj numer rekordu do usuniecia: ");
            scanf("%u", &pozycja);
        }
        pozycja -= 1; // zmniejszenie o 1 aby pozycja byla zgodna z Lp. wyswietlana przez PrintTab
        for (pozycja; pozycja < Rozmiar; pozycja++) {
            Tab[pozycja] = Tab[pozycja+1];
        }
        Rozmiar -= 1;
        Tab = (Towar*) realloc(Tab,sizeof(Towar)*Rozmiar);
        printf("Rekord zostal usuniety.");
    }
}

void RemoveTab(Towar *&Tab, unsigned &Rozmiar) {

}
