#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "zbior_ary.h"

static int global_q = 0;

long long mod(long long a)
{
    assert(global_q > 0);
    return (a % global_q + global_q) % global_q;
}

long long mniejszy(ciag a, ciag b)
{
    /* Najpierw porownuje reszte z dzielenia przez q, nastepnie poczatek ciagu, a finalnie koniec ciagu */
    long long m1 = mod(a.a), m2 = mod(b.a);
    if(m1 == m2)
        return (a.a==b.a ? a.b < b.b : a.a < b.a);
    return (m1 < m2); 
}

zbior_ary generuj(uint pojemnosc)
{
    zbior_ary wynik;
    wynik.tab = malloc(sizeof(ciag) * pojemnosc);
    wynik.rozmiar = 0;
    wynik.pojemnosc = pojemnosc;
    return wynik;
}

void dodaj(zbior_ary *A, ciag c)
{
    /* Sprawdza, czy ciag jest poprawny */
    if(c.a <= c.b)
    {
        /* Jeśli to konieczne alokuje wiecej pamieci */
        if(A->pojemnosc == A->rozmiar)
        {
            A->pojemnosc = (A->pojemnosc == 0 ? 2 : A->pojemnosc * 2);
            A->tab = realloc(A->tab, sizeof(ciag) * A->pojemnosc);
        }
        A->tab[A->rozmiar++] = c;
    }
}

zbior_ary ciag_arytmetyczny(int a, int q, int b)
{
    zbior_ary wynik = generuj(1);
    if(global_q == 0)
        global_q = q;
    dodaj(&wynik, (ciag){a, b});
    return wynik;
}

zbior_ary singleton(int a)
{
    return ciag_arytmetyczny(a, global_q, a);
}

zbior_ary suma(zbior_ary A, zbior_ary B)
{
    /* Rozmiar zbioru bedzie nie wiekszy niz suma rozmiarow zbiorow A i B*/
    zbior_ary wynik = generuj(A.rozmiar+B.rozmiar);
    uint i = 0, j = 0;
    while(i < A.rozmiar || j < B.rozmiar)
    {
        /* Wybieram mniejszy ciag */
        ciag obecny;
        if(i < A.rozmiar && (j == B.rozmiar || mniejszy(A.tab[i], B.tab[j])))
            obecny = A.tab[i++];
        else
            obecny = B.tab[j++];
        /* Sprawdzam czy ciag da sie scalic z poprzednio dodanym (o ile istnieje) */
        if(wynik.rozmiar == 0)
            dodaj(&wynik, obecny);
        else
        {
            ciag *ostatni = &wynik.tab[wynik.rozmiar - 1];
            if(mod(ostatni->a) == mod(obecny.a) && ostatni->b + global_q >= obecny.a)
                ostatni->b = max(ostatni->b, obecny.b);
            else
                dodaj(&wynik, obecny);
        }
    }
    return wynik;
}

zbior_ary iloczyn(zbior_ary A, zbior_ary B)
{
    /* Rozmiar zbioru bedzie nie wiekszy niz minimum z rozmiarow A i B */
    zbior_ary wynik = generuj(min(A.rozmiar, B.rozmiar));
    uint i = 0, j = 0;
    while(i < A.rozmiar && j < B.rozmiar)
    {
        /* Sprawdzam czy ciagi maja niepuste przeciecie i zwiekszam 'wskaźnik' na zbiorze, ktory ma mniejsze modulo, lub szybicej sie konczy jezeli modulo jest takie same*/
        ciag a = A.tab[i], b = B.tab[j];
        if(mod(a.a) == mod(b.a))
        {
            dodaj(&wynik, (ciag){max(a.a, b.a), min(a.b, b.b)});
            (a.b < b.b ? i++ : j++);
        }
        else
            (mod(a.a) < mod(b.a) ? i++ : j++);
    }
    return wynik;
}

zbior_ary roznica(zbior_ary A, zbior_ary B)
{
    /* Rozmiar zbioru bedzie niewiekszy niz rozmiar zbioru A */
    zbior_ary wynik = generuj(A.rozmiar);
    for(uint i=0,j=0;i<A.rozmiar;i++)
    {
        ciag a = A.tab[i];
        /* Zwiekszam 'wskaznik' na ciagi w zbiorze B dopoki te ciagi sa mniejsze niz obecnie rozpatrywany ciag w A */
        while(j < B.rozmiar && (mod(a.a) > mod(B.tab[j].a) || (mod(a.a) == mod(B.tab[j].a) && B.tab[j].b < a.a)))
            j++;
        ciag b = B.tab[j];
        while(j < B.rozmiar && mod(B.tab[j].a) == mod(a.a) && ((b.a <= a.b && a.b <= b.b) || (a.a <= b.b && b.b <= a.b)))
        {
            if(a.a <= b.a && b.b <= a.b) // Przypadek 1: Ciag b jest zawarty w ciagu a
            {
                dodaj(&wynik, (ciag){a.a, b.a - global_q});
                a.a = b.b + global_q;
            }
            if(a.a <= b.b && b.b <= a.b) // Przypadek 2: Ciag b jest prefiksem ciagu a
                a.a = b.b + global_q;
            if(b.a <= a.b && a.b <= b.b) // Przypadek 3: Ciag b jest suffiksem ciagu a
                a.b = b.a - global_q; 
            b = B.tab[++j];
        }
        /* Ciag b nalezacy do B moze miec niepuste przeciecie z wiecej niz jednym ciagiem nalezacym do A*/
        if(j>0)
            j--;
        dodaj(&wynik, a);
    }
    return wynik;
}

bool nalezy(zbior_ary A, int b)
{
    /* Element nie moze znajdowac sie w pustym zbiorze */
    if(A.rozmiar == 0)
        return 0;
    uint l = 0, r = A.rozmiar - 1, start;
    long long M = mod(b);
    /* Najpierw uzywam wyszukiwania binarnego, aby wyszukac pierwszy i ostatni element w A o takiej samej reszcie z dzielenia przez q co b */
    while(l<r)
    {
        uint m = l + (r - l) / 2;
        if(mod(A.tab[m].a) < M)
            l = m+1;
        else
            r = m;
    }
    /* Jeżeli nie ma takiego elementu, to b nie nalezy do A */
    if(mod(A.tab[l].a) != M) 
        return false;
    start = l;
    l = 0, r = A.rozmiar - 1;
    while(l<r)
    {
        uint m = l + (r - l + 1) / 2;
        if(mod(A.tab[m].a) > M)
            r = m-1;
        else
            l = m;
    }
    /* Znajac pierwszy i ostatni element sprawdzam czy istnieje taki ciag, ktory zawiera b */
    l = start;
    while(l < r)
    {
        uint m = l + (r - l + 1) / 2;
        if(A.tab[m].a <= b)
            l = m;
        else
            r = m - 1;
    }
    return (A.tab[l].a <= b && b <= A.tab[l].b);
}

uint moc(zbior_ary A)
{ 
    /* Zliczam kazdy ciag osobno, w jednym ciagu (a) jest (a.b - a.a) / q + 1 elementow */
    uint wynik = 0;
    for(uint i=0;i<A.rozmiar;i++)
        wynik += (uint)(A.tab[i].b - A.tab[i].a) / (uint)global_q + 1;
    return wynik;
}

uint ary(zbior_ary A)
{
    return A.rozmiar;
}