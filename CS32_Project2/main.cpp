//
//  main.cpp
//  CS32_Project2
//
//  Created by Tom Slavonia on 1/24/23.
//

/*#include <iostream>
#include <string>
#include <cassert>
#include "Set.h"

using namespace std;

        void test()
        {
            Set ss;
            assert(ss.insert("roti"));
            assert(ss.insert("pita"));
            assert(ss.size() == 2);
            assert(ss.contains("pita"));
            ItemType x = "laobing";
            assert(ss.get(0, x)  &&  x == "pita");
            assert(ss.get(1, x)  &&  x == "roti");
            
            
            Set s1;
            Set s2;
            Set r1;
            assert(s1.insert("hello")); // creating a set and making sure everything is inserting correctly
            assert(s1.insert("goodbye"));
            assert(s1.insert("ciao"));
            assert(s1.insert("hasta luego"));
            assert(s1.insert("adios"));
            assert(s2.insert("bye"));
            assert(s2.insert("hello"));
            assert(s2.insert("sayonara"));
            assert(s2.insert("adios"));
            assert(r1.insert("mom"));
            assert(r1.insert("dad"));
            unite(s1, s2, r1); // testing unite function
            assert(r1.contains("hello")); // making sure unite contains intended values
            assert(r1.contains("goodbye"));
            assert(r1.contains("ciao"));
            assert(r1.contains("hasta luego"));
            assert(r1.contains("adios"));
            assert(r1.contains("mom") == false);
            assert(r1.contains("dad") == false);
            assert(r1.contains("bye"));
            assert(r1.contains("sayonara"));
            assert(r1.size() == 7); // making sure unite output has the right size
            
            Set ss1;
            Set ss2;
            Set rr1;
            
            assert(ss1.insert("hello"));
            assert(ss1.insert("goodbye"));
            assert(ss1.insert("ciao"));
            assert(ss1.insert("hasta luego"));
            assert(ss1.insert("adios"));
            assert(ss2.insert("bye"));
            assert(ss2.insert("hello"));
            assert(ss2.insert("sayonara"));
            assert(ss2.insert("adios"));
            butNot(ss2, ss1, rr1); // testing butNot function
            assert(rr1.contains("bye"));
            assert(rr1.contains("sayonara"));
            assert(rr1.size() == 2); // making sure butNot output has the right size
            
            Set sss;
            
            assert(sss.insert("1"));
            assert(sss.insert("2"));
            assert(sss.insert("3"));
            ItemType y;
            assert(sss.get(1, y) && y == "2"); // testing get function works
            assert(sss.get(3, y) == false); // can't get value at size of the set
            
            Set ssss1;
            assert(ssss1.empty() == true);
            assert(ssss1.erase("hi") == false); // can't erase something that doesn't exist
            assert(ssss1.insert("bell"));
            assert(ssss1.insert("tell"));
            assert(ssss1.insert("fell"));
            assert(ssss1.insert("sell"));
            assert(ssss1.erase("sell") == true); // testing erase function
            assert(ssss1.erase("Fell") == false); // notice that Fell is now with capital
            assert(ssss1.contains("sell") == false);
            assert(ssss1.contains("fell") == true);
            assert(ssss1.size() == 3); // making sure erase is resetting size
            
            Set ssss2;
            assert(ssss2.insert("glide"));
            assert(ssss2.insert("tide"));
            assert(ssss2.insert("pride"));
            assert(ssss2.insert("slide"));
            assert(ssss2.insert("abide"));
            assert(ssss2.insert("confide"));
            assert(ssss2.insert("cried"));
            assert(ssss2.insert("decide"));
            assert(ssss2.insert("died"));
            
            ssss2.swap(ssss1); // swap test
            assert(ssss2.contains("fell") == true); // making sure intended values are in sets
            assert(ssss2.contains("bell") == true);
            assert(ssss2.contains("tell") == true);
            assert(ssss2.contains("pride") == false);
            assert(ssss2.contains("abide") == false);
            assert(ssss2.contains("sell") == false);
            assert(ssss2.contains("confide") == false);
            assert(ssss2.contains("died") == false);
            assert(ssss2.contains("glide") == false);
            assert(ssss1.contains("glide") == true);
            assert(ssss1.contains("died") == true);
            assert(ssss1.contains("tell") == false);
            assert(ssss1.contains("bell") == false);
            assert(ssss1.contains("fell") == false);
            
            Set set1;
            Set set2;
            
            assert(set1.insert("1")); // copy constructor test
            assert(set1.insert("2"));
            assert(set1.insert("3"));
            set2 = set1;
            assert(set2.contains("1")); 
            assert(set2.contains("2"));
            assert(set2.contains("3"));
            
            Set set3;
            Set set4;
            
            assert(set3.insert("1")); // assignment operator test
            assert(set3.insert("2"));
            assert(set3.insert("3"));
            assert(set4.insert("love"));
            assert(set4.insert("purpose"));
            set3 = set4;
            assert(set3.contains("love") == true);
            assert(set3.contains("purpose") == true);
            assert(set3.size() == 2);
            ItemType z;
            ItemType q;
            ItemType v;
            set3.get(0, z);
            set3.get(1, q);
            set4.get(0, v);
            assert(set3.contains("1") == false);
            assert(set3.contains("2") == false);
            assert(set3.contains("3") == false);
            assert(set3.get(3, z) == false); 
            assert(set3.erase("love") == true);
            assert(set3.size() == 1);
            assert(set3.erase("love") == false);
            
            unite(set2, set3, set2);  // special case unite test
            butNot(set1, set1, set1); // aliasing test for butNot
            assert(set1.size() == 0);
            
            Set set5;
            Set set6;
            Set set7; // created to test if destructor works for empty set
            
            assert(set5.insert("1"));
            assert(set5.insert("2"));
            assert(set5.insert("3"));
            assert(set5.insert("4"));
            assert(set5.insert("5"));
            assert(set5.insert("6"));
            assert(set5.insert("7"));
            assert(set5.insert("8"));
            assert(set5.insert("9"));
            assert(set5.insert("10"));
            assert(set6.insert("fun"));
            assert(set6.insert("scam"));
            assert(set6.insert("money"));
            assert(set6.insert("greed"));
            butNot(set6, set5, set6); // this causes infinite error
            assert(set6.size() == 4); // need to check if test is correct;
            assert(set6.erase("greed"));
            assert(set6.erase("fun"));
            assert(set6.insert("Love"));
            assert(set6.erase("scam"));
            
            Set set8;
            
            assert(set8.insert("dan"));
            assert(set8.insert("man"));
            assert(set8.insert("tan"));
            assert(set8.insert("fan"));
            assert(set8.insert("van"));
            assert(set8.erase("tan"));
            
            Set set9;
            Set set10;
            Set result;
            
            assert(set9.insert("can"));
            assert(set9.insert("ban"));
            assert(set9.insert("yam"));
            assert(set9.insert("sham"));
            assert(set10.insert("yell"));
            assert(set10.insert("hell"));
            assert(result.insert("rang"));
            assert(result.insert("ear"));
            assert(result.insert("drum"));
            assert(result.insert("speaker"));
            assert(result.insert("song"));
            assert(result.insert("yell"));
            unite(set10, set9, result); // a very involved unite test case
            assert(result.contains("song") == false);
            assert(result.contains("yell") == true);
            assert(result.contains("sham") == true);
            assert(result.contains("hell") == true);
            assert(result.contains("ear") == false);
            assert(result.size() == 6);
            
            
            
        }

        int main()
        {
            test();
            cout << "Passed all tests" << endl;
        }*/


