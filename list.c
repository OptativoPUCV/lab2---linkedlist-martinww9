#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List * list= (List*) malloc(sizeof(List));
  list->head=NULL;
  list->tail=NULL;
  list->current=NULL;
  return list;
}

void * firstList(List * list) {
  if(!list->head) return NULL;
  list->current=list->head;
    return (list->head->data);
}

void * nextList(List * list) {
  if(list->current == list->tail || list->current == NULL) return NULL;
  list->current = list->current->next;
    return (list->current->data);
}

void * lastList(List * list) {
  if(!list->tail) return NULL;
  list->current = list->tail;
  return(list->current->data);
}

void * prevList(List * list) {
    if(list->current == list->head || list->current == NULL) return NULL;
  list->current = list->current->prev;
    return (list->current->data);
}

void pushFront(List * list, void * data) {
  Node * nodeP = createNode(data);
    if(list->head == NULL){
      list->head= nodeP;
      list->tail = nodeP;
    }
  else {
    nodeP->next = list->head;
    list->head->prev = nodeP;
    list->head = nodeP;
    nodeP->prev = NULL;
  }
}

void pushBack(List * list, void * data) {
  list->current = list->tail;
  Node * nodeP = createNode(data);
  if(list->head == NULL){
      list->head= nodeP;
      list->tail = nodeP;
    }
    list->tail->next = nodeP;
    nodeP->prev = list->tail;
    list->tail = nodeP;
    nodeP->next = NULL;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node * nodeP = createNode(data);
  nodeP->prev = list->current;
  nodeP->next = list->current->next;
  if (list->current->next != NULL) {
            list->current->next->prev = nodeP;
        } else {
            list->tail = nodeP;
        }
  list->current->next = nodeP;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  Node * nodeP = list->current;
  void * data = list->current->data;
  if (nodeP == list->head && nodeP == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    } else if (nodeP == list->head) {
        list->head = nodeP->next;
        list->head->prev = NULL;
    } else if (nodeP == list->tail) {
        list->tail = nodeP->prev;
        list->tail->next = NULL;
} else{
  
  nodeP->prev->next = nodeP->next;
  nodeP->next->prev = nodeP->prev;
}
  list->current = nodeP->next;
  free(nodeP);
    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}