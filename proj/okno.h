#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include"algorytm.h"
#include<math.h>
#include<string>
/*#define N 30    
#define M 30*/
class okno
{
public:
    //okno(int szerokosc, int wysokosc);
    okno();
    ~okno();

    bool oknoOtwarte();                 //metoda zwracaj�ca stan okna
    void rysuj();                       //metoda rysuj�ca i wy�wietlaj�ca elementy w oknie
    void aktualizuj();                  //metoda do obs�ugi zdarze�

private:
    //zmienne biblioteki SFML - okno oraz elementy interfejsu
    sf::RenderWindow* oknoGry;
    sf::Event zdarzenie;
    sf::Font czcionka;
    sf::Text gornyPasek;
    sf::Text wynikTxt;
    sf::Text koniecTxt;
    sf::Text krokiTxt;
    sf::Text kroki2Txt;
    sf::Text instrukcja;
    sf::Text latwyTxt;
    sf::Text normalnyTxt;
    sf::Text trudnyTxt;
    sf::RectangleShape latwy;
    sf::RectangleShape normalny;
    sf::RectangleShape trudny;
    sf::RectangleShape koniecTlo;
    sf::RectangleShape koniecTlo2;

    sf::Text szerokoscWczytaj;
    sf::Text wysokoscWczytaj;
    sf::Text szansaWczytaj;
    sf::Text generujTxt;
    sf::Text ustawieniaTxt;
    sf::Text menuTxt;
    sf::Text rozwiazanieTxt;
    sf::Text edytorTxt;
    sf::Text poziomEdytoraTxt;
    sf::Text EdytorGenerujTxt;
    sf::Text ostrzezenieEdytor;
    sf::Text EdytorInstrukcja1;
    sf::Text EdytorInstrukcja2;
    sf::RectangleShape szerokoscPoleTxt;
    sf::RectangleShape wysokoscPoleTxt;
    sf::RectangleShape szansaPoleTxt;
    sf::RectangleShape guzikMenu;
    sf::RectangleShape guzikGeneruj;
    sf::RectangleShape poleKolor;
    sf::RectangleShape poleKolorBialy;
    sf::RectangleShape guzikRozwiazanie;
    sf::RectangleShape guzikEdytor;
    sf::RectangleShape guzikPoziomEdytora;
    sf::RectangleShape guzikEdytoraGeneruj;
        
    sf::RectangleShape kwadratGracz;    //objekt kwadratu gracza
    std::vector<std::vector<sf::RectangleShape>> kwadraty;  //tablica 2d kwadrat�w planszy
    sf::Vector2i pozycjaGracz;          //wektor pozycji gracza do por�wnywania z tablicami stan�w p�l
    sf::Vector2f pozycjaKursor;         //wektor pozycji kursora myszki do klikania w guziki

    int wynik;                          //bie��cy wynik - liczba wykonanych krok�w
    int oczekiwanyWynik;                //najkr�tsza droga w labiryncie obliczona algorytmem przeszukiwania wszerz

    int kroki;                          //zmienne do ustawiania poziomu trudno�ci tworzonej planszy
    float szansaCzarny;                 //

    bool koniecGry;                     //zmienna do zarz�dzania stanem gry
    bool menu;
    bool szerokoscWpisz;
    bool wysokoscWpisz;
    bool szansaWpisz;
    bool sprawdzanie;
    bool stopRuch;
    bool malowanie;
    bool mazanie;
    bool edytor;
    bool rozw;
    bool pozEdytora;
    bool wstawianieStart;

    int n;      //wysoko��
    int m;      //szeroko��
    float szansa;
    float skala;  //rozmiar kwadratu na podstawie wysoko�ci i szeroko�ci planszy
    int kolor;

    std::vector<std::vector<int>> czarne;   //tablice przechowuj�ce stan poszczeg�lnych p�l planszy
    std::vector<std::vector<int>> odwiedzone;                                   

    std::string daneN;
    std::string daneM;
    std::string daneSzansa;

    algorytm bfs;                       //objekt klasy algorytm do sprawdzania czy wylosowana plansza spe�nia warunki poziomu trudno�ci

    std::vector<int> ruchy;

    void resetZmienne();                //metoda zeruj�ca zmienne
    void tworzenieOkna();               //metoda tworz�ca okno
    void tworzeniePlanszy();            //metoda losuj�ca plansz�
    void kolorowaniePlanszy();          //metoda ustawiaj�ca kolor p�l planszy
    void restart();                     //metoda losuj�ca nowy poziom
    void optymalnaDroga();
    void PustyLabirynt();
    bool sczytajKolory();
    void resetWektory();
    void poziomEdytora();
};

