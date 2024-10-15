struct hitem {
    int num1;
    int num2;
};

void swap(struct hitem **it1, struct hitem **it2)
{
    struct hitem *temp = *it1;
    *it1 = *it2;
    *it2 = temp;
}

int hitemcmp(struct hitem *it1, struct hitem *it2)
{
    if (it1->num1 + it1->num2 > it2->num1 + it2->num2)
        return 1;
    else if (it1->num1 + it1->num2 < it2->num1 + it2->num2)
        return -1;
    else
        return 0;
}

struct maxheap {
    struct hitem **heap;
    int size;
    int len;
};

struct maxheap *maxheap_new(int size)
{
    struct maxheap *obj = malloc(sizeof(struct maxheap));
    if (!obj)
        return NULL;
    obj->size = size;
    obj->len = 0;
    obj->heap = malloc((obj->size + 1) * sizeof(struct item *));
    if (!obj->heap) {
        free(obj);
        return NULL;
    }
    return obj;
}

void maxheap_free(struct maxheap *obj)
{
    if (obj) {
        free(obj->heap);
        free(obj);
    }
}

void __heapify_down(struct maxheap *obj, int start)
{
    if (!obj || start < 1 || 2 * start > obj->len)
        return;
    if (2*start + 1 > obj->len || hitemcmp(obj->heap[2*start], obj->heap[2*start+1]) != -1) {
        if (hitemcmp(obj->heap[start], obj->heap[2*start]) == -1) {
            swap(&(obj->heap[start]), &(obj->heap[2*start]));
            __heapify_down(obj, 2*start);
        }
    } else {
        if (hitemcmp(obj->heap[start], obj->heap[2*start + 1]) == -1) {
            swap(&(obj->heap[start]), &(obj->heap[2*start+1]));
            __heapify_down(obj, 2*start + 1);
        }
    }
}

void __heapify_up(struct maxheap *obj, int start)
{
    if (!obj || start > obj->len || start/2 < 1)
        return;
    if (hitemcmp(obj->heap[start], obj->heap[start/2]) == 1) {
        swap(&(obj->heap[start]), &(obj->heap[start/2]));
        __heapify_up(obj, start/2);
    }
}

bool maxheap_add(struct maxheap *obj, struct hitem *it)
{
    if (!obj)
        return false;
    if (obj->len < obj->size) {
        obj->len ++;
        obj->heap[obj->len] = it;
        __heapify_up(obj, obj->len);
        return true;
    } else if (hitemcmp(it, obj->heap[1]) == -1) {
        obj->heap[1] = it;
        __heapify_down(obj, 1);
        return true;
    }
    return false;
}

struct hitem* maxheap_popmax(struct maxheap *obj)
{
    if (obj) {
        struct hitem *ret = obj->heap[1];
        obj->heap[1] = obj->heap[obj->len];
        obj->len --;
        __heapify_down(obj, 1);
        return ret;
    }
    return NULL;
}
