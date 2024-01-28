// This is the file containing the class used for a card
// and the class for the starting Card which in retrospect seems kind of useless 
// except for obtaining a more clear undersatnding of what a functions takes.



#ifndef SET_H
#define SET_H



class Card{

    public:

        enum class Color{
        blue,       //Blue is 0
        green,      //Green is 1
        red,        //Red is 2
        };

        enum class Shading{
        solid,      //Solid is 0
        striped,    //Striped is 1
        open,       //Open is 2
        };

        enum class Shape{
        oval,       //Oval is 0
        squiggle,   //Squigle is 1
        diamond,    //Diamond is 2
        };

        Card(int cardNo1, int shapeCount1, Color color1, Shading shading1, Shape shape1, Card* nextCard1);
        ~Card();
        friend std::ostream& operator<<(std::ostream&, const Color color);
        friend std::ostream& operator<<(std::ostream&, const Shading shading);
        friend std::ostream& operator<<(std::ostream&, const Shape shape);

        int getCardNo(){return this->cardNo;}
        int getShapeCount(){return this->shapeCount;}
        Color getColor(){return this->color;}
        Shading getShading(){return this->shading;}
        Shape getShape(){return this->shape;}
        Card* getNext(){return nextCard;}

        void setCardNo(int newCardNo){this->cardNo = newCardNo;}
        void setNext(Card* Address){this->nextCard = Address;}

    private:

        int cardNo;
        int shapeCount;
        Color color;
        Shading shading;
        Shape shape;
        Card* nextCard;

};

Card::Card(int cardNo1, int shapeCount1, Color color1, Shading shading1, Shape shape1, Card* nextCard1){
    cardNo = cardNo1;
    shapeCount = shapeCount1;
    color = color1;
    shading = shading1;
    shape = shape1;
    nextCard = nullptr;
}

Card::~Card(){
    delete nextCard;
    nextCard = nullptr;
}

std::ostream& operator<<(std::ostream& os, const Card::Color color)
{
    std::string color1{""};
    if(color == Card::Color::blue){
        color1 = "blue";
    }
    if(color == Card::Color::green){
        color1 = "green";
    }
    if(color == Card::Color::red){
        color1 = "red";
    }
    os << color1;

    return os;
} 

std::ostream& operator<<(std::ostream& os, const Card::Shading shading)
{
    std::string shading1{""};
    if(shading == Card::Shading::solid){
        shading1 = "solid";
    }
    if(shading == Card::Shading::striped){
        shading1 = "striped";
    }
    if(shading == Card::Shading::open){
        shading1 = "open";
    }
    os << shading1;

    return os;
} 

std::ostream& operator<<(std::ostream& os, const Card::Shape shape)
{
    std::string shape1{""};
    if(shape == Card::Shape::oval){
        shape1 = "oval";
    }
    if(shape == Card::Shape::diamond){
        shape1 = "diamond";
    }
    if(shape == Card::Shape::squiggle){
        shape1 = "squiggle";
    }
    os << shape1;

    return os;
} 

class cardHead{

    public:

        Card* getFirst(){return card_head;}
        void setFirst(Card* firstCard){card_head = firstCard;}
        cardHead(Card* card_head1);
        ~cardHead();
    
    private:
    
        Card* card_head;

};

cardHead::cardHead(Card* card_head1){
    card_head = card_head1;
}

cardHead::~cardHead(){
    delete card_head;
    card_head = nullptr;
}

#endif
