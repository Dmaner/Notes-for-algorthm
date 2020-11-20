#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Node
{
    public:
        unordered_map<char, Node*> next;
        bool isEnd;
        Node() 
        {
            isEnd = false;
        }
};

class WordDictionary {
public:
    Node* root;
    /** Initialize your data structure here. */
    WordDictionary() {
        root = new Node();
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        Node* p = root;
        for (char c : word)
        {
            if (!p->next.count(c)) p->next[c] = new Node();
            p = p->next[c];
        }
        p->isEnd = true;
    }
    
    bool dfs(Node* p, string& word, int index)
    {
        if (!p) return false;
        int n = word.length();
        if (n == index && p->isEnd) return true;
        if (index < n)
        {
            char c = word[index];
            if (c != '.' && p->next.count(c)) return dfs(p->next[c], word, index + 1);
            else if (c != '.') return false;
            else 
            {
                bool flag = false;
                for (auto entry: p->next) flag = flag || dfs(entry.second, word, index + 1);
                return flag;
            }
        }
        else return false;
    }

    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return dfs(root, word, 0);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */