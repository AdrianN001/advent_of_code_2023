#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define char_to_int(x) ((int)(x - '0'))

bool char_is_digit(char character) { 
    return ((character >= '0') && (character <= '9'));
}


int search_for_digits(char* line, size_t line_length){
    int left_side = -1;
    int right_side = -1;

    size_t left_pointer = 0;
    size_t right_pointer = line_length;

    while (left_side == -1){
        char current_char_on_left_pointer = line[left_pointer];

        if (char_is_digit(current_char_on_left_pointer)){
            left_side = char_to_int(current_char_on_left_pointer);
        }else { 
            left_pointer++;
        }
    }

    while (right_side == -1){
        char current_char_on_right_pointer = line[right_pointer];

        if (char_is_digit(current_char_on_right_pointer)){
            right_side = char_to_int(current_char_on_right_pointer);
        }else { 
            right_pointer--;
        }
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

    while (fgets(line_buffer, 512, fp)){

        line_size = strlen(line_buffer);
        number_found_in_the_line = search_for_digits(line_buffer, line_size);
        sum += number_found_in_the_line;
    }
    printf("The answer is [[ %lld ]] \n", sum);
    return 0;
}