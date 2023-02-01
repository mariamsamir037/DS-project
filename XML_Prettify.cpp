#include "XML_Prettify.h"

string XML_Prettify(string xml) {
    string s;
    int ind =0;
    string str="";
    int open = 0;
    int close = 0;
    string save;
    string sb;
    int i=0;
    while(i < xml.size()) {
        s = xml[i];
        sb = xml[i+1];
        if(s == "<" && sb!="/"){ //If it is not a closing tag!!
            save = "";
            while(s!=">"){
                s = xml[i];
                save +=s;
                i++;
            }
            open++;
            close = 0;
            if (open > 1) {
                ind++;
            }
            for (int j = 0; j < ind; j++) {
                str += "\t";		//print tab
            }
            str += save + "\n";	//print output
        }
        else if(s == "<" && sb == "/"){ //If it is a closing tag!!
            save = "";
            while(s!=">"){
                s = xml[i];
                save +=s;
                i++;
            }
            close++;
            open = 0;
            if (close > 1) {
                ind--;
            }
            for (int j = 0; j < ind; j++) {
                str += "\t";		//print tab
            }
            str += save + "\n";	//print output
        }
        else{ // If it is data (not an opened tag and not closed tag)
            save = "";
            sb=" ";
            while(sb!="<"){
                s = xml[i];
                sb= xml[i+1];
                save +=s;
                if(i>= xml.size()){
                    break;
                }
                i++;
            }
            for (int j = 0; j < ind; j++) {
                if(i>= xml.size()){
                    break;
                }
                str += "\t";		//print tab
             }
             str += save + "\n";
        }
    }
    return str;
}
//Test function
/*int main(){
    string s = "<users><user><id>1</id><name>M</name></user></users>";
    string r = XML_Prettify(s);
    cout<< r;
}*/
