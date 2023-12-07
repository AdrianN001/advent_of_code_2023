import * as fs from "fs";


enum HandValue{

    NotSure,
    High_Card,
    One_Pair,
    Two_Pair,
    Three_Of_A_Kind,
    Full_House,
    Four_Of_A_Kind,
    Five_Of_A_Kind
}

const cardValues = ['A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'];

class Hand{
    public hand: string[];
    public bid: number;
    constructor(string_repr: string, bid: number){
        this.hand = string_repr.split("");
        this.bid = bid;
    }
    public value() {
        const occurrences = this.hand.reduce(function (acc: any, curr: any):any {
            return acc[curr] ? ++acc[curr] : acc[curr] = 1, acc
        }, {});
        let possibilities: HandValue[] = [];
        let sureHandValue: HandValue = HandValue.NotSure;
        const sortedList = Object.keys(occurrences).sort((a,b) => occurrences[b] - occurrences[a]).forEach( e => {
            switch (occurrences[e]){
                case 5:
                    sureHandValue = HandValue.Five_Of_A_Kind;
                    return;
                case 4:
                    sureHandValue = HandValue.Four_Of_A_Kind;
                    return;
                case 3:
                    possibilities.push(HandValue.Three_Of_A_Kind);
                    possibilities.push(HandValue.Full_House);
                case 2:
                    if (possibilities.includes(HandValue.Full_House)){
                        possibilities = possibilities.filter(e => e != HandValue.Full_House);
                        sureHandValue = HandValue.Full_House;
                        return;
                    }
                    possibilities.push(HandValue.Two_Pair);
                    possibilities.push(HandValue.One_Pair);
                case 1:
                    sureHandValue = HandValue.High_Card;
                    return;
            }
        });
        if (possibilities.length == 1){
            sureHandValue = possibilities[0];
        }else{
            let found_two_pair = false;
            possibilities.forEach( e => {
                switch (e){
                    case HandValue.Two_Pair:
                        if (possibilities.filter( e => e == HandValue.One_Pair).length == 2){
                            sureHandValue = HandValue.Two_Pair;
                            found_two_pair = true;
                        }
                }
            })
            if (!found_two_pair){
                sureHandValue = HandValue.One_Pair;
            }
        }

        return sureHandValue;
    }
}

function main(){
    const input = fs.readFileSync("./input/day_seven.txt");
    const input_as_string: string = input.toString();
    const hands: Hand[] = input_as_string.split("\n").map(line => {
        const [hand, bid] = line.split(" ");
        const newHand = new Hand(hand, parseInt(bid));
        return newHand;
    })
    hands.sort( (a: Hand, b: Hand): number => {

        const handValueDiff = a.value() - b.value();
        if (handValueDiff != 0){
            return handValueDiff;
        }
        for (let i = 0; i < 5; i++){

            const a_Hand = a.hand[i];
            const b_Hand = b.hand[i];

            if (a_Hand != b_Hand){
                return cardValues.indexOf(b_Hand) - cardValues.indexOf(a_Hand);
            }
        }

        return 0;
    })
    const value = hands.map( (hand: Hand, index: number) => hand.bid * (index + 1));
    

    const answer = value.reduce((total, value) => total + value);
    
    console.log(answer);
}


main();