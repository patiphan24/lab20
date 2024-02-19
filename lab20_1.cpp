#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source;
    source.open(filename);
    
    string text;
    char name[50];
    char format[] = "%[^:]: %d %d %d";
    int a, b, c;
    while(getline(source,text)){
        sscanf(text.c_str(),format,name,&a,&b,&c);
        names.push_back(name);
        scores.push_back(a+b+c);
        grades.push_back(score2grade(a+b+c));
    }
    source.close();
}

void getCommand(string &command, string &key){
    cout << "Please input your command: ";
    cin >> command;
    cin.ignore();
    if(toUpperStr(command) == "NAME" || toUpperStr(command) == "GRADE") getline(cin,key);
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades , string key){
    cout <<"---------------------------------\n";
    bool x = 0;
    for(unsigned i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == key){
        x = 1;
        cout << names[i] << "'s score = " << scores[i] << endl;
        cout << names[i] << "'s grade = " << grades[i] << endl;
        }
    }
    if(!x)cout << "Cannot found.\n";
    cout <<"---------------------------------\n";
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    cout <<"---------------------------------\n";
    bool x = 0;
    for(unsigned i = 0; i < grades.size(); i++){
        if(grades[i] == key[0]){
        x = 1;
        cout << names[i] << " (" << scores[i] << ")" << endl;
        }
    }
    if(!x)cout << "Cannot found.\n";
    cout <<"---------------------------------\n";
}
int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}