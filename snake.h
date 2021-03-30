//Radosław Łada
#include <iostream>
#include <vector> //wąż jest stworzony z wektorow
#include <ncurses.h> 
#include <cstdlib> //generator losowych liczb
#include <unistd.h> //usleep - delay na macos
#ifndef SNAKE_H //zapobiega przypadkowej redefinicji
#define SNAKE_H

struct snakepart{ //struktura odpowiadająca za kawałki węża
    int x,y;
    snakepart(int col, int row); //konstruktor nr1
    snakepart(); // konstruktor nr2, pusty ponieważ ustawia wartości zero w 'x' i 'y'
};

class snakeclass{
    int points, del, maxwidth, maxheight; //punkty, delay, maks szerokość, maks wysokość
    char direction, partchar, oldalchar, foo; //kierunek, partchar=kawałek węża, oldalchar=krawędź gry, foo=food,
    bool get; //true w momencie zjedzenia przez węża pokarmu
    snakepart food; //lokalizacja jedzenia
    std::vector<snakepart> snake; //wektor przechowuje wszystkie kawałki węża

    void putfood(); //funkcja odpowiadająca za pozycje jedzenia
    bool collision(); //jeśli dojdzie do kolizji, funkja zmienia wartość bool get na true
    void movesnake(); //odpowiada za poruszanie węża
    public:
    snakeclass(); //konstruktor
    ~snakeclass(); //destruktor
    void start(); //funkja startująca gre
};


#endif //koniec programu