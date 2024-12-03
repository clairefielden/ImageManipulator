#include "ConnectedComponent.h"
#define CC FLDCLA001::ConnectedComponent

//default constructor
CC::ConnectedComponent(): id(0), numPixels(0)
{}

//customer constructor
//CC::ConnectedComponent(int id, int numPixels, map<unsigned char, pair<int, int>> pixels): id(id), numPixels(numPixels), pixels(pixels)
CC::ConnectedComponent(int id, int numPixels, vector<pair<int, int> > pixels): id(id), numPixels(numPixels), pixels(pixels)
{}

//destructor
CC::~ConnectedComponent()
{
    //cout<<"CC Destructor Called!"<<endl;
}

//copy constructor
CC::ConnectedComponent(const CC & c): id(c.id), numPixels(c.numPixels), pixels(c.pixels)
{}

//copy assignment operator
CC & CC::operator = (const ConnectedComponent & rhs)
{
    if(this!=&rhs)
    {
        this->id = rhs.id;
        this->numPixels = rhs.numPixels;
        this->pixels = rhs.pixels;
    }
    return *this;
}

//move constructor
CC::ConnectedComponent(CC && c): id(c.id), numPixels(c.numPixels), pixels(c.pixels)
{}

//move assignment operator
CC & CC::operator = (CC && rhs)
{
    if(this!=&rhs)
    {
        this->id = rhs.id;
        this->numPixels = rhs.numPixels;
        this->pixels = rhs.pixels;
    }
    return *this;
}

//overloading == operator for comparison of class objects
bool CC::operator==(const ConnectedComponent & other) const
{
    bool equals = false;
    if(this->id == other.id)
    {
        equals = true;
        if(this->numPixels == other.numPixels)
        {
            equals = true;
            if(this->pixels == other.pixels)
            {
                equals = true;
            }
            else
            {
                equals = false;
            }
        }
        else
        {
            equals = false;
        }
    }
    else
    {
        equals = false;
    }

    return equals;
}


