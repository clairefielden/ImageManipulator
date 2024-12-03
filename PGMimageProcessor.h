#ifndef __PIP__
#define __PIP__

#include "ConnectedComponent.h"
#include <map>
#include <string>
#include <queue>
#include <vector>
#include <memory>
using namespace std;
namespace FLDCLA001{
    class PGMimageProcessor
    {
        friend class ConnectedComponent;
        string version;
        string comment;
        int height;
        int width;
        unsigned char threshold; //value of pixel
        //vector<unsigned char**> imageSequence; //the original image
        //unsigned char **pixel_array;
        int **pixel_array;
        //map<int,weak_ptr<ConnectedComponent>> components; //vector of connected components
        vector<shared_ptr<ConnectedComponent>> components; //vector of connected components

        public:
        int extractComponents(unsigned char threshold, int minValidSize);
        int filterComponentsBySize(int minSize, int maxSize);
        bool writeComponents(const string & outFileName);
        int getComponentCount(void) const;
        int getLargestSize(void) const;
        int getSmallestSize(void) const;
        void printComponentData(const ConnectedComponent & theComponent) const;

        //the big 6
        PGMimageProcessor(); //default constructor
        PGMimageProcessor(string filaname);
        //the custom constructor reads in a file and sets member variables accordingly, storing image n a 2D pointer array
        //virtual ~PGMimageProcessor(); //destructor
        ~PGMimageProcessor(); //destructor
        PGMimageProcessor(const PGMimageProcessor &pip); //copy comstructor
        PGMimageProcessor(PGMimageProcessor && pip); //move constructor
        PGMimageProcessor &operator = (const PGMimageProcessor & rhs); //copy assignment operator
        PGMimageProcessor &operator = (PGMimageProcessor && rhs);

        //for the unit tests
        string getVersion() {return version;}
        string getComment() {return comment;}
        int getHeight(){return height;}
        int getWidth() {return width;}
        unsigned char getThreshold() {return threshold;}
        //unsigned char ** getArray() {return pixel_array;}
        int ** getArray() {return pixel_array;}
        vector<shared_ptr<ConnectedComponent>> getVector() {return components;}

        //for the component functions
        //void eQNeigh(int i, int j, queue<pair<int, int>> &q);
        int eQNeigh (int x, int y, int rows, int columns);
        void BFS(int **data, int x, int y, int id, int t, int minSize);

    };

}

#endif // __PIP__
