// TODO: clean this up later

#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>
#include <cmath>
#include <fstream>

struct BoundingBox
{
public:
    int top, bottom, left, right;
};

struct Vector2 {
    float x, y;
};
class Object
{
public:
    virtual void Tick(float dt) = 0;
    virtual void Render() = 0;
};

class Bird : public Object
{
public:
    Bird();
    void Tick(float dt) override;
    void Render() override;

private:
    float x, y;
    float velocity;
};

class Pipe : public Object
{
public:
    void Tick(float dt) override;
    void Render() override;
};

int main()
{
    // On setup la console pour la lecture de l'entrée clavier, en désactivant le mode ligne et l'écho pour pouvoir détecter les appuis de touches sans attendre la touche entrée et sans afficher les caractères tapés.
    #pragma region Console setup

    HANDLE h = GetStdHandle(STD_INPUT_HANDLE);   // input 
    HANDLE h2 = GetStdHandle(STD_OUTPUT_HANDLE); // output
    if (h == INVALID_HANDLE_VALUE)
    {
        std::cerr << "error" << std::endl;
        return 1;
    }
    if (h2 == INVALID_HANDLE_VALUE)
    {
        std::cerr << "error" << std::endl;
        return 1;
    }

    // use words for console io
    DWORD m = 0;
    DWORD m2 = 0;
    DWORD m3 = 0;
    if (!GetConsoleMode(h, &m))
    {
        std::cerr << "error" << std::endl;
        return 1;
    }
    m2 = m;
    m2 &= ~ENABLE_LINE_INPUT;
    m2 &= ~ENABLE_ECHO_INPUT;
    if (!SetConsoleMode(h, m2))
    {
        std::cerr << "error" << std::endl;
        return 1;
    }
    if (GetConsoleMode(h2, &m3))
        SetConsoleMode(h2, m3 | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    #pragma endregion

    // Ici on initialise les différents acteurs du jeu : Bird, Pipe, Score.
    #pragma region Bird
    // bird

    // y position (float)
    float by = 9.0f;
    // velocity
    float bv = 0.0f;            

    // top (int)
    int bt = 0;

    // bottom (int)
    int bb = 0;

    // left
    int bl = 10;

    // right
    int br = 10 + 2 - 1;

    // 0 = alive, 1 = dead
    int dead = 0;

    // spawn timer
    float t = 0.0f;

    // current score
    unsigned long long sc = 0;

    // best score
    unsigned long long bsc = 0;

    // hud padding

    // left padding
    int lp = 0;
    // right hud padding
    int rp = 0; 
    // pipe data |  x positions
    std::vector<float> px;
    // pipe data | gap tops
    std::vector<int> pg;

    // pipe data | scored flag (0 or 1)
    std::vector<int> ps;  

    #pragma endregion

    #pragma region Random setup
    // rng
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> d(2, 20 - 6 - 2); // gap position
    #pragma endregion

    #pragma region High score setup
    INPUT_RECORD rec;
    DWORD ne = 0;

    // int debug = 1;
    // if (debug) std::cout << "debug: game starting" << std::endl;

    // load best score
    std::ifstream fin("best-score.txt");
    if (fin)
    {
        fin >> bsc;
        if (!fin)
            bsc = 0; // reset if read failed
    }
    fin.close(); // close the file
    #pragma endregion

    // delta time setup, variable will be used to calculate deltatime in the main loop using current time - previous (prev) time
    auto prev = std::chrono::steady_clock::now();

    // main loop
    #pragma region Main loop
    while (dead == 0)
    {
        #pragma region Delta time
        // delta time
        auto now = std::chrono::steady_clock::now();
        float dt = std::chrono::duration<float>(now - prev).count();
        prev = now;
        if (dt > 0.1f)
            dt = 0.1f; // clamp delta time

        #pragma endregion

        #pragma region Input
        // read input events
        DWORD nEvents = 0;
        if (!GetNumberOfConsoleInputEvents(h, &nEvents))
        {
            SetConsoleMode(h, m);
            return 1;
        }

        for (DWORD i = 0; i < nEvents; ++i) // loop through events
        {
            if (!ReadConsoleInput(h, &rec, 1, &ne))
            {
                std::cerr << "Failed to read console input." << std::endl;
                SetConsoleMode(h, m);
                return 1;
            } // end if ReadConsoleInput

            if (rec.EventType == KEY_EVENT)
            {
                KEY_EVENT_RECORD k = rec.Event.KeyEvent;
                if (k.bKeyDown == TRUE)
                {
                    if (k.wVirtualKeyCode == VK_RETURN)
                    {
                        bv = -14.0f;
                    } // end if enter
                } // end if key down
            } // end if key event
        } // end for each event
        #pragma endregion

        #pragma region Bird actor tick
        bv = bv + 42.0f * dt;
        by = by + bv * dt;
        #pragma endregion

        #pragma region Pipe actor tick
        t = t + dt;
        if (t >= 1.4f)
        {
            t = t - 1.4f; // wtf
            px.push_back(50.0f);
            pg.push_back(d(rng));
            ps.push_back(0);
        }
       

        for (int i = 0; i < (int)px.size(); i++) // loop over all pipes
        {
            px[i] = px[i] - 18.0f * dt; // move pipe left

            int pipeRight = (int)std::floor(px[i]) + 6 - 1;
            if (ps[i] == 0 && pipeRight < 10)
            {
                ps[i] = 1;
                sc = sc + 1;
                if (sc > bsc)
                    bsc = sc;
            }
        }
        #pragma endregion

        for (int i = (int)px.size() - 1; i >= 0; i--) // reverse loop to safely remove pipes that are off screen
        {
            if (px[i] + 6.0f < 0.0f)
            {
                px.erase(px.begin() + i);
                pg.erase(pg.begin() + i);
                ps.erase(ps.begin() + i);
            }
        }

        #pragma region Collision detection
        // collision
        bt = (int)std::floor(by);
        bb = bt + 2 - 1;
        bl = 10;         // same every frame
        br = 10 + 2 - 1; // same every frame
        // check wall
        if (bt < 0 || bb >= 20)
        {
            dead = 1;
        }
        #pragma endregion
        
        if (!dead)
        {
            for (int i = 0; i < (int)px.size(); i++)
            {
                int pl = (int)std::floor(px[i]);
                int pr = pl + 6 - 1;

                if (br >= pl && bl <= pr)
                {
                    for (int y = bt; y <= bb; y++)
                    {
                        if (y < pg[i] || y >= pg[i] + 6)
                        {
                            dead = 1;
                            break;
                        }
                    }
                }

                if (dead != 0)
                    break;
            }
        }

        if (dead != 0) // if dead we dont render, but this is also the while loop exit condition, we should reorder operations to avoid doing this
            break;

        // frame setup
        std::vector<std::string> frame(20, std::string(50, ' '));

        #pragma region Pipe rendering
        for (int i = 0; i < (int)px.size(); i++)
        {
            int pl = (int)std::floor(px[i]);
            for (int dx = 0; dx < 6; dx++)
            {
                int x = pl + dx;
                if (x < 0 || x >= 50)
                    continue;
                for (int y = 0; y < 20; y++)
                {
                    if (!(y >= pg[i] && y < pg[i] + 6))
                    {
                        frame[y][x] = 'P';
                    }
                }
            }
        }

        #pragma endregion

        #pragma region Bird rendering

        for (int dy = 0; dy < 2; dy++)
        {
            int y = bt + dy;
            if (y < 0 || y >= 20)
                continue;
            for (int dx = 0; dx < 2; dx++)
            {
                int x = 10 + dx;
                if (x >= 0 && x < 50)
                    frame[y][x] = 'B';
            }
        }

        #pragma endregion

        #pragma region HUD rendering

        std::string scoreText = "Score: " + std::to_string(sc) + "   Best: " + std::to_string(bsc);
        if (scoreText.size() > 50)
            scoreText = scoreText.substr(0, 50);
        lp = (int)((50 - (int)scoreText.size()) / 2);
        rp = 50 - lp - (int)scoreText.size();

        std::cout << "\x1b[2J\x1b[H";
        std::cout << "+" << std::string(50, '-') << "+" << "\n";
        for (int y = 0; y < 20; y++)
        {
            std::cout << "|";
            for (int x = 0; x < 50; x++)
            {
                char c = frame[y][x];
                if (c == 'P')
                {
                    std::cout << "\x1b[32mP\x1b[0m";
                }
                else if (c == 'B')
                {
                    std::cout << "\x1b[33mB\x1b[0m"; // render bird yellow
                }
                else
                {
                    std::cout << ' ';
                }
            }
            std::cout << "|\n";
        }
        std::cout << "+" << std::string(50, '-') << "+" << "\n";
        std::cout << "+" << std::string(50, '-') << "+" << "\n";
        std::cout << "|" << std::string(lp, ' ') << scoreText << std::string(rp, ' ') << "|\n";
        std::cout << "+" << std::string(50, '-') << "+" << "\n";
        std::cout.flush();

        float ft = std::chrono::duration<float>(std::chrono::steady_clock::now() - now).count(); 
        if (ft < 1.0f / 30.0f)
        {
            std::this_thread::sleep_for(std::chrono::duration<float>(1.0f / 30.0f - ft)); // why are using delta time if we force 30 fps anyway
        }
    }

    #pragma endregion

    #pragma region Save high score
    // save best score to file
    std::ofstream fout("best-score.txt", std::ios::trunc);
    if (fout)
        fout << bsc; // write best score
    fout.close();    // close the file
    #pragma endregion

    // restore original console mode
    SetConsoleMode(h, m);
    return 0;
}