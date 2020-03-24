// Arnav and Roland brazilian fumarole interpeter file

#include "stdio.h"
#include "stdlib.h"

const char [50000]ritual;
char* ritual_ptr = &ritual;
int tribe [50000] = {}; //initializing to 0s
int* tribe_ptr = &tribe;
const char* legal_characters = {'<', '>', '+', '-', '(', ')', '*'};
const char* FILE_PATH = "/Users/arnavmuthiayen/Workarea/workspace/C/program.bf";

const char step_left = '<';
const char step_right = '>';
const char add_pebble = '+';
const char sub_pebble = '-';
const char left_pa = '(';
const char right_pa = ')';
const char print = '*';


int main() {
  get_file();
  replace_invalid_characters();
}

void get_file(FILE_PATH) {
  FILE* fp = fopen(FILE_PATH, "r");
	if (fp == NULL)
	{
		printf("Couldn't open file! \n");
		exit(1);
	}
  fgets(&ritual, 500000, fp);       //gets file, puts it into ritual
  fclose();
  printf(ritual);
}

void replace_invalid_characters() {
  for (int i = 0; i < str_len(ritual); i++) {
    if (strchr(legal_characters, ritual[i]) == NULL)
    {
      ritual[i] = '\0'; //turn into empty char
    }
  }
}

bool balanced_parenthesis() {
  countLeft = 0;
  countRight = 0;
  for (int i = 0; i < str_len(ritual); i++) {
    if (ritual[i] = "(") {
      countLeft ++;
    }
    else if (ritual[i] = ")") {
      countRight ++;
    }
  }
  if (countLeft == countRight) ) {
    return True;
  }
  else {
    return False;
  }
}

void interpreter() {
  while (*ritual_ptr < strlen(ritual)) {
    if (*ritual_ptr == step_left) {
      ritual_ptr--;
    }
    else if (*ritual_ptr == step_right) {
      ritual_ptr++;
    }
    else if (*ritual_ptr == add_pebble) {
      (*ritual_ptr)++;
    }
    else if (*ritual_ptr == sub_pebble) {
      (*ritual_ptr)--;
    }
    // kk10:20 reminder for myself
    else if (*ritual_ptr == left_pa) {
      if((*ritual_ptr) == 0) {
         while ((*ritual_ptr) != ')')
           ritual_ptr++;
      }
      else {
        ritual_ptr++;
      }
    }
    else if (*ritual_ptr == right_pa) {
      if (*(ritual_ptr)
    }
    else if (*ritual_ptr == print) {
      printf((*ritual_ptr))
    }

  }


}

void optimize () {

}





/* CODE TALK CORNER
A:


R:

*/
