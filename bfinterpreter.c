/*
Authors: Arnav Muthiayen and Roland Martinez
This program is a C implementation of a Brazilian Fumarole (modified Brainfuck)
interpreter.
*/

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

#define TRIBE_SIZE 50000 // Number of members in the tribe
#define MAX_RITUAL_SIZE 10000 // Max amount of runes in a ritual (bf file)

// Valid characters in a Brazilian Fumarole file
const char step_left = '<';
const char step_right = '>';
const char add_pebble = '+';
const char sub_pebble = '-';
const char left_pa = '(';
const char right_pa = ')';
const char print = '*';

/**description:
reads file, as characters are read in, it only keeps
the valid characters

params:
file_name ==> name of bf file
ritual[MAX_RITUAL_SIZE] ==> where the file is stuffed

**/
void read_file(char* file_name, char ritual[MAX_RITUAL_SIZE]) {
  FILE* fp = fopen(file_name, "r");
  //try catch-esque system ==> if can't open file let user know
  if (fp == NULL)
  {
    printf("Couldn't open file!\n");
    exit(1);
  }
  int i = 0;
  while(!feof(fp)) {
    char current_char = fgetc(fp);

    //if valid, stuff it into ritual, at position i, which increases
    //whenever there's a valid character, so that valid characters
    //are all next to each other in ritual
    if(current_char == step_left || current_char == step_right ||
        current_char == add_pebble || current_char == sub_pebble ||
        current_char == left_pa || current_char == right_pa ||
        current_char == print) {
      ritual[i] = current_char;
      i++;
    }
  }
  puts("AFTER READING FILE");
  puts(ritual);
  fclose(fp);
}

/**description:
checks if parentheses are balanced with a for loop
to go through ritual and an if statement to make sure
there isn't a right parentheses before a left parentheses

params:
char* ritual => pointer to valid characters in bf file

return:
bool ==> whether or not parentheses are balanced
**/
bool balanced_parentheses(char* ritual) {
  int countLeft = 0;
  int countRight = 0;
  bool leftAdded = false; //bool for whether there has been a left parentheses

  //going through each character in ritual
  for (int i = 0; i < strlen(ritual); i++) {
    //when left_pa, increase count and say that theres been a left_pa
    //so that when right_pa comes, it counts as valid
    if (ritual[i] == left_pa) {
      countLeft++;
      leftAdded = true;
    }
    //when at right parantheses and there's been a left before it, then then
    //right_pa is valid, so increase coount
    else if (ritual[i] == right_pa && leftAdded) {
      countRight++;
    }
  }

  //if same number of left_pa and right_pa, then we good
  if (countLeft == countRight) {
    return true;
  }

  //here's invalid, print something in main if this happens
  else {
    return false;
  }
}

/**description:
interpret the bf file's valid characters:
step_left ==> moves left in tribe

step_right ==> moves right in tribe

add_pebble ==> adds to tribe, wherever it's pointing to

sub_pebble ==> subtracts to tribe, wherever it's pointing to

left_pa ==> if current position in tribe is 0, it moves to matching right_pa,
if current position in tribe is greater than 0, then it does nothing (just
moves on in ritual)

right_pa ==> if current position in tribe is 0, it does nothing (just moves on in ritual),
if current position in tribe is greater than 0, then it goes back to matching left_pa

print ==> automatic decimal to char conversion by printf


params:
ritual ==> bf file's valid characters
tribe ==> array of 50000 0s, where commands in ritual are done
**/
void interpreter(char* ritual, unsigned char* tribe) {
  unsigned char* tribe_ptr = tribe; // Divine pointress that points to a tribe member

  //goes through ritual
  while (ritual < ritual + strlen(ritual)) {

    if (*ritual == step_left) {
      //if it goes out of bounds, then give a warning to user
      if (tribe_ptr == tribe) {
        puts("Invalid move. Undesirable left wrapping was prevented.");
        exit(1);
      }
      else {
        tribe_ptr--;
        ritual++;
      }
    }
    else if (*ritual == step_right) {
      //if it goes out of bounds, then give a warning to user
      if (tribe_ptr == tribe+TRIBE_SIZE-1) {
        puts("Invalid move. Undesirable right wrapping was prevented.");
        exit(1);
      }
      else {
        tribe_ptr++;
        ritual++;
      }
    }
    else if (*ritual == add_pebble) {
      (*tribe_ptr)++;
      ritual++;
    }
    else if (*ritual == sub_pebble) {
      (*tribe_ptr)--;
      ritual++;
    }
    else if (*ritual  == left_pa) {
      if((*tribe_ptr) == 0) {
        int countLeft = 0; //count of additional left_pa
        int countRight = 0; //count of additional right_pa

        ritual++; //moves on in ritual, so it doesn't count the left_pa
        //twice in coming while loop

        //keeps on going until at right_pa and count of excess
        //parentheses are the same
        while(*ritual != right_pa || countLeft != countRight) {
          //if there's a left_pa, then add to count (to make sure the
          //right_pa it goes to is matching)
          if (*ritual == left_pa) {
            countLeft++;
          }

          //if there's a right_pa, then add to count (to make sure
          //the right_pa it goes to is matching)
          if (*ritual == right_pa) {
            countRight++;
          }
          //keep on going forward 'till conditions are fulfilled
          ritual++;
        }
      }
      else {
        ritual++;
      }
    }
    else if (*ritual == right_pa) {
      if(*tribe_ptr == 0) {
        ritual++;
      }
      else {
        int countLeft = 0; //count of additional left_pa
        int countRight = 0; //count of additional right_pa

        ritual--;//moves on in ritual, so it doesn't count the right_pa
        //twice in coming while loop

        //keeps on going until at left_pa and count of excess
        //parentheses are the same
        while(*ritual != left_pa || countLeft != countRight) {
          //if there's a right_pa, then add to count (to make sure
          //the left_pa it goes to is matching)
          if (*ritual == right_pa) {
            countRight++;
          }
          //if there's a left_pa, then add to count (to make sure
          //the left_pa it goes to is matching)
          if (*ritual == left_pa) {
            countLeft++;
          }
          //keep on going backward 'till conditions are fulfilled
          ritual--;
        }
      }
    }
    else if (*ritual == print) {
      printf("%c", (*tribe_ptr)); //automatic decimal to char conversion by printf
      ritual++;
    }

    //if not a valid character, let's user know something went wrong
    else {
      printf("Oops. Error in the interpreter.");
      exit(1);
    }
  }
}

/**description:
read the bf file, check for validity, and intereprets

params:
argc ==> number of command-line params
argv ==> file name input by user in command-line
**/
int main(int argc, char** argv) {
  char* file_name = argv[1]; // sets file name equal to what's entered by user in command-line
  char ritual[MAX_RITUAL_SIZE]; // creates ritual of max ritual size
  unsigned char tribe[TRIBE_SIZE] = {0}; // unsigned so wraps numbers from 0 - 255
                                      // and all tribe members initially have 0 pebbles

  read_file(file_name, ritual);
  puts("Read the file and removed invalid characters.");

  if (!balanced_parentheses(ritual)) {
    puts("Oops, parenthesis aren't balanced.");
    exit(0);
  }

  puts("Intepreting...");

  interpreter(ritual, tribe);
  puts("\n\nProgram terminated.");
  exit(0);
}
