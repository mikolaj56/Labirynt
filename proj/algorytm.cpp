#include "algorytm.h"
using namespace std;

int algorytm::odlegloscMinimalna(std::vector<std::vector<int>> plansza)
{
    pole start(0, 0, 0);        //inicjalizacja obiektu pola

    vector<vector<int>> odwiedzone;     //tablica pól odwiedzonych/zablokowanych
    odwiedzone.resize(m, vector<int>(n));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (plansza[i][j] == 1)
                odwiedzone[i][j] = 1;//pole zablokowane
            else
                odwiedzone[i][j] = 0;//pole dostêpne

            if (plansza[i][j] == -1)//ustawienie pola pocz¹tkowego
            {
                start.wiersz = i;
                start.kolumna = j;
            }
            //std::cout << i << " " << j << std::endl;
        }
    }

    queue<pole> kolejka;
    kolejka.push(start);
    odwiedzone[start.wiersz][start.kolumna] = 1;
    while (!kolejka.empty())
    {
        pole p = kolejka.front();
        kolejka.pop();

        if (plansza[p.wiersz][p.kolumna] == 2)   //zwrót najkrótszej drogi w momencie napotkania szukanego pola
        {
            //std::cout << "Rozmiar kolejki = " << poprzednie.size() << std::endl;
            //std::cout << "Rozmiar kolejki = " << kolejka.size() << std::endl;
            return p.odleglosc;
        }
                
        if (p.wiersz - 1 >= 0 && odwiedzone[p.wiersz - 1][p.kolumna] == 0)//odwiedzanie pola wy¿ej
        {
            kolejka.push(pole(p.wiersz - 1, p.kolumna, p.odleglosc + 1));
            odwiedzone[p.wiersz - 1][p.kolumna] = 1;
        }

        if (p.wiersz + 1 < m && odwiedzone[p.wiersz + 1][p.kolumna] == 0)//odwiedzanie pola ni¿ej
        {
            kolejka.push(pole(p.wiersz + 1, p.kolumna, p.odleglosc + 1));
            odwiedzone[p.wiersz + 1][p.kolumna] = 1;
        }

        if (p.kolumna - 1 >= 0 && odwiedzone[p.wiersz][p.kolumna - 1] == 0)//odwiedzanie pola po lewej
        {
            kolejka.push(pole(p.wiersz, p.kolumna - 1, p.odleglosc + 1));
            odwiedzone[p.wiersz][p.kolumna - 1] = 1;
        }

        if (p.kolumna + 1 < n && odwiedzone[p.wiersz][p.kolumna + 1] == 0)//odwiedzanie pola po prawej
        {
            kolejka.push(pole(p.wiersz, p.kolumna + 1, p.odleglosc + 1));
            odwiedzone[p.wiersz][p.kolumna + 1] = 1;
        }
        }
    
    return -1;
}

void algorytm::rec(std::vector<std::vector<int>>& plansza, int optymalneKroki)
{
    int tmp=2;
    //int tmp2=1;
    int tmpX = 0;
    int tmpY = 0;
    int wynik = 0;


    while (tmp != optymalneKroki)// && tmp2!=0)
    {
        tmp = 1;
        //tmp2 = 0;

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (plansza[i][j] == 5) tmp++;
                //if (plansza[i][j] == 0) tmp2++;  
            }
        }

        while (plansza[tmpX][tmpY] != 0)
        {
            tmpX = std::rand() % m;
            tmpY = std::rand() % n;
        }

        plansza[tmpX][tmpY] = 1;

        wynik = odlegloscMinimalna(plansza);
        if (wynik == optymalneKroki)
            plansza[tmpX][tmpY] = 1;
        else
            plansza[tmpX][tmpY] = 5;
        
    }
}
/*
void algorytm::rec(std::vector<std::vector<int>>& plansza, int optymalneKroki)
{
    int kroki=0;
    int wynik=0;
    while (kroki != optymalneKroki)
    {
        if (plansza[i][j] == 5) kroki++;
        wynik = odlegloscMinimalna(plansza);
        if(wynik==optymalneKroki)
            plansza
    }

}*/
/*
int algorytm::odlegloscMinimalna(std::vector<std::vector<int>> plansza)
{

     //inicjalizacja obiektu pola
    pole start(0, 0, 0);
    vector<vector<int>> odwiedzone;     //tablica pól odwiedzonych/zablokowanych
    odwiedzone.resize(m, vector<int>(n));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (plansza[i][j] == 1)
                odwiedzone[i][j] = 1;//pole zablokowane
            else
                odwiedzone[i][j] = 0;//pole dostêpne

            if (plansza[i][j] == -1)//ustawienie pola pocz¹tkowego
            {
                start.wiersz = i;
                start.kolumna = j;
            }
        }
    }
    queue<elementKolejki> kolejka;
    kolejka.push();
    odwiedzone[start.wiersz][start.kolumna] = 1;
    while (!kolejka.empty())
    {
        pole p = kolejka.front();
        kolejka.pop();

        if (plansza[p.wiersz][p.kolumna] == 2)   //zwrót najkrótszej drogi w momencie napotkania szukanego pola
        {
            //std::cout << "Rozmiar kolejki = " << poprzednie.size() << std::endl;
            //std::cout << "Rozmiar kolejki = " << kolejka.size() << std::endl;
            return p.odleglosc;
        }

        if (p.wiersz - 1 >= 0 && odwiedzone[p.wiersz - 1][p.kolumna] == 0)//odwiedzanie pola wy¿ej
        {
            kolejka.push(pole(p.wiersz - 1, p.kolumna, p.odleglosc + 1));
            odwiedzone[p.wiersz - 1][p.kolumna] = 1;
        }

        if (p.wiersz + 1 < m && odwiedzone[p.wiersz + 1][p.kolumna] == 0)//odwiedzanie pola ni¿ej
        {
            kolejka.push(pole(p.wiersz + 1, p.kolumna, p.odleglosc + 1));
            odwiedzone[p.wiersz + 1][p.kolumna] = 1;
        }

        if (p.kolumna - 1 >= 0 && odwiedzone[p.wiersz][p.kolumna - 1] == 0)//odwiedzanie pola po lewej
        {
            kolejka.push(pole(p.wiersz, p.kolumna - 1, p.odleglosc + 1));
            odwiedzone[p.wiersz][p.kolumna - 1] = 1;
        }

        if (p.kolumna + 1 < n && odwiedzone[p.wiersz][p.kolumna + 1] == 0)//odwiedzanie pola po prawej
        {
            kolejka.push(pole(p.wiersz, p.kolumna + 1, p.odleglosc + 1));
            odwiedzone[p.wiersz][p.kolumna + 1] = 1;
        }
    }

    return -1;
}
*/