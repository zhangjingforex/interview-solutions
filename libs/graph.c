struct graphNode {
    void *pval;
    int adjsize;
    int adjlen;
    struct graphNode **adj;
    double *weights;
    int *adjtype;
    int flag;
};

int pvalcmp(void *pval1, void *pval2)
{
    return strcmp((char*)pval1, (char*)pval2);
}

struct graphNode *graph_newnode(void *pval)
{
    struct graphNode *obj = malloc(sizeof(struct graphNode));
    if (!obj)
        return NULL;
    obj->pval = pval;
    obj->adjsize = 1;
    obj->adjlen = 0;
    obj->flag = 0;
    obj->adj = malloc(obj->adjsize * sizeof(struct graphNode*));
    if (!obj->adj) {
        free(obj);
        return NULL;
    }
    obj->weights = malloc(obj->adjsize * sizeof(double));
    //err handling
    obj->adjtype = malloc(obj->adjsize * sizeof(int));
    
    return obj;
}

void graph_freenode(struct graphNode *obj)
{
    if (obj) {
        obj->flag = 1;
        for (int i = 0; i < obj->adjlen; i ++) {
            if (obj->adjtype[i] == 0)
                graph_freenode(obj->adj[i]);
        }
        obj->flag = 0;
        free(obj->weights);
        free(obj->adj);
        free(obj->adjtype);
        free(obj);
    }
}

void graph_addadj(struct graphNode *obj, struct graphNode *adj, double weight, int type)
{
    if (!obj || !adj)
        return;
    if (obj->adjlen >= obj->adjsize) {
        obj->adjsize *= 2;
        obj->adj = realloc(obj->adj, obj->adjsize * sizeof(struct graphNode*));
        obj->weights = realloc(obj->weights, obj->adjsize * sizeof(double));
        obj->adjtype = realloc(obj->adjtype, obj->adjsize * sizeof(int));
        //err handling
    }
    obj->adj[obj->adjlen] = adj;
    obj->adjtype[obj->adjlen] = type;
    obj->weights[obj->adjlen++] = weight;
}

struct graphNode *graph_getadj(struct graphNode *obj, void *pval)
{
    if (!obj)
        return NULL;
    struct graphNode *found = NULL;
    for (int i = 0; i < obj->adjlen; i ++) {
        if (!pvalcmp(obj->adj[i]->pval, pval)) {
            found = obj->adj[i];
            break;
        }
    }
    return found;
}

struct graphNode *graph_getnode(struct graphNode *obj, void *pval)
{
    if (!obj)
        return NULL;
    
    obj->flag = 1;
    struct graphNode *found = NULL;
    for (int i = 0; i < obj->adjlen; i ++) {
        if (obj->adj[i]->flag)
            continue;
        if (!pvalcmp(obj->adj[i]->pval, pval)) {
            obj->flag = 0;
            return obj->adj[i];
        } else {
            found = graph_getnode(obj->adj[i], pval);
            if (found) {
                obj->flag = 0;
                return found;
            }
        }
    }
    obj->flag = 0;
    return found;
}

bool graph_ispath(struct graphNode *from, struct graphNode *to, double *weight)
{
    from->flag = 1;
    for (int i = 0; i < from->adjlen; i ++) {
        if (from->adj[i]->flag)
            continue;
        if (from->adj[i] == to) {
            *weight = from->weights[i];
            from->flag = 0;
            return true;
        } else {
            double subwt = 0;
            if (graph_ispath(from->adj[i], to, &subwt)) {
                *weight = subwt * from->weights[i];
                from->flag = 0;
                return true;
            }
        }
    }
    from->flag = 0;
    *weight = -1.0;
    return false;
}
