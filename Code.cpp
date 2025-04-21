#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;
void toLowerCase(string &str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}
int editDistance(const string &a, const string &b) {
    int m = a.length();
    int n = b.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    for(int i = 0; i <= m; i++) {
        for(int j = 0; j <= n; j++) {
            if(i == 0) dp[i][j] = j;
            else if(j == 0) dp[i][j] = i;
            else if(a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
        }
    }
    return dp[m][n];
}
string findClosestMatch(const string &input, const map<string, string> &dictionary) {
    int minDist = INT_MAX;
    string closest = "";
    for (const auto &pair : dictionary) {
        int dist = editDistance(input, pair.first);
        if (dist < minDist) {
            minDist = dist;
            closest = pair.first;
        }
    }
    if (minDist <= 2) return closest;
    return "";
}
int main() {
    map<string, string> dictionary = {
        {"hi", "Hello! How can I help you?"},
        {"hello", "Hi there! How can I assist you today?"},
        {"how are you", "I'm just a program, but I'm functioning well!"},
        {"bye", "Goodbye! Have a great day!"},
        {"your name", "I'm ChatBot, your virtual assistant."},
        {"help", "You can greet me, ask my name, or type 'bye' to exit."}
    };
    string userInput;
    cout << "ChatBot: Hello! Type 'bye' to end the chat.\n";
    while (true) {
        cout << "You: ";
        getline(cin, userInput);
        toLowerCase(userInput);
        if (userInput == "bye") {
            cout << "ChatBot: " << dictionary["bye"] << endl;
            break;
        }
        if (dictionary.find(userInput) != dictionary.end()) {
            cout << "ChatBot: " << dictionary[userInput] << endl;
        } else {
            string corrected = findClosestMatch(userInput, dictionary);
            if (!corrected.empty()) {
                cout << "ChatBot (did you mean \"" << corrected << "\"?): " << dictionary[corrected] << endl;
            } else {
                cout << "ChatBot: Sorry, I don't understand that.\n";
            }
        }
    }
    return 0;
}



    
