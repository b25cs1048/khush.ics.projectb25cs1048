#include "Leaderboard.h"
#include  <iostream>
#include  <fstream>
#include  <vector>
using namespace std;

bool Leaderboard::hasAttempted (string username)
{
    ifstream file ("scores.txt");

    string name;
    int scoreofstudent;

    while (file >> name >> scoreofstudent)
    {
        if (name == username)
            return true;
    }
    return false;
}


void Leaderboard::totalPlayers()
{
    //input string from file collect
    ifstream file("scores.txt"); 

    string name;
    int scoreofstudent;
    
    int countinput = 0;

    while (file >> name >> scoreofstudent)
    {
        countinput++;
    }

    cout << "Total students : " << countinput << endl;
}

void  Leaderboard::saveScore(string username,int scoreofstudent,int total)
{
    //output  string from file collect
    ofstream file("scores.txt", ios::app); 
    file << username << " " << correct << " " << total << endl;
}

 void  Leaderboard::showLeaderboard()
{
    ifstream file ("scores.txt");

    vector <string>  players;
    vector <int> scoresofstudent;
    vector<int> totalQuestions;

    string player;
    int correctQUESTIONS;
    int correct, total;

    while (file >>  player >> correctQUESTIONS)
    {
        // pushback se array vector me  element ko add kar rahe hai 

         players.push_back(player);
        scoresofstudent.push_back(correctQUESTIONS);
        totalQuestions.push_back(total);
    } 
// idhar hum bubble sorting kar rahe hai player ke score ko using two for loops

    for (int ab =  0; ab < scoresofstudent.size(); ab++)
    {
        for (int cd =ab + 1; cd <scoresofstudent.size(); cd++)
        {
            if (scoresofstudent[cd] >  scoresofstudent[ab])
            {
                swap(scoresofstudent[ab],scoresofstudent[cd]);
                // if player cd ka score jyada hai to swap karenge
                swap(totalQuestions[ab], totalQuestions[cd]);

                swap(players[ab],players[cd]);
            }
        }
    }

    cout << "\nLeaderboard\n";

    for (int ab = 0; ab < players.size(); ab++)
    {
        if (ab == 0) cout << "\033[33m";

         // 1st place ko gold colour text dekayega

        else if (ab == 1) cout << "\033[37m";

          //2ndplace ko silver colour text dekhayega

        else if (ab == 2) cout << "\033[31m";

         //3rdplace ko bronze colour text dekhayega

        else cout << "\033[0m";
        double percentage = (double)scoresofstudent[ab] / totalQuestions[ab] * 100;

        cout << ab + 1 << ". " << players[ab]

             << " Score:  " << scoresofstudent[ab]
             << "/" << totalQuestions[ab]
             << " | Percentage: " << percentage << "%" << endl;  // terminal par output dikhayega

        cout <<  "\033[0m";
    }
}
