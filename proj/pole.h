#pragma once
class pole			//klasa przechowuj�ca koordynaty i odleg�o�� obiektu do u�ycia w kolejce w algorytmie
{
public:
	int wiersz;
	int kolumna;
	int odleglosc;
	pole(int w, int k, int o) :wiersz(w), kolumna(k), odleglosc(o) {};
};

