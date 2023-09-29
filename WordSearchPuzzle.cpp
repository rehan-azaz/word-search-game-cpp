#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <unistd.h>

using namespace std;

void displayMainMenu();
void startNewGame();
int selectLevel(int);
void displayHighScore();
void startEasyPuzzle();
void startIntermediatePuzzle();
int countWords();

int main()
{
    displayMainMenu();

    return 0;
}

void displayMainMenu()
{
    system("clear");
    cout << "\t\t##### Word Search Puzzle ##### \n";
    cout << "\t 1. New Game \n";
    cout << "\t 2. Select Game Level \n";
    cout << "\t 3. High Score \n";
    cout << "\t 4. Exit \n";

    int inputOption = 0;

    cout << "Select an option. Enter a value from 1 to 4." << endl;

    cin >> inputOption;

    switch (inputOption)
    {
    case 1:
        startNewGame();
        break;
    case 2:
        selectLevel(0);
        break;
    case 3:
        displayHighScore();
        break;
    default:
        exit(1);
        break;
    }
}

void startNewGame()
{
    system("clear");
    cout << "\t\t##### Word Search Puzzle ##### \n";

    string gameLevel;

    ifstream readGameLevel("gameLevel.txt");

    getline(readGameLevel, gameLevel);

    if (gameLevel == "")
    {
        gameLevel = "1";
        gameLevel = to_string(selectLevel(stoi(gameLevel)));
    }
    readGameLevel.close();
    if (gameLevel == "1")
    {
        startEasyPuzzle();
    }

    if (gameLevel == "2")
    {
        startIntermediatePuzzle();
    }
}

int selectLevel(int setLevel = 0)
{
    if (setLevel != 0)
    {
        ofstream writeGameData("gameLevel.txt");

        writeGameData << setLevel << endl;

        writeGameData.close();
        return setLevel;
    }
    else
    {
        system("clear");
        cout << "\t\t##### Select Game Level ##### \n";
        cout << "\t 1. Easy \n";
        cout << "\t 2. Intermediate \n";
        cout << "\t 3. Main Menu \n";
        cout << "\t 4. Exit \n";

        int gameLevelInput = 0;

        cout << "Select an option. Enter a value from 1 to 4." << endl;

        cin >> gameLevelInput;

        if (gameLevelInput == 1 || gameLevelInput == 2)
        {
            ofstream writeGameData("gameLevel.txt");

            writeGameData << gameLevelInput;

            writeGameData.close();

            if (gameLevelInput == 1)
            {
                cout << "Easy Level Selected.\n";
            }
            else if (gameLevelInput == 2)
            {
                cout << "Intermediate Level Selected.\n";
            }
            usleep(2000000);
            displayMainMenu();
        }
        else if (gameLevelInput == 3)
        {
            displayMainMenu();
        }
        else
        {
            exit(1);
        }
    }
    return setLevel;
}

void displayHighScore()
{
    system("clear");
    cout << "\t\t##### High Score ##### \n";

    string highScore;

    ifstream readHighScore("highScore.txt");

    while (getline(readHighScore, highScore))
    {
        cout << "\tHigh Score is: " << highScore << endl;
    }

    readHighScore.close();

    cout << "\n\n\t 1. Main Menu \n";
    cout << "\t 2. Exit \n";

    int inputOption = 0;

    cout << "Select an option. Enter a value from 1 or 2." << endl;

    cin >> inputOption;

    switch (inputOption)
    {
    case 1:
        displayMainMenu();
        break;
    default:
        exit(1);
        break;
    }
}

void startEasyPuzzle()
{
    int dictLen = countWords();

    string dict[dictLen] = {};

    ifstream readDict("dictionary.txt");

    for (int c = 0; c < dictLen; c++)
    {
        readDict >> dict[c];
    }

    readDict.close();

    int puzzleRow = 10;
    int puzzleCol = 10;

    char puzzle[puzzleRow][puzzleCol] = {};

    srand(time(NULL));
    int score = 0;
    do
    {
        for (int i = 0; i < puzzleRow; i++)
        {
            for (int j = 0; j < puzzleCol; j++)
            {
                puzzle[i][j] = 'a' + rand() % 26;
            }
        }

        int puzzleIndex = rand() % dictLen;
        int position = rand() % 2;
        string word = dict[puzzleIndex];
        cout << word << endl;
        int wordLen = word.length();

        if (position)
        {
            int row = rand() % 10;
            int col = rand() % 10;

            if ((wordLen >= 5 && col >= 5))
            {
                col -= wordLen;
            }

            for (int i = 0; word[i] != '\0'; i++)
            {
                puzzle[row][col] = word[i];
                col++;
            }
        }
        else
        {
            int row = rand() % 10;
            int col = rand() % 10;

            if ((wordLen >= 5 && row >= 5))
            {
                row -= wordLen;
            }

            for (int i = 0; word[i] != '\0'; i++)
            {
                puzzle[row][col] = word[i];
                row++;
            }
        }
        system("clear");
        cout << "\t\t##### Word Search Puzzle ##### \n\n";

        for (int i = 0; i < puzzleRow; i++)
        {
            cout << "\t" << i << "\t";
            for (int j = 0; j < puzzleCol; j++)
            {
                cout << puzzle[i][j] << "  ";
            }
            cout << endl;
        }

        string guess;

    replay:
        cout << "\nSearch a word in the puzzle:   ";

        cin >> guess;

        if (guess == word)
        {
            score++;
            cout << "\nCongratulations!!! You found the word.";
            cout << "\n\n Do you want to play again? (y/n)  ";
            cin >> guess;
            if (guess == "y")
            {
                continue;
            }
            if (guess == "n")
            {
                break;
            }
        }
        else
        {
            cout << "\nWrong Answer! ";
            cout << "\nGuess Again? (y/n)  ";
            cin >> guess;
            if (guess == "y")
            {
                goto replay;
            }
            if (guess == "n")
            {
                break;
            }
        }
    } while (true);

    cout << "\nYour Score is " << score << endl;

    int highScore;

    ifstream readHighScore("highScore.txt");

    readHighScore >> highScore;

    readHighScore.close();

    if (highScore < score)
    {
        ofstream writeHighScore("highScore.txt");

        writeHighScore << score << endl;

        writeHighScore.close();
    }
}

void startIntermediatePuzzle()
{
    int dictLen = countWords();

    string dict[dictLen] = {};

    ifstream readDict("dictionary.txt");

    for (int c = 0; c < dictLen; c++)
    {
        readDict >> dict[c];
    }

    readDict.close();

    int puzzleRow = 10;
    int puzzleCol = 10;

    char puzzle[puzzleRow][puzzleCol] = {};

    srand(time(NULL));
    int score = 0;
    do
    {
        for (int i = 0; i < puzzleRow; i++)
        {
            for (int j = 0; j < puzzleCol; j++)
            {
                puzzle[i][j] = 'a' + rand() % 26;
            }
        }

        int puzzleIndex = rand() % dictLen;
        int position = rand() % 2;
        string word = dict[puzzleIndex];
        int wordLen = word.length();
        int flag = rand() % 2;
        if (flag)
        {
            int n = wordLen - 1;
            for (int i = 0; i < (wordLen / 2); i++)
            {
                swap(word[i], word[n]);
                n--;
            }
        }

        int row = rand() % 10;
        int col = rand() % 10;

        if (position)
        {
            if ((wordLen >= 5 && col >= 5))
            {
                col -= wordLen;
            }

            for (int i = 0; word[i] != '\0'; i++)
            {
                puzzle[row][col] = word[i];
                col++;
            }
        }
        else
        {
            if ((wordLen >= 5 && row >= 5))
            {
                row -= wordLen;
            }

            for (int i = 0; word[i] != '\0'; i++)
            {
                puzzle[row][col] = word[i];
                row++;
            }
        }
        system("clear");
        cout << "\t\t##### Word Search Puzzle ##### \n\n";

        for (int i = 0; i < puzzleRow; i++)
        {
            cout << "\t" << i << "\t";
            for (int j = 0; j < puzzleCol; j++)
            {
                cout << puzzle[i][j] << "  ";
            }
            cout << endl;
        }

        if (flag)
        {
            int n = wordLen - 1;
            for (int i = 0; i < (wordLen / 2); i++)
            {
                swap(word[i], word[n]);
                n--;
            }
        }

        string guess;

    replay:
        cout << "\nSearch a word in the puzzle:   ";

        cin >> guess;

        if (guess == word)
        {
            score++;
            cout << "\nCongratulations!!! You found the word.";
            cout << "\n\n Do you want to play again? (y/n)  ";
            cin >> guess;
            if (guess == "y")
            {
                continue;
            }
            if (guess == "n")
            {
                break;
            }
        }
        else
        {
            cout << "\nWrong Answer! ";
            cout << "\nGuess Again? (y/n)  ";
            cin >> guess;
            if (guess == "y")
            {
                goto replay;
            }
            if (guess == "n")
            {
                break;
            }
        }
    } while (true);

    cout << "\nYour Score is " << score << endl;

    int highScore;

    ifstream readHighScore("highScore.txt");

    readHighScore >> highScore;

    readHighScore.close();

    if (highScore < score)
    {
        ofstream writeHighScore("highScore.txt");

        writeHighScore << score << endl;

        writeHighScore.close();
    }
}

int countWords()
{
    int count = 0;
    string word;
    ifstream readDict("dictionary.txt");

    while (getline(readDict, word))
    {
        count++;
    }

    readDict.close();

    return count;
}