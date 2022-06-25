#include "okno.h"

//okno::okno(int szerokosc, int wysokosc):n(wysokosc),m(szerokosc)
okno::okno()
{
    daneN = "30";
    daneM = "30";
    daneSzansa = "50";
    
    n = 30;
    m = 30;
    szansa = 50;

    menu = true;
    edytor = false;
    rozw = true;
    kolor = 1;

    if (m > n)
        skala = 750.f / (float)m;
    else
        skala = 750.f / (float)n;
    kroki = sqrt(n*m)*2;                    //zmienne, które nie potrzebuj¹ resetowania
    szansaCzarny = 0.35f;                   //
    latwy.setFillColor(sf::Color::White);   //
    normalny.setFillColor(sf::Color::Red);  //
    trudny.setFillColor(sf::Color::White);  //
	srand(time(0));
    resetZmienne();
	tworzenieOkna();
    tworzeniePlanszy();
    kolorowaniePlanszy();
    oknoGry->setTitle("Labirynt");
}

void okno::restart()
{
    menu = false;
    koniecGry = false;
    stopRuch = false;
    edytor = false;
    pozEdytora = false;
   
    if (m > n)
        skala = 750.f / (float)m;
    else
        skala = 750.f / (float)n;

    resetZmienne();
    tworzeniePlanszy();
    kolorowaniePlanszy();
}

void okno::PustyLabirynt()
{
    menu = false;
    koniecGry = false;
    stopRuch = true;
    wstawianieStart = true;
    edytor = true;
    pozycjaGracz = sf::Vector2i(0, 0);
    resetWektory();
    if (m > n)
        skala = 750.f / (float)m;
    else
        skala = 750.f / (float)n;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            czarne[i][j] = 0;
            odwiedzone[i][j] = 0;
            kwadraty[i][j].setFillColor(sf::Color::White);
        }
    }
    kolorowaniePlanszy();
    odwiedzone[pozycjaGracz.x][pozycjaGracz.y] = 0;
    kwadratGracz.setPosition(pozycjaGracz.x * skala, 150.f + pozycjaGracz.y * skala); 
    
}

bool okno::sczytajKolory()
{
    int wyjscie=0, wejscie=0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (kwadraty[i][j].getFillColor() == sf::Color::White)
                czarne[i][j] = 0;
            if (kwadraty[i][j].getFillColor() == sf::Color::Black)
                czarne[i][j] = 1;
            if (kwadraty[i][j].getFillColor() == sf::Color::Magenta)
            {
                czarne[i][j] = 2;
                wyjscie++;
            }
            if (kwadraty[i][j].getFillColor() == sf::Color::Blue)
            {
                std::cout << "Wyjscie na szerokosci " << i << " i wysokosci" << j << std::endl;
                czarne[i][j] = -1;
                wejscie++;
            }
        }
    }
    if (wejscie >0 && wyjscie > 0)
        return true;
    else
        return false;
}

void okno::poziomEdytora()
{
    if (sczytajKolory())
    {
        menu = false;
        koniecGry = false;
        stopRuch = false;
        edytor = false;
        pozEdytora = true;
        sprawdzanie = true;
        rozw = true;

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (czarne[i][j] == -1)
                {
                    pozycjaGracz.x = i;
                    pozycjaGracz.y = j;
                    kwadratGracz.setPosition(pozycjaGracz.x * skala, 150.f + pozycjaGracz.y * skala);
                    break;
                }

            }
        }
        odwiedzone[pozycjaGracz.x][pozycjaGracz.y] = 1;
        kwadratGracz.setFillColor(sf::Color::Red);
        kwadratGracz.setOutlineThickness(1);
        bfs.m = m;
        bfs.n = n;
        oczekiwanyWynik = bfs.odlegloscMinimalna(czarne);
        if (oczekiwanyWynik == -1) 
        {
            edytor = true;
            stopRuch = true;
            sprawdzanie = true;
            ostrzezenieEdytor.setString(L"Niemo¿liwy labirynt");
        }
            
    }
    else
        ostrzezenieEdytor.setString(L"Brak wejœcia lub wyjœcia");

}

void okno::resetWektory()
{
    ruchy.clear();
    czarne.clear();
    czarne.resize(m, std::vector<int>(n));
    odwiedzone.clear();
    odwiedzone.resize(m, std::vector<int>(n));
    kwadraty.clear();
    kwadraty.resize(m, std::vector<sf::RectangleShape>(n));
}

void okno::optymalnaDroga()
{
    if (rozw == true)
    {
        sprawdzanie = false;
        stopRuch = true;
        bfs.rec(czarne, oczekiwanyWynik);

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                //std::cout <<  czarne[i][j] << " ";
                if (czarne[i][j] == 5 || czarne[i][j] == -1)
                {
                    kwadraty[i][j].setFillColor(sf::Color::Green);
                    
                }
                    
            }
            //std::cout << std::endl;
        }

        kwadratGracz.setFillColor(sf::Color(0, 0, 0, 0));
        kwadratGracz.setOutlineThickness(0);
        rozw = false;
    }
}

okno::~okno()
{
	delete oknoGry;
}

bool okno::oknoOtwarte()
{
	return oknoGry->isOpen();
}

void okno::rysuj()
{
    //oknoGry->clear(sf::Color(142, 142, 142));
    oknoGry->clear(sf::Color(63, 178, 255));
    for (int i = 0; i < m; i++)             //ustawianie koloru pól na niebieski jeœli zosta³y odwiedzone i rysowanie wszystkich pól planszy
    {
        for (int j = 0; j < n; j++)
        {
            if (odwiedzone[i][j] && sprawdzanie == true && edytor == false) kwadraty[i][j].setFillColor(sf::Color::Blue);
            if (menu==false) oknoGry->draw(kwadraty[i][j]);
        }
    }

    char pasek[50];                         //ustawianie tekstu w górnym pasku
    sprintf_s(pasek, 50, "Oczekiwany wynik to %d", oczekiwanyWynik);
    gornyPasek.setString(pasek);

    sprintf_s(pasek, 50, "Wykorzystane ruchy:%d", wynik);
    wynikTxt.setString(pasek);

    if (edytor == true)
    {
        oknoGry->draw(poleKolorBialy);
        oknoGry->draw(poleKolor);
        oknoGry->draw(instrukcja);
        oknoGry->draw(szansaPoleTxt);
        oknoGry->draw(guzikPoziomEdytora);
        oknoGry->draw(guzikEdytoraGeneruj);
        oknoGry->draw(szansaWczytaj);
        oknoGry->draw(poziomEdytoraTxt);
        oknoGry->draw(EdytorGenerujTxt);
        oknoGry->draw(EdytorInstrukcja1);
        oknoGry->draw(EdytorInstrukcja2);
        oknoGry->draw(ostrzezenieEdytor);
    }
    if (menu == false && edytor == false && pozEdytora == false)
    {
        oknoGry->draw(latwy);                   //rysowanie reszty kszta³tów w odpowiedniej kolejnoœci i wyœwietlenie wszystkiego w oknie
        oknoGry->draw(normalny);
        oknoGry->draw(trudny);
        oknoGry->draw(latwyTxt);
        oknoGry->draw(normalnyTxt);
        oknoGry->draw(trudnyTxt);
    }
    if (menu == false && edytor == false)
    {
        oknoGry->draw(kwadratGracz);
        oknoGry->draw(gornyPasek);
        oknoGry->draw(wynikTxt);
        oknoGry->draw(koniecTlo2);
        oknoGry->draw(koniecTlo);
        oknoGry->draw(koniecTxt);
        oknoGry->draw(krokiTxt);
        oknoGry->draw(kroki2Txt);
        oknoGry->draw(guzikRozwiazanie);
        oknoGry->draw(rozwiazanieTxt);
    }
    if(menu==false)
    {
        oknoGry->draw(guzikMenu);
        oknoGry->draw(ustawieniaTxt);
    }
    if(menu==true)
    {
        //std::cout << "MENU" << std::endl;
        oknoGry->draw(szerokoscPoleTxt);
        oknoGry->draw(wysokoscPoleTxt);
        oknoGry->draw(guzikGeneruj);
        oknoGry->draw(guzikEdytor);
        oknoGry->draw(generujTxt);
        oknoGry->draw(edytorTxt);
        oknoGry->draw(menuTxt);
        oknoGry->draw(szerokoscWczytaj);
        oknoGry->draw(wysokoscWczytaj);
    }
    oknoGry->display();
}

void okno::aktualizuj()                     //obs³uga wciœniêtych klawiszy, guzików oraz zmian w grze
{
    while (oknoGry->pollEvent(zdarzenie))
    {
        if (zdarzenie.type == sf::Event::TextEntered && szerokoscWpisz==true)
        {
            if (zdarzenie.text.unicode > 47 && zdarzenie.text.unicode < 58 && daneM.length() < 3)
                daneM += (char)zdarzenie.text.unicode;
            else if (zdarzenie.text.unicode == 8)
                daneM = daneM.substr(0, daneM.length() - 1);
        }
        if (zdarzenie.type == sf::Event::TextEntered && wysokoscWpisz == true)
        {
            if (zdarzenie.text.unicode > 47 && zdarzenie.text.unicode < 58 && daneN.length() < 3)
                daneN += (char)zdarzenie.text.unicode;
            else if (zdarzenie.text.unicode == 8)
                daneN = daneN.substr(0, daneN.length() - 1);
        }
        if (zdarzenie.type == sf::Event::TextEntered && szansaWpisz == true)
        {
            if (zdarzenie.text.unicode > 47 && zdarzenie.text.unicode < 58 && daneSzansa.length() < 3)
                daneSzansa += (char)zdarzenie.text.unicode;
            else if (zdarzenie.text.unicode == 8)
                daneSzansa = daneSzansa.substr(0, daneSzansa.length() - 1);
        }
        if (zdarzenie.type == sf::Event::MouseMoved)
        {
            pozycjaKursor.x = zdarzenie.mouseMove.x;
            pozycjaKursor.y = zdarzenie.mouseMove.y;
            //std::cout << pozycjaKursor.x << "  " << pozycjaKursor.y << std::endl;
            //std::cout << "limit x: " << m * skala << std::endl;
            //std::cout << "limit y: " << n * skala << std::endl;


            if(malowanie == true && pozycjaKursor.x >= 0 && pozycjaKursor.x <= m * skala-1 && pozycjaKursor.y >= 150 && pozycjaKursor.y <= 150 + n * skala)
            {
                if (kolor == 1)
                    kwadraty[(int)(pozycjaKursor.x / skala)][(int)((pozycjaKursor.y - 150) / skala)].setFillColor(sf::Color::Black);
                if (kolor == 2)
                    kwadraty[(int)(pozycjaKursor.x / skala)][(int)((pozycjaKursor.y - 150) / skala)].setFillColor(sf::Color::Magenta);
                /*if (kolor == 3)
                    kwadraty[(int)(pozycjaKursor.x / skala)][(int)((pozycjaKursor.y - 150) / skala)].setFillColor(sf::Color::Blue);*/
            }
            if(mazanie == true && pozycjaKursor.x >= 0 && pozycjaKursor.x <= m * skala-1 && pozycjaKursor.y >= 150 && pozycjaKursor.y <= 150 + n * skala)
                kwadraty[(int)(pozycjaKursor.x / skala)][(int)((pozycjaKursor.y - 150) / skala)].setFillColor(sf::Color::White);
                
            //test podswietlania
          // if(pozycjaKursor.x >= 0 && pozycjaKursor.x <= 750 && pozycjaKursor.y >= 150 && pozycjaKursor.y <= 900)
           //     kwadraty[(int)(pozycjaKursor.x / skala)][(int)((pozycjaKursor.y - 150) / skala)].setFillColor(sf::Color::Cyan);
            
        }
        if (zdarzenie.type == sf::Event::MouseButtonReleased)
        {
            if (zdarzenie.mouseButton.button == sf::Mouse::Left)
                malowanie = false;
            if (zdarzenie.mouseButton.button == sf::Mouse::Right)
                mazanie = false;
        }
        if (zdarzenie.type == sf::Event::MouseButtonPressed)
        {
            if (zdarzenie.mouseButton.button == sf::Mouse::Right)
            {
                if (pozycjaKursor.x >= 0 && pozycjaKursor.x <= (int)(m*skala) && pozycjaKursor.y >= 150 && pozycjaKursor.y <= (int)(150 + n * skala) && edytor == true)
                    mazanie = true;
            }
            if (mazanie == true)
                kwadraty[(int)(pozycjaKursor.x / skala)][(int)((pozycjaKursor.y - 150) / skala)].setFillColor(sf::Color::White);
            if (zdarzenie.mouseButton.button == sf::Mouse::Left)
            {
                if (pozycjaKursor.x >= 0 && pozycjaKursor.x <= m*skala && pozycjaKursor.y >= 150 && pozycjaKursor.y <= 150 + n*skala && edytor == true)
                    malowanie = true;
                if (malowanie == true)
                {
                    if (kolor == 1)
                        kwadraty[(int)(pozycjaKursor.x / skala)][(int)((pozycjaKursor.y - 150) / skala)].setFillColor(sf::Color::Black);
                    if (kolor == 2)
                        kwadraty[(int)(pozycjaKursor.x / skala)][(int)((pozycjaKursor.y - 150) / skala)].setFillColor(sf::Color::Magenta);
                    if (kolor == 3 && wstawianieStart == true)
                    {
                        kwadraty[(int)(pozycjaKursor.x / skala)][(int)((pozycjaKursor.y - 150) / skala)].setFillColor(sf::Color::Blue);
                        wstawianieStart = false;
                    }
                        
                }
                if (latwy.getGlobalBounds().contains(pozycjaKursor) && menu == false && edytor == false)
                {
                    latwy.setFillColor(sf::Color::Red);
                    normalny.setFillColor(sf::Color::White);
                    trudny.setFillColor(sf::Color::White);
                    kroki = sqrt(3*n * m) * 1.5;
                    szansaCzarny = 0.15f;
                    restart();
                }
                if (normalny.getGlobalBounds().contains(pozycjaKursor) && menu == false && edytor == false)
                {
                    latwy.setFillColor(sf::Color::White);
                    normalny.setFillColor(sf::Color::Red);
                    trudny.setFillColor(sf::Color::White);
                    kroki = sqrt(3*n * m) * 2;
                    szansaCzarny = 0.35f;
                    restart();
                }
                if (trudny.getGlobalBounds().contains(pozycjaKursor) && menu == false && edytor == false)
                {
                    latwy.setFillColor(sf::Color::White);
                    normalny.setFillColor(sf::Color::White);
                    trudny.setFillColor(sf::Color::Red);
                    kroki = sqrt(3*n * m) * 2.5;
                    szansaCzarny = 0.4f;
                    restart();
                }
                if (guzikMenu.getGlobalBounds().contains(pozycjaKursor) && menu == false)
                {
                    menu = true;
                    edytor = false;
                }
                if (szerokoscPoleTxt.getGlobalBounds().contains(pozycjaKursor) && menu == true && edytor == false)
                {
                    daneM.clear();
                    std::cout << "szerokosc pole" << std::endl;
                    szerokoscWpisz = true;
                    wysokoscWpisz = false;
                }
                if (wysokoscPoleTxt.getGlobalBounds().contains(pozycjaKursor) && menu == true && edytor == false)
                {
                    daneN.clear();
                    std::cout << "wysokosc pole" << std::endl;
                    szerokoscWpisz = false;
                    wysokoscWpisz = true;
                }
                if (szansaPoleTxt.getGlobalBounds().contains(pozycjaKursor) && menu == false && edytor == true)
                {
                    daneSzansa.clear();
                    std::cout << "szansa pole" << std::endl;
                    szansaWpisz = true;
                }
                if (guzikGeneruj.getGlobalBounds().contains(pozycjaKursor) && menu == true && edytor == false)
                {
                    ostrzezenieEdytor.setString("");
                    std::cout << "GENERUJ" << std::endl;
                    if (daneN.length() == 0 || daneN == "00" || daneN == "000")
                        daneN = "30";
                    if (daneM.length() == 0 || daneN == "00" || daneN == "000")
                        daneM = "30";
                    n = std::stoi(daneN);
                    m = std::stoi(daneM);
                    if (n > 200)
                        n = 200;
                    if (n < 10)
                        n = 10;
                    if (m > 200)
                        m = 200;
                    if (m < 10)
                        m = 10;
                    szansaCzarny = 0.35f;
                    restart();
                    if(m == 21 && n == 37)
                    {
                        for (int i = 0; i < m; i++)
                        {
                            for (int j = 0; j < n; j++)
                            {
                                if(kwadraty[i][j].getFillColor() != sf::Color::Black)
                                    kwadraty[i][j].setFillColor(sf::Color::Yellow);
                            }
                        }
                    }
                    menu = false;
                }
                if (poleKolor.getGlobalBounds().contains(pozycjaKursor) && menu == false && edytor == true)
                {
                    kolor++;
                    if (kolor > 3)
                        kolor = 1;
                }
                if (guzikRozwiazanie.getGlobalBounds().contains(pozycjaKursor) && menu == false && edytor == false)
                    optymalnaDroga();
                if (guzikEdytor.getGlobalBounds().contains(pozycjaKursor) && menu == true && edytor == false)
                {
                    if (daneN.length() == 0 || daneN == "00" || daneN == "000")
                        daneN = "30";
                    if (daneM.length() == 0 || daneN == "00" || daneN == "000")
                        daneM = "30";
                    n = std::stoi(daneN);
                    m = std::stoi(daneM);
                    if (n > 200)
                        n = 200;
                    if (n < 10)
                        n = 10;
                    if (m > 200)
                        m = 200;
                    if (m < 10)
                        m = 10;
                    edytor = true;
                    PustyLabirynt();
                    std::cout << m << " "<<n;
                    ostrzezenieEdytor.setString("");

                }
                if (guzikEdytoraGeneruj.getGlobalBounds().contains(pozycjaKursor) && menu == false && edytor == true)
                {
                    if (daneN.length() == 0 || daneN == "00" || daneN == "000")
                        daneN = "50";
                    szansa = std::stoi(daneSzansa);
                    if (szansa > 100)
                        szansa = 100;
                    if (szansa < 0)
                        szansa = 0;
                    szansa = szansa / 100;
                    for (int i = 0; i < m; i++)
                    {
                        for (int j = 0; j < n; j++)
                        {
                                kwadraty[i][j].setFillColor(sf::Color::White);
                                //std::cout << "random: " << std::rand() / (float)RAND_MAX << " SZANSA: " << szansa << std::endl;
                                if (std::rand() / (float)RAND_MAX < szansa)
                                    kwadraty[i][j].setFillColor(sf::Color::Black);
                        }
                    }
                    wstawianieStart = true;
                }
                if (guzikPoziomEdytora.getGlobalBounds().contains(pozycjaKursor) && menu == false && edytor == true)
                {
                    poziomEdytora();
                }
            }
        }
        if (zdarzenie.type == sf::Event::Closed)
            oknoGry->close();
        if (zdarzenie.type == sf::Event::KeyPressed)
        {
            switch (zdarzenie.key.code)
            {
            case sf::Keyboard::Up:
                if (pozycjaGracz.y != 0 &&  czarne[pozycjaGracz.x][pozycjaGracz.y - 1] != 1 && odwiedzone[pozycjaGracz.x][pozycjaGracz.y - 1] != 1 && koniecGry == false && menu == false && stopRuch == false)
                {
                    pozycjaGracz.y -= 1;
                    if (odwiedzone[pozycjaGracz.x][pozycjaGracz.y] == 0)
                        odwiedzone[pozycjaGracz.x][pozycjaGracz.y] = 1;
                    ruchy.push_back(1);

                }
                break;
            case sf::Keyboard::Down:
                if (pozycjaGracz.y != n - 1 &&  czarne[pozycjaGracz.x][pozycjaGracz.y + 1] != 1 && odwiedzone[pozycjaGracz.x][pozycjaGracz.y + 1] != 1 && koniecGry == false && menu == false && stopRuch == false)
                {
                    pozycjaGracz.y += 1;
                    if (odwiedzone[pozycjaGracz.x][pozycjaGracz.y] == 0)
                        odwiedzone[pozycjaGracz.x][pozycjaGracz.y] = 1;
                    ruchy.push_back(2);
                }
                break;
            case sf::Keyboard::Right:
                if (pozycjaGracz.x != m - 1 && czarne[pozycjaGracz.x + 1][pozycjaGracz.y] != 1 && odwiedzone[pozycjaGracz.x + 1][pozycjaGracz.y] != 1 && koniecGry == false && menu == false && stopRuch == false)
                {
                    pozycjaGracz.x += 1;
                    if (odwiedzone[pozycjaGracz.x][pozycjaGracz.y] == 0)
                        odwiedzone[pozycjaGracz.x][pozycjaGracz.y] = 1;
                    ruchy.push_back(3);
                }
                break;
            case sf::Keyboard::Left:
                if (pozycjaGracz.x != 0 && czarne[pozycjaGracz.x - 1][pozycjaGracz.y] != 1 && odwiedzone[pozycjaGracz.x - 1][pozycjaGracz.y] != 1 && koniecGry == false && menu == false && stopRuch == false)
                {
                    pozycjaGracz.x -= 1;
                    if (odwiedzone[pozycjaGracz.x][pozycjaGracz.y] == 0)
                        odwiedzone[pozycjaGracz.x][pozycjaGracz.y] = 1;
                    ruchy.push_back(4);
                }
                break;
            case sf::Keyboard::Q:
                oknoGry->close();
                break;
            case sf::Keyboard::Z:
                /*while (!ruchy.empty()) {
                    std::cout << " " << ruchy.front();
                    ruchy.pop();
                }*/
                if (!ruchy.empty() && koniecGry==false && menu==false)
                {
                    int z = ruchy.back();
                    ruchy.pop_back();
                    switch (z)
                    {
                    case 1:
                        std::cout << "dol" << std::endl;
                        odwiedzone[pozycjaGracz.x][pozycjaGracz.y] = 0;
                        pozycjaGracz.y += 1;
                        
                        kwadraty[pozycjaGracz.x][pozycjaGracz.y-1].setFillColor(sf::Color::White);
                        break;
                    case 2:
                        std::cout << "gora" << std::endl;
                        odwiedzone[pozycjaGracz.x][pozycjaGracz.y] = 0;
                        pozycjaGracz.y -= 1;
                        
                        kwadraty[pozycjaGracz.x][pozycjaGracz.y+1].setFillColor(sf::Color::White);
                        break;
                    case 3:
                        std::cout << "lewo" << std::endl;
                        odwiedzone[pozycjaGracz.x][pozycjaGracz.y] = 0;
                        pozycjaGracz.x -= 1;
                        
                        kwadraty[pozycjaGracz.x+1][pozycjaGracz.y].setFillColor(sf::Color::White);
                        break;
                    case 4:
                        std::cout << "prawo" << std::endl;
                        odwiedzone[pozycjaGracz.x][pozycjaGracz.y] = 0;
                        pozycjaGracz.x += 1;
                        
                        kwadraty[pozycjaGracz.x-1][pozycjaGracz.y].setFillColor(sf::Color::White);
                        break;
                    }
                }
                break;
            /*case sf::Keyboard::Escape:
                if (menu == false)
                    menu = true;
                else
                    menu = false;
                std::cout << menu << std::endl;
                break;*/
            }
        }
    }

    //kwadratGracz.setPosition(pozycjaGracz.x * 25.f, 150.f + pozycjaGracz.y * 25.f); //aktualizacja pozycji kwadratu gracza na podstawie jego koordynatów
    kwadratGracz.setPosition(pozycjaGracz.x * skala, 150.f + pozycjaGracz.y * skala); //aktualizacja pozycji kwadratu gracza na podstawie jego koordynatów

    wynik = -1;                             //zliczanie liczby odwiedzonych pól
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            wynik += odwiedzone[i][j];
        }
    }

    if (czarne[pozycjaGracz.x][pozycjaGracz.y]==2)            //sprawdzenie czy gracz ukoñczy³ planszê
        koniecGry = true;
    if (koniecGry == true && sprawdzanie == true && oczekiwanyWynik!=wynik)
    {
        sprawdzanie = false;

        bfs.rec(czarne, oczekiwanyWynik);

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                //std::cout << czarne[i][j] << " ";
                if (czarne[i][j] == 5 || czarne[i][j] == -1) {
                    kwadraty[i][j].setFillColor(sf::Color::Green);
                    if (odwiedzone[i][j] == 1)
                        kwadraty[i][j].setFillColor(sf::Color::Cyan);
                }
            }
            //std::cout << std::endl;
        }
    }
    if (koniecGry == true)                  //ustawienie okna wygranej/przegranej kiedy gra siê skoñczy³a
    {
        koniecTlo.setPosition(5 * 25.f, 150.f + 10 * 25.f);
        koniecTlo.setOutlineThickness(4.f);
        koniecTlo.setOutlineColor(sf::Color::Black);
        koniecTlo.setFillColor(sf::Color(255,255,255,200));
        koniecTlo.setSize(sf::Vector2f(500.f, 250.f));

        koniecTlo2.setPosition(0, 0);
        koniecTlo2.setFillColor(sf::Color(0, 0, 0, 100));
        koniecTlo2.setSize(sf::Vector2f(750.f, 900.f));
        if (oczekiwanyWynik == wynik)
        {
            koniecTxt.setPosition(sf::Vector2f(195, 470));
            koniecTxt.setString("Gratulacje!");
        }
        else
        {
            koniecTxt.setString("Przegrana!");
            char zbedneKroki[3];
            sprintf_s(zbedneKroki, 3, "%d", wynik - oczekiwanyWynik);
            krokiTxt.setString(zbedneKroki);
            if(wynik-oczekiwanyWynik==1)
                kroki2Txt.setString(L"krok za du¿o");
            else if(wynik-oczekiwanyWynik>1 && wynik-oczekiwanyWynik<5)
                kroki2Txt.setString(L"kroki za du¿o");
            else
                kroki2Txt.setString(L"kroków za du¿o");
        }

    }
    else
    {
        koniecTlo.setPosition(5000,0);
        koniecTlo2.setPosition(5000, 0);
        koniecTxt.setString("");
        krokiTxt.setString("");
        kroki2Txt.setString("");
    }
    szerokoscWczytaj.setString(daneM);
    wysokoscWczytaj.setString(daneN);
    szansaWczytaj.setString(daneSzansa);

    if (kolor == 1)
    {
        poleKolor.setFillColor(sf::Color::Black);
        instrukcja.setString(L"Pole:\nZablokowane");
    }
    if (kolor == 2)
    {
        poleKolor.setFillColor(sf::Color::Magenta);
        instrukcja.setString(L"Pole:\nWyjœcia");
    }   
    if (kolor == 3)
    {
        poleKolor.setFillColor(sf::Color::Blue);
        instrukcja.setString(L"Pole:\nWejœcia");
    }
    if(rozw == false)
        guzikRozwiazanie.setFillColor(sf::Color::Green);
    else
        guzikRozwiazanie.setFillColor(sf::Color::White);
}

void okno::resetZmienne()                   //ustawienia elementów interfejsu oraz zerowanie stanu gry i tablic stanów pól planszy
{
    czcionka.loadFromFile("Anonymous_Pro.ttf");

	gornyPasek.setPosition(sf::Vector2f(10, 5));
	gornyPasek.setFillColor(sf::Color::Black);
	gornyPasek.setCharacterSize(25);
	gornyPasek.setFont(czcionka);
    

	wynikTxt.setPosition(sf::Vector2f(440, 5));
	wynikTxt.setFillColor(sf::Color::Black);
	wynikTxt.setCharacterSize(25);
	wynikTxt.setFont(czcionka);

    koniecTxt.setPosition(sf::Vector2f(210, 430));
    koniecTxt.setFillColor(sf::Color::Black);
    koniecTxt.setCharacterSize(65);
    koniecTxt.setFont(czcionka);

    krokiTxt.setPosition(sf::Vector2f(230, 512));
    krokiTxt.setFillColor(sf::Color::Black);
    krokiTxt.setCharacterSize(35);
    krokiTxt.setFont(czcionka);

    kroki2Txt.setPosition(sf::Vector2f(275, 512));
    kroki2Txt.setFillColor(sf::Color::Black);
    kroki2Txt.setCharacterSize(35);
    kroki2Txt.setFont(czcionka);

    instrukcja.setPosition(sf::Vector2f(175, 50));
    instrukcja.setFillColor(sf::Color::Black);
    instrukcja.setCharacterSize(20);
    instrukcja.setFont(czcionka);

    latwy.setPosition(sf::Vector2f(50, 80));
    latwy.setOutlineThickness(1.f);
    latwy.setOutlineColor(sf::Color::Black);    
    latwy.setSize(sf::Vector2f(150.f, 50.f));
    latwyTxt.setPosition(sf::Vector2f(90, 85));
    latwyTxt.setFillColor(sf::Color::Black);
    latwyTxt.setCharacterSize(25);
    latwyTxt.setFont(czcionka);
    latwyTxt.setString(L"£atwy");

    normalny.setPosition(sf::Vector2f(300, 80));
    normalny.setOutlineThickness(1.f);
    normalny.setOutlineColor(sf::Color::Black);
    normalny.setSize(sf::Vector2f(150.f, 50.f));
    normalnyTxt.setPosition(sf::Vector2f(320, 85));
    normalnyTxt.setFillColor(sf::Color::Black);
    normalnyTxt.setCharacterSize(25);
    normalnyTxt.setFont(czcionka);
    normalnyTxt.setString(L"Normalny");

    trudny.setPosition(sf::Vector2f(550, 80));
    trudny.setOutlineThickness(1.f);
    trudny.setOutlineColor(sf::Color::Black);
    trudny.setSize(sf::Vector2f(150.f, 50.f));
    trudnyTxt.setPosition(sf::Vector2f(585, 85));
    trudnyTxt.setFillColor(sf::Color::Black);
    trudnyTxt.setCharacterSize(25);
    trudnyTxt.setFont(czcionka);
    trudnyTxt.setString(L"Trudny");

    menuTxt.setPosition(sf::Vector2f(45,125));
    menuTxt.setFillColor(sf::Color::Black);
    menuTxt.setCharacterSize(25);
    menuTxt.setFont(czcionka);
    menuTxt.setString(L"Ustaw szerokoœæ i wysokoœæ tworzonego labiryntu\n        (wartoœci z przedzia³u 10 - 200)");

    szerokoscPoleTxt.setPosition(sf::Vector2f(187.5, 210));
    szerokoscPoleTxt.setOutlineThickness(1.f);
    szerokoscPoleTxt.setOutlineColor(sf::Color::Black);
    szerokoscPoleTxt.setSize(sf::Vector2f(75.f, 50.f));

    wysokoscPoleTxt.setPosition(sf::Vector2f(487.5, 210));
    wysokoscPoleTxt.setOutlineThickness(1.f);
    wysokoscPoleTxt.setOutlineColor(sf::Color::Black);
    wysokoscPoleTxt.setSize(sf::Vector2f(75.f, 50.f));

    guzikMenu.setPosition(sf::Vector2f(337.5, 50));
    guzikMenu.setOutlineThickness(1.f);
    guzikMenu.setOutlineColor(sf::Color::Black);
    guzikMenu.setSize(sf::Vector2f(75.f, 20.f));
    ustawieniaTxt.setPosition(sf::Vector2f(340, 52.5));
    ustawieniaTxt.setFillColor(sf::Color::Black);
    ustawieniaTxt.setCharacterSize(12);
    ustawieniaTxt.setFont(czcionka);
    ustawieniaTxt.setString(L"Ustawienia");

    guzikGeneruj.setPosition(sf::Vector2f(300, 300));
    guzikGeneruj.setOutlineThickness(1.f);
    guzikGeneruj.setOutlineColor(sf::Color::Black);
    guzikGeneruj.setSize(sf::Vector2f(150.f, 50.f));

    generujTxt.setPosition(sf::Vector2f(340, 310));
    generujTxt.setFillColor(sf::Color::Black);
    generujTxt.setCharacterSize(25);
    generujTxt.setFont(czcionka);
    generujTxt.setString(L"Losuj");

    guzikEdytor.setPosition(sf::Vector2f(300, 400));
    guzikEdytor.setOutlineThickness(1.f);
    guzikEdytor.setOutlineColor(sf::Color::Black);
    guzikEdytor.setSize(sf::Vector2f(150.f, 50.f));

    edytorTxt.setPosition(sf::Vector2f(340, 410));
    edytorTxt.setFillColor(sf::Color::Black);
    edytorTxt.setCharacterSize(25);
    edytorTxt.setFont(czcionka);
    edytorTxt.setString(L"Edytor");
    
    szerokoscWczytaj.setPosition(sf::Vector2f(189, 205));
    szerokoscWczytaj.setFillColor(sf::Color::Black);
    szerokoscWczytaj.setCharacterSize(45);
    szerokoscWczytaj.setFont(czcionka);

    wysokoscWczytaj.setPosition(sf::Vector2f(487.5, 205));
    wysokoscWczytaj.setFillColor(sf::Color::Black);
    wysokoscWczytaj.setCharacterSize(45);
    wysokoscWczytaj.setFont(czcionka);
    
    poleKolor.setPosition(sf::Vector2f(50, 30));
    poleKolor.setOutlineThickness(1.f);
    poleKolor.setOutlineColor(sf::Color::Black);
    poleKolor.setSize(sf::Vector2f(100.f, 100.f));

    poleKolorBialy.setPosition(sf::Vector2f(65, 15));
    poleKolorBialy.setOutlineThickness(1.f);
    poleKolorBialy.setOutlineColor(sf::Color::Black);
    poleKolorBialy.setFillColor(sf::Color::White);
    poleKolorBialy.setSize(sf::Vector2f(100.f, 100.f));

    guzikRozwiazanie.setPosition(sf::Vector2f(337.5, 15));
    guzikRozwiazanie.setOutlineThickness(1.f);
    guzikRozwiazanie.setOutlineColor(sf::Color::Black);
    guzikRozwiazanie.setSize(sf::Vector2f(75.f, 20.f));
    rozwiazanieTxt.setPosition(sf::Vector2f(345, 17.5));
    rozwiazanieTxt.setFillColor(sf::Color::Black);
    rozwiazanieTxt.setCharacterSize(12);
    rozwiazanieTxt.setFont(czcionka);
    rozwiazanieTxt.setString(L" Rozwi¹¿");

    guzikPoziomEdytora.setPosition(sf::Vector2f(550, 80));
    guzikPoziomEdytora.setOutlineThickness(1.f);
    guzikPoziomEdytora.setOutlineColor(sf::Color::Black);
    guzikPoziomEdytora.setSize(sf::Vector2f(150.f, 50.f));
    poziomEdytoraTxt.setPosition(sf::Vector2f(585, 85));
    poziomEdytoraTxt.setFillColor(sf::Color::Black);
    poziomEdytoraTxt.setCharacterSize(25);
    poziomEdytoraTxt.setFont(czcionka);
    poziomEdytoraTxt.setString(L" Graj");

    guzikEdytoraGeneruj.setPosition(sf::Vector2f(450, 80));
    guzikEdytoraGeneruj.setOutlineThickness(1.f);
    guzikEdytoraGeneruj.setOutlineColor(sf::Color::Black);
    guzikEdytoraGeneruj.setSize(sf::Vector2f(75.f, 50.f));
    EdytorGenerujTxt.setPosition(sf::Vector2f(440, 85));
    EdytorGenerujTxt.setFillColor(sf::Color::Black);
    EdytorGenerujTxt.setCharacterSize(25);
    EdytorGenerujTxt.setFont(czcionka);
    EdytorGenerujTxt.setString(L" Losuj");

    szansaPoleTxt.setPosition(sf::Vector2f(337.5, 80));
    szansaPoleTxt.setOutlineThickness(1.f);
    szansaPoleTxt.setOutlineColor(sf::Color::Black);
    szansaPoleTxt.setSize(sf::Vector2f(75.f, 50.f));

    EdytorInstrukcja1.setPosition(sf::Vector2f(270, 125));
    EdytorInstrukcja1.setFillColor(sf::Color::Black);
    EdytorInstrukcja1.setCharacterSize(20);
    EdytorInstrukcja1.setFont(czcionka);
    EdytorInstrukcja1.setString(L"% zablokowanych pól");

    EdytorInstrukcja2.setPosition(sf::Vector2f(55, 55));
    EdytorInstrukcja2.setFillColor(sf::Color::White);
    EdytorInstrukcja2.setCharacterSize(12);
    EdytorInstrukcja2.setFont(czcionka);
    EdytorInstrukcja2.setString(L"kliknij tutaj\n aby zmieniæ\n  typ pola");

    szansaWczytaj.setPosition(sf::Vector2f(338.5, 75));
    szansaWczytaj.setFillColor(sf::Color::Black);
    szansaWczytaj.setCharacterSize(45);
    szansaWczytaj.setFont(czcionka);
    szansaWczytaj.setString("100");

    ostrzezenieEdytor.setPosition(sf::Vector2f(245, 15));
    ostrzezenieEdytor.setFillColor(sf::Color::Red);
    ostrzezenieEdytor.setCharacterSize(20);
    ostrzezenieEdytor.setFont(czcionka);

	pozycjaGracz = sf::Vector2i(0, 0);

    resetWektory();

    
    /*std::cout << "AKTUALNE N - " << n << " AKTUALNE M - " << m << std::endl;
    std::cout << "AKTUALNE rozmiar czarne - " << czarne.size() << std::endl;*/


    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            czarne[i][j] = 0;
            odwiedzone[i][j] = 0;
            kwadraty[i][j].setFillColor(sf::Color::White);
        }
    }

	koniecGry = false;
    sprawdzanie = true;
    rozw = true;
}

void okno::tworzenieOkna()
{
    oknoGry = new sf::RenderWindow(sf::VideoMode(25 * 30, 150 + 25 * 30), "Labirynt", sf::Style::Titlebar | sf::Style::Close);
    oknoGry->setFramerateLimit(30);
}

void okno::tworzeniePlanszy()
{
    int zabezpieczenie = 0;
    do
    {
        if (zabezpieczenie > 100)
        {
            kroki = sqrt(3 * n * m) * 2;
            szansaCzarny = 0.1f;
        }
        zabezpieczenie++;
        //std::memset(czarne, 0, sizeof(czarne)); //zerowanie tablicy z zablokowanymi polami
        
        for (size_t y = 0; y < czarne.size(); y++)
        {
            for (size_t x = 0; x < czarne[y].size(); x++)
            {
                czarne[y][x] = 0;
            }
        }

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                float x = abs(i - j);

                if (std::rand() / (float)RAND_MAX < (szansaCzarny + 0.001f * x))        
                {
                    czarne[i][j] = 1;         //blokowanie losowych pól tablicy
                }

            }
        }

    for (int i = std::rand() % m; i < m; i = std::rand()%m) //losowanie poprawnej pozycji pocz¹tkowej kwadratu gracza
    {
        if (czarne[i][0]==0)
        {
            pozycjaGracz.x = i;
            czarne[i][0] = -1;          //ustawienie pola pocz¹tkowego dla algorytmu
            break;
        }
    }
      
        for (int i = 0; i < m; i++)
        {
            if (!czarne[i][n - 1])
                czarne[i][n - 1] = 2;      //ustawianie szukanych pól dla algorytmu sprawdzaj¹cego
        }
        bfs.m = m;
        bfs.n = n;
        oczekiwanyWynik = bfs.odlegloscMinimalna(czarne); //obliczanie najkrótszej drogi (jeœli istnieje) w wylosowanej planszy
        std::cout << oczekiwanyWynik << std::endl;
    } while (oczekiwanyWynik == -1);
    //} while (oczekiwanyWynik < kroki);  //losowanie trwa dopóki nie zostanie wylosowana plansza o najkrótszej drodze zgodnej z 'poziomem trudnoœci'
    char tytul[20];
    sprintf_s(tytul, 20, "Labirynt %dx%d", m, n);
    oknoGry->setTitle(tytul);
}

void okno::kolorowaniePlanszy()
{
    for (int i = 0; i < m; i++)             //ustawianie pól planszy
    {
        for (int j = 0; j < n; j++)
        {
            //kwadraty[i][j].setPosition(i * 25.f, 150.f + j * 25.f);
            kwadraty[i][j].setPosition(i * skala, 150.f + j * skala);
            kwadraty[i][j].setOutlineThickness(1.f);
            kwadraty[i][j].setOutlineColor(sf::Color::Black);
            //kwadraty[i][j].setSize(sf::Vector2f(50.f, 25.f));
            kwadraty[i][j].setSize(sf::Vector2f(skala, skala));

            if (czarne[i][j] == 1)
                kwadraty[i][j].setFillColor(sf::Color::Black);      //pola zablokowane s¹ pokolorowane na czarno
        }
    }
    
    for (int i = 0; i < m; i++)
    {
        if(czarne[i][n-1]!=1 && edytor == false)
            kwadraty[i][n-1].setFillColor(sf::Color::Magenta);     //dolna krawêdŸ jest pokolorowana kolorem fuksji
    }

                                                                   //ustawienia kwadratu gracza
    odwiedzone[pozycjaGracz.x][pozycjaGracz.y] = 1;
    //kwadratGracz.setPosition(pozycjaGracz.x * 25.f, 150.f + pozycjaGracz.y * 25.f);
    kwadratGracz.setPosition(pozycjaGracz.x * skala, 150.f + pozycjaGracz.y * skala);
    kwadratGracz.setOutlineThickness(1.f);
    kwadratGracz.setOutlineColor(sf::Color::Black);
    kwadratGracz.setFillColor(sf::Color::Red);
    //kwadratGracz.setSize(sf::Vector2f(25.f, 25.f));
    kwadratGracz.setSize(sf::Vector2f(skala, skala));
}


