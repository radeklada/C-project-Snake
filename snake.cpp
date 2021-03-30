//Radosław Łada
#include "snake.h" //cudzysłow ponieważ snkae.h znajduje się w tym samym folderze 

snakepart::snakepart(int col, int row){
    x=col; //wspołrzędne
    y=row;
}

snakepart:: snakepart(){
    x=0;
    y=0;
}

snakeclass::snakeclass(){
    initscr(); //inicjalizacja ekranu w konstruktorze ponieważ będzie użyta w pierwszej kolejności
    nodelay(stdscr,true); //getch nie czeka na naciśnięcie przycisku
    keypad(stdscr,true); //inicjalizacja klawiatury
    noecho(); //przyciski nie wyświetlają się
    curs_set(0); //niewidoczny kursor
    getmaxyx(stdscr,maxheight, maxwidth); //ustala wysokość i szerokość gry
    // inicjalizacja wariacji:
    partchar='x'; //znak z ktorego zbudowany jest wąż
    oldalchar=(char)219; // znak z ktorego zbudowana jest krawędź gry
    foo='*'; //znak pokarmu
    food.x=0; //pozycja jedzenia
    food.y=0;
    for(int i=0; i<5; i++) snake.push_back(snakepart(40+i,10)); //początkowa pozycja węża
    points=0; //punkty
    del=110000; //w mikrosekundach
    get=false; //fałsz do momentu zjedzenia pokarmu
    direction='l'; //początkowy kierunek
    srand(time(0)); //generator losowych liczb
    putfood(); //pozycja jedzenia
    for(int i=0; i<maxwidth-1; i++){ //gorna krawędź
        move(0,i);
        addch(oldalchar);
    }
    for(int i=0; i<maxwidth-1; i++){ //dolna krawędź
        move(maxheight-2,i);
        addch(oldalchar);
    }
    for(int i=0; i<maxheight-1; i++){ //lewa krawędź
        move(i,0);
        addch(oldalchar);
    }
    for(int i=0; i<maxheight-1; i++){ //prawa krawędź
        move(i,maxwidth-2);
        addch(oldalchar);
    }
    for(int i=0; i<snake.size(); i++){ //wyświetla węża na ekranie
        move(snake[i].y, snake[i].x);
        addch(partchar);
    }
    move(maxheight-1,0); //zmiana pozycji
    printw("%d",points); //wyświetlenie punktow
    move(food.y,food.x); //wyświetlenie jedzenia
    addch(foo);
    refresh(); //odświerzenie ekranu
}

snakeclass::~snakeclass(){ //dzięki temu gra się od razu nie wyłączy
    nodelay(stdscr,false);
    getch();
    endwin();
}

void snakeclass::putfood(){ //pozycja jedzenia
    while(1){ //nieskończona pętla do momentu kolizji węża z pokarmem
        int tmpx=rand()%maxwidth+1; //randomowa pozycja, bez krawędzi
        int tmpy=rand()%maxheight+1;
        for(int i=0; i<snake.size(); i++) if(snake[i].x==tmpx && snake[i].y==tmpy) continue; //jeśli warunek się sprawdzi, dzięki continue, wraca na początke funkcji, do momentu ustawienia jedzenia poza pozycją węża
        if(tmpx>=maxwidth-2 || tmpy>=maxheight-3) continue; //jw tylko, że zależy od krawędzi
        food.x=tmpx; //ustaweinie wartości
        food.y=tmpy;
        break; //wyjście z pętli
    }
    move(food.y,food.x); //zmiana pozycji
    addch(foo); //znak
    refresh(); //odświerzenie
}

bool snakeclass::collision(){
    if(snake[0].x==0 || snake[0].x==maxwidth-1 || snake[0].y==0 || snake[0].y==maxheight-2) return true; // sprawdza kolizje z krawędziami

    for(int i=2; i<snake.size(); i++) if(snake[0].x==snake[i].x && snake[i].y==snake[0].y) return true; //kolizja węża z samym sobą, sprawdza czy jakieś wartości ciała węża się powtarzają

    if(snake[0].x==food.x && snake[0].y==food.y){ //sprawdza kolizje z jedzeniem
        get=true; //kolizja z pokarmem
        putfood(); //zmiana pozycji pokarmu
        points+=10; //dodaje punkty
        move(maxheight-1,0); //zmienia pozycje znaku
        printw("%d",points); //wyświetla punkty
        if((points%100)==0) del-=10000; //co 100pkt, wąż przyśpiesza
    }else get=false; //brak kolizji z pokarmem
    return false;
}

void snakeclass:: movesnake(){ //funkja poruszania się węża
    int tmp=getch();
    switch(tmp){ //ustawienie przyciskow służących do poruszania się
        case KEY_LEFT:
            if(direction!='r') direction='l';
            break;
        case KEY_UP:
            if(direction!='d') direction='u';
            break;
        case KEY_DOWN:
            if(direction!='u') direction='d';
            break;
        case KEY_RIGHT:
            if(direction!='l') direction='r';
            break;
        case KEY_BACKSPACE: //wyjście z gry
            direction='q';
            break;
    }
    if(!get){ //dodaje znak do węża po zjedzeniu pokarmu
        move(snake[snake.size()-1].y, snake[snake.size()-1].x);
        addch(' ');
        refresh();
        snake.pop_back();
    }
    if(direction=='l') snake.insert(snake.begin(),snakepart(snake[0].x-1, snake[0].y)); //ruch węża
    else if (direction=='r') snake.insert(snake.begin(),snakepart(snake[0].x+1, snake[0].y));
    else if (direction=='u') snake.insert(snake.begin(),snakepart(snake[0].x, snake[0].y-1));
    else if (direction=='d') snake.insert(snake.begin(),snakepart(snake[0].x, snake[0].y+1));

    move(snake[0].y, snake[0].x);
    addch(partchar);
    refresh();
}

void snakeclass::start(){ //działanie gry
    while(1){ //nieskończona pętla
        if(collision()){ //jesli kolizja, to koneiec gry
            move(maxwidth/2,maxheight/2);
            printw("game over");
            break;
        }
        movesnake();
        if(direction=='q') break;
        usleep(del);
    }
}