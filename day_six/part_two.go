package main

import (
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

type Race struct{
	RecordDistance int
	RaceLength	   int 
}

func readFileInput() (string, error){
	file_data, err := os.ReadFile("../input/day_six_edited.txt")
	if err != nil {
		return "", err
	}
	return string(file_data), nil
}

func ParseRaces() []Race{
	file, _ := readFileInput()
	rows := strings.Split(file, "\n");
	times := strings.Split(rows[0][strings.Index(rows[0], ":") +1:], " ");
	records := strings.Split(rows[1][strings.Index(rows[1], ":") + 1:], " ");

	filtered_times := []int{};
	filtered_records := []int{};

	for _, v := range times {
		if v == ""{
			continue;
		}
		val, err := strconv.Atoi(v)
		if err != nil{
			continue
		}
		filtered_times = append(filtered_times, val);
	}

	for _, v := range records {
		if v == ""{
			continue;
		}
		val, err := strconv.Atoi(v)
		if err != nil{
			continue
		}
		filtered_records = append(filtered_records, val);
	}

	res := []Race{}
	
	for i := 0; i < len(filtered_records); i++{
		res = append(res, Race{
			RecordDistance: filtered_records[i], 
			RaceLength: filtered_times[i]})
	}
	return res;
}

func CalculateMovedDistanceFromButtonHold(timeHold, timeRemaining int) int {
	return timeHold * timeRemaining
}

func CalculateBetterOutcomes(race Race) int {

	var res int = 0

	for i := 0; i < race.RaceLength; i++{
		outcome := CalculateMovedDistanceFromButtonHold(i,int(math.Abs( float64(i - race.RaceLength) )) )
		if outcome > race.RecordDistance{
			res++
		}
	}
	return res
}

func main(){
	result := 1;
	for _, r := range ParseRaces() {
		y := CalculateBetterOutcomes(r)
		result *= y;
	}
	fmt.Printf("The answer is [[ %d ]]\n", result);
}