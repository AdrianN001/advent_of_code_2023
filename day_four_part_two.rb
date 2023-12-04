

def parse_numbers(input_string)
    input_string.split(" ", -1).map {|n| n.to_i }
end

$apperances = {}



def solve(line) 
    card_number_string = line[ line.index(" ")..line.index(":") -1]
    winning_numbers_string = line[ line.index(":")+2..line.index("|")-2]
    played_numbers_string = line[line.index("|")+2..]


    card_number = card_number_string.to_i
    winning_numbers = parse_numbers winning_numbers_string
    played_numbers = parse_numbers played_numbers_string 


    matched_numbers = winning_numbers & played_numbers

    matches = matched_numbers.length()
    card_in_stack = $apperances[card_number] == nil ? 1 : $apperances[card_number] + 1
    card_in_stack.times do
        
        (card_number+1..card_number+matches).each do |i| 
            if !$apperances.include?(i) then
                $apperances[i] = 1
            else 
                $apperances[i] += 1
            end
        end
    end

    $apperances[card_number] = $apperances[card_number] == nil ? 1 : $apperances[card_number] + 1
end


File.open("./input/day_four.txt", "r") do |f|
    
    f.each_line do |line|
        card_worth= solve line
    end
end

answer = $apperances.values.sum
puts "The answer is [[  #{answer} ]] "
