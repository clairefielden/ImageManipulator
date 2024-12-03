#include "PGMimageProcessor.h"
#include "ConnectedComponent.h"
#include "PGMimageProcessor.cpp"
#include "ConnectedComponent.cpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <utility>

using namespace std;
using namespace FLDCLA001;
/*
int main(int argc, char *argv[])
{

    string filename = argv[argc - 1];

    int cnt= 1;
    int min = 3;
    int max;
    unsigned char threshold = 128;
    vector<string> outs;
    bool print = false;
    bool write = false;
    bool fs = true;
    vector<string> ops;
    vector<pair<int, int> > fs_vect;

    while (cnt < argc - 2)
    {
        if (argv[cnt][1] == 's')
        {
            ops.push_back("fs");
            min = atoi(argv[cnt+ 1]);
            max = atoi(argv[cnt + 2]);
            fs_vect.push_back(make_pair(min, max));
            cnt= cnt+ 3;
        }

        if (argv[cnt][1] == 't')
        {
            threshold = atoi(argv[cnt + 1]);
            cnt= cnt+ 2;
        }

        if (argv[cnt][1] == 'p')
        {
            ops.push_back("print");
            cnt++;
        }

        if (argv[cnt][1] == 'w')
        {
            ops.push_back("write");
            string outfile = argv[cnt + 1];
            outs.push_back(outfile);
            cnt= cnt+ 2;
        }
    }

    PGMimageProcessor p(filename);
    cout << "# Extracted Components = " << p.extractComponents(threshold, min) << endl;


    int fCount = 0;
    int wCount = 0;
    for (int i = 0; i < ops.size(); ++i)
    {
        if (ops[i] == "fs")
        {
            pair<int, int> sizes = fs_vect[fCount];
            min = sizes.first;
            max = sizes.second;
            fCount++;
            cout << "# Filtered Components ="<<" [ "<< min << "],[" << max << "] : " << p.filterComponentsBySize(min, max) << endl;
        }
        if (ops[i] == "print")
        {
            cout << endl;
            cout << "Component Data\n" << endl;
            vector<shared_ptr<ConnectedComponent>> p_vect = p.getVector();

   	for(auto i = p_vect.begin(); i!=p_vect.end(); ++i)
    	{
        	shared_ptr<ConnectedComponent> c1(new ConnectedComponent());
        	c1 = (*i);
        	ConnectedComponent c2 = *c1;
        	p.printComponentData(c2);
    	}
            cout << "Total Components : " << p.getComponentCount() << endl;
            cout << "Largest Component : " << p.getLargestSize() <<endl;
            cout << "Smallest Component : " << p.getSmallestSize() << endl;
            std::cout << std::endl;
        }

        if (ops[i] == "write")
        {
            bool success = p.writeComponents(outs[wCount]);
            wCount++;
            if (success)
            {
                cout << "PGM Image outputted." <<endl;
            }
        }
    }

}
*/
  int main()
  {
    PGMimageProcessor p("chess-colour.pgm");
    int num = p.extractComponents('.',1);
    cout<<num<<endl;

    num = p.filterComponentsBySize(4000,9000);
    cout<<num<<endl;

    bool out = p.writeComponents("out.pgm");

    vector<shared_ptr<ConnectedComponent>> p_vect = p.getVector();

   for(auto i = p_vect.begin(); i!=p_vect.end(); ++i)
    {
        shared_ptr<ConnectedComponent> c1(new ConnectedComponent());
        c1 = (*i);
        ConnectedComponent c2 = *c1;
        p.printComponentData(c2);
    }

      return 0;
  }


