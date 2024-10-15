struct qitem {
    struct TreeNode *node;
    int col;
    struct qitem *next;
};

struct qitem *queue_newitem(struct TreeNode *node, int col)
{
    struct qitem *obj = malloc(sizeof(struct qitem));
    if (obj) {
        obj->node = node;
        obj->col = col;
        obj->next = NULL;
    }
    return obj;
}

void queue_freeitem(struct qitem *obj)
{
    if (obj)
        free(obj);
}

struct queue {
    struct qitem *head;
    struct qitem *tail;
};

struct queue *queue_new()
{
    struct queue *obj = malloc(sizeof(struct queue));
    if (obj) {
        obj->head = obj->tail = NULL;
    }
    return obj;
}

void queue_free(struct queue *obj)
{
    if (obj)
        free(obj);
}

void queue_in(struct queue *obj, struct TreeNode *node, int col)
{
    if (obj) {
        struct qitem *new = queue_newitem(node, col);
        if (new) {
            if (obj->tail) {
                obj->tail->next = new;
                obj->tail = new;
            } else {
                obj->head = obj->tail = new;
            }
        }
    }
}

struct qitem *queue_out(struct queue *obj)
{
    if (!obj || !obj->head)
        return NULL;
    struct qitem *ret = obj->head;
    obj->head = ret->next;
    if (!obj->head)
        obj->tail = NULL;
    return ret;
}

bool queue_isempty(struct queue *obj)
{
    if (obj)
        return obj->head == NULL;
    return true;
}
