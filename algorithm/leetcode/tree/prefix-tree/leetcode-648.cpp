#include <bits/stdc++.h>

#include <iostream>

using namespace std;

class Trie {
 public:
  bool isEnd;
  Trie* children[26];

  Trie() {
    isEnd = false;
    memset(children, 0, sizeof(children));
  }

  void insert(string key) {
    Trie* p = this;
    for (auto c : key) {
      if (p->children[c - 'a'] == NULL) p->children[c - 'a'] = new Trie();
      p = p->children[c - 'a'];
    }
    p->isEnd = true;
  }

  string find_prefix(string key) {
    string ans;
    Trie* p = this;

    for (auto c : key) {
        // shorter or no prefix
      if (p == NULL) return key;
      if (p->isEnd) return ans;
      ans += c;
      p = p->children[c - 'a'];
    }
    return ans;
  }
};

class Solution {
 public:
  string replaceWords(vector<string>& dictionary, string sentence) {
    Trie t = Trie();
    vector<string> sents;
    stringstream ss(sentence);
    string temp, ans;
    while (ss >> temp) sents.push_back(temp);
    for (string& s : dictionary) t.insert(s);
    for (int i = 0; i < sents.size(); i++) {
      if (i == 0)
        ans += t.find_prefix(sents[i]);
      else
        ans += " " + t.find_prefix(sents[i]);
    }
    return ans;
  }
};

int main(int argc, char const* argv[]) {
  vector<string> arg1 = {"cat", "bat", "rat"};
  string arg2 = "the cattle was rattled by the battery";
  Solution s;
  cout << s.replaceWords(arg1, arg2) << endl;
  return 0;
}
