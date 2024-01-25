#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include <time.h>
using namespace sf;

int sz = 48;
int plansza[12][12]; // Plansza z ukrytymi minami i liczbami
int z_plansza[12][12]; // Plansza do klikania

const int M_pacxon = 35;
const int N_pacxon = 56;
int liczba_pol = 0;

int grid[M_pacxon][N_pacxon] = { 0 }; // Plansza gry
int ts = 18; // Rozmiar kafla

struct Przeciwnik
{
    int x, y, dx, dy;

    Przeciwnik()
    {
        x = y = 300;
        dx = 4 - rand() % 8;
        dy = 4 - rand() % 8;
    }

    // Funkcja odpowiedzialna za ruch przeciwnika
    void move()
    {
        x += dx; if (grid[y / ts][x / ts] == 1) { dx = -dx; x += dx; }
        y += dy; if (grid[y / ts][x / ts] == 1) { dy = -dy; y += dy; }
    }
};

// Funkcja odsłaniająca obszar gry
void drop(int y, int x)
{
    if (grid[y][x] == 0) grid[y][x] = -1;
    if (grid[y - 1][x] == 0) drop(y - 1, x);
    if (grid[y + 1][x] == 0) drop(y + 1, x);
    if (grid[y][x - 1] == 0) drop(y, x - 1);
    if (grid[y][x + 1] == 0) drop(y, x + 1);
}


int N_snake = 30, M_snake = 20; // Rozmiar planszy (liczba kafelków w poziomie i pionie)
int rozmiar = 24; // Rozmiar pojedynczego kafelka
int sz_snake = rozmiar * N_snake; // Szerokość okna
int w_snake = rozmiar * M_snake; // Wysokość okna

int dir, num = 4; // Kierunek ruchu węża (0 - w dół, 1 - w lewo, 2 - w prawo, 3 - w górę), liczba segmentów węża

struct Snake
{
    int x, y;
}  s[100]; // Struktura przechowująca segmenty węża

struct Fruit
{
    int x, y;
} f; // Struktura przechowująca położenie owocu

void Tick()
{
    for (int i = num; i > 0; --i)
    {
        s[i].x = s[i - 1].x; s[i].y = s[i - 1].y; // Aktualizacja pozycji segmentów węża
    }

    if (dir == 0) s[0].y += 1; // Ruch w dół
    if (dir == 1) s[0].x -= 1; // Ruch w lewo
    if (dir == 2) s[0].x += 1; // Ruch w prawo
    if (dir == 3) s[0].y -= 1; // Ruch w górę

    if ((s[0].x == f.x) && (s[0].y == f.y))
    {
        num++; // Zwiększenie liczby segmentów węża po zjedzeniu owocu
        f.x = rand() % N_snake; f.y = rand() % M_snake; // Przemieszczenie owocu na losowe miejsce na planszy
    }

    if (s[0].x > N_snake) s[0].x = 0;  if (s[0].x < 0) s[0].x = N_snake; // Sprawdzenie, czy wąż nie wyszedł poza granice planszy
    if (s[0].y > M_snake) s[0].y = 0;  if (s[0].y < 0) s[0].y = M_snake;

    for (int i = 1; i < num; i++)
        if (s[0].x == s[i].x && s[0].y == s[i].y)  num = i; // Sprawdzenie kolizji z samym sobą
}
std::vector<std::vector<int>> board = {
    {0, 0, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 0, 0},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 2, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1},
    {0, 0, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 0, 0}
};

const int N_samotnik = 7; // Liczba pól w rzędzie/kolumnie
const int WindowSize = 400;
const int CellSize = WindowSize / N_samotnik;
int NUMBER_OF_REDS = 0;
int ROW = 0;
int COLUMN = 0;
int ROW_1 = -1;
int COLUMN_1 = -1;
int ROW_2 = -1;
int COLUMN_2 = -1;

void drawCircles(sf::RenderWindow& window, const std::vector<std::vector<int>>& board) {
    for (int i = 0; i < N_samotnik; ++i) {
        for (int j = 0; j < N_samotnik; ++j) {
            if (board[i][j] == 1) {
                sf::CircleShape circle(CellSize / 2);
                circle.setPosition(i * CellSize, j * CellSize);
                circle.setFillColor(sf::Color::Black);
                window.draw(circle);
            }
            else if (board[i][j] == 2) {
                sf::CircleShape circle(CellSize / 2);
                circle.setPosition(i * CellSize, j * CellSize);
                circle.setFillColor(sf::Color::White);
                window.draw(circle);
            }
            else if (board[i][j] == 3) {
                sf::CircleShape circle(CellSize / 2);
                circle.setPosition(i * CellSize, j * CellSize);
                circle.setFillColor(sf::Color::Red);
                window.draw(circle);
            }
            // Nie rysuj nic dla 0
        }
    }
}

void handleMouseClick(sf::RenderWindow& window, const sf::Vector2i& mousePosition, std::vector<std::vector<int>>& board) {
    // Sprawdź, który okrąg został kliknięty
    for (int i = 0; i < N_samotnik; ++i) {
        for (int j = 0; j < N_samotnik; ++j) {
            sf::FloatRect circleBounds(i * CellSize, j * CellSize, CellSize, CellSize);
            if (NUMBER_OF_REDS > 2) {
                for (int i = 0; i < N_samotnik; ++i) {
                    for (int j = 0; j < N_samotnik; ++j) {
                        if (i == 3 and j == 3) {
                            board[i][j] = 2;
                        }
                        else if (board[i][j] != 0) {
                            board[i][j] = 1;
                        }
                    }
                }
                NUMBER_OF_REDS = 0;
                ROW = 0;
                COLUMN = 0;
            }
            if (circleBounds.contains(sf::Vector2f(mousePosition)) and board[i][j] != 3) {
                // Zmiana wartości w tablicy na
                NUMBER_OF_REDS++;
                if (NUMBER_OF_REDS == 1) {
                    ROW_1 = j;
                    COLUMN_1 = i;
                    cout << ROW_1 << " " << COLUMN_1 << endl;
                }
                if (NUMBER_OF_REDS == 2) {
                    ROW_2 = j;
                    COLUMN_2 = i;
                    cout << ROW_2 << " " << COLUMN_2 << endl;
                }
            }

            if (circleBounds.contains(sf::Vector2f(mousePosition))) {
                // Zmiana wartości w tablicy na 3
                board[i][j] = 3;
                ROW += j;
                COLUMN += i;
            }
            if (NUMBER_OF_REDS == 2) {
                board[(COLUMN_1 + COLUMN_2) / 2][(ROW_1 + ROW_2) / 2] = 2;
                board[COLUMN_1][ROW_1] = 2;
                board[COLUMN_2][ROW_2] = 1;
                ROW_1 = -1;
                COLUMN_1 = -1;
                ROW_2 = -1;
                COLUMN_2 = -1;
                NUMBER_OF_REDS = 0;
            }
        }
    }

    // Spróbuj zamienić okręgi miejscami, jeśli to możliwe

}



void main() {
    RenderWindow MENU(VideoMode(960, 720), "Main Menu", Style::Default);
    MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y, 0);


    while (MENU.isOpen())
    {
        Event event;
        while (MENU.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                MENU.close();
            }

            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Up)
                {
                    mainMenu.MoveUp();
                    break;
                }
                if (event.key.code == Keyboard::Down)
                {
                    mainMenu.MoveDown();
                    break;
                }
                if (event.key.code == Keyboard::Return) {
                    RenderWindow GAME_MENU(VideoMode(960, 720), "MENU GAME");
                    RenderWindow OPTIONS(VideoMode(960, 720), "OPTIONS");
                    RenderWindow ABOUT(VideoMode(960, 720), "ABOUT");
                    //RenderWindow Play(VideoMode(960, 720), "game_name");

                    int x = mainMenu.MainMenuPressed();
                    if (x == 0)
                    {   
                        MENU.close();
                        MainMenu gameMenu(GAME_MENU.getSize().x, GAME_MENU.getSize().y, 1);

                        while (GAME_MENU.isOpen())
                        {

                            Event aevent;
                            while (GAME_MENU.pollEvent(aevent)) {
                                if (aevent.type == Event::Closed) {
                                    GAME_MENU.close();
                                }
                                if (aevent.type == Event::KeyPressed)
                                {
                                    if (aevent.key.code == Keyboard::Escape)
                                    {
                                        GAME_MENU.close();
                                    }
                                }
                                if (aevent.type == Event::KeyReleased)
                                {
                                    if (aevent.key.code == Keyboard::Up)
                                    {
                                        gameMenu.MoveUp();
                                        break;
                                    }
                                    if (aevent.key.code == Keyboard::Down)
                                    {
                                        gameMenu.MoveDown();
                                        break;
                                    }

                                    int y = gameMenu.MainMenuPressed();
                                    if (y == 0) {
                                        srand(time(0));

                                        // Inicjalizacja okna gry
                                        RenderWindow app(VideoMode(600, 600), "Saper");

                           

                                        Texture t;
                                        t.loadFromFile("saper/tiles.jpg");
                                        Sprite s(t);

                                        // Inicjalizacja planszy z ukrytymi minami i liczbami
                                        for (int i = 1; i <= 10; i++)
                                            for (int j = 1; j <= 10; j++)
                                            {
                                                z_plansza[i][j] = 10; // 10 oznacza ukryte pole
                                                if (rand() % 5 == 0)
                                                    plansza[i][j] = 9; // 9 oznacza minę
                                                else
                                                    plansza[i][j] = 0;
                                            }

                                        // Obliczanie liczby min w otoczeniu każdego pola
                                        for (int i = 1; i <= 10; i++)
                                            for (int j = 1; j <= 10; j++)
                                            {
                                                int n = 0;
                                                if (plansza[i][j] == 9) continue;
                                                if (plansza[i + 1][j] == 9) n++;
                                                if (plansza[i][j + 1] == 9) n++;
                                                if (plansza[i - 1][j] == 9) n++;
                                                if (plansza[i][j - 1] == 9) n++;
                                                if (plansza[i + 1][j + 1] == 9) n++;
                                                if (plansza[i - 1][j - 1] == 9) n++;
                                                if (plansza[i - 1][j + 1] == 9) n++;
                                                if (plansza[i + 1][j - 1] == 9) n++;
                                                plansza[i][j] = n;
                                            }

                                        while (app.isOpen())
                                        {
                                            Vector2i pos = Mouse::getPosition(app);
                                            int x = pos.x / sz;
                                            int y = pos.y / sz;

                                            Event e;
                                            while (app.pollEvent(e))
                                            {
                                                if (e.type == Event::Closed)
                                                    app.close();

                                                if (e.type == Event::MouseButtonPressed)
                                                {
                                                    if (e.key.code == Mouse::Left)
                                                        z_plansza[x][y] = plansza[x][y];
                                                    else if (e.key.code == Mouse::Right)
                                                        z_plansza[x][y] = 11; // Oznaczenie flagą
                                                }
                                            }

                                            app.clear(Color::White);

                                            // Wyświetlanie planszy
                                            for (int i = 1; i <= 10; i++)
                                                for (int j = 1; j <= 10; j++)
                                                {
                                                    if (z_plansza[x][y] == 9)
                                                        z_plansza[i][j] = plansza[i][j];
                                                    s.setTextureRect(IntRect(z_plansza[i][j] * sz, 0, sz, sz));
                                                    s.setPosition(i * sz, j * sz);
                                                    app.draw(s);
                                                }

                                            app.display();
                                        }
                                    }
                                    if (y == 1) {
                                        srand(time(0));

                                        RenderWindow window(VideoMode(sz_snake, w_snake), "Snake"); // Inicjalizacja okna gry

                                        Texture t1, t2, t3; // Tekstury dla kafelka planszy i węża
                                        t1.loadFromFile("snake/grey.png");
                                        t2.loadFromFile("snake/dark_blue.png");
                                        t3.loadFromFile("snake/red.png");

                                        Sprite sprite1(t1); // Sprite dla kafelka planszy
                                        Sprite sprite2(t2); // Sprite dla segmentu węża
                                        Sprite fruit(t3);

                                        Clock clock; // Zegar do mierzenia czasu
                                        float timer = 0, delay = 0.1; // Zmienne do kontrolowania prędkości gry

                                        f.x = 10;
                                        f.y = 10;

                                        while (window.isOpen())
                                        {
                                            float time = clock.getElapsedTime().asSeconds(); // Pobranie czasu od ostatniego ticka
                                            clock.restart(); // Zresetowanie zegara
                                            timer += time;

                                            Event e;
                                            while (window.pollEvent(e))
                                            {
                                                if (e.type == Event::Closed)
                                                    window.close();
                                            }

                                            if (Keyboard::isKeyPressed(Keyboard::Left)) dir = 1; // Ustawienie kierunku ruchu węża na lewo
                                            if (Keyboard::isKeyPressed(Keyboard::Right)) dir = 2; // Ustawienie kierunku ruchu węża na prawo
                                            if (Keyboard::isKeyPressed(Keyboard::Up)) dir = 3; // Ustawienie kierunku ruchu węża w górę
                                            if (Keyboard::isKeyPressed(Keyboard::Down)) dir = 0; // Ustawienie kierunku ruchu węża w dół

                                            if (timer > delay) { timer = 0; Tick(); } // Wywołanie funkcji Tick z określoną częstotliwością

                                            ////// draw  ///////
                                            window.clear(); // Wyczyszczenie okna

                                            for (int i = 0; i < N_snake; i++)
                                                for (int j = 0; j < M_snake; j++)
                                                {
                                                    sprite1.setPosition(i * rozmiar, j * rozmiar);  window.draw(sprite1); // Rysowanie kafelków planszy
                                                }

                                            for (int i = 0; i < num; i++)
                                            {
                                                sprite2.setPosition(s[i].x * rozmiar, s[i].y * rozmiar);  window.draw(sprite2); // Rysowanie segmentów węża
                                            }

                                            fruit.setPosition(f.x * rozmiar, f.y * rozmiar);  window.draw(fruit); // Rysowanie owocu

                                            window.display(); // Wyświetlenie zawartości okna
                                        }

                                 
                                        
                                    }
                                    if (y == 2) {
                                        
                                        srand(time(0));

                                        RenderWindow window(VideoMode(N_pacxon* ts, M_pacxon* ts), "Pac-xon");
                                        window.setFramerateLimit(60);

                                        Texture t1, t2, t3, t4;
                                        t1.loadFromFile("pacxon/tiles.png");
                                        t2.loadFromFile("pacxon/gameover.png");
                                        t3.loadFromFile("pacxon/enemy.png");
                                        t4.loadFromFile("pacxon/youwin.png");

                                        Sprite sTile(t1), sGameover(t2), sPrzeciwnik(t3), sYouwin(t4);
                                        sGameover.setPosition(200, 300);
                                        sYouwin.setPosition(280, 200);
                                        sPrzeciwnik.setOrigin(20, 20);

                                        int liczba_przeciwnikow = 6;
                                        Przeciwnik przeciwnicy[10];

                                        bool Gra = true;
                                        int x = 0;
                                        int y = 0;
                                        int dx = 0;
                                        int dy = 0;
                                        float timer = 0;
                                        float delay = 0.07;
                                        Clock zegar;

                                        // Inicjalizacja planszy
                                        for (int i = 0; i < M_pacxon; i++)
                                            for (int j = 0; j < N_pacxon; j++)
                                                if (i == 0 || j == 0 || i == M_pacxon - 1 || j == N_pacxon - 1)
                                                    grid[i][j] = 1;

                                        while (window.isOpen())
                                        {
                                            float time = zegar.getElapsedTime().asSeconds();
                                            zegar.restart();
                                            timer += time;

                                            Event e;
                                            while (window.pollEvent(e))
                                            {
                                                if (e.type == Event::Closed)
                                                    window.close();

                                                // Obsługa klawisza Escape - restart gry
                                                if (e.type == Event::KeyPressed)
                                                    if (e.key.code == Keyboard::Escape)
                                                    {
                                                        for (int i = 1; i < M_pacxon - 1; i++)
                                                            for (int j = 1; j < N_pacxon - 1; j++)
                                                                grid[i][j] = 0;

                                                        x = 10;
                                                        y = 0;
                                                        Gra = true;
                                                    }
                                            }

                                            // Obsługa klawiszy ruchu
                                            if (Keyboard::isKeyPressed(Keyboard::Left)) { dx = -1; dy = 0; };
                                            if (Keyboard::isKeyPressed(Keyboard::Right)) { dx = 1; dy = 0; };
                                            if (Keyboard::isKeyPressed(Keyboard::Up)) { dx = 0; dy = -1; };
                                            if (Keyboard::isKeyPressed(Keyboard::Down)) { dx = 0; dy = 1; };

                                            if (!Gra) continue;

                                            // Aktualizacja pozycji gracza
                                            if (timer > delay)
                                            {
                                                x += dx;
                                                y += dy;

                                                if (x < 0)
                                                    x = 0;
                                                if (x > N_pacxon - 1)
                                                    x = N_pacxon - 1;
                                                if (y < 0)
                                                    y = 0;
                                                if (y > M_pacxon - 1)
                                                    y = M_pacxon - 1;

                                                if (grid[y][x] == 2) Gra = false;
                                                if (grid[y][x] == 0) grid[y][x] = 2;
                                                timer = 0;
                                            }

                                            // Aktualizacja pozycji przeciwników
                                            for (int i = 0; i < liczba_przeciwnikow; i++) przeciwnicy[i].move();

                                            // Sprawdzenie kolizji z przeszkodami
                                            if (grid[y][x] == 1)
                                            {
                                                dx = dy = 0;

                                                // Odsłonięcie obszaru gry
                                                for (int i = 0; i < liczba_przeciwnikow; i++)
                                                    drop(przeciwnicy[i].y / ts, przeciwnicy[i].x / ts);

                                                // Zresetowanie planszy
                                                for (int i = 0; i < M_pacxon; i++)
                                                    for (int j = 0; j < N_pacxon; j++) {

                                                        if (grid[i][j] == -1) grid[i][j] = 0;
                                                        else grid[i][j] = 1;
                                                        if (grid[i][j] == 1) {
                                                            liczba_pol += 1;
                                                        }
                                                    }
                                            }

                                            // Sprawdzenie kolizji z przeciwnikami
                                            for (int i = 0; i < liczba_przeciwnikow; i++)
                                                if (grid[przeciwnicy[i].y / ts][przeciwnicy[i].x / ts] == 2) Gra = false;

                                            ///////// Rysowanie ////////
                                            window.clear();

                                            for (int i = 0; i < M_pacxon; i++)
                                                for (int j = 0; j < N_pacxon; j++)
                                                {
                                                    if (grid[i][j] == 0) continue;
                                                    if (grid[i][j] == 1) sTile.setTextureRect(IntRect(0, 0, ts, ts));
                                                    if (grid[i][j] == 2) sTile.setTextureRect(IntRect(54, 0, ts, ts));
                                                    sTile.setPosition(j * ts, i * ts);
                                                    window.draw(sTile);
                                                }

                                            sTile.setTextureRect(IntRect(36, 0, ts, ts));
                                            sTile.setPosition(x * ts, y * ts);
                                            window.draw(sTile);

                                            sPrzeciwnik.rotate(10);
                                            for (int i = 0; i < liczba_przeciwnikow; i++)
                                            {
                                                sPrzeciwnik.setPosition(przeciwnicy[i].x, przeciwnicy[i].y);
                                                window.draw(sPrzeciwnik);
                                            }

                                            // Wyświetlenie napisu "Game Over" w przypadku przegranej
                                            if (!Gra) window.draw(sGameover);

                                            // Wyświetlenie napisu "You Win" w przypadku zwycięstwa
                                            if (liczba_pol >= 600) {
                                                Gra = false;
                                                window.draw(sYouwin);
                                            }

                                            std::cout << liczba_pol << std::endl;

                                            liczba_pol = 0;

                                            window.display();
                                        }
                                    }
                                    if (y == 3) {
                                        sf::RenderWindow window(sf::VideoMode(WindowSize, WindowSize), "Samotnik");

                                        std::vector<std::vector<int>> board = {
                                            {0, 0, 1, 1, 1, 0, 0},
                                            {0, 0, 1, 1, 1, 0, 0},
                                            {1, 1, 1, 1, 1, 1, 1},
                                            {1, 1, 1, 2, 1, 1, 1},
                                            {1, 1, 1, 1, 1, 1, 1},
                                            {0, 0, 1, 1, 1, 0, 0},
                                            {0, 0, 1, 1, 1, 0, 0}
                                        };

                                        while (window.isOpen()) {
                                            sf::Event event;
                                            while (window.pollEvent(event)) {
                                                if (event.type == sf::Event::Closed) {
                                                    window.close();
                                                }

                                                // Obsługa kliknięcia myszą
                                                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                                                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                                                    handleMouseClick(window, mousePosition, board);
                                                }
                                            }

                                            window.clear(sf::Color(255, 255, 255)); // Kolor tła

                                            // Rysuj kółka na podstawie tablicy
                                            drawCircles(window, board);

                                            window.display();
                                        }
                                        
                                        
                                    }
                                          
                                }

                            }

                            OPTIONS.close();
                            ABOUT.close();
                            GAME_MENU.clear();
                            gameMenu.draw(GAME_MENU);
                            GAME_MENU.display();
                        }

                    }
                    if (x == 1)
                    {
                        while (ABOUT.isOpen())
                        {

                            Event aevent;
                            while (ABOUT.pollEvent(aevent)) {
                                if (aevent.type == Event::Closed) {
                                    ABOUT.close();
                                }
                                if (aevent.type == Event::KeyPressed)
                                {
                                    if (aevent.key.code == Keyboard::Escape)
                                    {
                                        ABOUT.close();
                                    }
                                }
                            }
                            GAME_MENU.close();
                            ABOUT.clear();
                            ABOUT.display();
                        }

                    }
                    
                    if (x == 2)
                        MENU.close();
                    break;
                }
            }
        }
        MENU.clear();
        mainMenu.draw(MENU);
        MENU.display();
    }
}

