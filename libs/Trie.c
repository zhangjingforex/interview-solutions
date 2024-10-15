struct TrieNode {
    struct TrieNode* map[26];
    char val;
    bool isword;
};

struct TrieNode *trie_newnode(char val, bool isword)
{
    struct TrieNode *obj = malloc(sizeof(struct TrieNode));
    if (!obj)
        return NULL;
    obj->val = val;
    obj->isword = isword;
    memset(obj->map, 0, 26 * sizeof(struct TrieNode*));
    return obj;
}

void trie_freenode(struct TrieNode *obj)
{
    if (obj) {
        for (int i = 0; i < 26; i ++) {
            if (obj->map[i])
                trie_freenode(obj->map[i]);
        }
        free(obj);
    }
}

struct TrieNode *trie_addchar(struct TrieNode *obj, char val, bool isword)
{
    if (!obj)
        return NULL;
    struct TrieNode *cur = obj->map[val - 'a'];
    if (!cur) {
        cur = trie_newnode(val, isword);
        obj->map[val - 'a'] = cur;
    }
    if (isword)
        cur->isword = true;
    return cur;
}

struct TrieNode *trie_getchar(struct TrieNode *obj, char val)
{
    return obj->map[val - 'a'];
}

struct TrieNode *trie_addword(struct TrieNode *obj, char *word)
{
    if (!obj)
        return NULL;
    int wlen;
    if (!word || (wlen = strlen(word)) < 1)
        return obj;
    
    struct TrieNode *cur = obj;
    bool isword = false;
    for (int i = 0; i < wlen; i ++) {
        isword = false;
        if (i == wlen - 1)
            isword = true;
        cur = trie_addchar(cur, word[i], isword);
    }
    return obj;
}

bool trie_prefixword(struct TrieNode *obj, char *word)
{
    if (!obj)
        return false;
    int wlen;
    if (!word || (wlen = strlen(word)) < 1)
        return false;
    
    struct TrieNode *cur = obj;
    for (int i = 0; i < wlen; i ++) {
        cur = trie_getchar(cur, word[i]);
        if (!cur)
            return false;
    }
    return cur != NULL;
}

bool trie_searchword(struct TrieNode *obj, char *word)
{
    if (!obj)
        return false;
    int wlen;
    if (!word || (wlen = strlen(word)) < 1)
        return false;
    
    struct TrieNode *cur = obj;
    for (int i = 0; i < wlen; i ++) {
        cur = trie_getchar(cur, word[i]);
        if (!cur)
            return false;
    }
    return cur->isword;
}

