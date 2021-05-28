#include <stdio.h>

#include "queue.h"

void simulate(long int *pages, int algo);
void fifo(Frame *f);
void lru(Frame *f);
void secondChance(Frame *f);

int includes(int p);

int numMisses = 0, numHits = 0, numEvicts = 0;
int n = 1000, k = 5;
int totalRefs[10];

int main() {
  // initialize array of 10000 random numbers
  long int nums[n];

  int i;
  // reduce random numbers to 0-9
  for (i = 0; i < n; i++) {
    nums[i] = random() % 100;
    
    if (nums[i] < 1) {
      nums[i] = 0;    
    } else if (nums[i] < 4) {
      nums[i] = 1;
    } else if (nums[i] < 9) {
      nums[i] = 2;
    } else if (nums[i] < 16) {
      nums[i] = 3;
    } else if (nums[i] < 25) {
      nums[i] = 4;
    } else if (nums[i] < 36) {
      nums[i] = 5;
    } else if (nums[i] < 49) {
      nums[i] = 6;
    } else if (nums[i] < 64) {
      nums[i] = 7;
    } else if (nums[i] < 81) {
      nums[i] = 8;
    } else if (nums[i] < 100) {
      nums[i] = 9;
    }
    
  }
 
  // prompt user for number of memory frames to simulate
  printf("Enter number of frames: ");
  scanf("%d", &k);

  // set max length of queue to number of simulation frames
  maxLen = k;
  int replaceAlgo;

  // prompt user for eviction algorithm choice
  printf("FIFO (0), LRU (1), Second Chance (2): ");
  scanf("%d", &replaceAlgo);

  // simulate page references
  simulate(nums, replaceAlgo);


  return 0;
}

void simulate(long int *refs, int algo) {
  int i;
  Frame *p = getFirst();
  Frame frames[n]; 
 
  int K = 0;
  // iterate through all page references
  for (i = 0; i < n; i++) {
    // incriment total references or proper page ref
    totalRefs[*(refs+i)]++;
    // incriment counter for resetting R bit
    K++;
    if (includes(*(refs+i)) == 0) {
      // if queue does not include page ref

      // incirment number of misses
      // create new frame object and initialize variables
      numMisses++;
      frames[i].next = NULL;
      frames[i].r = 0;
      frames[i].pageNum = *(refs+i);

      // attempt to add new page ref to queue   
      if (addLast(&frames[i]) == 0) {
        // if queue full and page was not added
        // incriment evicts
        numEvicts++;
        
        // execute user selected eviction algorithm
        switch(algo) {
          case 0:
            fifo(&frames[i]);
            break;
	  case 1:
            lru(&frames[i]);
            break;
          case 2:
            secondChance(&frames[i]);
            break;
        }       
      }
      // re-establish first in queue
      p = getFirst();
    } else {
      // if page ref already in queue
      // set R bit to 1
      // incriment number of hits
      setR(*(refs+i));
      numHits++;

      // if LRU algo was chosen
      if (algo == 1) {
        // move hit page to front of queue
        Frame *temp = removeRef(*(refs+i));
        addFirst(temp);    
                
      }
    }
    
    // clear all R bits in queue to 0 every 100 refs
    // used for second chance algo
    if (K % 100 == 0) {
      K = 0;
      clearR();
    }
 
  }   
 
 // finally print all counter data
 printf("Number of hits: %d\n", numHits);
 printf("Number of misses: %d\n", numMisses);
 printf("Number of evicts: %d\n", numEvicts);
 for (i = 0; i < 10; i++) {
   printf("Total refs for page num %d: %d\n", i, totalRefs[i]);
 }
}

void fifo(Frame *f) {
  removeFirst();
  addLast(f);
}

void lru(Frame *f) {
  Frame *temp = removeLast();
  addFirst(f);
 
}

void secondChance(Frame *f) {
  
  // initial potential victim
  Frame *temp = removeFirst();

  int i, flag = 0;
  // iterate through queue
  for (i = 0; i < maxLen; i++) {
    // upon finding page ref with R bit unset
    if (temp->r == 0) {
      // flag so I know a proper victim was found
      // break out of loop
      flag = 1;
      break;
    } else {
      // if R bit set
      // clear and place in back of queue
      temp->r = 0;
      addLast(temp);
    }
    // get next potential victim
    temp = removeFirst();
  }

  // if flag not set then all R bits in queue must have been set
  // victim will be first in queue, like fifo
  if (flag == 0) {
    removeFirst();
  }
  // add new page ref to end of queue
  addLast(f);
   
}

// helper function for checking if includes in queue
// takes page ref number
// if in queue return 1
// else return 0
int includes(int p) {

  int i;
  Frame *pi = getFirst(); 
  if (len == 0 || maxLen == 0) {
    return 0;
  }
  for (i = 0; i < len; i++) {
    if (pi->pageNum == p) {
      return 1;
    }
    pi = pi->next; 
  }
  return 0;
}
