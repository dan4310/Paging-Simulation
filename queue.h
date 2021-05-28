#ifndef queue
#define queue
#include<stdio.h>

// DOUBLY LINKED QUEUE

// define Frame structure
typedef struct Frame {
  int r;
  int pageNum;
 
  struct Frame *next;
  struct Frame *prev;
} Frame;

// variables to keep track of
int maxLen;
int len = 0;

Frame *last = NULL;
Frame *head = NULL;

// add frame to end of queue
// if added successfully return 1
// else queue must be full return 0
int addLast(Frame *p) {
  if (len == 0 && maxLen != 0) {
    last = p;
    head = p;
    len++;
    return 1;
  } else if (len < maxLen) {
    last->next = p;
    p->prev = last;
    last = p;
    len++;
    return 1;
  }
  return 0;
}

// get head of queue
Frame *getFirst() {
  return head;
}

// remove and return first in queue
// if queue empty then return NULL
Frame *removeFirst() {
  Frame *temp = head;
  if (head == NULL) {
    return NULL;
  }
  if (head->next == NULL) {
    last = NULL;
  } else {
    head->next->prev = NULL;
  }
  head = head->next;
  len--;

  return temp;
}

// remove and return frame by page reference number
Frame *removeRef(long int num) {
  Frame *current = head;
  Frame *previous = NULL;
  if (head == NULL) {
    return NULL;
  }

  while(current->pageNum != num) {
    if (current->next == NULL) {
      return NULL;
    } else {
      previous = current;
      current = current->next;
    }
  }

  if (current == head) {
    head = head->next;
  } else {
    current->prev->next = current->next;
  }
 
  if (current == last) {
    last = current->prev;
  } else {
    current->next->prev = current->prev;
  }
  len--;
  return current;

}

// clear all R bits in queue
void clearR() {
  int i;
  Frame *f = head;
  for (i = 0; i < len; i++) {
    f->r = 0;
    f = f->next;
  }
}

// set R bit in queue by page reference number
void setR(int num) {
  int i;
  Frame *f = head;
  for (i = 0; i < len; i++) {
    if (f->pageNum == num) {
      f->r = 1;
      break;
    }
    f = f->next;
  }
}

// remove and return last from queue
Frame *removeLast() {
  Frame *temp = last;
  if (len == 0 || maxLen == 0) {
    return temp;
  }
  if (head->next == NULL) {
    head = NULL;
  } else {
    last->prev->next = NULL;
  }
  len--;
  last = last->prev;
  return temp;

}

// add to front of queue
void addFirst(Frame *f) {
  if (len == maxLen) {
    return;
  }

  if (len == 0 && maxLen != 0) {
    last = f;
  } else {
    head->prev = f;
  }
  f->next = head;
  head = f;
  len++;
}

// print entire queue (for debugging)
void printQueue() {
  Frame *p = head;
  int i;
  for (i = 0; i < len; i++) {
    printf("(%d,R:%d) ", p->pageNum, p->r);
    p = p->next;
  } 
  printf("\n\n");
}
#endif
