#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <stack>

using namespace std;

void XML_Check(string xml){
    string s;
    string save;
    int i =0;
    string sb;
    stack<string> d, c, u;
    bool closing = false;
    string saveO; 
    string saveC;
    while(i<xml.size()){
        s = xml[i];
        if(s == "<"){
            sb = xml[i+1];
            if(sb!="/"){ 
               s = xml[i];
               while(s!=">"){
                s = xml[i];
                save += s; 
                i++;
               }
               closing = false; 
               
               saveO = save; 
               
               saveO.erase(remove(saveO.begin() ,saveO.end(), '<'), saveO.end());
               saveO.erase(remove(saveO.begin() ,saveO.end(), '>'), saveO.end());
               d.push(saveO); //push in stack d
            }
            else if(sb =="/"){
                while(s!=">"){
                    s = xml[i];
                    save += s; 
                    i++;
                }
                closing = true;
                
                saveC = save;
                 
                saveC.erase(remove(saveC.begin() ,saveC.end(), '<'), saveC.end());
                saveC.erase(remove(saveC.begin() ,saveC.end(), '/'), saveC.end());
                saveC.erase(remove(saveC.begin() ,saveC.end(), '>'), saveC.end());
                c.push(saveC); //push in stack c
            }
        }
        else 
        {
            while (s != "<")
            {
                save += s;
                i++;
                s = xml[i];
            }
        }
        if(closing && !d.empty()){ 
            if(c.top() != d.top()){ 
                while (!d.empty())
                {
                    u.push(d.top()); 
                    d.pop();
                    if (!d.empty())
                    {
                        if (c.top() == d.top())
                        {
                            c.pop();
                            d.pop();
                            while (!u.empty())
                            {
                                cout<<u.top()<<" tag isn't closed"<<endl;
                                u.pop();
                            }
                            break;
                        }
                    }
                }
                while (!u.empty()) 
                {
                    d.push(u.top());
                    u.pop();
                }
                if (!c.empty()) {
                    cout<< c.top() << " tag isn't opened" <<endl;
                    c.pop();
                }
            }
            else
            {
                d.pop();
                c.pop();
            }
            closing = false;
        
        }
        save = "";
        saveO = "";
        saveC = "";
    }
    while (!d.empty())
    {
        cout<<d.top() <<" tag is not closed"<<endl;
        d.pop();
    }
    while (!c.empty())
    {
        cout<<c.top() <<" tag is not closed"<<endl;
        c.pop();
    }
}