#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstring>
#include <cmath>
#include <cstdlib>

#define PI 3.14159265359

typedef uint8_t byte;

byte grid[20][12];
byte colliders[20][12];

enum GameState {
    MENU,
    PLAYING,
    GAMEOVER
};

struct Vec2 {
    byte y, x;
    Vec2() {}
    Vec2(byte dy, byte dx) : x(dx), y(dy) {}
};

struct Piece {
    Vec2 a, b, c, d;
    Piece() {}
    Piece(byte ax, byte ay, byte bx, byte by, byte cx, byte cy, byte dx, byte dy)
        : a(Vec2(ax, ay)), b(Vec2(bx, by)), c(Vec2(cx, cy)), d(Vec2(dx, dy)) {}
    Piece(Vec2 da, Vec2 db, Vec2 dc, Vec2 dd)
        : a(da), b(db), c(dc), d(dd) {}
};

enum PIECE_TYPE {
    S, Z, L, J, SQR, I, T
};

void resetGame(byte(&grid)[20][12], byte(&colliders)[20][12], unsigned int& scoreCounter, sf::Text& score) {
    memset(grid, 0, sizeof(grid));
    memset(colliders, 0, sizeof(colliders));
    scoreCounter = 0;
    score.setString("Score: 0");
}

Piece CreatePiece(PIECE_TYPE type) {
    switch (type) {
    case S: return Piece(Vec2(1, 5), Vec2(1, 4), Vec2(0, 4), Vec2(2, 5));
    case Z: return Piece(Vec2(1, 4), Vec2(1, 5), Vec2(0, 5), Vec2(2, 4));
    case L: return Piece(Vec2(1, 5), Vec2(1, 4), Vec2(1, 6), Vec2(0, 6));
    case J: return Piece(Vec2(1, 5), Vec2(1, 4), Vec2(1, 6), Vec2(0, 4));
    case SQR: return Piece(Vec2(1, 5), Vec2(1, 4), Vec2(0, 5), Vec2(0, 4));
    case I: return Piece(Vec2(1, 5), Vec2(1, 4), Vec2(1, 6), Vec2(1, 7));
    case T: return Piece(Vec2(1, 5), Vec2(1, 4), Vec2(1, 6), Vec2(0, 5));
    default: return Piece();
    }
}

void rotate(Piece& piece) {
    float angle = 90 * (PI / 180);

    float b_offset_x = piece.b.x - piece.a.x;
    float c_offset_x = piece.c.x - piece.a.x;
    float d_offset_x = piece.d.x - piece.a.x;

    float b_offset_y = piece.b.y - piece.a.y;
    float c_offset_y = piece.c.y - piece.a.y;
    float d_offset_y = piece.d.y - piece.a.y;

    float pbx = piece.a.x + (b_offset_x * cosf(angle) - b_offset_y * sinf(angle));
    float pby = piece.a.y + (b_offset_x * sinf(angle) + b_offset_y * cosf(angle));

    float pcx = piece.a.x + (c_offset_x * cosf(angle) - c_offset_y * sinf(angle));
    float pcy = piece.a.y + (c_offset_x * sinf(angle) + c_offset_y * cosf(angle));

    float pdx = piece.a.x + (d_offset_x * cosf(angle) - d_offset_y * sinf(angle));
    float pdy = piece.a.y + (d_offset_x * sinf(angle) + d_offset_y * cosf(angle));

    if (colliders[(byte)pby][(byte)pbx] != 2 &&
        colliders[(byte)pcy][(byte)pcx] != 2 &&
        colliders[(byte)pdy][(byte)pdx] != 2 &&
        piece.a.x != 1 && piece.a.y != 1) {
        piece.b.x = pbx;
        piece.b.y = pby;
        piece.c.x = pcx;
        piece.c.y = pcy;
        piece.d.x = pdx;
        piece.d.y = pdy;
    }
}

int main() {
    unsigned int timer = 0, gamespeed = 10, scoreCounter = 0;

    sf::Texture tile_tex;
    tile_tex.loadFromFile("images/tetris_tile.png");

    sf::Sprite tile(tile_tex);
    tile.setScale(2, 2);

    float tile_size = tile_tex.getSize().x * tile.getScale().x;
    size_t width = tile_size * 12, height = tile_size * 20;

    sf::Font font;
    font.loadFromFile("font/agencyfb_reg.ttf");

    // Menu texts
    sf::Text menuTitle;
    menuTitle.setFont(font);
    menuTitle.setCharacterSize(60);
    menuTitle.setFillColor(sf::Color::Green);
    menuTitle.setString("TETRIS");
    menuTitle.setPosition(width / 2 - 70, height / 3);

    sf::Text playButton;
    playButton.setFont(font);
    playButton.setCharacterSize(30);
    playButton.setFillColor(sf::Color::White);
    playButton.setString("Press SPACE to Play");
    playButton.setPosition(width / 2 - 100, height / 2.2);

    // Game texts
    sf::Text score;
    score.setFont(font);
    score.setCharacterSize(25);
    score.setFillColor(sf::Color::White);
    score.setPosition(10.0f, 18.0f);
    score.setString("Score: 0");

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER");
    gameOverText.setPosition(width / 2 - 75, height / 3);
    
    sf::Text pressReturn;
    pressReturn.setFont(font);
    pressReturn.setFillColor(sf::Color::Red);
    pressReturn.setString("Press ENTER to Play");
    pressReturn.setPosition(width / 2 - 100, height / 2.5);
    pressReturn.setCharacterSize(30);

    sf::RenderWindow window(sf::VideoMode(width, height), "Tetris", sf::Style::Titlebar | sf::Style::Close);
    window.setKeyRepeatEnabled(true);
    window.setFramerateLimit(60);

    GameState gameState = MENU;
    Piece piece = CreatePiece(static_cast<PIECE_TYPE>((rand() % 7)));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                window.close();
            }

            if (gameState == MENU && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                gameState = PLAYING;
                resetGame(grid, colliders, scoreCounter, score);
                piece = CreatePiece(static_cast<PIECE_TYPE>((rand() % 7)));
            }

            if (gameState == GAMEOVER && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                gameState = MENU;
            }

            if (gameState == PLAYING && event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    rotate(piece);
                }
                else if (event.key.code == sf::Keyboard::Left &&
                    piece.a.x != 0 && piece.b.x != 0 && piece.c.x != 0 && piece.d.x != 0 &&
                    (colliders[piece.a.y][piece.a.x - 1]) != 2 && (colliders[piece.b.y][piece.b.x - 1]) != 2 &&
                    (colliders[piece.c.y][piece.c.x - 1]) != 2 && (colliders[piece.d.y][piece.d.x - 1]) != 2) {
                    piece.a.x--; piece.b.x--; piece.c.x--; piece.d.x--;
                }
                else if (event.key.code == sf::Keyboard::Right &&
                    piece.a.x != 11 && piece.b.x != 11 && piece.c.x != 11 && piece.d.x != 11 &&
                    (colliders[piece.a.y][piece.a.x + 1]) != 2 && (colliders[piece.b.y][piece.b.x + 1]) != 2 &&
                    (colliders[piece.c.y][piece.c.x + 1]) != 2 && (colliders[piece.d.y][piece.d.x + 1]) != 2) {
                    piece.a.x++; piece.b.x++; piece.c.x++; piece.d.x++;
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                gamespeed = 10;
            }
        }

        if (gameState == PLAYING && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            gamespeed = 1;
        }

        window.clear(sf::Color(107, 36, 107, 255));

        if (gameState == MENU) {
            window.draw(menuTitle);
            window.draw(playButton);
        }
        else if (gameState == PLAYING) {

            sf::Sprite piece_tile = tile;
            piece_tile.setPosition(tile_size * piece.a.x, tile_size * piece.a.y);
            window.draw(piece_tile);
            piece_tile.setPosition(tile_size * piece.b.x, tile_size * piece.b.y);
            window.draw(piece_tile);
            piece_tile.setPosition(tile_size * piece.c.x, tile_size * piece.c.y);
            window.draw(piece_tile);
            piece_tile.setPosition(tile_size * piece.d.x, tile_size * piece.d.y);
            window.draw(piece_tile);

            for (size_t i = 0; i < 20; i++)
                for (size_t j = 0; j < 12; j++)
                    grid[i][j] = (colliders[i][j] == 2) ? 2 : 0;

            if (timer > gamespeed) {
                if (grid[piece.a.y + 1][piece.a.x] == 2 ||
                    grid[piece.b.y + 1][piece.b.x] == 2 ||
                    grid[piece.c.y + 1][piece.c.x] == 2 ||
                    grid[piece.d.y + 1][piece.d.x] == 2 ||
                    piece.a.y == 19 || piece.b.y == 19 || piece.c.y == 19 || piece.d.y == 19) {
                    grid[piece.a.y][piece.a.x] = 2;
                    grid[piece.b.y][piece.b.x] = 2;
                    grid[piece.c.y][piece.c.x] = 2;
                    grid[piece.d.y][piece.d.x] = 2;

                    colliders[piece.a.y][piece.a.x] = 2;
                    colliders[piece.b.y][piece.b.x] = 2;
                    colliders[piece.c.y][piece.c.x] = 2;
                    colliders[piece.d.y][piece.d.x] = 2;

                    piece = CreatePiece(static_cast<PIECE_TYPE>((rand() % 7)));
                }
                else {
                    grid[piece.a.y + 1][piece.a.x] = 1;
                    grid[piece.b.y + 1][piece.b.x] = 1;
                    grid[piece.c.y + 1][piece.c.x] = 1;
                    grid[piece.d.y + 1][piece.d.x] = 1;

                    piece.a.y++; piece.b.y++; piece.c.y++; piece.d.y++;
                }

                byte tetris_row = 0;
                for (size_t i = 0; i < 20; i++) {
                    byte blocks_in_a_row = 0;
                    for (size_t j = 0; j < 12; j++)
                        if (colliders[i][j] == 2)
                            blocks_in_a_row++;

                    if (blocks_in_a_row == 12) {
                        tetris_row++;
                        for (size_t k = i; k > 0; k--)
                            for (size_t l = 0; l < 12; l++)
                                colliders[k][l] = colliders[k - 1][l];

                        scoreCounter++;
                        char temp[256];
                        sprintf_s(temp, "Score: %i", scoreCounter);
                        score.setString(temp);
                    }
                }

                for (size_t i = 0; i < 12; i++)
                    if (colliders[0][i] == 2)
                        gameState = GAMEOVER;

                timer = 0;
            }
            else {
                timer++;
            }

            for (size_t i = 0; i < 20; i++) {
                for (size_t j = 0; j < 12; j++) {
                    if (grid[i][j] == 1 || colliders[i][j] == 2) {
                        sf::Sprite t = tile;
                        t.setPosition(tile_size * j, tile_size * i);
                        window.draw(t);
                    }
                }
            }
            window.draw(score);
        }
        else if (gameState == GAMEOVER) {
            for (size_t i = 0; i < 20; i++) {
                for (size_t j = 0; j < 12; j++) {
                    if (colliders[i][j] == 2) {
                        window.draw(gameOverText);
                    }
                }
            }
            window.draw(gameOverText);
			window.draw(pressReturn);

            sf::Text scoreText;
            scoreText.setFont(font);
            scoreText.setCharacterSize(30);
            scoreText.setFillColor(sf::Color::White);
            scoreText.setString("The Score: " + std::to_string(scoreCounter));
            scoreText.setPosition(width / 2 - 75, height / 2.2);

			window.draw(scoreText);
        }

        window.display();
    }

    return 0;
}