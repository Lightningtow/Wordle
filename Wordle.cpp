//
// Created by alexw on 10/31/2022.
//

#include <fstream>
//#include <bits/stdc++.h>
#include "Wordle.h"
#include <algorithm>
#include <random>

using namespace std;

void Wordle::create_rgb() { //this automatically creates an rgb string for empty spaces

    string newrgb;
    for(int i = 0; i < 5; i++) {

        if(guesses[0][guesscount][i] == targetword[i]) { // if green
            greenlist += guesses[0][guesscount][i];
            newrgb += 'g';
        }

        else if(targetword.find(guesses[0][guesscount][i]) == string::npos) { // if not found, meaning red

            newrgb += 'r';

            for(int j = 0; j < 29; j++) { // remove from displayboard
                if (guesses[0][guesscount][i] == displayboard[j]) displayboard[j] = ' ';
            }

        }
        else { // if its not in perfect position, but it is in string, then yellow?
            yellowlist += guesses[0][guesscount][i];
            newrgb += 'y';
        }
            // cout << "not in string" << endl;
//        if (guesses[0][guesscount] == search(targetword.begin(), targetword.end(), guesses[0][guesscount]))
//        cout << newrgb << endl;
    }
    guesses[1][guesscount] = newrgb;

//

}


bool Wordle::validWord(string& input) {
    //todo should eventually check if valid english word
    // would also make everything here unnecessary
    if(input.length() != 5) return false;
    if(allvalid) return true;
    transform(input.begin(), input.end(), input.begin(), ::tolower);

    ifstream fileInput;
//    fileInput.open(R"(C:\Users\alexw\CLionProjects\wordle\accepted_answers.txt)", ios::in);
    fileInput.open("../accepted_answers.txt", ios::in);

    string line;
    int curLine;
//    fileInput.open("target_words.txt");

    if(fileInput.is_open()) {
        while (getline(fileInput, line)) { // I changed this, see below
            curLine++;
            if (line.find(input) != string::npos) {
//                cout << "found: " << input << ", line: " << curLine << endl;
                fileInput.close();
                return true;
            }
        }
//        cout << "invalid" << endl;
        fileInput.close();
        return false;
    }
    else cout << "Unable to open file." << endl;
    exit(3);

}

//void Wordle::displayEverything(const char * board, const string * guesses) {
void Wordle::displayEverything(bool showboard) {
//    system(("chcp "s + std::to_string(CP_UTF8)).c_str());

//    cout << "\033[31mHello\033[0m" << endl;

    cout << "==========================================" << endl;
    for(int i = 0; i < 6; i++) { // for all 6 words
//        cout << i+1 << ") " << "\033[31m" << guesses[0][i] << "\033[0m" << endl;
        cout << " " << i+1 << ")  ";
        for(int j = 0; j < 5; j++) { // for all 5 letters
//            cout << "i == " << i << ", j == " << j << endl;
//            cout << "x";
            if(guesses[1][i][j] == 'r')
                cout << guesses[0][i][j];
//                cout << "\033[31m" << guesses[0][i][j] << "\033[0m";
            else if(guesses[1][i][j] == 'g')
                cout << "\033[32m" << guesses[0][i][j] << "\033[0m";
            else if(guesses[1][i][j] == 'y')
                cout << "\033[33m" << guesses[0][i][j] << "\033[0m";

            cout << " ";
        }
        cout << " " << endl;
    }
    cout << " " << endl;



    // displayboard
//    for(int i = 0; i < 28; i++) {
//        if (i == 21) cout << "  "; // provide indentation for last line
//        cout << displayboard[i] << " ";
//    } cout << endl;

    if(showboard) {
        cout << " " << endl;
        for(int i = 0; i < 28; i++) {
            if (i == 21) cout << "   "; // provide indentation for last line
            if(greenlist.find(displayboard[i]) != string::npos) cout << "\033[32m" << displayboard[i] << "\033[0m";
            else if(yellowlist.find(displayboard[i]) != string::npos) cout << "\033[33m" << displayboard[i] << "\033[0m";
            else cout << displayboard[i];

            cout << " ";
        } cout << endl;
    }
}

void Wordle::playWordle() {

    findTarget();
    bool flag = false;
    while(!flag) {
        cout << ">> ";
        getline(cin, inputstr);



        if (validWord(inputstr)) {
            guesses[0][guesscount] = inputstr;
//            guesses[1][guesscount] = create
            create_rgb();
            guesscount++;
//            cout << "valid" << endl;

//            for(int i = 0; i < 5; i++) {
//                inputword[i] = inputstr[i];
//            } inputword[5] = '\0';


//            cout << inputstr << endl;
//            cout << targetword << endl;
//        cout << inputstr << endl;

            if (inputstr == targetword) {
                flag = true;
                displayEverything(false);

                cout << "Word found!" << endl;
                exit(42);
//                flag = true;
            }
            else {
                for(int i = 0; i < 5; i++) {
//                    letterCheck(displayboard, targetword, inputstr[i]);
                }
            }

//            displayEverything(displayboard, guesses);
            displayEverything(true);
        }

        else if(inputstr == "ALLVALID") { allvalid = !allvalid; cout << "allvalid toggled to " << boolalpha << allvalid << endl; }
        else if(inputstr == "TELLME") cout << targetword << endl;
        else if(inputstr == "FORCEQUIT") exit(-1);


        else cout << "invalid" << endl;
        cout << endl;


//        cout << (targetword == inputword);
    }

}

void Wordle::findTarget() {
    ifstream fileInput;
//    fileInput.open(R"(C:\Users\alexw\CLionProjects\wordle\accepted_answers.txt)", ios::in);
    fileInput.open("../target_words.txt", ios::in);
    string line;
    int randline = 0;
    int curLine = 0;

    if(fileInput.is_open()) {
        while (getline(fileInput, line)) { // I changed this, see below
            curLine++;
        }
//        cout << curLine << endl;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, curLine);
        randline = dis(gen);

//        cout << randline << endl;
        fileInput.close();

        fileInput.open("../target_words.txt", ios::in);

        int linesRead = 0;
        if(fileInput.is_open()) {
            while (getline(fileInput, line)) { // I changed this, see below
                linesRead++;
                if(linesRead == randline) {
//                    cout << line << endl;
                    targetword = line;
                    return;
                }
            }

//            cout << randline << endl;
            fileInput.close();
        }
        else {
            cout << "Unable to open inner file." << endl;
            exit(3);
        }
    }
    else {
        cout << "Unable to open outer file." << endl;
        exit(3);
    }

    cout << "NO TARGET SET" << endl;
}


Wordle::Wordle() = default;
