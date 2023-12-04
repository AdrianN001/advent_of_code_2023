

def parse_numbers(input_string)
    input_string.split(" ", -1).map { |n|
        n.to_i
    }
end


def solve(line) 
    card_number_string = line[ line.index(" ")..line.index(":") -1]
    winning_numbers_string = line[ line.index(":")+2..line.index("|")-2]
    played_numbers_string = line[line.index("|")+2..]


    card_number = card_number_string.to_i
    winning_numbers = parse_numbers winning_numbers_string
    played_numbers = parse_numbers played_numbers_string 


    matched_numbers = winning_numbers & played_numbers

    matches = matched_numbers.length()
    return matches == 0 ? 0 : 2 ** (matches - 1)
end

def main 
    sum = 0

    File.open("./input/day_four.txt", "r") do |f|
        f.each_line do |line|
          card_worth= solve line
          sum += card_worth
        end
      end

    puts "The answer is [[ #{sum} ]]"

end


main
