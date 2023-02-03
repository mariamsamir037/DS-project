#include "xmltoJson_Converter.h"

string xmltoJson(string s)
{
    string json = "{";
    string append = "*";
    string w, word = "";
    //i for xml length, j for json length, x for repeated tags
    int i = 0, j = 1, x = 0;
    //tag for opening tags but they are popped when they are closed,   brackets for({,]) 
    stack<string> stack_open_tags, tag, brackets;
    //it's true if opening tag,and false if closing
    stack<bool> opening_tag;
    //bracket holds last printed bracket
    string last_closed_tag, bracket;
    //saves value of x (repeated tags)
    stack<int> ind;
    while (i < s.size()) {  //iterate over the whole xml file
        w = s[i];
        if (w == "\r" || w == "\n") {
        }
        //checking if it's tag or data to be printed
        if (w == "<") {
            i++;
            w = s[i];
            if (w != "/") {     //if opening tag
                while (w != ">") {
                    word += w;
                    i++;
                    w = s[i];
                }
                //if more than one <topic> repeated in scope of <topics>, delete topic from json and add [
                if (word == last_closed_tag) {
                    json.erase(x - ((brackets.size() + 1)) - 2, word.length() + 6 + ((brackets.size() + 1)));   //6 bec ({ \n " " : ), x->"
                    j -= (word.length() + 6 + ((brackets.size() + 1)));
                    json.insert(x - ((brackets.size() + 1)) - 2, "[\n");
                    j += 2;
                    brackets.pop();
                    brackets.push("]");
                    //return old value of x
                    if (!ind.empty()) {
                        ind.pop();
                        if (!ind.empty()) {
                            x = ind.top();
                        }
                    }
                    //skip new <topic>
                    i++;
                    stack_open_tags.push(word);
                    tag.push(word);
                    opening_tag.push(true);
                    json += "\n";
                    j += 1;
                    word = "";
                    continue;
                }
                //condition for the first opening tag bec stk is still empty
                if (stack_open_tags.empty()) {
                    json += "\n";
                }
                //if last thing in json was closing tag, no need to open "{"
                else if (opening_tag.top() == false) {

                    json += "\n";
                    j += 1;
                }
                else {
                    //for formating
                    for (int t = brackets.size() + 1; t > 0; t--) {
                        json += " ";
                        j += 1;
                    }
                    json += "{\n";
                    j += 2;

                    //assuming if there is array in xml file, it must be writtin as (users,user - topics,topic)
                    //save index of user in json to be deleted if it's repeated in the same scope of users
                    if (word + "s" == stack_open_tags.top()) {
                        x = j + brackets.size() + 3; //x->"
                        ind.push(x);
                    }
                    brackets.push("}");
                }
                //for formating
                for (int t = brackets.size() + 1; t > 0; t--) {
                    json += " ";
                    j += 1;
                }
                json += "\"";
                j++;
                json += word;
                j += word.length();
                json += "\": ";
                j += 3;
                stack_open_tags.push(word);
                tag.push(word);
                i++;
                opening_tag.push(true);
            }
            else {      //if closing tag
                while (w != ">") { //don't print closing tags
                    i++;
                    w = s[i];
                    word += w;
                }
                word.pop_back();

                //opening tags are pushed into tag*stack* and poped when they are closed
                //before poping they are stored in tags*string*
                //if opening tag is repeated after the closing tag, it will be deleted from json*string*
                if (word == tag.top()) {
                    last_closed_tag = word;
                    tag.pop();

                    //"topic", x=90->", topics length = count = 6, 
                    int count = last_closed_tag.length();
                    string currentWord;
                    currentWord = json[x + 1];
                    //currentWord = t

                    //if scope of topics ended without repeating topic, remove index of topic.
                    for (int L = x + 2; L < x + count; L++) {
                        currentWord += json[L]; //topic
                    }

                    //topic + s == topics
                    if (currentWord + "s" == last_closed_tag) {
                        //pop 90
                        ind.pop();
                        //x = index of post
                        if (!ind.empty()) {
                            x = ind.top();
                        }
                    }
                }
                //print closing brackets
                if (opening_tag.top() == false) {
                    string back;
                    back = json.back();

                    //removing unwanted commas
                    if ((brackets.top() == "]" && bracket == "}") || (brackets.top() == "}" && back == ",") || (brackets.top() == "]" && back == ","))
                    { //brackets.top()-> barcket to be printed, bracket->last printed bracket
                        json.pop_back();
                        j--;
                    }
                    json += "\n";
                    j += 1;
                    for (int t = brackets.size(); t > 0; t--) {
                        json += " ";
                        j += 1;
                    }
                    json += brackets.top();
                    bracket = brackets.top();
                    j++;
                    brackets.pop();
                    if (!brackets.empty()) {
                        json += ","; j++;
                    }
                }
                i++;
                opening_tag.push(false);
            }
        }
        //data to be printed char by char so no need for word here
        else {
            json += "\"";
            j++;
            while (w != "<")
            {
                json += w;
                j++;
                i++;
                w = s[i];
            }
            json += "\"";
            json += ",";
            j += 2;
        }
        word = "";
    }
    json += "\n}";  //closing json string
    j += 2;

    return json;
}

/*  testing the code
int main()
{
   // string xmlfile = "<users><user><id>1 </id ><name>Ahmed Ali< / name><posts><post><body> Mariam</body> <topics><topic>economy< / topic>";
       
    string xmlfile= "<users><user><name>Mar</name><id>1</id><address>24fahmystreet</address></user><user><name>sar</name><id>2</id></user></users>";
    string y = xmltoJson(xmlfile);
    cout << y << endl;

    return 0;
}
*/
