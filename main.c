#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*This  programme is a Kanban-style board with lists that contain items and interfaces.
that allows you to edit it,and save it */

// struct for list and items in our list using linked lists
typedef struct BoardItem {
    char name[100];
    struct BoardItem *next; //pointer to next board item
    struct BoardItem *prev; // pointer to the previous board item 
}BoardItem;

typedef struct BoardList {
   char name[100];
   BoardItem *head; // points to the first item in list
  
}BoardList;

void  print_menu();
void display_board(BoardList lists[], int numlists);
void loading_file(char * file_name);
void edit_list(BoardList lists[], int numlists,const char *filename);
void edit_board(BoardList lists[], int numlists,const char *filename);
void save_board(BoardList lists[], int numlists, const char *filename);
int choice;
char file_name[100];
int num_lists = 4;
bool run = true;


int main (){
  /* 
   1.Create an array of Boardlist structures.
   2.Initialise name of list and a null pointer
   3.(good practice for linked lists to start with null pointers).
 */
  BoardList lists[] = 
  { {"Nick", NULL},
    {"Tim",NULL},
    {"Dante", NULL},
    {"Abey", NULL}
  };

while (run){
 print_menu();
 switch (choice) {
            case 1:
                // Display the default board
                display_board(lists,4);
                break;
            case 2:
                // Load board from a file               
                printf("Load board from a file\n");
                loading_file(file_name);
                break;
            case 3:
                // Edit list           
                printf("Edit list\n");
                edit_list(lists,num_lists, file_name);
                break;
            case 4:
                // Edit board               
                printf("Edit board\n");
                edit_board(lists,num_lists, file_name);
            
                break;
            case 5:
                // Save board to a file        
                printf("Enter filename: "); 
                scanf("%s", file_name);    
                printf("Save board to a file\n");
                save_board(lists, num_lists, file_name);
                break;
            case 6:
                // Quit
                printf("Quitting...\n");
                run = false; 
                break;
            default:
                printf("Invalid choice. Please enter a number from 1 to 6.\n");
                break;
        }
      }
      // ascii art of a cat
    printf("     /\\_/\\\n");
    printf("    ( o.o )\n");
    printf("     > ^ <\n");
    return 0;


        return 0 ;
    }






void print_menu(){
    printf("Menu:\n");
    printf("1. Display Board:\n");
    printf("2. Load Board from a file:\n");
    printf("3. Edit list:\n");
    printf("4. Edit board\n");
    printf("5. Save board to a file\n");
    printf("6. Quit:\n");
    printf("Enter your choice(1-6): \n");
    scanf("%d", &choice);
}

void display_board(BoardList lists[], int numlists)
{
    int i;
  /* Initialise the board items for Nick.
    1.Allocate memory for item
    2.Use strcpy and pointer nick_item1  to put 3070 RTX into name array in boarditem struct
    3.Set next item to be null
  */
  BoardItem  *nick_item1 = (BoardItem*)malloc(sizeof(BoardItem));
  strcpy(nick_item1->name, "3070 RTX");
  nick_item1->next = NULL; 
  nick_item1->prev = NULL; 


  //Assigns the first item in Nick's list (links item to its list)
  lists[0].head = nick_item1;
  
  BoardItem *tim_item1 = (BoardItem*)malloc(sizeof(BoardItem));
  strcpy( tim_item1->name, "Oculus Quest 2");
  tim_item1->next = NULL;
  tim_item1->prev = NULL; 
  
  lists[1].head =  tim_item1;

  BoardItem *dante_item1 = (BoardItem*)malloc(sizeof(BoardItem));
  strcpy(dante_item1->name, "Oculus Quest 1");
  dante_item1->next = NULL;
  dante_item1->prev = NULL; 
  
  BoardItem *dante_item2 = (BoardItem*)malloc(sizeof(BoardItem));
  strcpy( dante_item2->name, "3070 RTX");
  dante_item2->next = NULL;
  dante_item2->prev = dante_item1;

  lists[2].head =  dante_item1;
  dante_item1->next = dante_item2;
  
  BoardItem *abey_item1 = (BoardItem*)malloc(sizeof(BoardItem));
  strcpy(abey_item1->name, "Oculus Pro");
  abey_item1->next = NULL;
  abey_item1->prev = NULL;

  BoardItem *abey_item2 = (BoardItem*)malloc(sizeof(BoardItem));
  strcpy( abey_item2->name, "Oculus Quest 1");
  abey_item2->next = NULL;
  abey_item2->prev = abey_item1;

  lists[3].head =  abey_item1;
  abey_item1->next = abey_item2;

 
   //For loop to print out list and items in list 

   for(i = 0; i< numlists; i++)
    {
      printf("%s\n", lists[i].name);
      BoardItem *item = lists[i].head;
       while(item != NULL)
        {
          printf("- %s\n", item->name);
          item = item->next;
        }
        
    }
 
 
}
void loading_file(char * file_name){
    

    FILE * fp ;

    printf("PLease enter a file name:");
    scanf("%s", file_name);

    fp = fopen (file_name, "r");

    if ( fp == NULL ){
        printf("Error: Couldn't Load File");
        return;
    }else {
        printf("File '%s' opened successfully.\n", file_name);
        fclose (fp );
    }
}

/* 
  Function takes in an array of structs BoardList



*/
void edit_list(BoardList lists[], int numlists, const char *filename)
{
  
  char list_name[100], item_name[100], new_item_name[100];
  int choice, i;
  bool found_list = false; //keep track if list has been found or not initial set to false.
    
  printf("Enter the name of the list to edit\n");
  scanf("%s", list_name);

  //search for list by iterating through BoardList struct array in lists array.
  
  for(i= 0; i<numlists; i++){
    if(strcmp(lists[i].name, list_name) == 0){
      found_list = true;
      printf("Choices:\n");
      printf("1.Edit an item\n");
      printf("2.Add a new item\n");
      printf("3.Delete an item\n");
      printf("4.Return to main menu\n");
      scanf("%d", &choice);


      if (found_list){
      switch(choice){
        case 1:{
        //edit an item
        printf("Enter the name of item to edit:\n");
        scanf("%s", item_name);

        /*search for item.
          declare pointer current_item to point to Boarditem struct 
          initialise pointer to point to the first item in the current list.
          */
        BoardItem *current_item = lists[i].head;
        bool found_item = false;
        while(current_item != NULL){
            if(strcmp(current_item->name, item_name) == 0)
            {
                found_item = true;
                printf("Enter the new name for item %s: \n", item_name);
                scanf("%s", new_item_name);
                strcpy(current_item->name, new_item_name);
                printf("Item %s renamed to %s\n", item_name, new_item_name);
                save_board(lists, numlists, filename);
                break;
            }
            current_item = current_item->next;
        }
        break;
        }
      

        case 2:{
        // Add a new item
        printf("Enter the name of the new item: ");
        getchar();
        fgets(item_name, sizeof(item_name), stdin);
        item_name[strcspn(item_name, "\n")] = '\0';  // remove trailing newline character

        BoardItem *new_item = (BoardItem *)malloc(sizeof(BoardItem));
        strcpy(new_item->name, item_name);
        new_item->next = NULL;
        new_item->prev = NULL;

        if (lists[i].head == NULL) {
        lists[i].head = new_item;
        } else {
        BoardItem *temp = lists[i].head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_item;
        new_item->prev = temp;
    }

    printf("Item '%s' added to list '%s'\n", item_name, list_name);
    save_board(lists, numlists, filename);
    break;
        }

      case 3:{
    // Delete an item
    printf("Enter the name of the item to delete: ");
    scanf(" %99[^\n]", item_name);


    BoardItem *prev_item = NULL;
    BoardItem *current_item = lists[i].head;
    bool found_item = false;

    while (current_item != NULL) {
        if (strcmp(current_item->name, item_name) == 0) {
            found_item = true;
            if (prev_item == NULL) {
                lists[i].head = current_item->next;
            } else {
                prev_item->next = current_item->next;
            }
            printf("Item '%s' deleted from list '%s'\n", item_name, list_name);
            save_board(lists, numlists, filename);
            free(current_item);
            break;
        }
        prev_item = current_item;
        current_item = current_item->next;
      }
      if (!found_item) {
        printf("Item '%s' not found in list '%s'\n", item_name, list_name);
    }}
    default:
    printf("Invalid choice. Please enter a number from 1 to 3.\n");
    break;
   }
 }
}
}
}


/*
1.This fucntion allows user to edit a list in the BoardList array
2.user is prompted to enter the name of the list they want to edit
3.the function then iterates through BoardList struct array.
4.if list is found user is given options 
*/
// Function to edit a board's lists (rename, add, or delete lists)
void edit_board(BoardList lists[], int numlists, const char *filename)
{
  
  char list_name[100], new_list_name[100];
  int choice, i,j;
  bool found_list = false; //keep track if list has been found or not initial set to false.
    
  printf("Enter the name of the list to edit\n");
  scanf("%s", list_name);

  //search for list by iterating through BoardList struct array in lists array.
  
  for(i= 0; i<numlists; i++){
    if(strcmp(lists[i].name, list_name) == 0){
      found_list = true;
      printf("Choices:\n");
      printf("1.Edit the name of a list\n");
      printf("2.Add a new list\n");
      printf("3.Delete an list\n");
      printf("4.Return to main menu\n");
      scanf("%d", &choice);


      
  switch (choice) {
  case 1: {
    printf("Enter new name for list %s:\n", list_name);
    scanf("%s", new_list_name);

    // check if new list name already exists
    found_list = false;
    for (i = 0; i < numlists; i++) {
      if (strcmp(lists[i].name, new_list_name) == 0) {
        printf("List name already exists.\n");
        found_list = true;
        break;
      }
    }

    // Rename the list
    if (!found_list) {
      for (i = 0; i < numlists; i++) {
        if (strcmp(lists[i].name, list_name) == 0) {
          strcpy(lists[i].name, new_list_name);
          printf("List %s renamed to %s\n", list_name, new_list_name);
          save_board(lists, numlists, filename);
          break;
        }
      }
    }
  }

  case 2: {
    // Add a new list
    printf("Enter the name of the new list:\n");
    scanf("%s", new_list_name);

    found_list = false;
    // check if list already exists
    for (i = 0; i < numlists; i++) {
      if (strcmp(lists[i].name, new_list_name) == 0) {
        printf("List name already exists. Try a different name\n");
        found_list = true;
        break;
      }
    }
    // if list name doesn't exist, add to BoardList array
    if (!found_list) {
      BoardList new_list;
      strcpy(new_list.name, new_list_name);
      new_list.head = NULL;
      lists[numlists] = new_list; // adds new list to end of array
      numlists++; // increments numlists to account for new list being added

      printf("List %s added\n", new_list_name);
      save_board(lists, numlists, filename);
    }
    break;
  }
        case 3:{
        //delete current list
        printf("Enter the name of the list to delete\n");
        scanf("%s",list_name);
         int list_found = 0;
        //Find the list to delete
        for(i = 0; i <numlists; i++){
          if(strcmp(lists[i].name, list_name) == 0){
            //free up memory allocated to the items in the list
            BoardItem *current_item = lists[i].head;
            while(current_item != NULL){
              BoardItem *temp_item = current_item;
              current_item  = current_item-> next;
              free(temp_item);
            }

            //remove list from array and update the number of lists 
            for(j = 0; j< (numlists-1); j++){
              lists[j] = lists[j +1];
    
            }
            numlists--;
            printf("List %s deleted\n", list_name);
            save_board(lists,numlists,filename);
            list_found = 1; 
            break;
          }
        }
        if(!list_found){
          printf("List not found\n");
        }
        break;
        }
       }
      }
    }
  }

// Function to save the contents of a board to a file
void save_board(BoardList lists[], int numlists, const char *filename) {
  // Open the file for writing
    FILE *file = fopen(filename, "w");
     // Check if the file was opened successfully
    if (file == NULL) {
        printf("Error: Unable to open file '%s' for writing.\n", filename);
        return;
    }

    for (int i = 0; i < numlists; i++) {
        fprintf(file, "List: %s\n", lists[i].name);
        BoardItem *current_item = lists[i].head;
        // Iterate through each item in the list
        while (current_item != NULL) {
           // Write the item name to the file
            fprintf(file, "  Item: %s\n", current_item->name);
             // Move to the next item in the list
            current_item = current_item->next;
        }
    }
 // Close the file after writing all the data
    fclose(file);
    printf("Board saved to file '%s'.\n", filename);
}
