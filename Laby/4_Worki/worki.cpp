#include "worki.h"
#include <assert.h>
#include <algorithm>

using namespace std;

// Główny korzeń struktury ("Biurko"), na którym lądują nowe elementy
worek *biurko = nullptr;

// Wskaźniki służące do późniejszego zwolnienia pamięci
przedmiot *ostatni_p = nullptr;
worek *ostatni_w = nullptr;
grupa *ostatni_g = nullptr;

// Licznik do nadawania id workom
int numer = 0;

// Tworzy nową "grupę". Grupa to warstwa pośrednia między workiem a jego zawartością.
grupa *nowa_grupa(worek *w)
{
    grupa *g = new grupa;
    g->wlasciciel = w;

    // Dodanie do listy sprzątania
    g->nastepny = ostatni_g;
    ostatni_g = g;

    return g;
}

// Inicjalizuje biurko przy pierwszym użyciu
void inicjalizuj()
{
    if(biurko == nullptr)
    {
        biurko = new worek;
        biurko->numer = -1;
        biurko->rozmiar = 0;
        biurko->rodzic = nullptr;
        biurko->srodek = nowa_grupa(biurko);
    }
}

// Aktualizuje rozmiar drzewa
void zmien(worek *w, int delta)
{
    if(delta)
    {
        while(w != nullptr)
        {
            w->rozmiar += delta;
            w = (w->rodzic != nullptr ? w->rodzic->wlasciciel : nullptr);
        }
    }
}

przedmiot *nowy_przedmiot()
{
    inicjalizuj();
    przedmiot *p = new przedmiot; 

    // Nowy przedmiot zawsze trafia na biurko
    p->rodzic = biurko->srodek;
    zmien(biurko, 1);

    // Dodanie do listy sprzątania
    p->nastepny = ostatni_p;
    ostatni_p = p;

    return p;
}

worek *nowy_worek()
{
    inicjalizuj();
    worek *w = new worek;
    w->numer = numer++;
    w->rozmiar = 0;

    // Nowy worek trafia na biurko
    w->rodzic = biurko->srodek;
    
    // Każdy worek ma własną grupę na swoją zawartość
    w->srodek = nowa_grupa(w);

    // Dodanie do listy sprzątania
    w->nastepny = ostatni_w;
    ostatni_w = w;

    return w;
}

void wloz(przedmiot *co, worek *gdzie)
{
    // Aktualizuje wartość i przepina wskaźnik przedmiotu
    zmien(co->rodzic->wlasciciel, -1);
    zmien(gdzie, 1);
    co->rodzic = gdzie->srodek;
}

void wloz(worek *co, worek *gdzie)
{
    // Aktualizuje wartość i przepina wskaźnik worka
    zmien(co->rodzic->wlasciciel, -co->rozmiar);
    zmien(gdzie, co->rozmiar);
    co->rodzic = gdzie->srodek;
}

void wyjmij(przedmiot *p)
{
    wloz(p, biurko);
}

void wyjmij(worek *w)
{
    wloz(w, biurko);
}

int w_ktorym_worku(przedmiot *p)
{
    return p->rodzic->wlasciciel->numer;
}

int w_ktorym_worku(worek *w)
{
    return w->rodzic->wlasciciel->numer;
}

int ile_przedmiotow(worek *w)
{
    return w->rozmiar;
}

void na_odwrot(worek *w)
{
    grupa *grupa_worka = w->srodek;
    grupa *grupa_biurka = biurko->srodek;

    // Zamienia zawartości biurka i worka
    swap(w->srodek, biurko->srodek);

    // Zamiana wlascicieli grup
    grupa_worka->wlasciciel = biurko;
    grupa_biurka->wlasciciel = w;

    // Aktualizacja rozmiaru i przepięcie wskaźników (na biurko nie trzeba aktualizować)
    w->rodzic = biurko->srodek;
    w->rozmiar = biurko->rozmiar - w->rozmiar;
}

void gotowe()
{
    // Czyszczenie pamięci
    while(ostatni_p)
    {
        przedmiot *p = ostatni_p->nastepny;
        delete ostatni_p;
        ostatni_p = p;
    }
    while(ostatni_w)
    {
        worek *w = ostatni_w->nastepny;
        delete ostatni_w;
        ostatni_w = w;
    }
    while(ostatni_g)
    {
        grupa *g = ostatni_g->nastepny;
        delete ostatni_g;
        ostatni_g = g;
    }
    if(biurko)
        delete biurko;
}
