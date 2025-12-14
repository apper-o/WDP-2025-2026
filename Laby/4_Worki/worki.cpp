#include "worki.h"
#include <assert.h>

using namespace std;

worek *biurko = nullptr;
przedmiot *ostatni_p = nullptr;
worek *ostatni_w = nullptr;
grupa *ostatni_g = nullptr;

int numer = 0;

grupa *nowa_grupa(worek *w)
{
    grupa *g = new grupa;
    g->wlasciciel = w;
    g->rozmiar = 0;

    g->nastepny = ostatni_g;
    ostatni_g = g;

    return g;
}

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
    p->rodzic = biurko->srodek;
    zmien(biurko, 1);

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
    w->rodzic = biurko->srodek;
    w->srodek = nowa_grupa(w);

    w->nastepny = ostatni_w;
    ostatni_w = w;

    return w;
}

void wloz(przedmiot *co, worek *gdzie)
{
    zmien(co->rodzic->wlasciciel, -1);
    zmien(gdzie, 1);
    co->rodzic = gdzie->srodek;
}

void wloz(worek *co, worek *gdzie)
{
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
    swap(w->srodek, biurko->srodek);

    grupa_worka->wlasciciel = biurko;
    grupa_biurka->wlasciciel = w;

    w->rodzic = biurko->srodek;
    w->rozmiar = biurko->rozmiar - w->rozmiar;
}

void gotowe()
{
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
    delete biurko;
}
