//clang bf.c -o bf && ./bf sample.bf
//clang -g -fsanitize=address bf.c -o bf && ./bf sample.bf

// Arnav and Roland brazilian fumarole interpeter file

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"


#define TRIBE_SIZE 50000
#define RITUAL_SIZE 10000

char ritual[RITUAL_SIZE];
char* ritual_ptr = ritual;
const char* init_ritual_ptr = ritual;

int tribe[TRIBE_SIZE] = {0}; //initializing to 0s
int* tribe_ptr = tribe;

const char legal_characters[7] = {'<', '>', '+', '-', '(', ')', '*'};
const char* ptr_legal_characters = legal_characters;

const char step_left = '<';
const char step_right = '>';
const char add_pebble = '+';
const char sub_pebble = '-';
const char left_pa = '(';
const char right_pa = ')';
const char print = '*';


void read_file(char* file_name) {
  FILE* fp = fopen(file_name, "r");
  if (fp == NULL)
  {
    printf("Couldn't open file! \n");
    exit(1);
  }
  fgets(ritual, RITUAL_SIZE, fp);       //gets file, puts it into ritual
  fclose(fp);
  //printf(ritual);
}

void replace_invalid_characters() {
  for (int i = 0; i < strlen(ritual); i++) {
    if (strchr(ptr_legal_characters, ritual[i]) == NULL)
    {
      ritual[i] = '\0'; //turn into empty char
    }
  }
}

bool balanced_parentheses() {
  int countLeft = 0;
  int countRight = 0;
  for (int i = 0; i < strlen(ritual); i++) {
    if (ritual[i] == left_pa) {
      countLeft++;
    }
    else if (ritual[i] == right_pa) {
      countRight++;
    }
  }
  if (countLeft == countRight) {
    return true;
  }
  else {
    return false;
  }
}

struct Addresses_of_Parentheses {
  char* left_pa; //location of left_pa
  char* right_pa; //location of right_pa
};
typedef struct Addresses_of_Parentheses pa_loc;

pa_loc** parentheses_check() {
  pa_loc** dic_pa = (pa_loc*) malloc(sizeof(pa_loc) * (RITUAL_SIZE/2));
  //pa_loc dic_pa[RITUAL_SIZE/2]; // array of locations for matching left_pa and right_pa
  int countLeft = 0; //count of left_pa and index in dic_pa
  int countRight = 0; //count of right_pa and index in dic_pa
  bool leftAdded = false; //bool to check if a left_pa has come before right_pa
  for(int i = 0; i < strlen(ritual); i++) {
    if (ritual[i] == left_pa) {
      dic_pa[countLeft].left_pa = (char*) (init_ritual_ptr + i); //putting location of left_pa in pa_loc struct
      countLeft++; //increasing the count of left_pa and index in dic_pa
      leftAdded = true; //telling method that there's been a left_pa
    }
    else if (ritual[i] == right_pa) {
      if (leftAdded) { //making sure that there's been a left_pa before right_pa, so that they're matching
        dic_pa[countRight].right_pa = (char*) (init_ritual_ptr + i); //putting location of right_pa in pa_loc struct with matching left_pa
        countRight++; //increasing the count of right_pa and index in dic_pa
        leftAdded = false; //telling method that dic_pa for this index is matched ==> setting up for next pair of pa in dic_pa
      }
      else {
        dic_pa[0].right_pa = 0; //setting right_pa = left_pa for first value in dic_pa, which will never normally happen, letting me know parentheses are illegal
        dic_pa[0].left_pa = 0;
        printf("Mismatched Parentheses. Terminating Program"); //if !leftPa then there hasn't been a left_pa before right_pa, so pa are mismatched in ritual
        return dic_pa; //returning invalid dic_pa
      }
    }
  }
  return dic_pa; //returning dictionary of matching parenthesis locations
}
//nice 4 now

void interpreter(pa_loc** dic_pa_ptr) {
  while (*ritual_ptr < strlen(ritual)) {
    if (*ritual_ptr == step_left) {
      if (*tribe_ptr == 0) {
        printf("Invalid move. Undesirable wrapping was prevented.");
        exit(1);
      }
      else {
        tribe_ptr--;
        ritual_ptr++;
      }
    }
    else if (*ritual_ptr == step_right) {
      if (*tribe_ptr == tribe [TRIBE_SIZE-1]) {
        printf("Invalid move. Undesirable wrapping was prevented.");
        exit(1);
      }
      else {
        tribe_ptr++;
        ritual_ptr++;
      }
    }
    else if (*ritual_ptr == add_pebble) {
      (*tribe_ptr)++;
      ritual_ptr++;
    }
    else if (*ritual_ptr == sub_pebble) {
      (*tribe_ptr)--;
      ritual_ptr++;
    }
    else if (*ritual_ptr  == left_pa) {
      if((*tribe_ptr) == 0) {
        for(int i = 0; i < RITUAL_SIZE/2; i++) {
          if(ritual_ptr == (dic_pa_ptr +i)->left_pa) {
            ritual_ptr = (dic_pa_ptr +i)->right_pa;
          }
        }
      }
      else {
        ritual_ptr++; ///////////////////////////////////// CHECK IF YOU JUST EXECUTE WHAT"S NEXT BUT DONT MOVE OR U DO MOVE W/ MATTTT
      }
    }
    else if (*ritual_ptr == right_pa) {
      if(*tribe_ptr == 0) {
        ritual_ptr++;
      }
      else {
        for (int i = 0; i < RITUAL_SIZE/2; i++) {
          if(ritual_ptr == (dic_pa_ptr +i)->right_pa) {
            ritual_ptr = (dic_pa_ptr +i)->left_pa;
          }
        }
      }
    }
    else if (*ritual_ptr == print) {
      printf("%c\n", (*tribe_ptr));
    }
    else {
      printf("some error msg");
      exit(1);
    }
  }
}

/*
void optimize () {

}
*/

int main(int argc, char** argv) {
  char* file_name = argv[1]; //what's this? why is argv a double pointer?
  read_file(file_name);
  replace_invalid_characters();
  pa_loc** dic_pa_ptr = parentheses_check();
  if ((*dic_pa_ptr).left_pa == 0 && (*dic_pa_ptr).right_pa == 0) {
    printf("Oops, parenthesis aren't balanced.");
    exit(0);
  }
  interpreter(dic_pa_ptr);
  free(dic_pa_ptr);
}


/* CODE TALK CORNER
A:


R:

*/
