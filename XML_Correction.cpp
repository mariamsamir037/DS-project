#include <iostream>
#include <stack>
#include <string>
#include<algorithm>

using namespace std;

void correct_XML(string XML){
    int i = 0;
    string temp, temp1, temp2, Tag, open_tag_name, closed_tag_name, correct;
    stack<string> open_st, closed_st, temp_st;
    while(i < XML.size()){
        temp1 = XML[i];
        if(temp1 == "<"){
            temp2 = XML[i+1];
            if(temp2 != "/"){
                temp1 = XML[i];
                while(temp1 != ">"){
                    temp1 = XML[i];
                    Tag += temp1;
                    i++;
                }
                open_tag_name = Tag;
                open_tag_name.erase(remove(open_tag_name.begin(), open_tag_name.end(),'<'), open_tag_name.end());
                open_tag_name.erase(remove(open_tag_name.begin(), open_tag_name.end(),'>'), open_tag_name.end());
                open_st.push(open_tag_name);
                if(!open_st.empty()&& !closed_st.empty()){
                    if(closed_st.top() == open_st.top()){
                        correct += Tag;
                        temp = closed_st.top();
                        temp.insert(0, "<");
                        temp.insert(1, "/");
                        int x = temp.length();
                        temp.insert(x, ">");
                        open_st.pop();
                        closed_st.pop();
                        correct += temp;
                    }
                    else{correct += Tag;}
                }
                else{correct += Tag;}
            }
            else if(temp2 == "/"){
                while(temp1 != ">"){
                    temp1 = XML[i];
                    Tag += temp1;
                    i++;
                }
                closed_tag_name = Tag;
                closed_tag_name.erase(remove(closed_tag_name.begin(), closed_tag_name.end(),'<'), closed_tag_name.end());
                closed_tag_name.erase(remove(closed_tag_name.begin(), closed_tag_name.end(),'>'), closed_tag_name.end());
                closed_tag_name.erase(remove(closed_tag_name.begin(), closed_tag_name.end(),'/'), closed_tag_name.end());
                closed_st.push(closed_tag_name);
                if(!open_st.empty()&& !closed_st.empty()){
                    if(closed_st.top() != open_st.top()){
                        while(!closed_st.empty()){
                            temp_st.push(closed_st.top());
                            closed_st.pop();
                        }
                    }
                    else if(closed_st.top() == open_st.top()){
                        while(!open_st.empty()&& !closed_st.empty()){
                            temp = closed_st.top();
                            temp.insert(0, "<");
                            temp.insert(1, "/");
                            int x = temp.length();
                            temp.insert(x, ">");
                            closed_st.pop();
                            open_st.pop();
                            correct += temp;
                        }
                    }
                }
            }
        }
        else{
            while(temp1 != "<"){
                Tag += temp1;
                i++;
                temp1 = XML[i];
            }
            correct += Tag;
        }
        Tag = "";
        open_tag_name = "";
        closed_tag_name = "";
        temp = "";
        while(!temp_st.empty()){
            closed_st.push(temp_st.top());
            temp_st.pop();
        }
    }
    while(!open_st.empty()&& closed_st.empty()){
        temp = open_st.top();
        temp.insert(0, "<");
        temp.insert(1, "/");
        int x = temp.length();
        temp.insert(x, ">");
        closed_st.push(temp);
        closed_st.pop();
        open_st.pop();
        correct += temp;
    }
    cout << correct << endl;
}
