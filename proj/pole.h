#pragma once
class pole			//klasa przechowuj¹ca koordynaty i odleg³oœæ obiektu do u¿ycia w kolejce w algorytmie
{
public:
	int wiersz;
	int kolumna;
	int odleglosc;
	pole(int w, int k, int o) :wiersz(w), kolumna(k), odleglosc(o) {};
};

