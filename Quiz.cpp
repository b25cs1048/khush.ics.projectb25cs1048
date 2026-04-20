 #include        "Quiz.h"
 #include  "Leaderboard.h"
 #include  <iostream>
 #include   <fstream>
   using namespace std; 
   #include  <sstream>
  #include   <vector>


struct Question {
    string q;
    string opt[4];
    int correct;
};

bool quiz_again (string u_name) {
     ifstream file("scores.txt");
     string u;
     int score;

    while (file >> u >> score) {//checking reattempt mat
        if (u == u_name) {
            return true;
        }
    }
    return false;
}

int   get_u_Score(string u_name) 
{
    ifstream file("scores.txt");
    string u;
    int score;

    while (file >> u >> score) 
    {
        if (u == u_name) 
        {
            return score ;
        }
    }
    return -1;
}

int  Quiz::startQuiz  ( const  string& username)   {

    if ( quiz_again (username)) {
        int score = get_u_Score(  username);

        cout   << "\nYou have already attempted the quiz\n";
        cout  << "Your Score: " << score << endl;

        cout << "If you want to reattempt, contact admin.\n";//prof or adm
        return   score;
    }

    ifstream  file("questions.txt");
    string line;

    vector  <  Question>  questions ;
    
    
    while (  getline ( file , line)) {
        stringstream ss(line);
        vector < string> parts ;
        string part;

        while (getline(ss, part, '|')) {
            parts.push_back(part);
        }

        if   (parts.size() != 6  ) continue;

        Question q; //quesion ka instance
        q.q = parts[0];
        for (int i = 0; i < 4; i++) {
            q.opt[i] = parts[i + 1];
        }
        q.correct = stoi(parts[5]);

        questions.push_back(q);
    }

    int n = questions.size();
    vector< int> answers(n, 0) ; 

    int current = 0;
    char opt_pick;

    while (true) {

        cout << "\nQuestion " << current + 1 << "/" << n << endl;
        cout << questions[current].q << endl;

        for (int i = 0; i < 4; i++) {
            cout << i + 1 << ". " << questions[current].opt[i] << endl;
        }

        if (answers[current] != 0) {
            cout << "Your current answer: " << answers[current] << endl;
        }

        cout << "\nEnter option (1-4), n (next), p (previous), s (submit): ";
        cin >> opt_pick;

        if (opt_pick >= '1' && opt_pick <= '4') {
            answers[current] = opt_pick - '0'; 
        }
        else if (opt_pick == 'n') {
            if (current < n - 1)
                current++;
            else
                cout << "This is last question!\n";
        }
        else if (opt_pick == 'p') {
            if (current > 0)
                current--;
            else
                cout << "This is first question!\n";
        }
        else if (opt_pick == 's') {
            break;
        }
        else {
            cout << "Invalid input!\n";
        }
    }

   
    int score = 0;
    for (int i = 0; i < n; i++) {
        if (answers[i] == questions[i].correct) {
            score++;
        }
    }

    cout << "\nFinal Score: " << score << "/" << n << endl;

   
    Leaderboard lb;
    lb.saveScore(username, score);

    return score;
}

