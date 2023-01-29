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
            if(sb!="/"){ //If it is not a closing tag!!
               s = xml[i];
               while(s!=">"){
                s = xml[i];
                save += s; //save the open tag
                i++;
               }
               closing = false; 
               //To save the open tag with tags in saveO
               saveO = save; 
               //To remove the '<' , '>' to push only inbetween the tags
               saveO.erase(remove(saveO.begin() ,saveO.end(), '<'), saveO.end());
               saveO.erase(remove(saveO.begin() ,saveO.end(), '>'), saveO.end());
               d.push(saveO); //push in stack d
            }
            else if(sb =="/"){ //If it is a closing tag!!
                while(s!=">"){
                    s = xml[i];
                    save += s; //save the close tag
                    i++;
                }
                closing = true;
                //To save the close tag with tags in saveC
                saveC = save;
                //To remove the '<' , '/', '>'  to push only inbetween the tags
                saveC.erase(remove(saveC.begin() ,saveC.end(), '<'), saveC.end());
                saveC.erase(remove(saveC.begin() ,saveC.end(), '/'), saveC.end());
                saveC.erase(remove(saveC.begin() ,saveC.end(), '>'), saveC.end());
                c.push(saveC); //push in stack c
            }
        }
        else //if(s != "<")
        {
            while (s != "<")
            {
                save += s;
                i++;
                s = xml[i];
            }
        }
        if(closing && !d.empty()){ //if it is a closing tag and the stack d (which store in it the opening tag) is not empty
            if(c.top() != d.top()){ //if stack c top(closing tag) is not equal stack d top(opening tag)
                while (!d.empty())
                {
                    u.push(d.top()); //push the top of stack d in stack u
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
        cout<<c.top() <<" tag is not opened"<<endl;
        c.pop();
    }
}
//Test Function
/* 
int main(){
    string s = "<Student>M</name>";
    XML_Check(s);
}
*/
