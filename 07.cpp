#include "ParserHelper.h"
#include <fmt/core.h>
#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>
#include <utility>
#include <variant>


enum Card {JOKER,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,T,J,Q,K,A};
enum Hand_Type {HC,OP,TP,ThreeOK,FH,FourOK,FiveOK};

class Hand {
    [[nodiscard]] Hand_Type get_hand_type() const{
        std::map<char, int> myMap;
        for (const auto &value : cards) {
            myMap[value]++;
        }

        std::size_t j = 0;
        if (auto it = myMap.find(JOKER);it != myMap.end()) {
            j=it->second;
        }

        if(j>0){
            myMap.erase(JOKER);

            std::vector<std::pair<char, int>> myVector(myMap.begin(), myMap.end());

            if (myVector.size() == 1 || myVector.empty())
                return FiveOK;
            for(auto [c,i]:myVector){
                if(j+i==4||j==4)
                    return FourOK;
            }
            if (j==1&&myVector.size()==2&&(myVector[0].second == 2 && myVector[1].second == 2))
                return FH;
            for(auto [c,i]:myVector){
                if(j+i==3||j==3)
                    return ThreeOK;
            }
            return OP;
        }else {

            std::vector<std::pair<char, int>> myVector(myMap.begin(), myMap.end());

            if (myVector.size() == 1)
                return FiveOK;
            if (myVector.size() == 2 && (myVector[0].second == 4 || myVector[1].second == 4))
                return FourOK;
            if (myVector.size() == 2 && ((myVector[0].second == 3 && myVector[1].second == 2) || (myVector[0].second == 2 && myVector[1].second == 3)))
                return FH;
            if (myVector.size() == 3 && (myVector[0].second == 3 || myVector[1].second == 3 || myVector[2].second == 3))
                return ThreeOK;
            if (myVector.size() == 3)
                return TP;
            if (myVector.size() == 4)
                return OP;
        }
        return HC;
    }


public:
    u_int64_t bid;
    std::vector<Card> cards;

    Hand(u_int64_t bid, const std::vector<Card> &cards) : bid(bid), cards(cards) {}
    auto operator<(const Hand& other) const {
        auto a = get_hand_type();
        auto b = other.get_hand_type();

        if(a==b){
            for(std::size_t i = 0;i<cards.size();i++){
                if(cards[i]==other.cards[i]){
                    continue;
                }
                return cards[i]<other.cards[i];
            }
            //They are equal
            return false;
        }
        return a<b;
    }

};


Hand parse_hand(const std::string &s,bool with_joker=false){
    auto line = ParserHelper::parseStrsFromString(s, " ");
    std::vector<Card> cards;
    u_int64_t bid = std::stol(line[1]);
    std::unordered_map<char, Card> c2c{ {'2', TWO}, {'3', THREE}, {'4', FOUR}, {'5', FIVE}, {'6', SIX}, {'7', SEVEN}, {'8', EIGHT}, {'9', NINE},
                                       {'T', T}, {'Q', Q}, {'K', K}, {'A', A} };
    if(with_joker)
        c2c['J'] = JOKER;
    else
        c2c['J'] = J;

    for (char i : line[0])
        cards.push_back(c2c[i]);

    return {bid,cards};
}

u_int64_t second_solution(const std::vector<std::string> &strings) {
    std::vector<Hand> hands = ranges::views::transform(strings, [](auto s){return parse_hand(s,true);}) | ranges::to_vector;

    ranges::sort(hands,[](auto a,auto b){return a<b;});

    return ranges::fold_left(ranges::views::zip(ranges::views::iota(1),hands),0L,[](long acc,auto b){
        auto [rank,hand] = b;
        return acc+(rank*hand.bid);});
}

u_int64_t first_solution(const std::vector<std::string> &strings) {
    std::vector<Hand> hands = ranges::views::transform(strings, [](auto s){return parse_hand(s);}) | ranges::to_vector;

    ranges::sort(hands,[](auto a,auto b){return a<b;});

    return ranges::fold_left(ranges::views::zip(ranges::views::iota(1),hands),0L,[](long acc,auto b){
        auto [rank,hand] = b;
        return acc+(rank*hand.bid);});
}

int main() {
    auto strings = ParserHelper::readLinesFromFile("../Input/07.txt");

    fmt::print("Solution 1: {}\n", first_solution(strings));
    fmt::print("Solution 2: {}\n", second_solution(strings));

    return 0;
}
