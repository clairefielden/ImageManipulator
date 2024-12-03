#ifndef __CC__
#define __CC__

#include <map>
#include <vector>
using namespace std;
namespace FLDCLA001{
    class ConnectedComponent
    {

        friend class PGMimageProcessor;
        int id;
        int numPixels; //number of pixels in component
        //map<unsigned char, pair<int, int>> pixels; //storage of pixels in component
        vector<pair<int, int> > pixels;

        public:
        ConnectedComponent();
        ConnectedComponent(const int id, const int numPixels,const vector<pair<int, int> > coords);// const map<unsigned char,pair<int, int>> pixels);
        //virtual ~ConnectedComponent();
        ~ConnectedComponent();
        ConnectedComponent(const ConnectedComponent & c);
        ConnectedComponent(ConnectedComponent && c);
        ConnectedComponent &operator =(const ConnectedComponent & rhs);
        ConnectedComponent &operator =(ConnectedComponent && rhs);

        //for the PGM functions
        int getPix() const noexcept {return numPixels;}
        int getID() const noexcept {return id;}
        //map<unsigned char, pair<int, int>> getMap() const noexcept {return pixels;}
        vector<pair<int, int> > getMap() const noexcept{return pixels;};
        bool operator==(const ConnectedComponent & other) const;
    };

}
#endif // __CC__
