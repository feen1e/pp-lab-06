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

// Wypisanie elementow tablicy spelniajacych dany warunek
void PrintCondition(Towar *Tab, unsigned int Rozmiar);

// TODO zapis danych pamiętanych w tablicy dynamicznej do pliku dyskowego oraz
//  wczytanie uprzednio zapisanych danych do nowej tablicy dynamicznej

// Zapisanie aktualnej tablicy do pliku
void SaveToFile(Towar *&Tab, unsigned int &Rozmiar);

// Wczytanie nowej tablicy z pliku
void LoadFromFile(Towar *&Tab, unsigned int &Rozmiar);

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
        printf("|| *5* Wypisanie zakupow spelniajacych dany warunek                      ||\n");
        printf("|| *6* Usuniecie tablicy                                                 ||\n");
        printf("|| *7* Zakoncz dzialanie programu                                        ||\n");
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
            case 5: PrintCondition(Tab, Rozmiar); break;
            case 6: RemoveTab(Tab, Rozmiar); break;
            default: printf("Niepoprawna liczba.");
        }
    } while (wybranaOpcja != 7);


    return 0;
}

void InitTab(Towar *&Tab, unsigned int &Rozmiar) {
    char Odpowiedz;
    if (Tab != NULL) {
        printf("\nTablica zostala wczesniej utworzona.\n"
               "Utworzenie nowej spowoduje suniecie wszystkich rekordow znajdujacych sie aktualnie w tablicy.\n"
               "Czy chcesz utworzyc nowa tablice? (T/N): ");
        fflush(stdin);
        scanf("%c", &Odpowiedz);
        if (Odpowiedz == 'T' || Odpowiedz == 't') {
            RemoveTab(Tab, Rozmiar);
        }
        else {
            printf("Aktualna tablica nie zostala usunieta.\n");
            return;
        }
    }
    printf("Podaj rozmiar nowej tablicy:");
    scanf("%u", &Rozmiar);
    if (Rozmiar == 0) {
        printf("Rozmiar musi byc liczba wieksza od 0.");
        return;
    }
    Tab = (Towar*) calloc(Rozmiar,sizeof(Towar));
    printf("\nTablica o rozmiarze %u zostala utworzona.\n", Rozmiar);

    printf("\nCzy chcesz zaczac wczytywac dane do tablicy? (T/N): ");
    fflush(stdin);
    scanf("%c", &Odpowiedz);
    if (Odpowiedz == 'T' || Odpowiedz == 't') {
        for (int i = 0; i < Rozmiar; i++) {
            printf("\nRekord nr %d:\n", i+1);
            fflush(stdin);
            AddRecord(Tab, Rozmiar);
        }
        printf("Pomyslnie wczytano dane.");
    }
}

void PrintTab(Towar *Tab, unsigned int Rozmiar) {
    if (Tab == NULL) {
        printf("Tablica nie zostala jeszcze utworzona.");
    }
    /*else if (Rozmiar == 0) {
        printf("W tablicy nie znajduja sie jeszcze zadne rekordy.");
    }*/
    else {
        printf("\n\n");
        printf("  Lp.  |         Nazwa         |    Cena    |  Ilosc  |      Wartosc     \n");
        printf("-------------------------------------------------------------------------\n");
        for (int i = 0; i < Rozmiar; i++) {
            printf(" %5d | %-20s  | %10.2f | %7d | %16.2f \n",
                i+1, Tab[i].nazwa, Tab[i].cena, Tab[i].ilosc, Tab[i].cena*Tab[i].ilosc);
        }
        printf("-------------------------------------------------------------------------\n");
        printf("\n\n\n");
    }
}

void AddRecord(Towar *&Tab, unsigned &Rozmiar) {
    if (Tab == NULL) {
        printf("Tablica nie zostala jeszcze utworzona.");
    }
    else {
        unsigned int pozycja;
        //printf("%d\n", Rozmiar);
        for (pozycja = 0; pozycja < Rozmiar; pozycja++) {
            if (Tab[pozycja].nazwa[0] == '\0') {
        //        printf("NULL! %d\n", pozycja);
                break;
            }
        }
        if (pozycja >= Rozmiar) {
            //printf("Zmieniono pozycje");
            Rozmiar += 1;
            Tab = (Towar*) realloc(Tab,sizeof(Towar)*Rozmiar);
            pozycja = Rozmiar - 1;
        }
        printf("Podaj nazwe: ");
        fgets(Tab[pozycja].nazwa, 20, stdin);
        Tab[pozycja].nazwa[strlen(Tab[pozycja].nazwa)-1] = 0; // usuwa znak nowej linii \n
        if (Tab[pozycja].nazwa[0] >= 97 && Tab[pozycja].nazwa[0] <= 122) Tab[pozycja].nazwa[0] -= 32;
        printf("Podaj cene:");
        scanf("%f", &Tab[pozycja].cena);
        printf("Podaj ilosc:");
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
            printf("Podany rekord nie istnieje.\n");
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
    if (Tab == NULL) {
        printf("Tablica nie zostala jeszcze utworzona.");
    }
    else {
        free(Tab);
        Tab = NULL;
        Rozmiar = 0;
        printf("Tablica zostala usunieta.\n");
    }
}

void PrintCondition(Towar *Tab, unsigned Rozmiar) {
    if (Tab == NULL) {
        printf("Tablica nie zostala jeszcze utworzona.");
    }
    else {
        unsigned short int Pole;
        printf("Jakiego pola dotyczy warunek?\n"
               "1. Nazwa\n"
               "2. Cena\n"
               "3. Ilosc\n"
               "4. Wartosc\n"
               "Podaj numer pola: ");
        do {
            fflush(stdin);
            scanf("%hu", &Pole);
            if (Pole < 1 || Pole > 4) {
                printf("Niepoprawny numer pola. Wprowadz ponownie: ");
            }
        } while (Pole < 1 || Pole > 4);
        if (Pole == 1) {
            printf("Wybierz opcje:\n"
                   "1. Wypisz rekordy ktorych nazwa zaczyna sie dana litera.\n"
                   "2. Wypisz rekordy o danej nazwie.\n"
                   "Podaj numer opcji: ");
            unsigned short int Opcja;
            do {
                fflush(stdin);
                scanf("%hu", &Opcja);
                if (Opcja < 1 || Opcja > 2) {
                    printf("Niepoprawny numer opcji. Wprowadz ponownie: ");
                }
            } while (Opcja < 1 || Opcja > 2);
            if (Opcja == 1) {
                char Znak;
                printf("Podaj znak, ktorym maja zaczynac sie nazwy:");
                fflush(stdin);
                scanf("%c", &Znak);
                if (Znak >= 97 && Znak <= 122) Znak -= 32;
                printf("\n\n");
                printf("  Lp.  |         Nazwa         |    Cena    |  Ilosc  |      Wartosc     \n");
                printf("-------------------------------------------------------------------------\n");
                for (int i = 0; i < Rozmiar; i++) {
                    if (Tab[i].nazwa[0] == Znak) {
                        printf(" %5d | %-20s  | %10.2f | %7d | %16.2f \n",
                            i+1, Tab[i].nazwa, Tab[i].cena, Tab[i].ilosc, Tab[i].cena*Tab[i].ilosc);
                    }
                }
            }
            if (Opcja == 2) {
                printf("Podaj nazwe rekordow do wypisania:");
                char Nazwa[20];
                fflush(stdin);
                fgets(Nazwa, 20, stdin);
                Nazwa[strlen(Nazwa)-1] = 0; // usuwa znak nowej linii \n
                if (Nazwa[0] >= 97 && Nazwa[0] <= 122) Nazwa[0] -= 32;
                printf("\n\n");
                printf("  Lp.  |         Nazwa         |    Cena    |  Ilosc  |      Wartosc     \n");
                printf("-------------------------------------------------------------------------\n");
                for (int i = 0; i < Rozmiar; i++) {
                    if (strcmp(Tab[i].nazwa,Nazwa) == 0) {
                        printf(" %5d | %-20s  | %10.2f | %7d | %16.2f \n",
                            i+1, Tab[i].nazwa, Tab[i].cena, Tab[i].ilosc, Tab[i].cena*Tab[i].ilosc);
                    }
                }
            }
            printf("-------------------------------------------------------------------------\n");
            printf("\n\n\n");
        }
        else {
            printf("Wybierz warunek:\n"
                   "1. Mniejsza niz... <\n"
                   "2. Mniejsza lub rowna... <=\n"
                   "3. Rowna... =\n"
                   "4. Wieksza lub rowna... >=\n"
                   "5. Wieksza niz... >\n");
            unsigned short int Opcja;
            do {
                fflush(stdin);
                scanf("%hu", &Opcja);
                if (Opcja < 1 || Opcja > 5) {
                    printf("Niepoprawny numer opcji. Wprowadz ponownie: ");
                }
            } while (Opcja < 1 || Opcja > 5);
            float Warunek;
            printf("Podaj wartosc do porownania:");
            fflush(stdin);
            scanf("%f", &Warunek);

            printf("\n\n");
            printf("  Lp.  |         Nazwa         |    Cena    |  Ilosc  |      Wartosc     \n");
            printf("-------------------------------------------------------------------------\n");
            if (Opcja == 1) {
                for (int i = 0; i < Rozmiar; i++) {
                    if (Pole == 2 && Tab[i].cena < Warunek) {
                        printf(" %5d | %-20s  | %10.2f | %7d | %16.2f \n",
                            i+1, Tab[i].nazwa, Tab[i].cena, Tab[i].ilosc, Tab[i].cena*Tab[i].ilosc);
                    }
                    else if (Pole == 3 && Tab[i].ilosc < (int) Warunek) {
                        printf(" %5d | %-20s  | %10.2f | %7d | %16.2f \n",
                            i+1, Tab[i].nazwa, Tab[i].cena, Tab[i].ilosc, Tab[i].cena*Tab[i].ilosc);
                    }
                    else if (Pole == 4 && Tab[i].cena*Tab[i].ilosc < Warunek) {
                        printf(" %5d | %-20s  | %10.2f | %7d | %16.2f \n",
                            i+1, Tab[i].nazwa, Tab[i].cena, Tab[i].ilosc, Tab[i].cena*Tab[i].ilosc);
                    }
                }
            }
            else if (Opcja == 2) {
                for (int i = 0; i < Rozmiar; i++) {
                    if (Pole == 2 && Tab[i].cena <= Warunek) {
                        printf(" %5d | %-20s  | %10.2f | %7d | %16.2f \n",
                            i+1, Tab[i].nazwa, Tab[i].cena, Tab[i].ilosc, Tab[i].cena*Tab[i].ilosc);
                    }
                    else if (Pole == 3 && Tab[i].ilosc <= (int) Warunek) {
                        printf(" %5d | %-20s  | %10.2f | %7d | %16.2f \n",
                            i+1, Tab[i].nazwa, Tab[i].cena, Tab[i].ilosc, Tab[i].cena*Tab[i].ilosc);
                    }
                    else if (Pole == 4 && Tab[i].cena*Tab[i].ilosc <= Warunek) {
                        printf(" %5d | %-20s  | %10.2f | %7d | %16.2f \n",
                            i+1, Tab[i].nazwa, Tab[i].cena, Tab[i].ilosc, Tab[i].cena*Tab[i].ilosc);
                    }
                }
            }
            else if (Opcja == 3) {
                for (int i = 0; i < Rozmiar; i++) {
                    if (Pole == 2 && Tab[i].cena == Warunek) {
                        printf(" %5d | %-20s  | %10.2f | %7d | %16.2f \n",
                            i+1, Tab[i].nazwa, Tab[i].cena, Tab[i].ilosc, Tab[i].cena*Tab[i].ilosc);
                    }
                    else if (Pole == 3 && Tab[i].ilosc == (int) Warunek) {
                        printf(" %5d | %-20s  | %10.2f | %7d | %16.2f \n",
                            i+1, Tab[i].nazwa, Tab[i].cena, Tab[i].ilosc, Tab[i].cena*Tab[i].ilosc);
                    }
                    else if (Pole == 4 && Tab[i].cena*Tab[i].ilosc == Warunek) {
                        printf(" %5d | %-20s  | %10.2f | %7d | %16.2f \n",
                            i+1, Tab[i].nazwa, Tab[i].cena, Tab[i].ilosc, Tab[i].cena*Tab[i].ilosc);
                    }
                }
            }
            else if (Opcja == 4) {
                for (int i = 0; i < Rozmiar; i++) {
                    if (Pole == 2 && Tab[i].cena >= Warunek) {
                        printf(" %5d | %-20s  | %10.2f | %7d | %16.2f \n",
                            i+1, Tab[i].nazwa, Tab[i].cena, Tab[i].ilosc, Tab[i].cena*Tab[i].ilosc);
                    }
                    else if (Pole == 3 && Tab[i].ilosc >= (int) Warunek) {
                        printf(" %5d | %-20s  | %10.2f | %7d | %16.2f \n",
                            i+1, Tab[i].nazwa, Tab[i].cena, Tab[i].ilosc, Tab[i].cena*Tab[i].ilosc);
                    }
                    else if (Pole == 4 && Tab[i].cena*Tab[i].ilosc >= Warunek) {
                        printf(" %5d | %-20s  | %10.2f | %7d | %16.2f \n",
                            i+1, Tab[i].nazwa, Tab[i].cena, Tab[i].ilosc, Tab[i].cena*Tab[i].ilosc);
                    }
                }
            }
            else if (Opcja == 5) {
                for (int i = 0; i < Rozmiar; i++) {
                    if (Pole == 2 && Tab[i].cena > Warunek) {
                        printf(" %5d | %-20s  | %10.2f | %7d | %16.2f \n",
                            i+1, Tab[i].nazwa, Tab[i].cena, Tab[i].ilosc, Tab[i].cena*Tab[i].ilosc);
                    }
                    else if (Pole == 3 && Tab[i].ilosc > (int) Warunek) {
                        printf(" %5d | %-20s  | %10.2f | %7d | %16.2f \n",
                            i+1, Tab[i].nazwa, Tab[i].cena, Tab[i].ilosc, Tab[i].cena*Tab[i].ilosc);
                    }
                    else if (Pole == 4 && Tab[i].cena*Tab[i].ilosc > Warunek) {
                        printf(" %5d | %-20s  | %10.2f | %7d | %16.2f \n",
                            i+1, Tab[i].nazwa, Tab[i].cena, Tab[i].ilosc, Tab[i].cena*Tab[i].ilosc);
                    }
                }

            }
            printf("-------------------------------------------------------------------------\n");
            printf("\n\n\n");
        }
    }
}

void SaveToFile(Towar *&Tab, unsigned &Rozmiar) {
    // TODO
}

void LoadFromFile(Towar *&Tab, unsigned &Rozmiar) {
    // TODO
}

