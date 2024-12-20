#include "../header/file.h"
#include <stdlib.h>
#include <stddef.h>
void enfiler(FileNode *file, int node)
{
    ElementFile *element = (ElementFile *)malloc(sizeof(ElementFile));
    element->node = node;
    element->next = NULL;

    if (file->head == NULL) {
        file->head = element;
        file->tail = element;
    } else {
        file->tail->next = element;
        file->tail = element;
    }
}
int defiler(FileNode *file)
{
    if (file->head == NULL) {
        return -1;
    }
    int node = file->head->node;
    ElementFile *element = file->head;
    file->head = file->head->next;
    if (file->head == NULL) {
        file->tail = NULL;
    }
    free(element);
    return node;
}