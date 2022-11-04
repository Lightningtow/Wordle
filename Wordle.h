//
// Created by alexw on 10/31/2022.
//

#ifndef WORDLE_WORDLE_H
#define WORDLE_WORDLE_H

//#include <string>
#include <iostream>
#include <algorithm>
//#include <windows.h>

using namespace std;

class Wordle {
private:
//    void displayEverything(const char[], const string[]);
    void displayEverything(const bool);
//void displayBoard(const char[]);
    bool validWord(string&);
//    string letterCheck(char[], const string&, char);
    void create_rgb();
    void findTarget();
//    void displayBoard(const char[]) const;



    char displayboard[29] = {'q','w','e','r','t','y','u','i','o','p','\n',
                             'a','s','d','f','g','h','j','k','l','\n',
                             'z','x','c','v','b','n','m','\0'};

//    char targetword[6] = {'h','e','l','l','o','\0'};
    string targetword = "hello";
    bool allvalid = false;
//    static string targetword;
    char inputword[6]  = {'w','o','r','l','d','\0'};
//    static string inputword;
    string inputstr;
    string greenlist;
    string yellowlist;
//    char greenlist[5];
//    char yellowlist[6];
    string guesses[2][6] = {" ", " "," ", " "," ", " ",
                            " ", " "," ", " "," ", " "};
    // guesses[0][x] is word guess, guesses[1][x] is colors for the guess
//    string guesscolors[6] = {" ", " "," ", " "," ", " "};
    int guesscount = 0;



public:
    Wordle();
//    static void wordleRun();
    void playWordle();
};


#endif //WORDLE_WORDLE_H
