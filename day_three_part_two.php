<?php

const indicator = "*";

function search_for_the_numers($file_buffer, $row,$collumn){
    $pivot = $file_buffer[$row][$collumn];
    $number = intval($pivot);
    $left_offset = 1;


    // Search for the left side;
    while (true) {
        if (!is_numeric($file_buffer[$row][$collumn - $left_offset])){
            break;
        }
        $digit = intval($file_buffer[$row][$collumn - $left_offset]);
        
        $number += $digit * pow(10, $left_offset);

        $left_offset++;
    }

    $right_offset = 1;

    // Search for the right side;
    while (true) {
        if (!is_numeric($file_buffer[$row][$collumn + $right_offset])){
            break;
        }
        $digit = intval($file_buffer[$row][$collumn + $right_offset]);
        
        $number *= 10;
        $number += $digit;

        $right_offset++;
    }
    return $number;

}


function search_for_part_numbers($file_buffer){

    $gear_ration = 0;

    for ($row_id=0; $row_id < count($file_buffer); $row_id++) { 
        
        $current_row = $file_buffer[$row_id];

        for($index = 0; $index < strlen($current_row); $index++){

            if ($current_row[$index] == indicator){

                $found_numbers = array();

                for ($horizotal_offset=-1; $horizotal_offset <2 ; $horizotal_offset++) { 
                    for ($vertical_offset=-1; $vertical_offset <2 ; $vertical_offset++) {

                        $currently_checing_box = $file_buffer[$row_id + $vertical_offset][$index + $horizotal_offset];
                        if (!is_numeric($currently_checing_box) || $currently_checing_box == "."){continue;}
                        
                        $number_found = search_for_the_numers($file_buffer, $row_id + $vertical_offset, $index + $horizotal_offset);
                        if(!in_array($number_found, $found_numbers)){
                            array_push($found_numbers, $number_found);
                        }
                         
                    }
                }
                if (count($found_numbers) == 2){
                    $gear_ration += $found_numbers[0] * $found_numbers[1];
                }
                

            }
        }



    }


    return $gear_ration;

}





function readfile_to_buffer($file) {
    
    $base_array = array();

    while (!feof($file)){
        $current_line = fgets($file);
        array_push($base_array, $current_line);
        
    }
    return $base_array;
}


$input_file = fopen("./input/day_three.txt", "r");
$line_buffers = readfile_to_buffer($input_file);

$result = search_for_part_numbers($line_buffers);
echo " The answer is: [[ $result ]] \n";

?>