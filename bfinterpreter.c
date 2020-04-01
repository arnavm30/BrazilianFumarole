//clang bf.c -o bf && ./bf sample1.bf
//clang -g -fsanitize=address bfinterpreter.c -o bfinterpreter && ./bfinterpreter sample1.bf

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
//  printf("I EQUALS%d\n", i);
  char new_file_contents[i];

  for(int j = 0; j < i; j++) {
    new_file_contents[j] = file_contents[j];
    //printf("NEW%c\n", new_file_contents[j]);
    //printf("OLD%c\n", file_contents[j]);
  }
  //printf("%d\n", sizeof(new_file_contents));
  //printf("OLD %d\n", sizeof(file_contents));
  fclose(fp);
}

char* replace_invalid_characters(char file_contents[]) {
  //printf("%s\n", file_contents);
  printf("SIZE: %lu\n", strlen(file_contents));
  char* ritual = (char*) (malloc(strlen(file_contents) * sizeof(char)));
  for (int i = 0; i < strlen(file_contents); i++) {
    printf("INDEX: %d\n", i);
    printf("%d\n",strchr(ptr_legal_characters, file_contents[i]) != NULL);
    puts("BEFORE IF");
    if (strchr(ptr_legal_characters, file_contents[i]) != NULL) {
      ritual[i] = file_contents[i];
      printf("INDEX (IF): %d\n", i);
      printf("%c\n", ritual[i]);
      //ritual[i] = '\0'; //turn into empty char
    }
    else
    {
      puts("IN ELSE");
      ritual[i] = '\0';
    }
    printf("INDEX: %d\n", i);
  }
  puts("HELLOOOO");//didnt print this maybe stuck in loop
  return ritual;
}

int main(int argc, char** argv) {
  char* file_name = argv[1];
  char file_contents[MAX_RITUAL_SIZE];
  int tribe[TRIBE_SIZE] = {0}; //initializing to 0s


  read_file(file_name, file_contents);
  puts("READ THE FILE");
  replace_invalid_characters(file_contents); //breaking here
  puts("REplacing CHARACTERS");

}


/* CODE TALK CORNER
A:


R:

*/
