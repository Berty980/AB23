#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

vector<vector<string>> wordBreak(string s, unordered_set<string>& wordDict) {
    int n = s.length();
    vector<vector<vector<string>>> dp(n + 1);  // dp[i] = todas las particiones posibles de s[0:i-1] en palabras del diccionario
    dp[0] = {{}};  // la cadena vacía se puede dividir en una única partición vacía

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (!dp[j].empty() && wordDict.count(s.substr(j, i - j))) {
                string word = s.substr(j, i - j);
                for (auto& partition : dp[j]) {
                    partition.push_back(word);
                    dp[i].push_back(partition);
                    partition.pop_back();
                }
            }
        }
    }
    for (int i = 0; i <= n; i++) {
        cout << "i = " << i << endl;
        for (int j = 0; j < dp[i].size(); j++) {
            cout << "\t";
            for (int k = 0; k < dp[i][j].size(); k++) {
                cout << dp[i][j][k] << " ";
            }
            cout << endl;
        }
    }
    return dp[n];
}

int main() {
    string s = "catsanddog";
    unordered_set<string> wordDict = {"cat", "cats", "and", "sand", "dog", "catsand"};

    vector<vector<string>> partitions = wordBreak(s, wordDict);

    if (partitions.empty()) {
        cout << "La cadena no se puede dividir en palabras del diccionario" << endl;
    } else {
        cout << "Todas las particiones posibles de la cadena en palabras del diccionario son:" << endl;
        for (auto& partition : partitions) {
            for (int i = 0; i < partition.size(); i++) {
                cout << partition[i];
                if (i < partition.size() - 1) {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }

    return 0;
}
