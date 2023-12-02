#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define char_to_int(x) ((int)(x - '0'))
const char* valid_numbers[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
const char initials[6] = "otfsen";
const char endings[6] = "eorxnt";


bool char_is_digit(char character) { 
    return ((character >= '0') && (character <= '9'));
}

int is_initial(char character) {
    for (int i = 0; i < 6; i++){
        if (character == initials[i]){
            return i;
        }
    }
    return -1;
}
int is_ender(char character){
    for (int i = 0; i < 6; i++){
        if (character == endings[i]){
            return i;
        }
    }
    return -1;
}

int start_tracking_l_2_r(char* line,size_t line_length, size_t pointer, char initial){
    for (int i = 0; i < 9; i++){
        char initial_of_the_number = valid_numbers[i][0];
        if (initial_of_the_number != initial) continue;

        char* current_number = valid_numbers[i];
        size_t length_of_the_string = strlen(current_number);
        int res = strncmp(current_number, &line[pointer],length_of_the_string );
        if (res == 0){
            return i + 1;
        }
    }
    return -1;
}
int start_tracking_r_2_l(char* line,size_t line_length, size_t pointer, char ender){
    for (int i = 0; i < 9; i++){
        size_t length_of_the_number = strlen(valid_numbers[i]);
        char ending_of_the_number = valid_numbers[i][length_of_the_number -1];
        if (ending_of_the_number != ender) continue;

        char* current_number = valid_numbers[i];
        int start_of_the_sequence = pointer - length_of_the_number +1;
        if(start_of_the_sequence <= -1) continue;

        int res = strncmp(current_number, &line[start_of_the_sequence], length_of_the_number);
        if (res == 0){
            return i + 1;
        }
    }
    return -1;
}


int search_for_digits(char* line, size_t line_length){
    int left_side = -1;
    int right_side = -1;

    size_t left_pointer = 0;
    size_t right_pointer = line_length -2;
    int initial;
    int ender;

    while (left_side == -1){
        char current_char_on_left_pointer = line[left_pointer];

        if (char_is_digit(current_char_on_left_pointer)){
            left_side = char_to_int(current_char_on_left_pointer);
        }else if ( (initial = is_initial(current_char_on_left_pointer)) != -1){
            int res = start_tracking_l_2_r(line, line_length, left_pointer, initials[initial]);
            if (res != -1){
                left_side = res;
            }
        }
        left_pointer++;
    }
    
    while (right_side == -1){
        char current_character_on_right_pointer = line[right_pointer];
        if(char_is_digit(current_character_on_right_pointer)){
            right_side = char_to_int(current_character_on_right_pointer);
        }else if( (ender = is_ender(current_character_on_right_pointer)) != -1  ){
            int res = start_tracking_r_2_l(line, line_length, right_pointer, endings[ender]);
            if (res != -1){
                right_side = res;
            }
        }
        right_pointer--;
    }
    return (left_side * 10) + right_side;

}

int main(void){
    FILE *fp;

    fp = fopen("./input/day_one.txt", "r");
    if (fp == NULL){
        printf("Error while executing code.\n Input file wasn't found! \n");
        return 1;
    }
    
    char line_buffer[512] = {0};
    size_t line_size; 
    int number_found_in_the_line;
    long long sum = 0;

    int x = 6;

    while (fgets(line_buffer, 512, fp)){

        line_size = strlen(line_buffer);
        number_found_in_the_line = search_for_digits(line_buffer, line_size);
        sum += number_found_in_the_line;

    }
    printf("The answer is [[ %lld ]] \n", sum);
    return 0;
}