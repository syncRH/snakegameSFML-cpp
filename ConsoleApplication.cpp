    #include <iostream>
    #include <SFML/Graphics.hpp>
    #include <sstream>
    #include <algorithm>
    #include <fstream>
    #include <algorithm>   


    using namespace sf;

    int size(600);
    RenderWindow window(VideoMode(size, size), "SNAKE");
    class app {
    public:
        int x;
        int y;

        app() {};
        // случайное распределение
        void getncoord(int b) {
            x = rand() % 50 * b - b / 2;
            y = rand() % 50 * b - b / 2;
        }
    };

    struct snake {
        int x;
        int y;
    };
    // управление
    void keys(int& dir) {
        if (Keyboard::isKeyPressed(Keyboard::Up)) dir = 0;
        if (Keyboard::isKeyPressed(Keyboard::Right)) dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::Down)) dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::Left)) dir = 3;
    };
    void tick(int& snakec, snake* s, int& dir, int b, bool& go, int quadc, int& speed, app* a, int& playerscore) {
        if (dir >= 0 && dir <= 3) {
            for (int i = snakec; i > 0; i--) {
                s[i].x = s[i - 1].x;
                s[i].y = s[i - 1].y;
            }
        }
            
        switch (dir) {
        case 0: s->y -= b; break;
        case 1: s->x += b; break;
        case 2: s->y += b; break;
        case 3: s->x -= b; break;
        }

        for (int i = 0; i < 10; i++) {
            if (s->x == a[i].x && s->y == a[i].y) {
                snakec++;
                playerscore++;
                a[i].getncoord(b);
                speed -= 1000;
            }
        };

        for (int i = 1; i < snakec; i++) {
            if (s[0].x == s[i].x && s[0].y == s[i].y && (dir >= 0 && dir <= 3))
                go = true;
        };

        if ((s->x<0 || s->x>b * quadc) || (s->y<0 || s->y>b * quadc)) go = true;
    };
    void fullstats(bool& isMenuS, bool& isMenuG) {
        Font font;
        font.loadFromFile("2206.ttf"); 
        Text text("", font, 40);
        text.setOutlineColor(Color::Black);
        text.setFillColor(Color::White);  
        text.setStyle(sf::Text::Bold); 
        Text text1 = text;
        Text text2 = text;
        Text text3 = text;
        Text text4 = text;
        Texture menuTexture1, menuTexture2, menuBackground;
        menuTexture1.loadFromFile("images/13.png");
        menuTexture2.loadFromFile("images/12.png");
        menuBackground.loadFromFile("images/24.png");
        Sprite menu1(menuTexture1), menu2(menuTexture2), menuBg(menuBackground);
        bool isMenu = 1;
        int menuNum = 0;
        menu1.setPosition(-280, -282);
        menu2.setPosition(280, -282);
        menuBg.setPosition(0, 0);
        std::ostringstream pss; 
        std::ostringstream pss1;
        std::ostringstream pss2;
        std::ostringstream pss3;
        std::ostringstream pss4;
        int pdata[5], i = 0, count;

        std::ifstream file("input.txt");
        int temp;
        for (int i = 0; i < 5; i++) pdata[i] = 0;
        while (file >> temp) { if (temp > 0) pdata[i] = temp; i++; }
        file.close();
        pss << pdata[0];
        text.setString("1.    " + pss.str());
        text.setPosition(214, 149); 
        pss1 << pdata[1];
        text1.setString("2.    " + pss1.str());
        text1.setPosition(214, 242);
        pss2 << pdata[2];
        text2.setString("3.    " + pss2.str());
        text2.setPosition(214, 322);
        pss3 << pdata[3];
        text3.setString("4.    " + pss3.str());
        text3.setPosition(214, 410);
        pss4 << pdata[4];
        text4.setString("5.    " + pss4.str());
        text4.setPosition(214, 497);

        
        while (isMenu)
        {
            menu1.setColor(Color::White);
            menu2.setColor(Color::White);
            menuNum = 0;
            window.clear(Color(129, 181, 221));

            if (IntRect(10, 10, 20, 20).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Cyan); menuNum = 1; }
            if (IntRect(570, 10, 20, 20).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Cyan); menuNum = 2; }
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                if (menuNum == 1) { isMenuS = false;  isMenu = false; isMenuG = true;  }
                if (menuNum == 2) { isMenu = false; isMenuG = false; }
            }

            window.draw(menuBg);
            window.draw(menu1);
            window.draw(menu2);
            window.draw(text);
            window.draw(text1);
            window.draw(text2);
            window.draw(text3);
            window.draw(text4);
            window.display();
        }

    }
    void menu(bool& start) {
        Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
        menuTexture1.loadFromFile("images/4.png");
        menuTexture2.loadFromFile("images/5.png");
        menuTexture3.loadFromFile("images/6.png");
        menuBackground.loadFromFile("images/2.png");
        Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
        bool isMenu = 1, isMenuS = 1;
        int menuNum = 0;
        menu1.setPosition(0, -80);
        menu2.setPosition(0, 40);
        menu3.setPosition(0, 200);
        menuBg.setPosition(0, 0);

        while (isMenu)
        {
            menu1.setColor(Color::White);
            menu2.setColor(Color::White);
            menu3.setColor(Color::White);
            menuNum = 0;
            isMenuS = 1;
            window.clear(Color(129, 181, 221));

            if (IntRect(150, 180, 300, 100).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Cyan); menuNum = 1; }
            if (IntRect(150, 300, 300, 100).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Cyan); menuNum = 2; }
            if (IntRect(150, 460, 300, 100).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Magenta); menuNum = 3; }

            if (Mouse::isButtonPressed(Mouse::Left))
            {
                if (menuNum == 1) isMenu = false, start = false;   
                if (menuNum == 2) {
                    while (isMenuS) {
                        fullstats(isMenuS, isMenu);
                        if (!isMenu) {
                            window.close(); break;
                        }
                    }
                }
                if (menuNum == 3) { window.close(); isMenu = false; }

            }
            window.draw(menuBg);
            window.draw(menu1);
            window.draw(menu2);
            window.draw(menu3);
            window.display();
        }
    }

    void gameover(bool& start, int playerscore) {
        Font font;
        font.loadFromFile("20784.ttf");
        Text text("", font, 50); 
        text.setOutlineColor(Color::Red);
        text.setFillColor(Color::Green); 
        text.setStyle(sf::Text::Bold);
        Texture menuTexture1, menuTexture2, menuBackground;
        menuTexture1.loadFromFile("images/8.png");
        menuTexture2.loadFromFile("images/9.png");
        menuBackground.loadFromFile("images/7.png");
        Sprite menu1(menuTexture1), menu2(menuTexture2), menuBg(menuBackground);
        bool isMenu = 1;
        int menuNum = 0;
        menu1.setPosition(-65, 169);
        menu2.setPosition(65, 169);
        menuBg.setPosition(0, 0);
        std::ostringstream playerScoreString;
        playerScoreString << playerscore;
        text.setString(playerScoreString.str());
        text.setPosition(370, 170);
        while (isMenu)
        {
            menu1.setColor(Color::White);
            menu2.setColor(Color::White);
            menuNum = 0;
            window.clear(Color(129, 181, 221));

            if (IntRect(195, 430, 80, 80).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Cyan); menuNum = 1; }
            if (IntRect(330, 430, 80, 80).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Cyan); menuNum = 2; }
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                if (menuNum == 1) { isMenu = false; start = false; }
                if (menuNum == 2) { window.close(); isMenu = false; break; }
            }
            window.draw(menuBg);
            window.draw(menu1);
            window.draw(menu2);
            window.draw(text);
            window.display();
        }
    }
    void mainsnake(bool& isGameOver, int& playerscore)
    {
        Font font; 
        font.loadFromFile("CyrilicOld.ttf"); 
        Text text("", font, 20); 
        text.setOutlineColor(Color::Red);
        text.setFillColor(Color::Red);
        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        int quadCount = 50;
        int b = size / quadCount;
        int dir;
        RectangleShape rect(Vector2f(b, b));
        int speed(200000);
        int countGreen = 11;
        int countRed = 0;
        int snakec = 4;
        playerscore = 0;
        snake s[100];
        Clock clock;
        srand(time(NULL));
        app a[10];
        for (int i = 0; i < snakec; i++) {
            s[i].x = b * (quadCount / 2) - (b / 2);
            s[i].y = b * (quadCount / 2) - (b / 2) + i * b;
        }
        for (int i = 0; i < 10; i++) {
            a[i].getncoord(b);
        }
        while (window.isOpen() && !isGameOver) {
            keys(dir);
            float time = clock.getElapsedTime().asMicroseconds();
            if (time > speed && !isGameOver) {
                tick(snakec, s, dir, b, isGameOver, quadCount, speed, a, playerscore);
                clock.restart();
            }
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();
            }
            window.clear();
            for (int i = 0; i < quadCount; i++)
                for (int j = 0; j < quadCount; j++) {
                    for (int k = 0; k < snakec; k++)
                        if (s[k].x == i * b - (b / 2) && s[k].y == j * b - (b / 2))
                            countGreen++;
                    for (int l = 0; l < 10; l++)
                        if (a[l].x == i * b - (b / 2) && a[l].y == j * b - (b / 2))
                            countRed++;

                    if (countGreen > 0) rect.setFillColor(Color::Green);
                    else if (countRed > 0) rect.setFillColor(Color::Red);
                    else rect.setFillColor(Color::Black);
                    rect.setPosition(i * b, j * b);
                    window.draw(rect);
                    countGreen = 0;
                    countRed = 0;
                }
            std::ostringstream playerScoreString;  
            playerScoreString << playerscore;		
            text.setString("Собрано яблок: " + playerScoreString.str());
            text.setPosition(0, 0);
            window.draw(text);
            window.display();
        }
    }
    void sortmass(int *pdata, int playerscore)
    {
        bool work(true);
        int temp = 0;
        using namespace std;
        ofstream file("input.txt", ios::trunc);
        for (auto i = 0; i < 5; i++) 
        {
            if (pdata[i] < playerscore && work) 
            {
                work = false;
                pdata[i] = playerscore;
            }
        }
        std::sort(pdata, pdata + (sizeof pdata / sizeof pdata[0]), std::greater<int>());

        for (int i = 0; i < 5; i++) if (pdata[i] > 0) file << pdata[i] << endl;
        file.close();
    }
    bool isGameOver(true);
    int playerscore = 0;
    int pdata[4];
    int main() 
    {
        for (int i = 0; i < 5; i++) pdata[i] = 0;
        menu(isGameOver);
        while (!isGameOver) {
            mainsnake(isGameOver, playerscore);
            sortmass(pdata, playerscore);
            if (isGameOver == true) { gameover(isGameOver, playerscore); }
        }
        return 0;
    }