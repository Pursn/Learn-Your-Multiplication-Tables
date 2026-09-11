/****************************************************************************
 * FILENAME:      main.c
 * DESCRIPTION:   Learn-Your-Multiplication-Tables (LYMT)
 *                A C program that helps you learn your multiplication tables.
 * CREATOR:       Jose Duarte
 * DATE:          September 6, 2026
 * LICENSE:       GPL-3.0 license
 ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

char conf_file_path[1024];
#define CONF_FILE ".lymt_conf"
#define MAX_TABLE_LENGTH "20"

FILE *file_ptr;

void clear_screen(){
  system("clear");
}

void clear_input_buffer(){
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

bool file_exists(){
  file_ptr = fopen(conf_file_path, "r");

  if(file_ptr == NULL)  return false;
  return true;
}//end of file_exists function

void file_check(){
  //If our .conf file doesn't exist, we make it exist.
  if(!(file_exists())){
    file_ptr = fopen(conf_file_path, "w");
    fprintf(file_ptr, MAX_TABLE_LENGTH);
    fflush(file_ptr);
  }
}//end of file_check function

void select_table_to_practice();

void modify_learning_settings();

int main(){
  clear_screen();

  char *home = getenv("HOME");
  snprintf(conf_file_path, sizeof(conf_file_path), "%s/%s", home, CONF_FILE);

  file_check();
  
  char option[2];//This includes the null character at the end
  bool option_loop;
  
  do{
    option_loop = false;

    printf("Learn-Your-Multiplication-Tables (LYMT)\n");
    printf("What would you like to do?\n");
    printf("1.)  Choose a table to practice\n");
    printf("2.)  Modify learning settings\n");

    fgets(option, sizeof(option), stdin);
    
    clear_screen();

    //The switch needs the first character without the null character.
    switch(option[0]){
      case '1':
        printf("Which table would you like to practice?:\n");
        select_table_to_practice();
        break;
      case '2':
        printf("Set a MAX table length (10-100):\n");
        modify_learning_settings();
        break;
      default:
        //Ask the user to answer again.
        option_loop = true;
        printf("Please try again...\n");
    }//end of switch
  }//end of do
  while(option_loop);

  //We are done with everything
  fclose(file_ptr);
  return 0;
}//end of main function




void select_table_to_practice(){
  //Read data from conf file
  file_ptr = fopen(conf_file_path, "r");

  char max_table_length_buffer[5];
  fgets(max_table_length_buffer, sizeof(max_table_length_buffer), file_ptr);

  int max_table_length = strtol(max_table_length_buffer, NULL, 10);

  //This gets the length of characters an integer has.
  char chosen_number_buffer[(int)log10(max_table_length) + 1];
  int chosen_number = -1;

  bool loop = true;
  do{

    //Gets user input
    fgets(chosen_number_buffer, sizeof(chosen_number_buffer), stdin);

    chosen_number = strtol(chosen_number_buffer, NULL, 10);

    if(chosen_number > 0 && chosen_number <= max_table_length){
      loop = false;
    }
  }//end of do
  while(loop);
  

  
  //Create array
  int array[max_table_length];
  
  //Random dependent on using current time
  srand(time(NULL));
  
  //Fill the array
  for(int i = 0; i < max_table_length; i++){
    array[i] = i + 1;
  }

  //Shuffle array: Fisher-Yates algorithm
  //https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
  for(int i = max_table_length - 1; i > 0; i--){
    //Random index from 0 to current index
    int random_index = rand() % (i + 1);

    //Swap current index's element with the one at the random index
    int temp_holder = array[i];
    array[i] = array[random_index];
    array[random_index] = temp_holder;
  }
  
  int answer;
  int count_of_correct = 0;

  char answer_buffer[5];

  clear_input_buffer();

  for(int index = 0; index < max_table_length; index++){
    clear_screen();

    printf("Correct: %d/%d\n", count_of_correct, max_table_length);
    printf("%d.)  %d X %d = ", (index + 1), chosen_number, array[index]);
    
    fgets(answer_buffer, sizeof(answer_buffer), stdin);
    printf("\n");
    answer = strtol(answer_buffer, NULL, 10);
    
    if(answer == (chosen_number * array[index])){
      count_of_correct++;
    }

    clear_screen();
  }

  printf("Done: %d/%d\n", count_of_correct, max_table_length);
}//end of select_table_to_practice function

void modify_learning_settings(){
  char buffer[4];

  clear_input_buffer();

  fgets(buffer, sizeof(buffer), stdin);

  int response = strtol(buffer, NULL, 10);
  file_ptr = fopen(conf_file_path, "w");

  if(response < 10){
    fprintf(file_ptr, "10");
  }
  else if(response > 100){
    fprintf(file_ptr, "100");
  }
  else{
    fprintf(file_ptr, buffer);
  }
}//end of modify_learning_settings function

