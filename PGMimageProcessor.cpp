#include "PGMimageProcessor.h"

#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <iomanip>
#include <map>
#include <queue>
#include <memory>

#define PIP FLDCLA001::PGMimageProcessor

//default constructor
PIP::PGMimageProcessor(): version(""), comment(""), height(0), width(0),threshold('\0')
{}

PIP::PGMimageProcessor(string filename)
{
        //open the file and get the first few lines
        ifstream infile(filename, ios::binary);
        infile.unsetf(ios_base::skipws);
        //read in binary file with white spaces

        if (!infile)
        {
            printf("File does not exist\n");
            exit(1);
        }

        string inputLine = "";

        // First line : version
        getline(infile,inputLine);
        if(inputLine.compare("P5") != 0 && inputLine.compare("P2") != 0)
        {
            cerr << "Version error" << endl;
        }
        else
        {
            version = inputLine;
        }

        // Second line : comment

         getline(infile, inputLine);

    while (inputLine[0] == '#')
    {

        getline(infile, inputLine);
    }

    string h = inputLine.substr(inputLine.find(" ") + 1, inputLine.find_last_not_of(" "));
    height = stoi(h);
    string w = inputLine.substr(0, inputLine.find(" "));
    width = stoi(w);

    //fourth line : max brightness
    getline(infile, inputLine);
    int bright = stoi(inputLine);
    threshold = (unsigned char) bright;
    //unsigned char ws;

    //save the whole image into an array
    // Following lines : data
    pixel_array = new int * [height];

    unsigned char pixel;
    for(int i = 0; i<height; i++)
    {
        pixel_array[i] = new int [width];
        for(int j = 0; j<width; j++)
        {
            infile>>pixel;
            pixel_array[i][j]=(int)pixel;
        }
    }
    infile.close();

}
//the custom constructor reads in a file and sets member variables accordingly, storing image n a 2D pointer array

PIP::~PGMimageProcessor()
{
/*
   if(pixel_array)
   {
       for(int i = 0; i<height; i++)
       {
           delete[] pixel_array[i];
       }
       delete[] pixel_array;
   }
*/

   cout<<"PGM Destructor Called!"<<endl;
}
//destructor

PIP::PGMimageProcessor(const PGMimageProcessor &pip): version(pip.version), comment(pip.comment), height(pip.height), width(pip.width), threshold(pip.threshold)
{
    if(pip.pixel_array)
    {
        pixel_array = new int*[height];

        for (int i = 0; i < height; i++)
        {
            pixel_array[i] = new int[width];
        }

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width+1; j++)
            {
                pixel_array[i][j] = pip.pixel_array[i][j];
            }
        }
    }

    //copy the components vector
    components = pip.components;

}
//copy constructor

PIP::PGMimageProcessor(PGMimageProcessor && pip): version(pip.version), comment(pip.comment), height(pip.height), width(pip.width), threshold(pip.threshold), pixel_array(pip.pixel_array), components(pip.components)
{
    pip.pixel_array = nullptr;
}

//move constructor
PIP &PIP:: operator = (const PGMimageProcessor & rhs)
{
    if(this!=&rhs)
    {
        this->version = rhs.version;
        this->comment = rhs.comment;
        this->height = rhs.height;
        this->width = rhs.width;
        this->threshold = rhs.threshold;

        if(this->pixel_array != nullptr)
        {
            delete this-> pixel_array;
            this->pixel_array = nullptr;
        }
        if(rhs.pixel_array!=nullptr)
        {
            this->pixel_array = new int*[height];

            for (int i = 0; i < height; i++)
            {
                this->pixel_array[i] = new int[width];
            }

            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width+1; j++)
                {
                    this->pixel_array[i][j] = rhs.pixel_array[i][j];
                }
            }
        }

        this->components = rhs.components;
        return *this;
    }
}//copy assignment operator

PIP &PIP:: operator = (PGMimageProcessor && rhs)
{
    if(this!=&rhs)
    {
        this->version = rhs.version;
        this->comment = rhs.comment;
        this->height = rhs.height;
        this->width = rhs.width;
        this->threshold = rhs.threshold;

        if(this->pixel_array != nullptr)
        {
            delete this-> pixel_array;
            this->pixel_array = nullptr;
        }
        if(rhs.pixel_array!=nullptr)
        {
            this->pixel_array = rhs.pixel_array;

            rhs.pixel_array = nullptr;
        }

       this->components = rhs.components;
    }
 return *this;

} //move assignment operator

int PIP::eQNeigh (int x, int y, int rows, int columns)
{

    // check if the coordinate is negative
    if (x < 0 || y < 0)
    {
        return 0;
    }
    // check if the coordinate is outside of the bounds of the image
    if (x >= rows || y >= columns)
    {
        return 0;
    }
    return 1;
}
/*
void PIP::BFS(int row, int col, int pix, int id, int thr, int minSize)
{
    int numPixels = 0;
   map<unsigned char, pair<int, int>> pMap;

    int visited[height][width];
    memset(visited, 0, sizeof(visited));
    // Create a queue of coordinates to be visited
    queue<pair<int, int>> toVisit;

    // add the specified starting coordinate to the queue
    toVisit.push(make_pair(row,col));
    pMap[numPixels]=make_pair(row,col);
    numPixels++;

    // mark this intial starting coordinate as visited
    visited[row][col] = 1;

    // loop until the queue is empty
    while (toVisit.empty() != 1)
    {
        // get the coordinate at the front of the queue
        pair<int, int> coordinate = toVisit.front();
        //int x = coordinate.first;
        //int y = coordinate.second;

        pixel_array[row][col] = 0;

        // Popping front pair of queue
        toVisit.pop();

        if (eQNeigh(row + 1, col, height, width) && visited[row + 1][col] == 0 && pixel_array[row + 1][col] >= thr)
        {
            toVisit.push(make_pair(row + 1, col));
            pMap[numPixels]=make_pair(row, col);
            numPixels++;
            visited[row + 1][col] = 1;
        }

        // For Downside Pixel or Cell
        if (eQNeigh(row - 1, col, height, width) && visited[row - 1][col] == 0 && pixel_array[row - 1][col] >= thr)
        {
            toVisit.push(make_pair(row - 1, col));
            pMap[numPixels]=make_pair(row, col);
            numPixels++;
            visited[row - 1][col] = 1;
        }

        // For Right side Pixel or Cell
        if (eQNeigh(row, col + 1, height, width) && visited[row][col + 1] == 0 && pixel_array[row][col + 1] >= thr)
        {
            toVisit.push(make_pair(row, col + 1));
            pMap[numPixels]=make_pair(row, col);
            numPixels++;
            visited[row][col + 1] = 1;
        }

        // For Left side Pixel or Cell
        if (eQNeigh(row, col - 1, height, width) && visited[row][col - 1] == 0 && pixel_array[row][col - 1] >= thr)
        {
            toVisit.push(std::make_pair(row, col - 1));
            pMap[numPixels]=make_pair(row, col);
            numPixels++;
            visited[row][col - 1] = 1;
        }


    if (numPixels >= minSize)
   {
        ConnectedComponent comp = ConnectedComponent(id, numPixels, pMap);
        //cout<<"Map: "<<id<<endl;
        /*
        auto j = pMap.begin();
        //j is the components map
        //the size of the map for that component
        while(j!=pMap.end())
        {
            pair<int,int> pair1 = (*j).second;
            cout<<"["<<pair1.first<<"]["<<pair1.second<<"]"<<endl;
            j++;
        }

        shared_ptr<ConnectedComponent> p = make_shared<ConnectedComponent>(comp);
        components.push_back(p);
    }

}
    */


void PIP::BFS(int **data, int x, int y, int id, int t, int minSize)
{
    int numPixels = 0;
    std::vector<std::pair<int, int> > coords;

    int visited[height][width];
    memset(visited, 0, sizeof(visited));
    // Create a queue of coordinates to be visited
    std::queue<std::pair<int, int> > toVisit;

    // add the specified starting coordinate to the queue
    toVisit.push(std::make_pair(x, y));
    coords.push_back(std::make_pair(x, y));
    numPixels++;

    // mark this intial starting coordinate as visited
    visited[x][y] = 1;

    // loop until the queue is empty
    while (toVisit.empty() != 1)
    {

        // get the coordinate at the front of the queue
        std::pair<int, int> coordinate = toVisit.front();
        int x = coordinate.first;
        int y = coordinate.second;

        data[x][y] = 0;

        // Popping front pair of queue
        toVisit.pop();

        // For Upside Pixel or Cell
        // check if there is a pixel above the current one
        // if that pixel has been visited yet (i.e visited = 0) and if the data at that pixel is greater than the threshold
        if (eQNeigh(x + 1, y, height, width) && visited[x + 1][y] == 0 && data[x + 1][y] >= t)
        {
            toVisit.push(std::make_pair(x + 1, y));
            coords.push_back(std::make_pair(x, y));
            numPixels++;
            visited[x + 1][y] = 1;
        }

        // For Downside Pixel or Cell
        if (eQNeigh(x - 1, y, height, width) && visited[x - 1][y] == 0 && data[x - 1][y] >= t)
        {
            toVisit.push(std::make_pair(x - 1, y));
            coords.push_back(std::make_pair(x, y));
            numPixels++;
            visited[x - 1][y] = 1;
        }

        // For Right side Pixel or Cell
        if (eQNeigh(x, y + 1, height, width) && visited[x][y + 1] == 0 && data[x][y + 1] >= t)
        {
            toVisit.push(std::make_pair(x, y + 1));
            coords.push_back(std::make_pair(x, y));
            numPixels++;
            visited[x][y + 1] = 1;
        }

        // For Left side Pixel or Cell
        if (eQNeigh(x, y - 1, height, width) && visited[x][y - 1] == 0 && data[x][y - 1] >= t)
        {
            toVisit.push(std::make_pair(x, y - 1));
            coords.push_back(std::make_pair(x, y));
            numPixels++;
            visited[x][y - 1] = 1;
        }
    }

    if (numPixels >= minSize)
   {
        ConnectedComponent comp = ConnectedComponent(id, numPixels, coords);
        shared_ptr<ConnectedComponent> p = std::make_shared<ConnectedComponent>(comp);
        components.push_back(p);
    }

}


int PIP::extractComponents(unsigned char threshold, int minValidSize)
{
    int thr = threshold;
    //find the connected components
    //the ids to store the connected components
    int insertions = 1;

    for(int i = 0; i<height; i++)
    {
        for(int j = 0; j<width; j++)
        {
           int pix = pixel_array[i][j];
           if(pix>=thr)
           {
               BFS(pixel_array, i, j, insertions, thr, minValidSize);
               //BFS(i,j,pix,insertions,thr,minValidSize);
               insertions++;
           }
        }
    }

    return insertions-1;
}

int PIP::filterComponentsBySize(int minSize, int maxSize)
{
    vector<shared_ptr<ConnectedComponent>>::iterator ptr;
    vector<shared_ptr<ConnectedComponent>> newVect;

    for(ptr = components.begin(); ptr!=components.end(); ++ptr)
    {
        int np = (*ptr)->getPix();
        if(np>=minSize && np<=maxSize)
        {
            newVect.push_back(*ptr);
        }
    }
    components = newVect;
    return newVect.size();
}

bool PIP::writeComponents(const string & outFileName)
{
    ofstream outputImage;
    outputImage.open(outFileName, ios::binary);
    if(outputImage.fail())
    {
        return false;
    }

    outputImage<<"P5"<<"\n";
    outputImage<<"#Created by Claire"<<"\n";
    outputImage<<width<<" "<<height<<"\n";
    outputImage<<(unsigned int)threshold<<"\n";


    for(int row = 0; row < height; row++)
    {
        for(int col = 0; col < width; col++)
        {
            pixel_array[row][col] = 0;
        }
    }

    auto i = components.begin();
    while(i<components.end())
    {
        //map<unsigned char, pair<int, int>> pMap = (*i)->getMap();
        vector<pair<int, int>> pMap = (*i)->getMap();
        //i is the current component
        auto j = pMap.begin();
        //j is the components map
        //the size of the map for that component
        int p_count = 0;
        while(j!=pMap.end())
        {
            //pair<int,int> pair1 = (*j).second;
            pair<int,int> pair1 = (*j);
            pixel_array[pair1.first][pair1.second] = 255;
            p_count++;
            j++;
        }
        i++;
    }

    // Now print the array to see the result
    for(int row = 0; row < height; row++)
    {
        for(int col = 0; col < width; col++)
        {
            outputImage<<char(pixel_array[row][col]);
        }
        //outputImage<<"\n";
    }
    outputImage.close();

    return true;
}

int PIP::getComponentCount(void) const
{
    return components.size();
}

int PIP::getLargestSize(void) const
{
    int biggest = 0;
    int np = 0;

    for(auto i = components.begin(); i!=components.end(); i++)
    {
        np = (*i)->getPix();
        if(np>biggest)
        {
            biggest = np;
        }
    }
    return biggest;
}

int PIP::getSmallestSize(void) const
{
    int smallest = this->getLargestSize();
    int np = 0;

    for(auto i = components.begin(); i!=components.end(); i++)
    {
        np = (*i)->getPix();
        if(np<smallest)
        {
            smallest = np;
        }
    }
    return smallest;
}

void PIP::printComponentData(const ConnectedComponent & theComponent) const
{
    cout<<"Component ID: "<<theComponent.getID()<<endl;
    cout<<"Component number of pixels: "<<theComponent.getPix()<<endl;
}

