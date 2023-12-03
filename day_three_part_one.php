<?php

const indicators = array('#','%','&','*','+','-','/','=','@','$');


function search_for_part_numbers($file_buffer){

    $parts_sum = 0;

    $currently_building_number = 0;
    $surely_a_part_number = false;

    for ($row_id=0; $row_id < count($file_buffer); $row_id++) { 
        
        $current_row = $file_buffer[$row_id];

        for($index = 0; $index < strlen($current_row); $index++){
            
            if ($current_row[$index] == '.' || in_array($current_row[$index], indicators)  ){
                if($currently_building_number != 0){

                }
                if ($surely_a_part_number){
                    $parts_sum += $currently_building_number;

                    
                }
                $surely_a_part_number = false;
                $currently_building_number = 0;
                continue;
            }

            if (is_numeric($current_row[$index])){

                $currently_building_number *= 10; 
                $currently_building_number += intval( $current_row[$index]) ;
                
                if($surely_a_part_number){continue;}
                if ($row_id != 0){
                    $top_left = $file_buffer[$row_id -1][$index -1];
                    $top = $file_buffer[$row_id -1][$index ];
                    $top_right = $file_buffer[$row_id -1][$index +1];

                    
                    if( in_array($top_left, indicators) || in_array($top, indicators) || in_array($top_right, indicators)){
                        $surely_a_part_number = true;
                        continue;
                    }
                }

                $neighbour_left = $file_buffer[$row_id][$index -1];
                $neighbour_right = $file_buffer[$row_id][$index +1];
                if (in_array($neighbour_left, indicators) || in_array($neighbour_right, indicators)){
                    $surely_a_part_number = true;
                    continue;
                }

                if ($row_id != count($file_buffer) -1){
                    $bottom_left = $file_buffer[$row_id +1][$index -1];
                    $bottom = $file_buffer[$row_id +1][$index ];
                    $bottom_right = $file_buffer[$row_id +1][$index +1];

                    if( in_array($bottom_left, indicators) || in_array($bottom, indicators) || in_array($bottom_right, indicators)){
                        $surely_a_part_number = true;
                        continue;
                    }
                }

            }

            if ($index == strlen($current_row) -1){
                if ($surely_a_part_number){
                    $parts_sum += $currently_building_number;

                }
                $surely_a_part_number = false;
                $currently_building_number = 0;
            }
        }



    }


    return $parts_sum;

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