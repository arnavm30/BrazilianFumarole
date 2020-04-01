//clang bf.c -o bf && ./bf sample.bf
//clang -g -fsanitize=address bf.c -o bf && ./bf sample.bf

// Arnav and Roland brazilian fumarole interpeter file

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"


#define TRIBE_SIZE 50000
#define MAX_RITUAL_SIZE 10000

const char legal_characters[7] = {'<', '>', '+', '-', '(', ')', '*'};
const char* ptr_legal_characters = legal_characters;

const char step_left = '<';
const char step_right = '>';
const char add_pebble = '+';
const char sub_pebble = '-';
const char left_pa = '(';
const char right_pa = ')';
const char print = '*';


void read_file(char* file_name, char file_contents[MAX_RITUAL_SIZE]) {
  FILE* fp = fopen(file_name, "r");
  if (fp == NULL)
  {
    printf("Couldn't open file! \n");
    exit(1);
  }
  int i = 0;
  while(!feof(fp)) {
    file_contents[i] = fgetc(fp);
    //printf("%d", i);
    //printf("%c\n", file_contents[i]);
    i++;
  }
  //printf("%d\n", i);
  fclose(fp);
}

void replace_invalid_characters(char file_contents[]) {
  //puts("PLEASE WORK");
  for (int i = 0; i < (strlen(file_contents) * sizeof(char)); i++) {
    //puts("IN LOOP");
    //printf(ritual[i]);  ////strchr(ptr_legal_characters, ritual[i]) != NULL
    if (file_contents[i] == legal_characters[0] || file_contents[i] == legal_characters[1] ||
       file_contents[i] == legal_characters[2]|| file_contents[i] == legal_characters[3] ||
        file_contents[i] == legal_characters[4] || file_contents[i] == legal_characters[5] ||
         file_contents[i] == legal_characters[6]) {
      //puts("inside if");
      //printf("%c", file_contents[i]);
    }
    else {
      file_contents[i] = '\0';
    }
    //puts("outside if");
  }
  //puts(file_contents);
  //puts("HELLOOOO");
}

bool balanced_parentheses(char* ritual) {
  int countLeft = 0;
  int countRight = 0;
  bool leftAdded = false;
  for (int i = 0; i < strlen(ritual); i++) {
    if (ritual[i] == left_pa) {
      countLeft++;
      leftAdded = true;
    }
    else if (ritual[i] == right_pa && leftAdded) {
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



/**
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
**/



void interpreter(char* ritual, unsigned char* tribe) {
  unsigned char* tribe_ptr = tribe;
//  printf("%lu\n", strlen(ritual));
//  printf("%s\n", ritual);
  //printf("%d\n", *ritual);
  //printf("%d\n", ritual + strlen(ritual));
  while (ritual < ritual + strlen(ritual)) {
  //  printf("Iteration %s\n", ritual);
    //int count = 0;
    if (*ritual == step_left) {
    //  puts("LEFT STEPS:");
    //  printf("%d\n", count);
      //count++;
      if (tribe_ptr == tribe) { //what changed??just chekcing to see which ( it's messing up on)
        puts("Invalid move. Undesirable wrapping to the left was prevented.");
        exit(1);
      }
      else {
      //  puts("STEPPING LEFT");
        tribe_ptr--;
        ritual++;
      }
    }
    else if (*ritual == step_right) {
      //puts("In step right");
    //  printf("%d\n", *tribe_ptr);
    //  printf("%d\n", TRIBE_SIZE);
    //  printf("%d\n", tribe[TRIBE_SIZE-1]);
      if (tribe_ptr == tribe+TRIBE_SIZE-1) {
        puts("Invalid move. Undesirable wrapping was prevented to the right.");
        exit(1);
      }
      else {
      //  puts("STEPPING RIGHT");
        tribe_ptr++;
        ritual++;
      }
    }
    else if (*ritual == add_pebble) {
      (*tribe_ptr)++;
      //puts("ADDING PEBBLE");
      ritual++;
    }
    else if (*ritual == sub_pebble) {
      (*tribe_ptr)--;
      //puts("REMOVING PEBBLE");
      ritual++;
    }
    else if (*ritual  == left_pa) {
      if((*tribe_ptr) == 0) {
        int countLeft = 0;
        int countRight = 0;
        ritual++;
        while(*ritual != right_pa || countLeft != countRight) {
          if (*ritual == left_pa) {
            countLeft++;
          }
          if (*ritual == right_pa) {
            countRight++;
          }
          ritual++;
        }
        /**
        for(int i = 0; i < RITUAL_SIZE/2; i++) {
          if(ritual_ptr == (dic_pa_ptr +i)->left_pa) {
            ritual_ptr = (dic_pa_ptr +i)->right_pa;
          }
        }
        **/
      }
      else {
        ritual++; ///////////////////////////////////// CHECK IF YOU JUST EXECUTE WHAT"S NEXT BUT DONT MOVE OR U DO MOVE W/ MATTTT
      }
    }
    else if (*ritual == right_pa) {
      if(*tribe_ptr == 0) {
        ritual++;
      }
      else {
        int countLeft = 0;
        int countRight = 0;
        ritual--;
        while(*ritual != left_pa || countLeft != countRight) { //tcuz if nested therell be more of only ( right

          if (*ritual == right_pa) {
            countRight++;
          }
          if (*ritual == left_pa) {
            countLeft++;
          }
          ritual--;

        }
      }
    }
    else if (*ritual == print) {
      //printf("%d\n", (*tribe_ptr)); //int version
      printf("%c", (*tribe_ptr)); //ASCII version
      //puts("PRINTING PEBBLE");
      ritual++;
    }
    else {
      printf("some error msg");
      exit(1);
    }
    //printf("Ritual left to interepret: %s\n", ritual);
    //printf("Last char pointed at: %c\n", *ritual);
  }
}

int main(int argc, char** argv) {
  char* file_name = argv[1];
  char file_contents[MAX_RITUAL_SIZE];
  unsigned char tribe[TRIBE_SIZE] = {0}; //initializing to 0s

  read_file(file_name, file_contents);
  //printf("%s", "Contents of file: ");
  //puts(file_contents);
  puts("READ THE FILE");

  replace_invalid_characters(file_contents);
  puts("REPLACING CHARACTERS");
  char* ritual = file_contents;
  printf("%s", "Ritual: ");
  //puts(ritual);

  if (!balanced_parentheses(ritual)) {
    puts("Oops, parenthesis aren't balanced.");
    exit(0);
  }

  interpreter(ritual, tribe);

  /**
  pa_loc** dic_pa_ptr = parentheses_check();
  if ((*dic_pa_ptr).left_pa == 0 && (*dic_pa_ptr).right_pa == 0) {
    printf("Oops, parenthesis aren't balanced.");
    exit(0);
  }
  interpreter(dic_pa_ptr);
  free(dic_pa_ptr);
  **/
}
