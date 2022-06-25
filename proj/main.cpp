#include"okno.h"

int main()
{   
    okno oknoGry;

    while (oknoGry.oknoOtwarte())
    {
        oknoGry.aktualizuj();
        oknoGry.rysuj();
    }

    return 0;
}