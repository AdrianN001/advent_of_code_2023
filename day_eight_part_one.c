#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct node{
    char* name; 

    char* left_side_name;
    struct node* left_side;

    char* right_side_name;
    struct node* right_side; 
} node_t;


typedef struct{
    node_t* start;
    node_t* end;
} endpoints;

node_t create_node(char* buffer, size_t length){
    char* name = (char*)malloc(sizeof(char) * 4);
    for(int i = 0; i < 3; i++){
        name[i] = buffer[i];
    }
    name[3] = '\0';

    char* left_side_name = (char*)malloc(sizeof(char) * 4);
    for (int i = 7; i < 10; i++){
        left_side_name[i-7] = buffer[i];
    }
    left_side_name[3] = '\0';

    char* right_side_name = (char*)malloc(sizeof(char) * 4);
    for (int i = 12; i < 15; i++){
        right_side_name[i - 12] = buffer[i];
    }
    right_side_name[3] = '\0';

    return (node_t){
        .name=name,
        .left_side_name = left_side_name,
        .left_side = NULL,

        .right_side_name = right_side_name,
        .right_side = NULL
    };
}
endpoints get_endpoints( node_t* nodes, size_t number_of_nodes){
    node_t* start = NULL;
    node_t* end = NULL;
    for (int i = 0; i<number_of_nodes;i++){
        node_t* curr = &nodes[i];
        if (!strncmp(curr->name, "AAA", 3)){
            start = curr;
        }else if(!strncmp(curr->name, "ZZZ", 3)){
            end = curr;
        }
    }
    return ( endpoints ) {
        .start=start,
        .end=end
    };
}

void join_nodes(node_t* node_list, size_t number_of_nodes){
    for (int i = 0; i < number_of_nodes; i++){
        node_t* current_node = &node_list[i];

        for (int j = 0; j < number_of_nodes; j++){
            node_t* currently_view_node = &node_list[j];
            if (!strncmp(currently_view_node->name, current_node->left_side_name, 3)){
                current_node->left_side = currently_view_node;
            }
            if (!strncmp(currently_view_node->name, current_node->right_side_name, 3)){
                current_node->right_side = currently_view_node;
            }
        }
    }
}

int traverse_all_nodes(endpoints two_endoints, bool* instructions, size_t number_of_instructions, node_t* all_nodes, size_t number_of_nodes){
    node_t* start = two_endoints.start;
    node_t* destination = two_endoints.end;

    node_t* current_node = start;

    int steps = 0;
    while(true){

        for (int i = 0; i < number_of_instructions; i++){
            // Right
            if (instructions[i]){
                current_node = current_node->right_side;
            }else{
                current_node = current_node->left_side;
            }
            steps++;
            if(current_node == destination){

                goto RETURNING_SOLUTION;
            }
        }
    }

RETURNING_SOLUTION:
    return steps;
    
}


void print_node(node_t* node){
    printf("Name: %s \nLeft_Side: %s \nRight_Side: %s \nPointer:%p\n", node->name, node->left_side->name, node->right_side->name, node);
}

bool* read_in_the_instructions(char* buffer, size_t buffer_size){
    bool* instruction_buffer = (bool*)malloc(sizeof(bool) * 1024);
    
    for (int i = 0; i < buffer_size; i++){
        instruction_buffer[i] = buffer[i] == 'R' ? 1 : 0;
    }
    return instruction_buffer;
}
void free_all(node_t* all_nodes, size_t number_of_nodes){
    for (int i = 0; i < number_of_nodes;i++){
        free(all_nodes[i].left_side_name);
        free(all_nodes[i].right_side_name);
        free(all_nodes[i].name);
    }
}

int main(void){
    FILE* fp; 
    fp = fopen("./input/day_eight.txt","r");

    node_t all_nodes[1024] = {0};
    size_t current_node_pointer = 0;

    char buffer[1024];
    size_t line_length;

//  Reading in the first line
    fgets(buffer, 1024, fp);
    size_t number_of_instructions = strlen(buffer) -1;


    bool* instructions = read_in_the_instructions(buffer, number_of_instructions);

    while(fgets(buffer, 1024, fp)){
        line_length = strlen(buffer);
        if (line_length == 1){
            continue;
        }

        all_nodes[current_node_pointer] = create_node(buffer, line_length); 
        current_node_pointer++;

    }
    join_nodes(all_nodes, current_node_pointer);
    endpoints endpoint = get_endpoints(all_nodes, current_node_pointer);
    for (int i =0; i<current_node_pointer;i++){
        print_node(&all_nodes[i]);
    }
    
    int answer = traverse_all_nodes(
        endpoint,
        instructions,
        number_of_instructions,
        all_nodes,
        current_node_pointer
    );
    printf("DONE %d", answer);
    free_all(all_nodes, current_node_pointer);

    fclose(fp);
    return 0;
}