#include "XML_Correction.h"

void correct_XML(vector<string> XML){
    int bars_repeat = 0;
    int bars_num = XML.size();
    string bar;
    stack<labels> gather;

    while(bars_repeat < bars_num){
        bar = XML[bars_repeat];
        int key = 0;
        while(bar[key] != '\0'){
            if(bar[key] == '<'){
                string label;
                if(bar[key+1] == '/'){
                    key = key + 2;
                    while(bar[key -1] != '>'){
                    label.push_back(bar[key++]);
                    }
                CheckLabel:
                    if(!gather.empty()){
                        if(label == (gather.top()).features){
                            gather.pop();
                        }
                        else{
                            bool absentOpenTag = 1;
                            stack<labels> tempGather = gather;
                            tempGather.pop();
                            while(!(tempGather.empty())){
                                if(label == (tempGather.top()).features){
                                    labels tempLabel = gather.top();
                                    gather.pop();
                                    string tempBar = XML[tempLabel.bar];
                                    tempLabel.features = "</" + tempLabel.features;
                                    tempBar.insert(tempLabel.margin, tempLabel.features);
                                    XML[tempLabel.bar] = tempBar;
                                    absentOpenTag = 0;
                                    goto CheckLabel;
                                }
                                tempGather.pop();
                            }
                            if(absentOpenTag == 1){
                                labels tempLabel = gather.top();
                                string tempBar = XML[tempLabel.bar];
                                label = "<" + label;
                                tempBar.insert(tempLabel.margin, label);
                                XML[tempLabel.bar] = tempBar;
                            }
                        }
                    }
                    else{
                        string tempBar = XML[0];
                        label = "<" + label;
                        tempBar.insert(0,label);
                        XML[0] = tempBar;
                    }
                }
                else{
                    if(bar[key+1] != '?'){
                        labels *ptr;
                        key = key + 1;
                        while(bar[key -1] != '>'){
                            if(bar[key] == ' '){
                                label.push_back('>');
                                break;
                            }
                            label.push_back(bar[key++]);
                        }
                        ptr = new labels(label, bars_repeat, key);
                        gather.push(*ptr);
                    }
                    else{break;}
                }
            }
            else{key++;}
        }
        bars_repeat++;
    }
    while(!(gather.empty())){
        string tempLabel = (gather.top()).features;
        gather.pop();
        tempLabel = "</" + tempLabel;
        XML.push_back(tempLabel);
    }
    string corrected;
    corrected = accumulate(begin(XML), end(XML), corrected);
    cout << corrected << endl;
}
