#pragma once
class pole			//klasa przechowująca koordynaty i odległość obiektu do użycia w kolejce w algorytmie
{
public:
	int wiersz;
	int kolumna;
	int odleglosc;
	pole(int w, int k, int o) :wiersz(w), kolumna(k), odleglosc(o) {};
};

