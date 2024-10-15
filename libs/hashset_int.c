#define HPRIME 6151
int hashfunc(int val)
{
    return (unsigned int) val% HPRIME;
}

struct item {
    int val;
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
    obj->set = calloc(HPRIME, sizeof(struct item*));
    if (!obj->set) {
        free(obj);
        return NULL;
    }
    obj->size = 0;
    return obj;
}

void hashset_free(struct hashset *obj)
{
    if (!obj) {
        if (obj->set) {
            for (int i = 0; i < HPRIME; i ++) {
                struct item *cur = obj->set[i];
                while (cur) {
                    struct item *next = cur->next;
                    free(cur);
                    cur = next;
                }
            }
            free(obj->set);
        }
        free(obj);
    }
}

void hashset_put(struct hashset *obj, int val) 
{
    if (!obj)
        return;
    int idx = hashfunc(val);
    struct item *cur = obj->set[idx];
    while (cur && cur->val != val) cur = cur->next;
    if (!cur) {
        struct item *new = malloc(sizeof(struct item));
        if (!new)
            return;
        new->val = val;
        new->count = 1;
        new->next = obj->set[idx];
        obj->set[idx] = new;
        obj->size ++;
    } else {
        cur->count ++;
    }
}

struct item *hashset_get(struct hashset *obj, int val)
{
    if (!obj)
        return NULL;
    int idx = hashfunc(val);
    struct item *cur = obj->set[idx];
    while (cur && cur->val != val)  cur = cur->next;
    return cur;
}

void hashset_del(struct hashset *obj, int val)
{
    if (!obj)
        return;
    int idx = hashfunc(val);
    struct item *cur = obj->set[idx];
    struct item *parent = NULL;
    while (cur && cur->val != val) {
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
    if (obj)
        return obj->size;
    else
        return 0;
}

