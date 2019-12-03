//This inserts the color as an integer into chicken update.
//Within chicken update, a switchcase decides what color the chicken is.

//For the next level, I made it so every 5 levels it increases the speed (via a for loop up to level 50)

//It should go back to the menu now after pressing the button

//Make cars go the same way - Solved this by making a separate array and then comparing values with a switchcase
//Not pretty but it should work

//Return Highscores - I made a function within class World to return the level they died on.
//This is appended to an array (similar to python) and then sorted in descending order. - This requires something called a vector in C
//The score screen will display the top 5 scores - tap to proceed









//Haven't Done yet
//Fix Button Delay - honestly it might work to just paste that code several times in the main function
//If so, pass the buttons into a function to make it easier to call instead of copying and pasting 15 lines
//@James i think buttons is an object? not sure so plz elaborate - look something like this: moveDirection = pressedButtons(buttons)
// where -  int pressedButtons(ButtonBoard)  - returns an integer

//Fix wacky rectangles - I have no idea why this is happening. Plz help @brain


#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <LCDColors.h>
#include <FEHRandom.h>
//#include <vector>
//#include <bits/stdc++.h>
using namespace std;
//#include <iostream>
//#include <string.h>
//#include <time.h>
//#include <cstdlib>

class World
{
    public:
    //Initialize all variables, I don't think I need this constructor function
    World();
    //In the case of the next level, this will reinitialize all the car coordinates and increase speed and level
    void nextLevel(ButtonBoard);

    //These will just update the variables themselves
    void chickenUpdate(int);
    void carsUpdate();

    //This will print the variables
    void screenUpdate(int);

    //This will check for collisions
    void checkCollisions();

    //This will check to keep on running the game and level flags
    bool checkGameFlag();
    bool checkLevelFlag();

    //This will return the Level
    int checkLevel();

    void reset();

    int rate;

    private:
    //x and y coordinates for the chicken and cars
    int xchicken, ychicken, ChickenColor;
    int xcars[15], ycars[15], dircars[15];
    //speed and level
    int speed;
    int level;
    //This will make it easier to modify within the functions
    //A check____Flag function will be made to return a boolean value for the real flag
    bool GameFlag, LevelFlag;

};



int main(void)
{
    bool GameFlag = true;
    bool LevelFlag = true;
    float x, y, xi, yi, x3, y3, x1, y1;
    int moveDirection, newScore, ChickenColor=1;
    int highscore=0, lastscore=0;
    bool keepPlay;
    World world;
    ButtonBoard buttons(FEHIO::Bank0);
    LCD.SetBackgroundColor(FEHLCD::Black);
    LCD.Clear();
    LCD.SetFontColor(FEHLCD::White);
    //vector<int> scoreBoard;
   // std::srand(0);

    LCD.Write("Welcome to Crossy TA!  Help the TA cross the road without getting hit by any cars!  Touch anywhere to continue.");
    while(!LCD.Touch(&x,&y)) {}
    while(LCD.Touch(&x1, &y1)) {}
    LCD.SetBackgroundColor(FEHLCD::Black);
    LCD.Clear();

    while(true)
    {
        //Draw Pretty Rectangles
        LCD.SetFontColor(FEHLCD::Red);
        LCD.FillRectangle(0, 0, 160, 240);
        LCD.SetFontColor(FEHLCD::Green);
        LCD.FillRectangle(160, 0, 80, 120);
        LCD.SetFontColor(FEHLCD::Blue);
        LCD.FillRectangle(240, 0, 80, 120);
        LCD.SetFontColor(FEHLCD::Gray);
        LCD.FillRectangle(160, 120, 80, 120);
        LCD.SetFontColor(FEHLCD::Scarlet);
        LCD.FillRectangle(240, 120, 80, 120);

        //Print names to screen
        LCD.SetFontColor(FEHLCD::White);
        LCD.WriteAt("Play", 70, 110);
        LCD.WriteAt("Score", 190, 50);
        LCD.WriteAt("Shop", 270, 50);
        LCD.WriteAt("Rules", 190, 170);
        LCD.WriteAt("Credits", 270, 170);

        //Touch Inputs to save
        while(!LCD.Touch(&x,&y)) {
        }
        while(LCD.Touch(&x1, &y1)) {
            x = x1;
            y = y1;
        }

        if(x < 160)
        {
            keepPlay = true;
            while(keepPlay)
            {
                while (GameFlag)
                {
                    LevelFlag = true;
                    //This will initialzie all the basic positions of the cars and the chicken
                    //LCD.WriteLine("Next Level");
                    world.nextLevel(buttons);
                    while (LevelFlag)
                    {

                        if(buttons.LeftPressed())
                        {
                            moveDirection = 1;
                        }
                        else if(buttons.RightPressed())
                        {
                            moveDirection = 2;
                        }
                        else if(buttons.MiddlePressed())
                        {
                            moveDirection = 3;
                        }

                        //chickenUpdate and carsUpdate can be grouped together into the same function
                        world.chickenUpdate(moveDirection);

                        //This should not be necessary due to the the bool Touched value
                        moveDirection = 0;

                        // Update coordinates of the cars
                        world.carsUpdate();

                        // Print the coordinates of cars and chicken to the screen
                        world.screenUpdate(ChickenColor);

                        //Check for collisions/position of ychicken and change LevelFlag and GameFlag accordinly
                        world.checkCollisions();

                        //Check the flags withing class world
                        LevelFlag = world.checkLevelFlag();
                        GameFlag = world.checkGameFlag();

                        //This is the refresh rate - 1 ms
                        Sleep(world.rate);
                    }

                }
                //Print GameOver
                LCD.Clear (FEHLCD :: Black);
                LCD.WriteAt ("Game Over", 120, 20);

                lastscore = world.checkLevel()-1;
                if(lastscore > highscore)
                {
                    highscore = lastscore;
                }

                //Vector stuff here
                newScore = world.checkLevel();
                //scoreBoard.insert(vec.begin(), newScore);
                //Sleep(5.0);
                //LCD.Clear (FEHLCD :: Black);
                LCD.WriteAt ("Score: ", 120, 50);
                LCD.WriteAt (lastscore, 190, 50);
                LCD.WriteAt ("Press right to continue", 20, 80);
                LCD.WriteAt ("Press left for menu", 25, 110);

                while(!buttons.LeftPressed() && !buttons.RightPressed());
                while(buttons.LeftPressed() || buttons.RightPressed())
                {
                    if(buttons.LeftPressed())
                    {
                        keepPlay = false;
                        world.reset();
                        GameFlag = true;
                        LevelFlag = true;
                    }
                    else
                    {
                        world.reset();
                        GameFlag = true;
                        LevelFlag = true;
                    }
                }
            }
        }//end of game if

        else if (x < 240 && y < 120){
                    //Score Function
                    int ScoreFlag = 1;
                    while (ScoreFlag == 1){
                        LCD.SetBackgroundColor(FEHLCD::Black);
                        LCD.Clear();
                        LCD.WriteAt ("High score: ", 20, 80);
                        LCD.WriteAt (highscore, 150, 80);
                        LCD.WriteAt ("Last score: ", 20, 110);
                        LCD.WriteAt (lastscore, 150, 110);
                        LCD.WriteAt ("Touch to continue", 20, 140);
                        while(!LCD.Touch(&x,&y)) {
                        }
                        while(LCD.Touch(&x1, &y1)) {
                            x = x1;
                            y = y1;
                        }
                        ScoreFlag = 0;
                        LCD.SetBackgroundColor(FEHLCD::Black);

                    }
                }//end of score if

        else if (y < 120){
                    //Shop Function
                    bool ShopFlag = true;
                    LCD.SetBackgroundColor(FEHLCD::Black);
                    LCD.Clear();
                    LCD.SetFontColor (FEHLCD::White);
                    LCD.Write("Pick your color below");
                    while (ShopFlag){
                        //This is the exit button
                        LCD.SetFontColor(FEHLCD::Red);
                        LCD.FillRectangle(0,200,40,40);
                        LCD.FillRectangle(20,20,30,30);

                        LCD.SetFontColor(FEHLCD::Green);
                        LCD.FillRectangle(60,20,30,30);

                        LCD.SetFontColor(FEHLCD::Blue);
                        LCD.FillRectangle(100,20,30,30);

                        LCD.SetFontColor(FEHLCD::Scarlet);
                        LCD.FillRectangle(140,20,30,30);

                        LCD.SetFontColor(FEHLCD::Gray);
                        LCD.FillRectangle(180,20,30,30);

                        LCD.SetFontColor (FEHLCD::White);
                        LCD.WriteAt("Exit", 0, 200);

                        while(!LCD.Touch(&x,&y)) {
                        }
                        while(LCD.Touch(&x1, &y1)) {
                            x = x1;
                            y = y1;
                        }

                        if(y > 20 && y < 50){
                            if (x < 50 && x > 20){
                                ChickenColor = 0;
                            }
                            if (x < 90 && x > 60){
                                ChickenColor = 1;
                            }
                            if (x < 130 && x > 100){
                                ChickenColor = 2;
                            }
                            if (x < 170 && x > 140){
                                ChickenColor = 3;
                            }
                            if (x < 210 && x > 180){
                                ChickenColor = 4;
                            }
                        }
                        if (y > 200 && x < 40){
                            ShopFlag = false;
                            LCD.SetBackgroundColor(FEHLCD::Black);
                        }
                    }
                }//end of shop if
        else if(x < 240)
        {
            LCD.SetBackgroundColor(FEHLCD::Black);
            LCD.Clear();
            LCD.SetFontColor (FEHLCD::White);
            LCD.Write("Press the middle button to jump forwards.  Press the left and right buttons to move left and right.  If you make it to the top of the screen, you move to the next level.  Don't get hit by any cars or you'll DIE.  Have fun!");
            while(!LCD.Touch(&x,&y)) {}
            while(LCD.Touch(&x1, &y1)) {}
        }//end of rules if
        else
        {
            LCD.SetBackgroundColor(FEHLCD::Black);
            LCD.Clear();
            LCD.SetFontColor (FEHLCD::White);
            LCD.Write("Game created by James Johnson & Matt Hu AKA the QT Creators ;)");
            while(!LCD.Touch(&x,&y)) {}
            while(LCD.Touch(&x1, &y1)) {}
        }//end of credits if


    }
}

World::World()
{
    speed = 1;
    rate = 200;
    level = 1;
}

//This function imports an integer moveDirection taken from the main source code
//I do not know if this is allowed or possible, consult with James, Ian, Brian, Sean or some other god-tier programmer
//Moving left or right will move 15 pixels while hopping will move 30 pixels forwards or backwards
void World :: chickenUpdate(int moveDirection){
    switch (moveDirection){
        case 0:
            break;
        case 1:
            xchicken -= 15;
            break;
        case 2:
            xchicken += 15;
            break;
        case 3:
            ychicken -= 30;
            break;
    }
}

//This will move the cars left or right
//This function may change if fillRectangle still works from a negative value (ex: an x = -15 will still show half of the block on the screen)
void World :: carsUpdate(){
    int i;

    for (i=0; i < 15; i++){

        // cars move left
        if (dircars[i] == 0){
            xcars[i] += speed;
        }
        // cars move right
        else if (dircars[i] == 1){
            xcars[i] -= speed;
        }

        //if the cars go off the edge it will reinitialize on the other side
        //yes if this goes too quickly, there is absolutely no chance to win
        if (xcars[i] <= 0 && dircars[i] == 0){
            xcars[i] = 320;
        }
        if (xcars[i] >= 320 && dircars[i] == 1){
            xcars[i] = 0;
        }
    }
}

//This will clear the screen to black, fill a blue rectangle (for chicken), and fill 15 white squares(for cars)
//This will update all the changes made in carsUpdate and chickenUpdate
void World :: screenUpdate(int colorNum){
    //Initializing ChickenColor
    int ChickenColor = colorNum;
    //Clear the entire screen as black
    LCD.Clear(FEHLCD :: Black);
    //Set the font color for the chicken and set the font color to white for the cars
    switch(ChickenColor){
        case 0:
            LCD.SetFontColor(FEHLCD :: Red);
            break;
        case 1:
            LCD.SetFontColor(FEHLCD :: Green);
            break;
        case 2:
            LCD.SetFontColor(FEHLCD :: Blue);
            break;
        case 3:
            LCD.SetFontColor(FEHLCD :: Scarlet);
            break;
        case 4:
            LCD.SetFontColor(FEHLCD :: Gray);
            break;
    }
    LCD.FillRectangle(xchicken, ychicken, 30, 30);
    LCD.SetFontColor(FEHLCD :: White);
    for(int i = 0 ; i < 15 ; i++){
        LCD.FillRectangle(xcars[i], ycars[i], 30, 30);
    }
}

//This will increment the speed of the cars and level
//This will reinitialize the coordinates of x and y chicken in the center
//This will "randomly" generate cars x positions;  the y positions are set for 2 per row
//This will "randomly" generate 0s and 1s for dircars
void World :: nextLevel(ButtonBoard buttons){
    LCD.Clear (FEHLCD :: Black);
    LCD.WriteAt ("Level ", 120, 80);
    LCD.WriteAt (level, 195, 80);
    LCD.WriteAt ("Press the left/right button", 0, 120);

    while(!buttons.LeftPressed() && !buttons.RightPressed());
    while(buttons.LeftPressed() || buttons.RightPressed());

    int i;
    int array1[7];
    //speed += 1;
    rate -= 30;
    level += 1;
    for (i=1 ; i < 11; i++){
        if(level == 5*i)
        {
            rate = 200;
            speed += 1;
        }
    }

    xchicken = 145;
    ychicken = 210;
    LevelFlag = true;

    for (i = 0 ; i < 15 ; i++){
        xcars[i] = (Random.RandInt()%320);
    }
    for (i = 0 ; i < 15 ; i++){
        ycars[i] = (Random.RandInt()%7) * 30;
    }
    for (i=0;  i < 7 ; i++){
        array1[i] = (Random.RandInt()%2);
    }
    for (i=0; i<15 ; i++){
        switch(ycars[i]){
            case 0:
                dircars[i] = array1[0];
                break;
            case 30:
                dircars[i] = array1[1];
                break;
            case 60:
                dircars[i] = array1[2];
                break;
            case 90:
                dircars[i] = array1[3];
                break;
            case 120:
                dircars[i] = array1[4];
                break;
            case 150:
                dircars[i] = array1[5];
                break;
            case 180:
                dircars[i] = array1[6];
                break;

        }
    }
}

//This function will take ychicken, if 0 the level will advance
//else, it will cycle through all ycars and if equal to ychicken will compare the line to the beginning or end points of the cars
void World :: checkCollisions(){
    int i;
    int j;
    //Level advance
    if (ychicken == 0){
        LevelFlag = false;
    }
    //Compare to cars
    else {
        for (j = 0 ; j < 15 ; j++){
            if (ychicken == ycars[j]){
                for (i=0 ; i<=30 ; i++){
                    if (xchicken + i == xcars[j] || xchicken + i == xcars[j] + 30){
                        LevelFlag = false;
                        GameFlag = false;
                    }
                }
            }
        }
    }
}

//This will return a boolean value to the real Level and Game Flags
bool World :: checkLevelFlag (){
    return LevelFlag;
}
bool World :: checkGameFlag (){
    return GameFlag;
}

int World::checkLevel(){
    return level;
}

void World::reset()
{
    speed = 1;
    rate = 200;
    level = 1;
    GameFlag = true;
    LevelFlag = true;
}
