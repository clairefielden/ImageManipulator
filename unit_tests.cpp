#define CATCH_CONFIG_MAIN
#include "catch.hpp"

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

using namespace std;
using namespace FLDCLA001;


//UNIT TESTS FOR PGM
/*
    TEST_CASE("PGMimageProcessor Big 6 Unit Tests")
    {

        SECTION("Default Constructor")
        {
            PGMimageProcessor p;
            REQUIRE(p.getVersion() == "");
            REQUIRE(p.getHeight() == 0);
            REQUIRE(p.getWidth() == 0);
            REQUIRE(p.getThreshold() == '\0');
        }

        SECTION("Custom Constructor")
        {
            PGMimageProcessor p("sloan_image.pgm");
            REQUIRE(p.getVersion()=="P5");
            REQUIRE(p.getHeight() == 1968);
            REQUIRE(p.getWidth() == 4130);
            REQUIRE(p.getThreshold() == 255);
        }

        SECTION("Copy Constructor")
        {
            PGMimageProcessor p1("sloan_image.pgm");
            PGMimageProcessor p2(p1);
            REQUIRE(p2.getVersion()==p1.getVersion());
            REQUIRE(p2.getHeight() == p1.getHeight());
            REQUIRE(p2.getWidth() == p1.getWidth());
            REQUIRE(p2.getThreshold() == p1.getThreshold());

            int ** p1_array = p1.getArray();
            int ** p2_array = p2.getArray();

            REQUIRE(p2_array != p1_array);

            for(int i = 0; i<p2.getHeight(); i++)
            {
                for(int j = 0; j<p2.getWidth(); j++)
                {
                    REQUIRE(p2_array[i][j]==p1_array[i][j]);
                }
            }

            vector<shared_ptr<ConnectedComponent>> p1Vect = p1.getVector();
            vector<shared_ptr<ConnectedComponent>> p2Vect = p2.getVector();

            auto i = p1Vect.begin();
            auto j = p2Vect.begin();

            while(i!=p1Vect.end() && j!=p2Vect.end())
            {
                shared_ptr<ConnectedComponent> c1(new ConnectedComponent());
                c1 = *i;
               shared_ptr<ConnectedComponent> c2(new ConnectedComponent());
                c2 = *j;
                REQUIRE(c1==c2);
                i++;
                j++;
            }

        }

        SECTION("Move Constructor")
        {
            PGMimageProcessor p1("sloan_image.pgm");
            int **arrAdr = p1.getArray();

            PGMimageProcessor p2(std::move(p1));
            REQUIRE(p1.getVersion()==p2.getVersion());
            REQUIRE(p1.getHeight() == p2.getHeight());
            REQUIRE(p1.getWidth() == p2.getWidth());
            REQUIRE(p1.getThreshold() == p2.getThreshold());

            int **p2_array = p2.getArray();

            REQUIRE(p1.getArray()==nullptr);
            REQUIRE(p2.getArray()==arrAdr);

            for(int i = 0; i<p2.getHeight(); i++)
            {
                for(int j = 0; j<p2.getWidth(); j++)
                {
                    REQUIRE(p2_array[i][j]==arrAdr[i][j]);
                }
            }

            vector<shared_ptr<ConnectedComponent>> p1Vect = p1.getVector();
            vector<shared_ptr<ConnectedComponent>> p2Vect = p2.getVector();

            auto i = p1Vect.begin();
            auto j = p2Vect.begin();

            while(i!=p1Vect.end() && j!=p2Vect.end())
            {
                shared_ptr<ConnectedComponent> c1(new ConnectedComponent());
                c1 = *i;
               shared_ptr<ConnectedComponent> c2(new ConnectedComponent());
                c2 = *j;
                REQUIRE(c1==c2);
                i++;
                j++;
            }

        }

        SECTION("Copy Assignment Operator")
        {
            PGMimageProcessor p1("sloan_image.pgm");
            PGMimageProcessor p2;

            p2 = p1;

            REQUIRE(p1.getVersion()==p2.getVersion());
            REQUIRE(p1.getHeight() == p2.getHeight());
            REQUIRE(p1.getWidth() == p2.getWidth());
            REQUIRE(p1.getThreshold() == p2.getThreshold());

            REQUIRE(p1.getArray()!=p2.getArray());
            int ** p1_array = p1.getArray();
            int ** p2_array = p2.getArray();
            for(int i = 0; i<p2.getHeight(); i++)
            {
                for(int j = 0; j<p2.getWidth(); j++)
                {
                    REQUIRE(p2_array[i][j]==p1_array[i][j]);
                }
            }

           vector<shared_ptr<ConnectedComponent>> p1Vect = p1.getVector();
            vector<shared_ptr<ConnectedComponent>> p2Vect = p2.getVector();

            auto i = p1Vect.begin();
            auto j = p2Vect.begin();

            while(i!=p1Vect.end() && j!=p2Vect.end())
            {
                shared_ptr<ConnectedComponent> c1(new ConnectedComponent());
                c1 = *i;
               shared_ptr<ConnectedComponent> c2(new ConnectedComponent());
                c2 = *j;
                REQUIRE(c1==c2);
                i++;
                j++;
            }
            //check self-assignment

            int **arrAdr = p1.getArray();
            p1 = p1;

            REQUIRE(p1.getArray()==arrAdr);
            p1_array = p1.getArray();
            for(int i = 0; i<p1.getHeight(); i++)
            {
                for(int j = 0; j<p1.getWidth(); j++)
                {
                    REQUIRE(p2_array[i][j]==p1_array[i][j]);
                }
            }

        }

        SECTION("Move Assignment Operator")
        {
            PGMimageProcessor p1("sloan_image.pgm");
            int **arrAdr = p1.getArray();

            PGMimageProcessor p2;
            p2 = std::move(p1);

            REQUIRE(p1.getVersion()==p2.getVersion());
            REQUIRE(p1.getHeight() == p2.getHeight());
            REQUIRE(p1.getWidth() == p2.getWidth());
            REQUIRE(p1.getThreshold() == p2.getThreshold());

            int **p2_array = p2.getArray();

            REQUIRE(arrAdr==p2.getArray());
            REQUIRE(p1.getArray()==nullptr);

            for(int i = 0; i<p2.getHeight(); i++)
            {
                for(int j = 0; j<p2.getWidth(); j++)
                {
                    REQUIRE(p2_array[i][j]==arrAdr[i][j]);
                }
            }

            vector<shared_ptr<ConnectedComponent>> p1Vect = p1.getVector();
            vector<shared_ptr<ConnectedComponent>> p2Vect = p2.getVector();

            auto i = p1Vect.begin();
            auto j = p2Vect.begin();

            while(i!=p1Vect.end() && j!=p2Vect.end())
            {
                shared_ptr<ConnectedComponent> c1(new ConnectedComponent());
                c1 = *i;
                shared_ptr<ConnectedComponent> c2(new ConnectedComponent());
                c2 = *j;
                REQUIRE(c1==c2);
                i++;
                j++;
            }

            //check self-assignment

            p2 = std::move(p2);
            REQUIRE(p2.getArray()==arrAdr);
            p2_array = p2.getArray();
            for(int i = 0; i<p1.getHeight(); i++)
            {
                for(int j = 0; j<p1.getWidth(); j++)
                {
                    REQUIRE(p2_array[i][j]==arrAdr[i][j]);
                }
            }

        }

    }
*/
    //UNIT TESTS FOR PGM FUNCTIONS

     TEST_CASE("PGMimageProcessor Functions")
    {

        SECTION("Component Extraction")
        {
            PGMimageProcessor p1("chess-colour.pgm");
            //valid size = 1
            int num = p1.extractComponents(45,1);
            REQUIRE(num==p1.getVector().size());
            //valid size = 3
            PGMimageProcessor p2("chess-colour.pgm");
            num = p2.extractComponents(45,2);
            REQUIRE(num==p2.getVector().size());
        }

        SECTION("Component Filter")
        {

            PGMimageProcessor p1("chess-colour.pgm");
            int num = p1.extractComponents(45,1);
            //valid size = 1
            num = p1.filterComponentsBySize(2,7);
            REQUIRE(num==p1.getVector().size());
        }

        SECTION("Component Write")
        {

            PGMimageProcessor p1("chess-colour.pgm");
            int num = p1.extractComponents(45,1);
            bool out = p1.writeComponents("output.pgm");
            REQUIRE(out == true);
        }

        SECTION("Component Count")
        {

            PGMimageProcessor p1("chess-colour.pgm");
            int num1 = p1.getComponentCount();
            REQUIRE(num1 == 0);
            int num = p1.extractComponents(45,1);
            num1 = p1.getComponentCount();
            REQUIRE(num1 == num);
            int num2 = p1.filterComponentsBySize(2,7);
            num1 = p1.getComponentCount();
            REQUIRE(num1==num2);
        }


        SECTION("Largest Component")
        {
            PGMimageProcessor p1("chess-colour.pgm");
            int num1 = p1.getLargestSize();
            REQUIRE(num1 == 0);
            int num = p1.extractComponents(45,1);
            num1 = p1.getLargestSize();
            REQUIRE(num1>=1);
            num = p1.filterComponentsBySize(2,7);
            num1 = p1.getLargestSize();
            REQUIRE(num1<=7);
        }

        SECTION("Smallest Component")
        {
            PGMimageProcessor p1("chess-colour.pgm");
            int num1 = p1.getSmallestSize();
            REQUIRE(num1 == 0);
            int num = p1.extractComponents(45,1);
            num1 = p1.getSmallestSize();
            REQUIRE(num1>=1);
            num = p1.filterComponentsBySize(2,7);
            num1 = p1.getSmallestSize();
            REQUIRE(num1<=7);
        }

        SECTION("Print Component")
        {
            //vector<ConnectedComponent>::const_iterator ptr;
            int counter = 0;
            PGMimageProcessor p1("chess-colour.pgm");
            int num = p1.extractComponents(45,1);

            vector<shared_ptr<ConnectedComponent>> p1Vect = p1.getVector();

            for(auto i = p1Vect.begin(); i!=p1Vect.end(); ++i)
            {
                shared_ptr<ConnectedComponent> c1(new ConnectedComponent());
                c1 = (*i);
                ConnectedComponent c2 = *c1;
                p1.printComponentData(c2);
                counter++;
            }
            REQUIRE(counter==p1Vect.size());

            num = p1.filterComponentsBySize(2,7);
            counter = 0;
            p1Vect = p1.getVector();

            for(auto i = p1Vect.begin(); i!=p1Vect.end(); ++i)
            {
                shared_ptr<ConnectedComponent> c1(new ConnectedComponent());
                c1 = (*i);
                ConnectedComponent c2 = *c1;
                p1.printComponentData(c2);
                counter++;
            }
            REQUIRE(counter==p1Vect.size());

        }
    }
/*

  //UNIT TESTS FOR CONNECTED COMPONENTS CLASS

  TEST_CASE("ConnectedComponents Functions")
    {

        SECTION("Default Constructor")
        {
            ConnectedComponent c;
            REQUIRE(c.getID() == 0);
            REQUIRE(c.getPix() == 0);
        }

        SECTION("Custom Constructor")
        {
            unsigned char uc = 'c';
            pair<int,int> pair1;
            pair1.first = 0;
            pair1.second = 0;
            vector<pair<int,int>> cmap;
            cmap[uc] = pair1;
            ConnectedComponent c(400,5000,cmap);
            REQUIRE(c.getID()==400);
            REQUIRE(c.getMap().size()==1);
            vector<pair<int,int>> constr_map = c.getMap();
            REQUIRE(constr_map[uc]==pair1);
        }

        SECTION("Copy Constructor")
        {
            unsigned char uc = 'c';
            pair<int,int> pair1;
            pair1.first = 0;
            pair1.second = 0;
            vector<pair<int,int>> cmap;
            cmap[uc] = pair1;
            ConnectedComponent c1(400,5000,cmap);
            ConnectedComponent c2(c1);
            REQUIRE(c2.getID()==c1.getID());
            REQUIRE(c2.getPix() == c1.getPix());
            REQUIRE(c2.getMap().size() == c1.getMap().size());

            vector<pair<int,int>> constr1_map = c1.getMap();
            vector<pair<int,int>> constr2_map = c2.getMap();
            REQUIRE(constr1_map[uc] == constr2_map[uc]);
        }


        SECTION("Move Constructor")
        {

            unsigned char uc = 'c';
            pair<int,int> pair1;
            pair1.first = 0;
            pair1.second = 0;
            vector<pair<int,int>> cmap;
            cmap[uc] = pair1;
            ConnectedComponent c1(400,5000,cmap);
            ConnectedComponent c2(std::move(c1));

            REQUIRE(c2.getID()==c1.getID());
            REQUIRE(c2.getPix() == c1.getPix());
            REQUIRE(c2.getMap().size() == c1.getMap().size());

           vector<pair<int,int>> constr1_map = c1.getMap();
            vector<pair<int,int>> constr2_map = c2.getMap();
            REQUIRE(constr1_map[uc] == constr2_map[uc]);

        }


        SECTION("Copy Assignment Operator")
        {
            unsigned char uc = 'c';
            pair<int,int> pair1;
            pair1.first = 0;
            pair1.second = 0;
            vector<pair<int,int>> cmap;
            cmap[uc] = pair1;

            ConnectedComponent c1(400,5000,cmap);
            ConnectedComponent c2;
            c2 = c1;

            REQUIRE(c2.getID()==c1.getID());
            REQUIRE(c2.getPix() == c1.getPix());
            REQUIRE(c2.getMap().size() == c1.getMap().size());

            vector<pair<int,int>> constr1_map = c1.getMap();
            vector<pair<int,int>> constr2_map = c2.getMap();
            REQUIRE(constr1_map[uc] == constr2_map[uc]);

        }


        SECTION("Move Assignment Operator")
        {
            unsigned char uc = 'c';
            pair<int,int> pair1;
            pair1.first = 0;
            pair1.second = 0;
            vector<pair<int,int>> cmap;
            cmap[uc] = pair1;

            ConnectedComponent c1(400,5000,cmap);
            ConnectedComponent c2;
            c2 = std::move(c1);

            REQUIRE(c2.getID()==c1.getID());
            REQUIRE(c2.getPix() == c1.getPix());
            REQUIRE(c2.getMap().size() == c1.getMap().size());

            vector< pair<int,int>> constr1_map = c1.getMap();
            vector<pair<int,int>> constr2_map = c2.getMap();
            REQUIRE(constr1_map[uc] == constr2_map[uc]);

        }

        SECTION("Equals Operator for Connected Component")
        {
            unsigned char uc = 'c';
            pair<int,int> pair1;
            pair1.first = 0;
            pair1.second = 0;
            vector<pair<int,int>> cmap;
            cmap[uc] = pair1;

            ConnectedComponent c1(400,5000,cmap);
            ConnectedComponent c2(400,5000,cmap);
            REQUIRE(c1==c2);
        }

    }
*/
