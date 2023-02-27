// Fig. 12.3: fig12_03.c
// Inserting and deleting nodes in a list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// self-referential structure
struct Node { // each listNode contains a character
  int id;
  char name[100];
  struct Node *nextPtr; // pointer to next node
  struct Node *pPtr;
}; // end structure listNode

typedef struct Node LLnode; // synonym for struct listNode
typedef LLnode *LLPtr;      // synonym for ListNode*

// prototypes

int deletes(LLPtr *sPtr, int value); //มี* เพราะมีการเปลี่ยนค่า
int isEmpty(LLPtr sPtr);
void insert(LLPtr *sPtr, int value, char names[]);
void printList(LLPtr currentPtr); //แค่แสดงผลเฉย ๆ เลยไม่มี *
void instructions(void);
void reversedlist(LLPtr currentPtr);

int main(void) {
  LLPtr startPtr = NULL; // initially there are no nodes สร้าง node ว่าง1
  LLPtr tempPtr = startPtr;
  unsigned int choice; // user's choice
  int ids;
  char names[100];

  instructions(); // display the menu
  printf("%s", "? ");
  scanf("%u", &choice);

  // loop while user does not choose 3
  while (choice != 3) {

    switch (choice) {
    case 1:

      printf("%s", "Enter an id: ");
      scanf("%d", &ids);
      printf("%s", "Enter a name: ");
      scanf("%s", names);
      insert(&startPtr, ids, names);
      printList(startPtr);
      reversedlist(startPtr);

      break;
    case 2: // delete an element
      // if list is not empty
      if (!isEmpty(startPtr)) {
        printf("%s", "Enter an id to be deleted: ");
        scanf("%d", &ids);

        // if character is found, remove it
        if (deletes(&startPtr, ids)) { // remove item
          printf("%d deleted.\n", ids);
          printList(startPtr);
        } // end if
        else {
          printf("%d not found.\n\n", ids);
        } // end else
      }   // end if
      else {
        puts("List is empty.\n");
      } // end else

      break;
    default:
      puts("Invalid choice.\n");
      instructions();
      break;
    } // end switch

    printf("%s", "? ");
    scanf("%u", &choice);
  } // end while
  /* Clear all nodes at the end of nodes*/
  while (tempPtr != NULL) {
    printf("deleting id = %d\n", tempPtr->id);
    tempPtr = tempPtr->nextPtr;
    free(startPtr);
    startPtr = tempPtr;
  }
  puts("End of run.");
} // end main

// display program instructions to user
void instructions(void) {
  puts("Enter your choice:\n"
       "   1 to insert an element into the list.\n"
       "   2 to delete an element from the list.\n"
       "   3 to end.");
} // end function instructions

// insert a new value into the list in sorted order
void insert(LLPtr *sPtr, int value, char names[]) {
  LLPtr newPtr;      // pointer to new node
  LLPtr previousPtr; // pointer to previous node in list
  LLPtr currentPtr;  // pointer to current node in list

  newPtr = (LLPtr)malloc(sizeof(LLnode)); // create node

  if (newPtr != NULL) { // is space available
    newPtr->id = value; // place value in node
    strcpy(newPtr->name, names);
    newPtr->nextPtr = NULL; // node does not link to another node
    newPtr->pPtr = NULL;

    previousPtr = NULL;
    currentPtr = *sPtr;

    // loop to find the correct location in the list
    while (currentPtr != NULL && value > currentPtr->id) {
      previousPtr = currentPtr;         // walk to ...
      currentPtr = currentPtr->nextPtr; // ... next node
    }                                   // end while

    // insert new node at beginning of list
    if (previousPtr == NULL) {
      newPtr->nextPtr = *sPtr;
      if (currentPtr !=
          NULL) //แปลว่า current!=null เนื่องจากตัวสุดท้ายไม่ต้องมี null แล้ว
        (currentPtr)->pPtr = newPtr;
      *sPtr = newPtr;

    }      // end if
    else { // insert new node between previousPtr and currentPtr
      previousPtr->nextPtr = newPtr;
      newPtr->pPtr = previousPtr;

      //เชื่อมกลับ
      newPtr->nextPtr = currentPtr;
      if (currentPtr !=
          NULL) //แปลว่า current!=null เนื่องจากตัวสุดท้ายไม่ต้องมี null แล้ว
        currentPtr->pPtr = newPtr;

    } // end else
  }   // end if
  else {
    printf("%d not inserted. No memory available.\n", value);
  } // end else
} // end function insert

int deletes(LLPtr *sPtr, int value) {
  LLPtr previousPtr; // pointer to previous node in list
  LLPtr currentPtr;  // pointer to current node in list
  LLPtr tempPtr;     // temporary node pointer

  // delete first node
  if (value == (*sPtr)->id) {
    tempPtr = *sPtr;          // hold onto node being removed
    *sPtr = (*sPtr)->nextPtr; // de-thread the node

    if (*sPtr)
      (*sPtr)->pPtr = NULL;
    free(tempPtr); // free the de-threaded node
    return value;
  } // end if
  else {
    previousPtr = *sPtr;
    currentPtr = (*sPtr)->nextPtr;

    // loop to find the correct location in the list
    while (currentPtr != NULL && currentPtr->id != value) {
      previousPtr = currentPtr;         // walk to ...
      currentPtr = currentPtr->nextPtr; // ... next node

    } // end while

    // delete node at currentPtr
    if (currentPtr != NULL) {
      tempPtr = currentPtr;
      previousPtr->nextPtr = currentPtr->nextPtr;

      if (currentPtr->nextPtr != NULL)
        currentPtr->nextPtr->pPtr = previousPtr;

      free(tempPtr);
      return value;
    } // end if
  }   // end else

  return '\0';
} // end function delete

// return 1 if the list is empty, 0 otherwise
int isEmpty(LLPtr sPtr) { return sPtr == NULL; } // end function isEmpty

// print the list
void printList(LLPtr currentPtr) {
  // if list is empty
  if (isEmpty(currentPtr)) {
    puts("List is empty.\n");
  } // end if
  else {
    puts("The list is:");

    // while not the end of the list
    while (currentPtr->nextPtr != NULL) {
      printf("%d %s --> ", currentPtr->id, currentPtr->name);
      currentPtr = currentPtr->nextPtr;
    } // end while

    printf("%d %s --> NULL\n", currentPtr->id, currentPtr->name);

  } // end else
} // end function printList

void reversedlist(
    LLPtr currentPtr) { //ต้องไปข้างหน้าจนถึงตัวสุดท้ายก่อน แล้วค่อยเริ่มจากตัวสุดท้ายมาข้างหน้า
  // if list is empty
  if (isEmpty(currentPtr)) {
    puts("List is empty.\n");
  } // end if
  else {
    puts("The reversed list is:");

    while (currentPtr->nextPtr != NULL) {
      currentPtr = currentPtr->nextPtr;
    }

    while (currentPtr->pPtr != NULL) {
      printf("%d %s --> ", currentPtr->id, currentPtr->name);
      currentPtr = currentPtr->pPtr;
    }

    printf("%d %s --> NULL\n", currentPtr->id, currentPtr->name);

  } // end else
} // end function printList