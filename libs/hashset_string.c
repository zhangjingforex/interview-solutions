int hashfunc(char *str)
{
    int ret = 0;
    while (*str) {
        ret |= *str;
        str ++;
    }
    return ret % 97;
}

struct item {
    char *word;
    int count;
    struct item *next;
};

struct hashset {
    struct item **set;
    int size;
};

struct hashset *hashset_new()
{
    struct hashset *obj = malloc(sizeof(struct hashset));
    if (!obj)
        return NULL;
    obj->set = calloc(97, sizeof(struct item*));
    if (!obj->set) {
        free(obj);
        return NULL;
    }
    obj->size = 0;
    return obj;
}

void hashset_free(struct hashset *obj)
{
    if (obj) {
        if (obj->set) {
            for (int i = 0; i < 97; i ++) {
                struct item *cur = obj->set[i];
                while (cur) {
                    struct item *next = cur->next;
                    free(cur->word);
                    free(cur);
                    cur = next;
                }
            }
            free(obj->set);
        }
        free(obj);
    }
}

void hashset_put(struct hashset *obj, char *word)
{
    if (!obj)
        return;
    int idx = hashfunc(word);
    struct item *cur = obj->set[idx];
    while (cur && strcmp(cur->word, word)) cur = cur->next;
    if (!cur) {
        struct item *new = malloc(sizeof(struct item));
        if (!new)
            return;
        new->word = word;
        new->count = 1;
        new->next = obj->set[idx];
        obj->set[idx] = new;
        obj->size ++;
    } else {
        cur->count ++;
    }
}

struct item *hashset_get(struct hashset *obj, char *word)
{
    if (!obj)
        return NULL;
    int idx = hashfunc(word);
    struct item *cur = obj->set[idx];
    while (cur && strcmp(word, cur->word))  cur = cur->next;
    return cur;
}

void hashset_del(struct hashset *obj, char *word)
{
    if (!obj)
        return NULL;
    int idx = hashfunc(word);
    struct item *cur = obj->set[idx];
    struct item *parent = NULL;
    while (cur && strcmp(word, cur->word)) {
        parent = cur;
        cur = cur->next;
    }
    if (cur) {
        cur->count --;
        if (cur->count == 0) {
            if (parent)
                parent->next = cur->next;
            else
                obj->set[idx] = cur->next;
            free(cur);
            obj->size --;
        }
    }
}

int hashset_size(struct hashset *obj)
{
    return obj->size;
}



//get item with max count
struct item *hashset_getmax(struct hashset *obj)
{
    if (!obj)
        return NULL;
    struct item *max = NULL;
    struct item *cur;
    for (int i = 0; i < 97; i ++) {
        cur = obj->set[i];
        while (cur) {
            if (max == NULL || cur->count > max->count)
                max = cur;
            cur = cur->next;
        }
    }
    return max;
}

char **get_words(char *para, struct hashset *banned)
{
    int len = strlen(para);
    char **output = malloc((len + 1) * sizeof(char*));
    if (!output)
        return NULL;
    int olen = 0;
    
    int wstart = -1;
    for (int i = 0; i <= len; i ++) {
        if (isalpha(para[i])) {
            if (wstart < 0)
                wstart = i;
        } else if (wstart >= 0) {
            char *word = malloc((i - wstart + 1)*sizeof(char));
            if (!word) {
                for (int k = 0; k < olen; k ++) free(output[k]);
                free(output);
                return NULL;
            }
            int wlen = 0;
            while (wstart < i)
                word[wlen++] = tolower(para[wstart++]);
            word[wlen] = 0;
            if (!hashset_get(banned, word))
                output[olen++] = word;
            else
                free(word);
            wstart = -1;
        }
    }
    output[olen++] = 0;
    char **newout = realloc(output, olen * sizeof(char*));
    if (newout)
        return newout;
    else
        return output;
}
