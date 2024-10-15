struct minheap {
    int *heap;
    int size;
    int len;
};

void swap(int *n1, int *n2)
{
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

struct minheap *minheap_new(int size)
{
    struct minheap *obj = malloc(sizeof(struct minheap));
    if (!obj)
        return NULL;
    obj->size = size;
    obj->len = 0;
    obj->heap = malloc((obj->size + 1) * sizeof(int));
    if (!obj->heap) {
        free(obj);
        return NULL;
    }
    return obj;
}

void minheap_free(struct minheap *obj)
{
    if (obj) {
        free(obj->heap);
        free(obj);
    }
}

void __heapify_down(struct minheap *obj, int start)
{
    if (!obj || start < 1 || 2 * start > obj->len)
        return;
    if (2*start + 1 > obj->len || obj->heap[2*start] <= obj->heap[2*start+1]) {
        if (obj->heap[start] > obj->heap[2*start]) {
            swap(&(obj->heap[start]), &(obj->heap[2*start]));
            __heapify_down(obj, 2*start);
        }
    } else {
        if (obj->heap[start] > obj->heap[2*start + 1]) {
            swap(&(obj->heap[start]), &(obj->heap[2*start+1]));
            __heapify_down(obj, 2*start + 1);
        }
    }
}

void __heapify_up(struct minheap *obj, int start)
{
    if (!obj || start > obj->len || start/2 < 1)
        return;
    if (obj->heap[start] < obj->heap[start/2]) {
        swap(&(obj->heap[start]), &(obj->heap[start/2]));
        __heapify_up(obj, start/2);
    }
}

void minheap_add(struct minheap *obj, int num)
{
    if (!obj)
        return;
    if (obj->len < obj->size) {
        obj->len ++;
        obj->heap[obj->len] = num;
        __heapify_up(obj, obj->len);
    } else if (num > obj->heap[1]) {
        obj->heap[1] = num;
        __heapify_down(obj, 1);
    }
}

int minheap_getmin(struct minheap *obj)
{
    if (obj)
        return obj->heap[1];
    return INT_MIN;
}
