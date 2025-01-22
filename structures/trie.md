### Trie

```cpp
struct Trie {
    bool isWord;
    Trie* child[26];

    Trie() { 
        isWord = false;
        for (int i = 0; i < 26; i++) child[i] = nullptr;
    }
    ~Trie() { for (int i = 0; i < 26; i++) 
        if (child[i] != nullptr)
            delete child[i];
    }
    void insert(const char* str) {
        if (*str == '\0') { isWord = true; return; }

        int index = *str - 'a';
        if (child[index] == nullptr)
            child[index] = new Trie();
        child[index]->insert(str + 1);
    }
    bool find(const char* str) {
        if (*str == '\0') return isWord;

        int index = *str - 'a';
        if (child[index] == nullptr)
            return false;
        return child[index]->find(str + 1);
    }
};
```

### Trie Iterative

```cpp
struct TrieIter {
    bool isWord;
    TrieIter* child[26];

    TrieIter() {
        isWord = false;
        for (int i = 0; i < 26; i++) child[i] = nullptr;
    }
    ~TrieIter() {
        for (int i = 0; i < 26; i++)
            if (child[i] != nullptr)
                delete child[i];
    }
    void insert(const char* str) {
        TrieIter* node = this;
        for (int i = 0; str[i]; ++i) {
            int index = str[i] - 'a';
            if (node->child[index] == nullptr)
                node->child[index] = new TrieIter();
            node = node->child[index];
        }
        node->isWord = true;
    }
    bool find(const char* str) {
        TrieIter* node = this;
        for (int i = 0; str[i]; ++i) {
            int index = str[i] - 'a';
            if (node->child[index] == nullptr)
                return false;
            node = node->child[index];
        }
        return node->isWord;
    }
};
```
