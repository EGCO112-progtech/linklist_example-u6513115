// Fig. 12.3: fig12_03.c
// Inserting and deleting nodes in a list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// self-referential structure
struct Node {
  int id; // each listNode contains a character
  char name[100];
  struct Node *nextPtr; // pointer to next node
  struct Node *pPtr;
}; // end structure listNode

typedef struct Node LLnode; // synonym for struct listNode
typedef LLnode *LLPtr;      // synonym for ListNode*

// prototypes

int deletes(LLPtr *sPtr, int value); //มี* เพราะมีการเปลี่ยนค่า
int isEmpty(LLPtr sPtr);
void insert(LLPtr *sPtr, int value);
void printList(LLPtr currentPtr); //แค่แสดงผลเฉย ๆ เลยไม่มี *
void instructions(void);
void reversedlist(LLPtr currentPtr);
void insertstr(LLPtr *sPtr, char value[]);
void deletesname(LLPtr *sPtr, char value[]);
void printListstr(LLPtr currentPtr); 

int main(void) {
  LLPtr startPtr = NULL; // initially there are no nodes สร้าง node ว่าง1
  LLPtr startPtr2 = NULL;
  unsigned int choice; // user's choice
  int item;            // char entered by user
  char name[100];
  LLPtr tmp;
  LLnode *Nt;

  instructions(); // display the menu
  printf("%s", "? ");
  scanf("%u", &choice);

  // loop while user does not choose 3
  while (choice != 3) {

    switch (choice) {
    case 1:
      printf("%s", "Enter an id: ");
      scanf("%d", &item);
      insert(&startPtr, item); // insert item in list

      printf("%s", "Enter a name: ");
      scanf("%s", name);
      insertstr(&startPtr2, name); // insert item in list

      printList(startPtr);
      reversedlist(startPtr);

      printListstr(startPtr2);

      break;
    case 2: // delete an element
      // if list is not empty
      if (!isEmpty(startPtr)) {
        printf("%s", "Enter number to be deleted: ");
        scanf("%d", &item);

        // if character is found, remove it
        if (deletes(&startPtr, item)) { // remove item
          deletesname(&startPtr2, name);
          printf("%d deleted.\n", item);
          printList(startPtr);
          printf("\n");
          printList();
        } // end if
        else {
          printf("%d not found.\n\n", item);
        } // end else
      }   // end if
      else {
        puts("List is empty.\n");
      } // end else

      break;

      case 3:
          tmp = startPtr;
          while (isEmpty(startPtr)) {
            printf("+\n"); //เช็คว่าทำงานได้จริง
            Nt = tmp->nextPtr;
            free(tmp);
            tmp = Nt;
  }
        
    default:
      puts("Invalid choice.\n");
      instructions();
      break;
    } // end switch

    printf("%s", "? ");
    scanf("%u", &choice);
  } // end while
  /* Clear all nodes at the end of nodes*/
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
void insert(LLPtr *sPtr, int value) {
  LLPtr newPtr;      // pointer to new node
  LLPtr previousPtr; // pointer to previous node in list
  LLPtr currentPtr;  // pointer to current node in list

  newPtr = (LLPtr)malloc(sizeof(LLnode)); // create node

  if (newPtr != NULL) {     // is space available
    newPtr->id = value;     // place value in node
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

// delete a list element
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
      printf("%d --> ", currentPtr->id);
      currentPtr = currentPtr->nextPtr;
    } // end while

    printf("%d --> NULL\n", currentPtr->id);

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
      printf("id = %d\n", currentPtr->id);
      currentPtr = currentPtr->pPtr;
    }

    printf("id = %d\n", currentPtr->id);

  } // end else
} // end function printList

void insertstr(LLPtr *sPtr, char value[]) {
  LLPtr newPtr;      // pointer to new node
  LLPtr previousPtr; // pointer to previous node in list
  LLPtr currentPtr;  // pointer to current node in list

  newPtr = (LLPtr)malloc(sizeof(LLnode)); // create node

  if (newPtr != NULL) {     // is space available
    strcpy(newPtr->name,value);
    newPtr->nextPtr = NULL; // node does not link to another node
    newPtr->pPtr = NULL;

    previousPtr = NULL;
    currentPtr = *sPtr;

    // loop to find the correct location in the list
    while (currentPtr != NULL && strcmp(currentPtr->name,value)>0) {
      previousPtr = currentPtr;         // walk to ...
      currentPtr = currentPtr->nextPtr; // ... next node
    }                                   // end while

    // insert new node at beginning of list
    if (previousPtr == NULL) {
      newPtr->nextPtr = *sPtr;
      if (currentPtr !=NULL) //แปลว่า current!=null เนื่องจากตัวสุดท้ายไม่ต้องมี null แล้ว
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
    printf("%s not inserted. No memory available.\n", value);
  } // end else
} // end function insert

void deletesname(LLPtr *sPtr, char value[]) {
  LLPtr previousPtr; // pointer to previous node in list
  LLPtr currentPtr;  // pointer to current node in list
  LLPtr tempPtr;     // temporary node pointer

  // delete first node
  if (strcmp(value,(*sPtr)->name)==0) {
    tempPtr = *sPtr;          // hold onto node being removed
    *sPtr = (*sPtr)->nextPtr; // de-thread the node

    if (*sPtr)
      (*sPtr)->pPtr = NULL;
    free(tempPtr); // free the de-threaded node
    
  } // end if
  else {
    previousPtr = *sPtr;
    currentPtr = (*sPtr)->nextPtr;

    // loop to find the correct location in the list
    while (currentPtr != NULL && strcmp(currentPtr->name,value)!=0) {
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

    } // end if
  }   // end else

} // end function delete

void printListstr(LLPtr currentPtr) {
  // if list is empty
  if (isEmpty(currentPtr)) {
    puts("List is empty.\n");
  } // end if
  else {
    puts("The list is:");

    // while not the end of the list
    while (currentPtr->nextPtr != NULL) {
      printf("%s --> ", currentPtr->name);
      currentPtr = currentPtr->nextPtr;
    } // end while

    printf("%s --> NULL\n", currentPtr->name);

  } // end else
} // end function printList
