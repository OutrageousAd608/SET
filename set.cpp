// This file includes all functions that are used, I didn't comment all the functions 
// so if there's any questions just hit me up on linkedin @ www.linkedin.com/in/richarddong2005 and I can explain.

#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include "set.h"
#include "random.h"
using namespace Random;

bool duplicate{};
int guess1{};
int guess2{};
int guess3{};

int main();
void boardPrinter(cardHead* cardStarter);
void change3(cardHead* cardStarter, std::vector<Card*>& remainingDeck, int& remainingCards, int index1, int index2, int index3, bool replace, bool add3, bool arrange);
cardHead* choose12(std::vector<Card*>& remainingDeck, int& remainingCards);
cardHead* dozenGenerator();
void erase(std::vector<Card*>& remainingDeck, int remainingCards, int index);
std::vector<Card*> fullGameGen();
void fullGameRunner();
void setCardNo(cardHead* cardStarter);
bool setDeterminer(Card* card1, Card* card2, Card* card3);
int* setFinder(cardHead* cardStarter);
void setPractice();
void setRevealer(int* trios);
bool setUserInput(int* trios);

int main(){
std::cout 
<< "WELCOME TO SET!!!" << std::endl
<< "Set is a mind numbing game that involves the major league gamer playing to" << std::endl
<< "find a set given a dozen of different cards." << std::endl << std::endl

<< "The rules are simple, find a set as quickly as you can." << std::endl << std::endl

<< "What is a set?" << std::endl
<< "A set contains 3 distinct cards. Cards are differentiated through" << std::endl
<< "4 characteristics." << std::endl
<< "1. The number of shapes on a card" << std::endl
<< "2. The color of the shape(s) on a card" << std::endl
<< "3. The shading of the shape(s) on a card" << std::endl
<< "4. The shape of the shape(s) on a card" << std::endl
<< "For a set of 3 cards to actually constitute being a set, the 3 cards must" << std::endl
<< "share the same value for the characteristic in question or all have different" << std::endl
<< "values for the characteristic in question." << std::endl << std::endl

<< "Sounds simple?" << std::endl
<< "Good!" << std::endl
<< "Let's get started..." << std::endl << std::endl;

    char game{};
    while(1){
        std::cout << "What would you like to do, practice or play a full game? (p/g) ";
        std::cin >> game;
        switch(game){
            case('p'): setPractice();
                break;
            case('g'): fullGameRunner();
                break;
            default: std::cout << "What you entered was not one of the two options, please try again." << std::endl << std::endl;
        }
    }
    return 0;
}

void boardPrinter(cardHead* cardStarter){
    Card* cardIterator{cardStarter->getFirst()};
    Card* firstCard;
    Card* secondCard;
    Card* thirdCard;
    int spaceFromBorder{};
    int spaceBetween{};
    int row{};
    int shapes{};
    int iterator{};
    int shapeIterator{};

    std::string_view roofGround{"__________________"};
    std::string filling{""};

    while(cardIterator){
        firstCard = cardIterator;
        secondCard = cardIterator->getNext();
        thirdCard = cardIterator->getNext()->getNext();
        row = 1;
        printf("\x1b[37m");
        if(firstCard->getCardNo() == 10 || firstCard->getCardNo() == 13){
            std::cout << "        " << firstCard->getCardNo() << "                  " << secondCard->getCardNo() << "                  " << thirdCard->getCardNo() << std::endl;
        }else{
            std::cout << "        " << firstCard->getCardNo() << "                   " << secondCard->getCardNo() << "                   " << thirdCard->getCardNo() << std::endl;
        }
        std::cout << roofGround << "  " << roofGround << "  " << roofGround << std::endl;
        while(row < 5){
            printf("\x1b[37m");
            std::cout << "|";
            if(firstCard->getShapeCount() == 1){
                spaceFromBorder = 6;
                spaceBetween = 0;
                shapes = 1;
            }else{
                if(firstCard->getShapeCount() == 2){
                    spaceFromBorder = 3;
                    spaceBetween = 2;
                    shapes = 2;
                }else{
                    spaceFromBorder = 1;
                    spaceBetween = 1;
                    shapes = 3;
                }
            }
            iterator = 0;
            while(iterator < spaceFromBorder){
                std::cout << " ";
                ++iterator;
            }
            switch(firstCard->getColor()){
                case(Card::Color::blue): printf("\x1b[34m");
                    break;
                case(Card::Color::green): printf("\x1b[32m");
                    break;
                case(Card::Color::red): printf("\x1b[31m");
                    break;
            }
            shapeIterator = 0;
            while(shapeIterator < shapes){
                if(row == 1){
                    if(firstCard->getShape() == Card::Shape::oval){
                        std::cout << " __ ";
                    }
                    if(firstCard->getShape() == Card::Shape::diamond){
                        std::cout << " /\\ ";
                    }
                    if(firstCard->getShape() == Card::Shape::squiggle){
                        std::cout << "___ ";
                    }
                }
                if(row == 2){
                    switch(firstCard->getShading()){
                        case(Card::Shading::open): filling = "  ";
                            break;
                        case(Card::Shading::solid): filling = "@@";
                            break;
                        case(Card::Shading::striped): filling = "^^";
                            break;
                    }
                    if(firstCard->getShape() == Card::Shape::oval){
                        std::cout << "(" << filling << ")";
                    }
                    if(firstCard->getShape() == Card::Shape::diamond){
                        std::cout << "/" << filling << "\\";
                    }
                    if(firstCard->getShape() == Card::Shape::squiggle){
                        std::cout << "\\" << filling << "\\";
                    }
                }
                if(row == 3){
                    switch(firstCard->getShading()){
                        case(Card::Shading::open): filling = "  ";
                            break;
                        case(Card::Shading::solid): filling = "@@";
                            break;
                        case(Card::Shading::striped): filling = "^^";
                            break;
                    }
                    if(firstCard->getShape() == Card::Shape::oval){
                        std::cout << "(" << filling << ")";
                    }
                    if(firstCard->getShape() == Card::Shape::diamond){
                        std::cout << "\\" << filling << "/";
                    }
                    if(firstCard->getShape() == Card::Shape::squiggle){
                        std::cout << "/" << filling << "/";
                    }
                }
                if(row == 4){
                    if(firstCard->getShape() == Card::Shape::oval){
                        std::cout << "`--'";
                    }
                    if(firstCard->getShape() == Card::Shape::diamond){
                        std::cout << " \\/ ";
                    }
                    if(firstCard->getShape() == Card::Shape::squiggle){
                        std::cout << "\\__\\";
                    }
                }
                if(shapeIterator != shapes - 1){
                    iterator = 0;
                    while(iterator < spaceBetween){
                        std::cout << " ";
                        ++iterator;
                    }
                }
                ++shapeIterator;
            }
            iterator = 0;
            while(iterator < spaceFromBorder){
                std::cout << " ";
                ++iterator;
            }
            printf("\x1b[37m");
            std::cout << "|" << "  ";

//_________________________________________________________
            printf("\x1b[37m");
            std::cout << "|";
            if(secondCard->getShapeCount() == 1){
                spaceFromBorder = 6;
                spaceBetween = 0;
                shapes = 1;
            }else{
                if(secondCard->getShapeCount() == 2){
                    spaceFromBorder = 3;
                    spaceBetween = 2;
                    shapes = 2;
                }else{
                    spaceFromBorder = 1;
                    spaceBetween = 1;
                    shapes = 3;
                }
            }
            iterator = 0;
            while(iterator < spaceFromBorder){
                std::cout << " ";
                ++iterator;
            }
            switch(secondCard->getColor()){
                case(Card::Color::blue): printf("\x1b[34m");
                    break;
                case(Card::Color::green): printf("\x1b[32m");
                    break;
                case(Card::Color::red): printf("\x1b[31m");
                    break;
            }
            shapeIterator = 0;
            while(shapeIterator < shapes){
                if(row == 1){
                    if(secondCard->getShape() == Card::Shape::oval){
                        std::cout << " __ ";
                    }
                    if(secondCard->getShape() == Card::Shape::diamond){
                        std::cout << " /\\ ";
                    }
                    if(secondCard->getShape() == Card::Shape::squiggle){
                        std::cout << "___ ";
                    }
                }
                if(row == 2){
                    switch(secondCard->getShading()){
                        case(Card::Shading::open): filling = "  ";
                            break;
                        case(Card::Shading::solid): filling = "@@";
                            break;
                        case(Card::Shading::striped): filling = "^^";
                            break;
                    }
                    if(secondCard->getShape() == Card::Shape::oval){
                        std::cout << "(" << filling << ")";
                    }
                    if(secondCard->getShape() == Card::Shape::diamond){
                        std::cout << "/" << filling << "\\";
                    }
                    if(secondCard->getShape() == Card::Shape::squiggle){
                        std::cout << "\\" << filling << "\\";
                    }
                }
                if(row == 3){
                    switch(secondCard->getShading()){
                        case(Card::Shading::open): filling = "  ";
                            break;
                        case(Card::Shading::solid): filling = "@@";
                            break;
                        case(Card::Shading::striped): filling = "^^";
                            break;
                    }
                    if(secondCard->getShape() == Card::Shape::oval){
                        std::cout << "(" << filling << ")";
                    }
                    if(secondCard->getShape() == Card::Shape::diamond){
                        std::cout << "\\" << filling << "/";
                    }
                    if(secondCard->getShape() == Card::Shape::squiggle){
                        std::cout << "/" << filling << "/";
                    }
                }
                if(row == 4){
                    if(secondCard->getShape() == Card::Shape::oval){
                        std::cout << "`--'";
                    }
                    if(secondCard->getShape() == Card::Shape::diamond){
                        std::cout << " \\/ ";
                    }
                    if(secondCard->getShape() == Card::Shape::squiggle){
                        std::cout << "\\__\\";
                    }
                }
                if(shapeIterator != shapes - 1){
                    iterator = 0;
                    while(iterator < spaceBetween){
                        std::cout << " ";
                        ++iterator;
                    }
                }
                ++shapeIterator;
            }
            iterator = 0;
            while(iterator < spaceFromBorder){
                std::cout << " ";
                ++iterator;
            }
            printf("\x1b[37m");
            std::cout << "|" << "  ";
//_________________________________________________________

            printf("\x1b[37m");
            std::cout << "|";
            if(thirdCard->getShapeCount() == 1){
                spaceFromBorder = 6;
                spaceBetween = 0;
                shapes = 1;
            }else{
                if(thirdCard->getShapeCount() == 2){
                    spaceFromBorder = 3;
                    spaceBetween = 2;
                    shapes = 2;
                }else{
                    spaceFromBorder = 1;
                    spaceBetween = 1;
                    shapes = 3;
                }
            }
            iterator = 0;
            while(iterator < spaceFromBorder){
                std::cout << " ";
                ++iterator;
            }
            switch(thirdCard->getColor()){
                case(Card::Color::blue): printf("\x1b[34m");
                    break;
                case(Card::Color::green): printf("\x1b[32m");
                    break;
                case(Card::Color::red): printf("\x1b[31m");
                    break;
            }
            shapeIterator = 0;
            while(shapeIterator < shapes){
                if(row == 1){
                    if(thirdCard->getShape() == Card::Shape::oval){
                        std::cout << " __ ";
                    }
                    if(thirdCard->getShape() == Card::Shape::diamond){
                        std::cout << " /\\ ";
                    }
                    if(thirdCard->getShape() == Card::Shape::squiggle){
                        std::cout << "___ ";
                    }
                }
                if(row == 2){
                    switch(thirdCard->getShading()){
                        case(Card::Shading::open): filling = "  ";
                            break;
                        case(Card::Shading::solid): filling = "@@";
                            break;
                        case(Card::Shading::striped): filling = "^^";
                            break;
                    }
                    if(thirdCard->getShape() == Card::Shape::oval){
                        std::cout << "(" << filling << ")";
                    }
                    if(thirdCard->getShape() == Card::Shape::diamond){
                        std::cout << "/" << filling << "\\";
                    }
                    if(thirdCard->getShape() == Card::Shape::squiggle){
                        std::cout << "\\" << filling << "\\";
                    }
                }
                if(row == 3){
                    switch(thirdCard->getShading()){
                        case(Card::Shading::open): filling = "  ";
                            break;
                        case(Card::Shading::solid): filling = "@@";
                            break;
                        case(Card::Shading::striped): filling = "^^";
                            break;
                    }
                    if(thirdCard->getShape() == Card::Shape::oval){
                        std::cout << "(" << filling << ")";
                    }
                    if(thirdCard->getShape() == Card::Shape::diamond){
                        std::cout << "\\" << filling << "/";
                    }
                    if(thirdCard->getShape() == Card::Shape::squiggle){
                        std::cout << "/" << filling << "/";
                    }
                }
                if(row == 4){
                    if(thirdCard->getShape() == Card::Shape::oval){
                        std::cout << "`--'";
                    }
                    if(thirdCard->getShape() == Card::Shape::diamond){
                        std::cout << " \\/ ";
                    }
                    if(thirdCard->getShape() == Card::Shape::squiggle){
                        std::cout << "\\__\\";
                    }
                }
                if(shapeIterator != shapes - 1){
                    iterator = 0;
                    while(iterator < spaceBetween){
                        std::cout << " ";
                        ++iterator;
                    }
                }
                ++shapeIterator;
            }
            iterator = 0;
            while(iterator < spaceFromBorder){
                std::cout << " ";
                ++iterator;
            }
            printf("\x1b[37m");
            std::cout << "|" << std::endl;
            ++row;
        }
        std::cout << roofGround << "  " << roofGround << "  " << roofGround << std::endl << std::endl << std::endl;
        cardIterator = thirdCard->getNext();
    }
}

void change3(cardHead* cardStarter, std::vector<Card*>& remainingDeck, int& remainingCards, int index1, int index2, int index3, bool replace, bool add3, bool arrange){
    int temp1 = index1;
    int temp2 = index2;
    int temp3 = index3;
    if(temp1 < temp2 && temp1 < temp3){
        index1 = temp1;
        if(temp2 < temp3){
            index2 = temp2;
            index3 = temp3;
        }else{
            index2 = temp3;
            index3 = temp2;
        }
    }
    if(temp2 < temp1 && temp2 < temp3){
        index1 = temp2;
        if(temp1 < temp3){
            index2 = temp1;
            index3 = temp3;
        }else{
            index2 = temp3;
            index3 = temp1;
        }
    }
    if(temp3 < temp1 && temp3 < temp2){
        index1 = temp3;
        if(temp1 < temp2){
            index2 = temp1;
            index3 = temp2;
        }else{
            index2 = temp2;
            index3 = temp1;
        }
    }
    if(replace){
        if(remainingCards > 0){
            Card* cardIterator{cardStarter->getFirst()};
            Card* before(nullptr);
            Card* after(nullptr);
            int index{index1};
            int random{};
            while(cardIterator != nullptr){
                random = get(0, remainingCards - 1);
                after = cardIterator->getNext();
                if(cardIterator->getCardNo() == 1){
                    if(cardIterator->getCardNo() == index){
                        cardIterator->setNext(nullptr);
                        delete cardIterator;
                        cardStarter->setFirst(remainingDeck[random]);
                        cardStarter->getFirst()->setCardNo(index);
                        erase(remainingDeck, remainingCards, random);
                        --remainingCards;
                        cardStarter->getFirst()->setNext(after);
                        cardIterator = after;
                        before = cardStarter->getFirst();
                        ++index;
                    }else{
                        before = cardIterator;
                        cardIterator = cardIterator->getNext();
                    }
                }else{
                    if(cardIterator->getCardNo() == index){
                        cardIterator->setNext(nullptr);
                        delete cardIterator;
                        before->setNext(remainingDeck[random]);
                        erase(remainingDeck, remainingCards, random);
                        --remainingCards;
                        before->getNext()->setCardNo(index);
                        before->getNext()->setNext(after);
                        cardIterator = before->getNext();
                        ++index;
                    }
                    before = cardIterator;
                    cardIterator = cardIterator->getNext();
                }
                if(index == index1 + 1){
                    index = index2;
                }
                if(index == index2 + 1){
                    index = index3;
                }
                if(index == index3 + 1){
                    break;
                }
            }
        }else{
            
        }
    }

    if(add3){
        Card* cardIterator{cardStarter->getFirst()};
        while(cardIterator->getNext() != nullptr){
            cardIterator = cardIterator->getNext();
        }
        int three{};
        int random{};
        three = 0;
        while(three < 3){
            random = get(0, remainingCards - 1);
            cardIterator->setNext(remainingDeck[random]);
            erase(remainingDeck, remainingCards, random);
            --remainingCards;
            cardIterator = cardIterator->getNext();
            ++three;
        }
        setCardNo(cardStarter);
    }

//this one deletes three cards from the current card board depending on what the user guessed as a set
//should be called if there were originally 15 cards on the board or there are no more cards reamining.

    if(arrange){
        Card* cardIterator{cardStarter->getFirst()};
        Card* before(nullptr);
        Card* after(nullptr);
        int index{index1};
        while(cardIterator != nullptr){
            after = cardIterator->getNext();
            if(cardIterator->getCardNo() == 1){
                if(cardIterator->getCardNo() == index){
                    cardIterator->setNext(nullptr);
                    delete cardIterator;
                    cardStarter->setFirst(after);
                    cardIterator = after->getNext();
                    before = cardStarter->getFirst();
                    ++index;
                }else{
                    before = cardIterator;
                    cardIterator = cardIterator->getNext();
                }
            }else{
                if(cardIterator->getCardNo() == index){
                    cardIterator->setNext(nullptr);
                    delete cardIterator;
                    before->setNext(after);
                    cardIterator = before;
                    ++index;
                }
                before = cardIterator;
                cardIterator = cardIterator->getNext();
            }
            if(index == index1 + 1){
                index = index2;
            }
            if(index == index2 + 1){
                index = index3;
            }
            if(index == index3 + 1){
                break;
            }
        }
        setCardNo(cardStarter);
    }
}

cardHead* choose12(std::vector<Card*>& remainingDeck, int& remainingCards){
    cardHead* cardStarter{new cardHead(nullptr)};
    int random{get(0, remainingCards - 1)};
    cardStarter->setFirst(remainingDeck[random]);
    erase(remainingDeck, remainingCards, random);
    --remainingCards;

    Card* cardIterator{cardStarter->getFirst()};

    int iterator{2};
    while(iterator < 13){
        random = get(0, remainingCards - 1);
        cardIterator->setNext(remainingDeck[random]);
        erase(remainingDeck, remainingCards, random);
        --remainingCards;
        cardIterator = cardIterator->getNext();
        ++iterator;
    }
    setCardNo(cardStarter);

    return cardStarter;
}

cardHead* dozenGenerator(){
    
    cardHead* cardStarter{new cardHead(nullptr)};
    cardStarter->setFirst(new Card(1, get(1, 3), (Card::Color)get(0, 2), (Card::Shading)get(0, 2), (Card::Shape)get(0, 2), nullptr));
    Card* cardIterator{cardStarter->getFirst()};

    int iterator{2};
    while(iterator < 13){
        cardIterator->setNext(new Card(iterator, get(1, 3), (Card::Color)get(0, 2), (Card::Shading)get(0, 2), (Card::Shape)get(0, 2), nullptr));
        Card* duplicateIterator{cardStarter->getFirst()};
        bool duplicate{0};
        while(duplicateIterator != nullptr){
            if((cardIterator->getNext()->getShapeCount() == duplicateIterator->getShapeCount()) && (cardIterator->getNext()->getColor() == duplicateIterator->getColor()) && (cardIterator->getNext()->getShading() == duplicateIterator->getShading()) && (cardIterator->getNext()->getShape() == duplicateIterator->getShape()) && (cardIterator->getNext()->getCardNo() != duplicateIterator->getCardNo())){
                delete cardIterator->getNext();
                cardIterator->setNext(nullptr);
                duplicate = 1;
                break;
            }
            duplicateIterator = duplicateIterator->getNext();
        }
        if(!duplicate){
            cardIterator = cardIterator->getNext();
            ++iterator;
        }
    }
    return cardStarter;
}

void erase(std::vector<Card*>& remainingDeck, int remainingCards, int index){
    while(index < remainingCards - 1){
        remainingDeck[index] = remainingDeck[index + 1];
        ++index;
    }
    remainingDeck.pop_back();
}

std::vector<Card*> fullGameGen(){
    std::vector<Card*> cards(81);
    int cardNo{1};
    int shapeCount{1};
    int color{};
    int shading{};
    int shape{};
    while(shapeCount < 4){
        color = 0;
        while(color < 3){
            shading = 0;
            while(shading < 3){
                shape = 0;
                while(shape < 3){
                    cards[cardNo - 1] = new Card((int)cardNo, (int)shapeCount, (Card::Color)color, (Card::Shading)shading, (Card::Shape)shape, nullptr);
                    ++cardNo;
                    ++shape;
                }
                ++shading;
            }
            ++color;
        }
        ++shapeCount;
    }
    return cards;
}

void fullGameRunner(){
    std::cout << std::endl;
    std::vector<Card*> remainingDeck{fullGameGen()};
    int remainingCards{81};
    cardHead* cardStarter{choose12(remainingDeck, remainingCards)};
    Card* cardIterator{nullptr};
    int* trios{nullptr};
    int totalTrios{};
    int currentBoard{12};
    std::string choice{""};
    while(totalTrios > 0 || remainingCards > 0){
        cardIterator = cardStarter->getFirst();
        currentBoard = 0;
        while(cardIterator != nullptr){
            ++currentBoard;
            cardIterator = cardIterator->getNext();
        }
        trios = setFinder(cardStarter);
        totalTrios = trios[0];
        if(totalTrios == 0 && remainingCards == 0){
            std::cout << "You have found all the sets!" << std::endl;
            std::cout << "Nice job gamer, GGS." << std::endl << std::endl;
            break;
        }
        boardPrinter(cardStarter);
        std::cout << "There are " << remainingCards << " cards left in the deck aside from the " << currentBoard << " cards that are on the board" << std::endl;
        std::cout << "Would you like to make a guess or add 3 cards to the board? (G/A) ";
        std::cin >> choice;
        std::cout << std::endl;
        if(choice == "G" || choice == "g"){
            if(setUserInput(trios)){
                std::cout << std::endl;
                std::cout << "Nice! You have found a set" << std::endl << std::endl;
                if(currentBoard == 15){
                    std::cout << "Changing the board back to 12 cards. Perfectly balanced as all things should be." << std::endl;
                    std::cout << std::endl;
                    change3(cardStarter, remainingDeck, remainingCards, guess1, guess2, guess3, 0, 0, 1);
                }else{
                    if(currentBoard == 12 && remainingCards){
                        change3(cardStarter, remainingDeck, remainingCards, guess1, guess2, guess3, 1, 0, 0);
                    }else{
                        change3(cardStarter, remainingDeck, remainingCards, guess1, guess2, guess3, 0, 0, 1);
                    }
                }
            }else{
                std::cout << std::endl;
                std::cout << "Sorry, what you entered was not a set." << std::endl << std::endl;
            }
        }else{
            if(choice == "A" || choice == "a"){
                if(currentBoard < 15){
                    if(remainingCards > 0){
                        std::cout << "Ok, adding 3 new cards to the board." << std::endl;
                        std::cout << std::endl;
                        change3(cardStarter, remainingDeck, remainingCards, 0, 0, 0, 0, 1, 0);
                    }else{
                        std::cout << "Sorry, you do not have enough cards." << std::endl;
                        std::cout << std::endl;
                    }
                }else{
                    std::cout << "Sorry, there's already 15 cards on the board. You can't add anymore." << std::endl;
                    std::cout << std::endl;
                }
            }else{
                std::cout << "What you entered was not one of the 2 choices." << std::endl;
                std::cout << std::endl;
            }
        }
    }
}

void setCardNo(cardHead* cardStarter){
    Card* cardIterator{cardStarter->getFirst()};
    int cardNo{1};
    while(cardIterator){
        cardIterator->setCardNo(cardNo);
        cardIterator = cardIterator->getNext();
        ++cardNo;
    }
}

bool setDeterminer(Card* card1, Card* card2, Card* card3){
    //First check if the passed trio contains a duplicate
    //if it does then we immediately return false as that does not follow the rules.
    if((card1->getCardNo() == card2->getCardNo()) || (card2->getCardNo() == card3->getCardNo()) || (card3->getCardNo() == card1->getCardNo()))
        return 0;

    if(((card1->getShapeCount() == card2->getShapeCount()) && (card2->getShapeCount() == card3->getShapeCount()) && (card3->getShapeCount() == card1->getShapeCount()))
    || ((card1->getShapeCount() != card2->getShapeCount()) && (card2->getShapeCount() != card3->getShapeCount()) && (card3->getShapeCount() != card1->getShapeCount()))){
        if((((int)card1->getColor() == (int)card2->getColor()) && ((int)card2->getColor() == (int)card3->getColor()) && ((int)card3->getColor() == (int)card1->getColor()))
        || (((int)card1->getColor() != (int)card2->getColor()) && ((int)card2->getColor() != (int)card3->getColor()) && ((int)card3->getColor() != (int)card1->getColor()))){
            if((((int)card1->getShading() == (int)card2->getShading()) && ((int)card2->getShading() == (int)card3->getShading()) && ((int)card3->getShading() == (int)card1->getShading()))
            || (((int)card1->getShading() != (int)card2->getShading()) && ((int)card2->getShading() != (int)card3->getShading()) && ((int)card3->getShading() != (int)card1->getShading()))){
                if((((int)card1->getShape() == (int)card2->getShape()) && ((int)card2->getShape() == (int)card3->getShape()) && ((int)card3->getShape() == (int)card1->getShape()))
                || (((int)card1->getShape() != (int)card2->getShape()) && ((int)card2->getShape() != (int)card3->getShape()) && ((int)card3->getShape() != (int)card1->getShape()))){
                    return 1;
                }else{
                    return 0;
                }
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

int* setFinder(cardHead* cardStarter){
    //duplicates are taken care of in the setDeterminer function. Update: it's also here lmao.
    Card* iterator1{cardStarter->getFirst()};
    Card* iterator2{cardStarter->getFirst()->getNext()};
    Card* iterator3{cardStarter->getFirst()->getNext()->getNext()};

    int* trios{new int[]{}};
    int trioIterator{0};

    while(iterator1->getNext()->getNext() != nullptr){
        while(iterator2->getNext() != nullptr){
            while(iterator3 != nullptr){
                if((iterator1->getCardNo() != iterator2->getCardNo()) && (iterator2->getCardNo() != iterator3->getCardNo()) && (iterator3->getCardNo() != iterator1->getCardNo()) && setDeterminer(iterator1, iterator2, iterator3)){
                    ++trioIterator;
                    trios[trioIterator] = iterator1->getCardNo();
                    ++trioIterator;
                    trios[trioIterator] = iterator2->getCardNo();
                    ++trioIterator;
                    trios[trioIterator] = iterator3->getCardNo();
                }
                iterator3 = iterator3->getNext();
            }
            iterator2 = iterator2->getNext();
            iterator3 = iterator2->getNext();
        }
        iterator1 = iterator1->getNext();
        iterator2 = iterator1->getNext();
        iterator3 = iterator2->getNext();
    }  
    trios[0] = trioIterator/3;
    return trios;
}

void setPractice(){
    std::cout << std::endl;
    cardHead* cardStarter{dozenGenerator()};
    int* trios{setFinder(cardStarter)};
    int totalTrios{trios[0]};
    int triosFound{};
    std::string reveal{""};
    bool revealNoOfSets{0};
    bool revealSets{0};
    std::string revealAllSets{""};
    while(1){
        if(triosFound == totalTrios){
            std::cout << std::endl << "Nice job gamer, you've found all the sets within this dozen. GGs." << std::endl << std::endl;
            std::cout << "If you want to stop, you can simply enter \"Stop\" now or enter \"Continue\" to keep practicing: ";
            std::cin >> revealAllSets;
            revealAllSets == "Stop" || revealAllSets == "stop" ? revealSets = 1 : revealSets = 0;
            if(revealSets){
                break;
            }else{
                delete cardStarter;
                delete cardStarter->getFirst();
                cardStarter = dozenGenerator();
                trios = setFinder(cardStarter);
                totalTrios = trios[0];
                triosFound = 0;
                reveal = "";
                revealNoOfSets = 0;
                revealSets = 0;
                revealAllSets = "";
            }
        }
        boardPrinter(cardStarter);
        if(!revealNoOfSets){
            std::cout << "Would you like to see how many sets you have to find out of this dozen (Yes/No)? ";
            std::cin >> reveal;
            if(reveal == "Yes" || reveal == "yes"){
                revealNoOfSets = 1;
                if(totalTrios == 1){
                    std::cout << "There is " << totalTrios << " set within this dozen of cards." << std::endl << std::endl;
                }else{
                    std::cout << "There are " << totalTrios << " sets within this dozen of cards." << std::endl << std::endl;
                }
            }else{
                revealNoOfSets = 0;
                std::cout << "Ok buddy, you're choice." << std::endl;
            }
        }
        duplicate = 0;
        if(setUserInput(trios)){
            if(triosFound != totalTrios - 1){
                std::cout << std::endl << "Nice! You have found a set" << std::endl << std::endl;
            }
            ++triosFound;
        }else{
            if(duplicate){
                std::cout << std::endl << "Dude, you already found that set." << std::endl << std::endl;
            }else{
                std::cout << "Sorry, what you entered was not a set. Please try again" << std::endl << std::endl;
            }
        }
        if((triosFound != totalTrios) && revealNoOfSets){
        std::cout << "You still have " << totalTrios - triosFound << " set that needs to be found" << std::endl << std::endl;
        }
    }
    std::cout << std::endl << "This game is just for practice. See you next time!" << std::endl;
}

void setRevealer(int* trios){
    int numberOfElements{trios[0] * 3};
    if (numberOfElements == 0){
        std::cout << std::endl << "No sets within this Dozen." << std::endl;
        return;
    }
    int element{1};
    while(element <= numberOfElements){
        std::cout << "Set #: " << (element/3) + 1 << std::endl;
        std::cout << "(" << trios[element] << ", ";
        ++element;
        std::cout << trios[element] << ", ";
        ++element;
        std::cout << trios[element] << ")" << std::endl << std::endl;
        ++element;
    }
}

bool setUserInput(int* trios){
    bool setFound{0};
    int trioIterator{1};
    int totalTrios{trios[0]};
    int firstCard{};
    int secondCard{};
    int thirdCard{};
    std::cout << "Enter the first card # of your suspected set: ";
    std::cin >> firstCard;
    guess1 = firstCard;
    std::cout << "Enter the second card # of your suspected set: ";
    std::cin >> secondCard;
    guess2 = secondCard;
    std::cout << "Enter the third card # of your suspected set: ";
    std::cin >> thirdCard;
    guess3 = thirdCard;
    if((firstCard == secondCard) || (secondCard == thirdCard) || (thirdCard == firstCard)){
        std::cout << std::endl << "You think you're slick huh?" << std::endl;
        return 0;
    }
    bool firstCardFound{0};
    bool secondCardFound{0};
    bool thirdCardFound{0};
    int x{1};
    while((trioIterator <= totalTrios) && !setFound){
        firstCardFound = 0;
        secondCardFound = 0;
        thirdCardFound = 0;
        if(firstCard == trios[x] || firstCard == trios[x + 1] || firstCard == trios[x + 2]){
            firstCardFound = 1;
        }
        if(secondCard == trios[x] || secondCard == trios[x + 1] || secondCard == trios[x + 2]){
            secondCardFound = 1;
        }
        if(thirdCard == trios[x] || thirdCard == trios[x + 1] || thirdCard == trios[x + 2]){
            thirdCardFound = 1;
        }
        int y{0};
        if((firstCard + 20) == trios[x] || (firstCard + 20) == trios[x + 1] || (firstCard + 20) == trios[x + 2]){
            ++y;
        }
        if((secondCard + 20) == trios[x] || (secondCard + 20) == trios[x + 1] || (secondCard + 20) == trios[x + 2]){
            ++y;
        }
        if((thirdCard + 20) == trios[x] || (thirdCard + 20) == trios[x + 1] || (thirdCard + 20) == trios[x + 2]){
            ++y;
        }
        if(y == 3){
            duplicate = 1;
            return 0;
        }
        if(firstCardFound && secondCardFound && thirdCardFound){
        setFound = 1;
        trios[x] = trios[x] + 20;
        trios[x + 1] = trios[x + 1] + 20;
        trios[x + 2] = trios[x + 2] + 20;
        }
        x += 3;
        ++trioIterator;
    }
    return setFound;
}
