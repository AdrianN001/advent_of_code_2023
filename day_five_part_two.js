const fs = require("fs");
const { isString, isNumber } = require("util");
const input_file_content = fs.readFileSync("./input/day_five_template.txt").toString().split("\n").filter(e => e !== "");


const range = (start, stop, step = 1) =>  Array.from({ length: (stop - start) / step + 1}, (_, i) => start + (i * step))

const groupArr = (data, n) =>{
    var group = [];
    for (var i = 0, j = 0; i < data.length; i++) {
        if (i >= n && i % n === 0)
            j++;
        group[j] = group[j] || [];
        group[j].push(data[i])
    }
    return group;
}

// 
//       !!NOT YET SOLVED!! 
//

const extract_seeds = (line) => {
    const starting_point = line.indexOf(":");
    const numbers_in_stirng = line.substring(starting_point + 1);
    const numbers = numbers_in_stirng.split(" ").map(e => {
        return parseInt(e);
    }).filter(e => !isNaN(e));
    const grouped_numbers = groupArr(numbers, 2);
    const ranges = grouped_numbers.map( e => range(e[0], e[1]));
    console.log(ranges)
    return [1,2];
}

const generate_range = (destination_range_start, source_range_start, range_length) => {
    return (seed_number) => {
        // It is in range
        if ( seed_number < (source_range_start + range_length) && seed_number >= source_range_start ){
            return (destination_range_start + (seed_number - source_range_start));
        }else{
            return seed_number;
        }
    } 

}
const seeds = extract_seeds(input_file_content[0]);
const isDigit = e => e <= '9' && e >= 0;

const generate_almanac_object = (file_content) => { 
    let almanac = {};
    let current_section = "";
    file_content.forEach(element => {
        if (isDigit( element[0])) {
            const [dest_rng_start, src_range_start, rng_len] = element.split(" ").map( e => parseInt(e));
            const generator = generate_range(dest_rng_start, src_range_start, rng_len);
            almanac[current_section].push(generator);
        }else if (isString(element)){
            current_section = element;
            almanac[current_section] = [];
        }
    });
    return almanac;
} 
const almanac = generate_almanac_object(input_file_content.slice(1))

const plant_the_seed = (seed, almanac) => {
    for (const prop in almanac){
        const generators = almanac[prop]
        generators.every(generator =>  {
            const new_seed = generator(seed);
            if (seed != new_seed){
                seed = new_seed;
                return false;
            }
            return true;
        })
    }
    return seed;
}

(function main() {
    const locations = seeds.map( e => {
       return plant_the_seed(e,almanac);
    })
    const min = Math.min(...locations);
    console.log(` The answer is [[ ${min} ]]`)
}())
