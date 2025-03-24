#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "raylib.h"

#define windowWidth 1400
#define windowHeight 1610
#define MAZE_WIDTH 28
#define MAZE_HEIGHT 31
#define FRIGHTENED_TIME 9
#define SCATTER_TIME 6
#define pixelSize 50
#define INFO_BAR_H  60
#define pacSpeed 1
#define MAX_INPUT_CHARS 30

Texture pac1;
Texture pac2;
Vector2 pacPos = {14, 15};
Vector2 Ghost1Pos;
Vector2 Ghost2Pos;
Vector2 Ghost3Pos;
Vector2 Ghost4Pos;
Vector2 Ghost5Pos;
Texture GameOver;
Texture G1;
Texture G2;
Texture G3;
Texture G4;
Texture G5;
Texture cherry;
Texture apple;
Texture Hallopino;
Texture mushroom;
int animFrame = 0;
int framerate = 10;
int lives = 3;
int menu = 0;
int score = 0;
char map1[MAZE_HEIGHT][MAZE_WIDTH+1] = {
    "############################",
    "#            ##            #",
    "#  ###  ###  ##  ####  ### #",
    "#  ###  ###  ##  ####  ### #",
    "#  ###  ###  ##  ####  ### #",
    "#                          #",
    "# #### ## ######## ##  ### #",
    "# #### ## ######## ##  ### #",
    "#      ##    ##    ##      #",
    "###### ####  ##  ####   ####",
    "#      ##### ## ##### #    #",
    "#    # ##          ##      #",
    "#    # ## ###  ### ## #    #",
    "###### ## #      # ## ######",
    "#         #      #         #",
    "###  # ## #      # ## ######",
    "#    # ## ######## ## #    #",
    "#    # ##          ##      #",
    "#    # ## ######## ## #    #",
    "###### ## ######## ## ######",
    "#            ##            #",
    "# #### ##### ## ##### #### #",
    "# #### ##### ## ##### #### #",
    "#   ##                ##   #",
    "### ## ## ######## ## ## ###",
    "### ## ## ######## ## ## ###",
    "#      ##    ##    ##      #",
    "# ########## ## ########## #",
    "# ########## ## ########## #",
    "#                          #",
    "############################"
};
char map2[MAZE_HEIGHT][MAZE_WIDTH + 1] = {
"############################",
"#            ##            #",
"#  # #  # #  ##  #  #  # # #",
"#  # #  # #  ##  #  #  # # #",
"#  # #  # #  ##  #  #  # # #",
"#                          #",
"# #### ## ######## ##  # # #",
"# #### ## ######## ##  # # #",
"#      ##    ##    ##      #",
"###### ####  ##  ####   # ##",
"#      ##### ## ##### #    #",
"#    # ##          ##      #",
"#    # ## ###  ### ## #    #",
"###### ## #      # ## ##  ##",
"#         #      #         #",
"###  # ## #      # ## ##  ##",
"#    # ## ### #### ## #    #",
"#    # ##          ##      #",
"#    # ## ######## ## #    #",
"###### ## ######## ## ######",
"#            ##            #",
"#  ### ## ## ## ##### #### #",
"#  ### ## ## ## ##### #### #",
"#   ##                ##   #",
"##  ## ## ######## ## ## ###",
"##  ## ## ######## ## ## ###",
"#      ##    ##    ##      #",
"#  ######### ## #########  #",
"#  ######### ## #########  #",
"#                          #",
"############################",
};
char map[MAZE_HEIGHT][MAZE_WIDTH + 1];

int Snackes = 0;
int SpeedyTime = 0;
int EatGhostTime = 0;
int Roatation = 0;
int ghostSpeed = 1;
char name[31] = "\0";
Sound firstmp3;
Sound munch1;
Sound frightendtime;
Sound credit;
Sound music;
Sound dead;
Sound gameover;

typedef struct record
{
    char name[31];
    char date[21];
    int score;
} record;


void loadmap()
{
    int num = rand() % 2;
    switch (num)
    {
        case 1:
            for(int i=0 ; i < MAZE_HEIGHT ; i++)
            {
                strcpy(map[i], map1[i]);
            }
            break;
        case 0:
            for(int i=0 ; i < MAZE_HEIGHT ; i++)
            {
                strcpy(map[i], map1[i]);
            }
            break;
            
    }

}

void loadTextures()
{
    Image pacman1 = LoadImage("resources//sprites//pac//pacman2.png");
    Image pacman2 = LoadImage("resources//sprites//pac//pacWide1.png");
    pac1 = LoadTextureFromImage(pacman1);
    pac2 = LoadTextureFromImage(pacman2);

    UnloadImage(pacman1);
    UnloadImage(pacman2);

    Image gameover = LoadImage("resources//gameover.png");
    GameOver = LoadTextureFromImage(gameover);
    UnloadImage(gameover);

    Image ghost1 = LoadImage("resources//sprites//ghosts//blinky.png");
    G1 = LoadTextureFromImage(ghost1);
    UnloadImage(ghost1);

    Image ghost2 = LoadImage("resources//sprites//ghosts//blueghost.png");
    G2 = LoadTextureFromImage(ghost2);
    UnloadImage(ghost2);

    Image ghost3 = LoadImage("resources//sprites//ghosts//clyde.png");
    G3 = LoadTextureFromImage(ghost3);
    UnloadImage(ghost3);

    Image ghost4 = LoadImage("resources//sprites//ghosts//inky.png");
    G4 = LoadTextureFromImage(ghost4);
    UnloadImage(ghost4);

    Image ghost5 = LoadImage("resources//sprites//ghosts//pinky.png");
    G5 = LoadTextureFromImage(ghost5);
    UnloadImage(ghost5);

    Image chery = LoadImage("resources//sprites//Snackes//Clipped_image_20250118_113521.png");
    cherry = LoadTextureFromImage(chery);
    UnloadImage(chery);

    Image halo = LoadImage("resources//sprites//Snackes//Clipped_image_20250118_113652.png");
    Hallopino = LoadTextureFromImage(halo);
    UnloadImage(halo);

    Image mush = LoadImage("resources//sprites//Snackes//Clipped_image_20250118_113916.png");
    mushroom = LoadTextureFromImage(mush);
    UnloadImage(mush);

    Image app = LoadImage("resources//sprites//Snackes//Clipped_image_20250118_113501.png");
    apple = LoadTextureFromImage(app);
    UnloadImage(app);

}

void loadSounds()
{
    firstmp3 = LoadSound("resources//Audio//take_on_me_small.mp3");
    munch1 = LoadSound("resources//Audio//munch_1.wav");
    frightendtime = LoadSound("resources//Audio//sup_pellet.mp3");
    credit = LoadSound("resources//Audio//credit.wav");
    music = LoadSound("resources//Audio//Heads'll Roll.mp3");
    dead = LoadSound("resources//Audio//death.mp3");
    gameover = LoadSound("resources//Audio//game-over.mp3");

}

void UnloadSounds()
{
    UnloadSound(firstmp3);
    UnloadSound(munch1);
    UnloadSound(frightendtime);
    UnloadSound(credit);
    UnloadSound(music);
    UnloadSound(dead);
    UnloadSound(gameover);
}

Vector2 RandomPos()
{
    Vector2 NewPos;
    while (1)
    {
        NewPos.x = rand() % MAZE_WIDTH;
        NewPos.y = rand() % MAZE_HEIGHT;
        if(map[(int) NewPos.y][(int) NewPos.x] == ' ')
            break;
    }
    
    return NewPos;
    
}

Vector2 RandomGhostMove(int x, int y)
{
    Vector2 newPos = {x, y};
    int direction = rand() % 4;
    switch (direction)
    {
        case 0: // Move up
            if (map[y - ghostSpeed][x] != '#')
                newPos.y -= ghostSpeed;
            break;
        case 1: // Move down
            if (map[y + ghostSpeed][x] != '#')
                newPos.y += ghostSpeed;
            break;
        case 2: // Move left
            if (map[y][x - ghostSpeed] != '#')
                newPos.x -= ghostSpeed;
            break;
        case 3: // Move right
            if (map[y][x + ghostSpeed] != '#')
                newPos.x += ghostSpeed;
            break;
    }
    return newPos;
}

void makingSnackes()
{
    while(Snackes < 10)
    {
        int x = rand() % MAZE_WIDTH;
        int y = rand() % MAZE_HEIGHT;
        int thing = rand() % 5;
        if(map[y][x] == ' ')
        {
            switch (thing)
            {
                case 1:
                    map[y][x] = '.'; // cheese
                    break;
                case 2:
                    map[y][x] = 'O'; // cherry
                    break;
                case 3:
                    map[y][x] = 'A'; // apple
                    break;
                case 4:
                    map[y][x] = 'H'; // jalapeno
                    break;
                default:
                    map[y][x] = 'T'; // toxic mushroom
                    break;
            }
            Snackes++;
        }
    }
}

void StartOfGame()
{
    int SelectedLine = 1;
    PlaySound(firstmp3);
    SetSoundVolume(firstmp3, 0.5f);
    while(!WindowShouldClose())
    {
        if(IsKeyDown(KEY_BACKSPACE))
        {
            menu = 0;
            return;
        }
        BeginDrawing();
        ClearBackground(BLACK);
        //DrawTexture(pacStart, 500, 200, WHITE);
        DrawText("PACMAN", 300, 200, 200, GOLD);
        DrawText("MADE BY F.SHAHRIARI", 480, 500, 40, BEIGE);
        DrawText("Press ENTER to start", 600, 1400, 20, GRAY);
        DrawText("Press BACKSPACE to get back to menu.", 500, 1450, 25, GRAY);
        switch (SelectedLine)
        {
            case 1:
                DrawText("1. EASY", 700, 800, 30, RED);
                DrawText("2. NORMAL", 700, 850, 30, YELLOW);
                DrawText("3. HARD", 700, 900, 30, YELLOW);
                break;
            case 2:
                DrawText("1. EASY", 700, 800, 30, YELLOW);
                DrawText("2. NORMAL", 700, 850, 30, RED);
                DrawText("3. HARD", 700, 900, 30, YELLOW);
                break;
            case 3:
                DrawText("1. EASY", 700, 800, 30, YELLOW);
                DrawText("2. NORMAL", 700, 850, 30, YELLOW);
                DrawText("3. HARD", 700, 900, 30, RED);
                break;
        }
        EndDrawing();
        
        if(IsKeyDown(KEY_DOWN))
        {
            SelectedLine ++;
            if(SelectedLine > 3)
                SelectedLine %= 3;
        }
        else if(IsKeyDown(KEY_UP))
        {    
            SelectedLine --;
            if(SelectedLine < 1)
                SelectedLine = SelectedLine % 3 + 3;
        }
        else if(IsKeyDown(KEY_ENTER))
        {
            switch (SelectedLine)
            {
            case 1:
                ghostSpeed = 1;
                lives = 5;
                break;
            case 2:
                ghostSpeed = 1;
                lives = 3;
                break;
            case 3:
                ghostSpeed = 1;
                lives = 1;
                break;
            }
            Ghost1Pos = RandomPos();
            Ghost2Pos = RandomPos();
            Ghost3Pos = RandomPos();
            Ghost4Pos = RandomPos();
            Ghost5Pos = RandomPos();
            score = 0;
            StopSound(firstmp3);
            loadmap();
            return;
        }
    }

}

void GettingName()
{
    PlaySound(firstmp3);
    SetSoundVolume(firstmp3, 0.5f);

    int letterCount = 0;

    Rectangle textBox = { 200, 1000, 1000, 50 };
    bool mouseOnText = false;

    int framesCounter = 0;

    //--------------------------------------------------------------------------------------

    // Main loop
    while (!WindowShouldClose())    // Detect window close button or esc key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
        else mouseOnText = false;

        if (mouseOnText)
        {
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
                {
                    name[letterCount] = (char)key;
                    name[letterCount+1] = '\0'; // Add null terminator at the end of the string.
                    letterCount++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name[letterCount] = '\0';
            }
        }
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (mouseOnText) framesCounter++;
        else framesCounter = 0;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            DrawText("PACMAN", 300, 200, 200, GOLD);
            DrawText("MADE BY F.SHAHRIARI", 480, 500, 40, BEIGE);

            DrawText("PLACE MOUSE OVER INPUT BOX!", 500, 700, 20, GRAY);
            DrawText("PRESS ENTER TO CONTINUE", 500, 1400, 25, GRAY);

            DrawRectangleRec(textBox, LIGHTGRAY);
            if (mouseOnText) 
                DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
            else 
                DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

            DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

            DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 500, 1150, 25, DARKGRAY);

            if (mouseOnText)
            {
                if (letterCount < MAX_INPUT_CHARS)
                {
                    // Draw blinking underscore char
                    if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
                }
                else DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
            }

            if(IsKeyDown(KEY_ENTER))
            {
                EndDrawing();
                return;
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    
}

int Menu()
{
    int selectedline = 1;
    PlaySound(firstmp3);
    SetSoundVolume(firstmp3, 0.5f);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("PACMAN", 300, 200, 200, GOLD);
        DrawText("MADE BY F.SHAHRIARI", 480, 500, 40, BEIGE);
        DrawText("Press ENTER to continue", 600, 1400, 20, GRAY);
        if(IsKeyDown(KEY_DOWN))
        {
            selectedline++;
            if( selectedline > 3)
                selectedline %= 3;
        }
        else if(IsKeyDown(KEY_UP))
        {
            selectedline--;
            if(selectedline < 1)
                selectedline = selectedline % 3 + 3;
        }
        else if(IsKeyDown(KEY_ENTER))
        {
            switch(selectedline)
            {
                case 1:
                    return 1;
                    break;
                case 2:
                    return 2;
                    break;
                case 3:
                    return 3;
                    break;
            }
        }
        switch(selectedline)
        {
            case 1:
                DrawText("1. PLAY", 700, 800, 30, RED);
                DrawText("2. RECORDS", 700, 850, 30, YELLOW);
                DrawText("3. Exit", 700, 900, 30, YELLOW);
                break;
            case 2:
                DrawText("1. PLAY", 700, 800, 30, YELLOW);
                DrawText("2. RECORDS", 700, 850, 30, RED);
                DrawText("3. Exit", 700, 900, 30, YELLOW);
                break;
            case 3:
                DrawText("1. PLAY", 700, 800, 30, YELLOW);
                DrawText("2. RECORDS", 700, 850, 30, YELLOW);
                DrawText("3. Exit", 700, 900, 30, RED);
                break;
        }
        EndDrawing();
    }

    return 0;
}

void DrawWalls()
{
    int i, j;

    for(i = 0; i < MAZE_HEIGHT; i++)
    {
        for(j = 0; j < MAZE_WIDTH; j++)
        {
            if(map[i][j] == '#')
            {
                DrawRectangle(j*pixelSize, i*pixelSize + INFO_BAR_H, pixelSize, pixelSize, BLUE);
            }
            else if(map[i][j] == '.')
            {
                DrawCircle(j*pixelSize+25, i*pixelSize+25 + INFO_BAR_H, 5, YELLOW);
            }
            else if(map[i][j] == 'O')
            {
                DrawCircle(j*pixelSize+25, i*pixelSize+25 + INFO_BAR_H, 10, PINK);
                DrawTexture(cherry, i*pixelSize, j*pixelSize + INFO_BAR_H, WHITE);
            }
            else if(map[i][j] == 'A')
            {
                DrawCircle(j*pixelSize+25, i*pixelSize+25 + INFO_BAR_H, 10, RED);
                //DrawTexture(apple, i*pixelSize, j*pixelSize + INFO_BAR_H, WHITE);

            }
            else if(map[i][j] == 'H')
            {
                //DrawTexture(Hallopino, i*pixelSize, j*pixelSize + INFO_BAR_H, WHITE);
                DrawCircle(j*pixelSize+25, i*pixelSize+25 + INFO_BAR_H, 10, GREEN);
            }
            else if(map[i][j] == 'T')
            {
                //DrawTexture(mushroom, i*pixelSize, j*pixelSize + INFO_BAR_H, WHITE);
                DrawCircle(j*pixelSize+25, i*pixelSize+25 + INFO_BAR_H, 10, PURPLE);
            }
            DrawTexture(G1, Ghost1Pos.x*pixelSize, Ghost1Pos.y*pixelSize + INFO_BAR_H, WHITE);
            DrawTexture(G2, Ghost2Pos.x*pixelSize, Ghost2Pos.y*pixelSize + INFO_BAR_H, WHITE);
            DrawTexture(G3, Ghost3Pos.x*pixelSize, Ghost3Pos.y*pixelSize + INFO_BAR_H, WHITE);
            DrawTexture(G4, Ghost4Pos.x*pixelSize, Ghost4Pos.y*pixelSize + INFO_BAR_H, WHITE);
            DrawTexture(G5, Ghost5Pos.x*pixelSize, Ghost5Pos.y*pixelSize + INFO_BAR_H, WHITE);
        }
    }
}

void Death()
{
    StopSound(music);
    PlaySound(dead);
    lives --;
    //animation
    Texture2D deathFrames[11];
    for (int i = 0; i < 11; i++)
    {
        char filePath[50];
        sprintf(filePath, "resources//sprites//pac//death%d.png", i + 1);
        Image img = LoadImage(filePath);
        deathFrames[i] = LoadTextureFromImage(img);
        UnloadImage(img);
    }

    // Play death animation
    for (int i = 0; i < 11; i++)
    {
        BeginDrawing();
        DrawTexture(deathFrames[i], pacPos.x * pixelSize, pacPos.y * pixelSize + INFO_BAR_H, WHITE);
        EndDrawing();
    }

    // Unload death animation frames
    for (int i = 0; i < 11; i++)
    {
        UnloadTexture(deathFrames[i]);
    }
    pacPos = RandomPos();
    ResumeSound(music);
}

void movment()
{

    int cur_x, cur_y;

    cur_x = (int) round(pacPos.x);
    cur_y = (int) round(pacPos.y);
    
    if(IsKeyDown(KEY_RIGHT) && map[cur_y][cur_x + pacSpeed] != '#')
    {
        pacPos.x += pacSpeed;
        Roatation = 0;
    }
    else if(IsKeyDown(KEY_LEFT) && map[cur_y][cur_x - pacSpeed] != '#')
    {
        pacPos.x -= pacSpeed;
        Roatation = 180;
    }
    else if(IsKeyDown(KEY_UP) && map[cur_y - pacSpeed][cur_x] != '#')
    {
        pacPos.y -= pacSpeed;
        Roatation = 270;
    }
    else if(IsKeyDown(KEY_DOWN) && map[cur_y + pacSpeed][cur_x] != '#')
    {
        pacPos.y += pacSpeed;
        Roatation = 90;
    }

    cur_x = (int) round(pacPos.x);
    cur_y = (int) round(pacPos.y);

    if(map[cur_y][cur_x] == '.')
    {
        PlaySound(munch1);
        SetSoundVolume(munch1, 0.07f);
        score += 10;
        Snackes--;
        map[(int) pacPos.y][(int) pacPos.x] = ' ';
    }
    else if(map[cur_y][cur_x] == 'O')
    {
        PlaySound(credit);
        SetSoundVolume(credit, 0.07f);
        score += 50;
        Snackes --;
        EatGhostTime = 7 * framerate; // seconds
        map[cur_y][cur_x] = ' ';
        PauseSound(music);
        PlaySound(frightendtime);
    }
    else if(map[cur_y][cur_x] == 'A')
    {
        PlaySound(credit);
        SetSoundVolume(credit, 0.07f);
        score += 50;
        lives += 1;
        Snackes --;
        map[cur_y][cur_x] = ' ';
    }
    else if(map[cur_y][cur_x] == 'H')
    {
        PlaySound(credit);
        SetSoundVolume(credit, 0.07f);
        score += 50;
        Snackes --;
        framerate = 60;
        SpeedyTime += 7 * framerate; // seconds
        map[cur_y][cur_x] = ' ';
        PauseSound(music);
        PlaySound(frightendtime);
    }
    else if(map[cur_y][cur_x] == 'T')
    {
        PlaySound(credit);
        SetSoundVolume(credit, 0.07f);
        score += 50;
        Snackes --;
        map[cur_y][cur_x] = ' ';
        Death(); //death animation!
    }
    
    else if(pacPos.x == Ghost1Pos.x && pacPos.y == Ghost1Pos.y)
    {
        if(EatGhostTime <= 0)
        {
            Death();
        }
        else
        {
            PlaySound(credit);
            SetSoundVolume(credit, 0.07f);
            score += 200;
            Ghost1Pos = RandomPos();
        }
        
    }
    else if(pacPos.x == Ghost2Pos.x && pacPos.y == Ghost2Pos.y)
    {
        if(EatGhostTime <= 0)
        {
            Death();
        }
        else
        {
            PlaySound(credit);
            SetSoundVolume(credit, 0.07f);
            score += 200;
            Ghost2Pos = RandomPos();
        }
        
    }
    else if(pacPos.x == Ghost3Pos.x && pacPos.y == Ghost3Pos.y)
    {
        if(EatGhostTime <= 0)
        {
            Death();
        }
        else
        {
            PlaySound(credit);
            SetSoundVolume(credit, 0.07f);
            score += 200;
            Ghost3Pos = RandomPos();
        }
        
    }
    else if(pacPos.x == Ghost4Pos.x && pacPos.y == Ghost4Pos.y)
    {
        if(EatGhostTime <= 0)
        {
            Death();
        }
        else
        {
            PlaySound(credit);
            SetSoundVolume(credit, 0.07f);
            score += 200;
            Ghost4Pos = RandomPos();
        }
        
    }
    else if(pacPos.x == Ghost5Pos.x && pacPos.y == Ghost5Pos.y)
    {
        if(EatGhostTime >= 0)
        {
            Death();
        }
        else
        {
            PlaySound(credit);
            SetSoundVolume(credit, 0.07f);
            score += 200;
            Ghost5Pos = RandomPos();
        }
        
    }

    Ghost1Pos = RandomGhostMove(Ghost1Pos.x, Ghost1Pos.y);

    Ghost2Pos = RandomGhostMove(Ghost2Pos.x, Ghost2Pos.y);

    Ghost3Pos = RandomGhostMove(Ghost3Pos.x, Ghost3Pos.y);

    Ghost4Pos = RandomGhostMove(Ghost4Pos.x, Ghost4Pos.y);

    Ghost5Pos = RandomGhostMove(Ghost5Pos.x, Ghost5Pos.y);

}


void GameLoop()
{
    Texture selectedtxt = pac2;
    PlaySound(music);
    while (!WindowShouldClose() && lives > 0)
    {
        if(IsKeyDown(KEY_BACKSPACE))
        {
            menu = 0;
            lives = 0;
            StopSound(music);
            return;
        }
        animFrame += 1;
        if (animFrame > framerate)
            animFrame = 0;
        selectedtxt = (animFrame > framerate / 2) ? pac1 : pac2;
        if (Snackes <= 0)
            makingSnackes();
        if (SpeedyTime > 0)
            SpeedyTime--;
        else
            framerate = 10;
        if(!IsSoundPlaying(frightendtime))
        {
            ResumeSound(music);
            if(!IsSoundPlaying(music))
                PlaySound(music);
        }
        if(EatGhostTime == 1)
            framerate = 10;
        if (EatGhostTime > 0)
            EatGhostTime--;

        BeginDrawing();
        ClearBackground(BLACK);
        movment();
        DrawWalls();
        DrawTexture(selectedtxt, pacPos.x * pixelSize, pacPos.y * pixelSize + 60, WHITE);
        for (int i = lives; i > 0; i--)
        {
            DrawTexture(pac2, 10 + (i - 1) * pixelSize, 0, WHITE);
        }
        DrawText(TextFormat("Score: %d", score), 900, 10, pixelSize, WHITE);
        EndDrawing();
    }

    StopSound(music);
    StopSound(frightendtime);
    return;
}

void RecordScore()
{
    //FILE *fp = fopen("scores.txt", "a");
    // getting date
    char date[11]; // Buffer size for "YYYY-MM-DD" format
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(date, sizeof(date), "%Y-%m-%d", timeinfo);

    //fprintf(fp, "%s %s %d\n", name, date, score);

    //fclose(fp);

    FILE *file = fopen("scores.bin", "ab");

    record r;  
    strcpy(r.name, name); 
    strcpy(r.date, date); 
    r.score = score;

    fwrite(&r, sizeof(record), 1, file);  

    fclose(file);  
}

void EndOfGame()
{
    PlaySound(gameover);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(GameOver, 500, 200, WHITE);
        DrawText(name, 600, 1100, 50, WHITE);
        DrawText(TextFormat("score: %d", score), 600, 1200, 50, WHITE);
        DrawText("Press ENTER to continue", 600, 1400, 20, GRAY);
        DrawText("Press ESC to close", 600, 1450, 20, GRAY);
        EndDrawing();
        if (IsKeyDown(KEY_ENTER))
            break;
        
    }
}

void ShowRecords()
{
    PlaySound(firstmp3);
    SetSoundVolume(firstmp3, 0.5f);
    char str[100];
    int count;

    FILE *file = fopen("scores.bin", "rb");
      

    // Get the number of records in the file  
    fseek(file, 0, SEEK_END);  
    int numRecords = ftell(file) / sizeof(record);  
    rewind(file);  

    if (numRecords == 0) 
    {  
        fclose(file);
        while(!WindowShouldClose())
        { 
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("NO RECORDS FOUND!", 500, 500, 55, RED);
            DrawText("Press BACKSPACE to get back to menu.", 500, 1400, 25, GRAY);
            EndDrawing();
            if(IsKeyDown(KEY_BACKSPACE))
            {
                menu = 0;
                return;
            }

        } 
    }  

    record *records = (record*)malloc(numRecords * sizeof(record));  
    fread(records, sizeof(record), numRecords, file);  

    fclose(file);  

    // Sort scores  
    for (int i = 0; i < numRecords; i++) {  
        for (int j = i + 1; j < numRecords; j++) {  
            if (records[i].score < records[j].score) {  
                record temp = records[i];  
                records[i] = records[j];  
                records[j] = temp;  
            }  
        }  
    }  

    count = (numRecords < 10) ? numRecords : 10;

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        for(int i = 0 ; i < count ; i++)
        {
            sprintf(str, "%s %s %d", records[i].name, records[i].date, records[i].score);
            DrawText(str, 400, i*pixelSize  + 100, 40, WHITE);
        }
        
        DrawText("Press BACKSPACE to get back to menu.", 500, 1400, 25, GRAY);
        EndDrawing();
        if(IsKeyDown(KEY_BACKSPACE))
        {
            menu = 0;
            free(records);
            return;
        }
    } 
}

int main(void)
{
    srand(time(NULL));
    InitWindow(windowWidth, windowHeight, "PACMAN");
    InitAudioDevice();
    SetTargetFPS(framerate);
    loadTextures();
    loadSounds();
    GettingName();

    while (!WindowShouldClose())
    {
        menu = Menu();
        switch (menu)
        {
        case 1:
            StartOfGame();
            if(menu == 0)
                continue;
            GameLoop();
            EndOfGame();
            RecordScore();
            break;
        case 2:
            ShowRecords();
            break;
        case 0:
            continue;
        }
        if(menu == 3)
            break;
    }

    UnloadSounds();
    CloseAudioDevice();
    CloseWindow();

    return 0;
}