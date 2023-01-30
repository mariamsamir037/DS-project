#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDir>
#include <QMenu>
#include <QAction>
#include <QStatusBar>
#include <QKeyEvent>
#include <QStack>
#include <stack>
#include <QString>
#include <QDebug>
#include <bits/stdc++.h>
#include <QTextCursor>
#include<algorithm>
#define MAX_TREE_HT 256

class labels{

public:

    int bar;
    int margin;
    std::string features;

public:

    labels(std::string f, int b, int m){
    features = f;
    bar = b;
    margin = m;
    }
};
std::vector<std::string> split(std::string str, std::string token){
    std::vector<std::string>result;
    while(str.size()){
        int index = str.find(token);
        if(index!=std::string::npos){
            result.push_back(str.substr(0,index));
            str = str.substr(index+token.size());
            if(str.size()==0)result.push_back(str);
        }else{
            result.push_back(str);
            str = "";
        }
    }
    return result;
}
std::string correct_XML(std::vector<std::string> XML){
    int bars_repeat = 0;
    int bars_num = XML.size();
    std::string bar;
    std::stack<labels> gather;

    while(bars_repeat < bars_num){
        bar = XML[bars_repeat];
        int key = 0;
        while(bar[key] != '\0'){
            if(bar[key] == '<'){
                std::string label;
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
                            std::stack<labels> tempGather = gather;
                            tempGather.pop();
                            while(!(tempGather.empty())){
                                if(label == (tempGather.top()).features){
                                    labels tempLabel = gather.top();
                                    gather.pop();
                                    std::string tempBar = XML[tempLabel.bar];
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
                                std::string tempBar = XML[tempLabel.bar];
                                label = "<" + label;
                                tempBar.insert(tempLabel.margin, label);
                                XML[tempLabel.bar] = tempBar;
                            }
                        }
                    }
                    else{
                        std::string tempBar = XML[0];
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
        std::string tempLabel = (gather.top()).features;
        gather.pop();
        tempLabel = "</" + tempLabel;
        XML.push_back(tempLabel);
    }
    std::string corrected;
    corrected = accumulate(begin(XML), end(XML), corrected);
    std::cout << corrected << std::endl;
    return corrected;
    }
std::string RemoveSpace(std::string xml) {
   std:: string removed = "";
   std::string s, s1;
    int size = xml.length();
    int i = 0;

    while (i < size) {
        s = xml[i];
            s1 = xml[i + 1];

            if (s == " " && s1 == " ") {
                i += 2;
            }

            else if (s == "\r" || s == "\n" || s == "\t") {
                i++;
            }

            else {
                removed += s;
                i++;
            }

    }
    return removed;
}
// to map each character its huffman value
std::map<char, std::string> codes;
// To store the frequency of character of the input data
std::map<char, int> freq;
struct MinHeapNode {
    char data; // One of the input characters
    int freq; // Frequency of the character
    MinHeapNode *left, *right; // Left and right child

    MinHeapNode(char data, int freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};
// utility function for the priority queue
struct compare {
    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        return (l->freq > r->freq);
    }
};
// utility function to print characters along with
// there huffman value
// utility function to store characters along with
// there huffman value in a hash table, here we
// have C++ STL map
void storeCodes(struct MinHeapNode* root, std::string str)
{
    if (root == NULL)
        return;
    if (root->data != '$')
        codes[root->data] = str;
    storeCodes(root->left, str + "0");
    storeCodes(root->right, str + "1");
}

// STL priority queue to store heap tree, with respect
// to their heap root node value
std::priority_queue<MinHeapNode*, std::vector<MinHeapNode*>, compare>
    minHeap;

// function to build the Huffman tree and store it
// in minHeap
void HuffmanCodes(int size)
{
    struct MinHeapNode *left, *right, *top;
    for (std::map<char, int>::iterator v = freq.begin();
         v != freq.end(); v++)
        minHeap.push(new MinHeapNode(v->first, v->second));
    while (minHeap.size() != 1) {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        top = new MinHeapNode('$',
                              left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
    storeCodes(minHeap.top(), "");
}

// utility function to store map each character with its
// frequency in input string
void calcFreq(std::string str, int n)
{
    for (int i = 0; i < str.size(); i++)
        freq[str[i]]++;
}
void printCodes(struct MinHeapNode* root, std::string str)
{
    if (!root)
        return;
    //if (root->data != '$')
       // std::cout <<root->data << ": " << str << "\n";
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}
std::string decode_file(struct MinHeapNode* root, std::string s)
{
    std::string ans = "";
    struct MinHeapNode* curr = root;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;

        // reached leaf node
        if (curr->left == NULL and curr->right == NULL) {
            ans += curr->data;
            curr = root;
        }
    }
    // cout<<ans<<endl;
    return ans + '\0';
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()

{
    delete ui;
}

void MainWindow::on_Clear_btn_clicked()
{
    ui->input_text->clear();
    ui->output_text->clear();
 }
void MainWindow::on_actionClear_triggered()
{
    ui->input_text->clear();
    ui->output_text->clear();
}

void MainWindow::on_actionFull_Screen_triggered()
{

    if (isFullScreen()) {

        showNormal();
        }
    else {
        showFullScreen();
        ui->statusbar->showMessage("Click again on FullScreen to return to normal",5000);

    }
}
void MainWindow::on_actionExit_triggered()
{
   close();
}

void MainWindow::on_Browse_btn_clicked()
{
    ui->output_text->clear();
    //QFile file("/home/smile/GUI/sample.xml");
    QString extn = ".xml (*.xml)";
    QString file_name = QFileDialog::getOpenFileName(this,"Open a file", QDir::homePath(),extn);
    QFile file (file_name);
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"Warning","file not open");
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->input_text->setPlainText(text);
    file.close();
}
void MainWindow::on_actionbrowse_triggered()
{
    QString extn = ".xml (*.xml)";
    QString file_name = QFileDialog::getOpenFileName(this,"Open a file", QDir::homePath(),extn);
    QFile file (file_name);
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"Warning","file not open");
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->input_text->setPlainText(text);
    file.close();
}

void MainWindow::on_Save_btn_clicked()
{
     //ui->input_text->insertPlainText("hello ");
    QString file_name = QFileDialog::getSaveFileName(this,"Save As", QDir::homePath());
    QFile file(file_name);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"Warning","file not open");
    }
    else{
    QTextStream out(&file);
    QString text;
    if (ui->output_text->toPlainText() == ""){
    text = ui->input_text->toPlainText();}
    else{
    text = ui->output_text->toPlainText();}
    out<<text;
    file.flush();
    file.close();
    ui->statusbar->showMessage("Successfully saved",5000);
    }
}
void MainWindow::on_actionSave_as_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this,"Save As", QDir::homePath());
    QFile file(file_name);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"Warning","file not open");
    }
    else{
    QTextStream out(&file);
    QString text = ui->input_text->toPlainText();
    out<<text;
    file.flush();
    file.close();
    ui->statusbar->showMessage("Successfully saved",5000);
    }
}

void MainWindow::on_CheckErr_btn_clicked()
{
    ui->output_text->clear();
    QString qstr = ui->input_text->toPlainText();
    std:: string xml=qstr.toStdString();
    xml = RemoveSpace(xml);

    std::string s;
    std::string save;
    QMessageBox msgBox;
    int i =0;
    std::string sb;
    std::stack<std::string> d, c, u;
    bool closing = false;
    std::string saveO;
    std::string saveC;
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
               d.push(saveO);
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
                c.push(saveC);
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

                                //msgBox.setText("Message Box " +QString::fromStdString(" tag isn't closed" +(u.top())));
                                //cout<<u.top()<<" tag isn't closed"<<endl;
                                 ui -> output_text->append((QString::fromStdString(u.top())) + " tag isn't closed ");
                                u.pop();
                            }
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
                while (!u.empty())
                {
                    d.push(u.top());
                    u.pop();
                }
                if (!c.empty()) {
                   //std::cout<< c.top() << " tag isn't opened" <<endl;
                   ui -> output_text->append((QString::fromStdString(c.top())) + " tag isn't opened ");
                   //QMessageBox::warning(this,"Warning","tag isn't opened");
                    c.pop();
                }
            }
            else
            {
                //msgBox.setText("Message Box " +QString::fromStdString(" tag is true"));
                //ui -> output_text->append((QString::fromStdString(d.top())) + " tag is true ");
                //cout<<d.top()<<" Tag is true"<<endl;
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
        ui -> output_text->append((QString::fromStdString(d.top())) + " tag isn't closed ");
        //QMessageBox::warning(this,"Warning",QString(("tag isn't closed")));
        //cout<<d.top() <<" tag is not closed"<<endl;
        d.pop();
    }
    while (!c.empty())
    {
        ui -> output_text->append((QString::fromStdString(c.top())) + " tag isn't opened ");
        //QMessageBox::warning(this,"Warning","tag is not closed");
       // cout<<c.top() <<" tag is not closed"<<endl;
        c.pop();
    }
}
void MainWindow::on_actionCheck_for_Errors_triggered()
{
    ui->output_text->clear();
    QString qstr = ui->input_text->toPlainText();
    std:: string xml=qstr.toStdString();
    xml = RemoveSpace(xml);

    std::string s;
    std::string save;
    QMessageBox msgBox;
    int i =0;
    std::string sb,next;
//    std::string open_tag_name;
//    std::string close_tag_name;
    std::stack<std::string> d, c, u;
    bool closing = false;
    std::string saveO;
    std::string saveC;
    while(i<xml.size()){
        s = xml[i];
        if(s == "<"){
            sb = xml[i+1];
            if(sb!="/"){
               s = xml[i];
               //zawedt hena
               while(s!=">"){
                //w hena
                s = xml[i];
                next = xml[i+1];
//                if (s ==" "){
//                    save +=">";
//                    ui -> output_text->append((QString::fromStdString(save)) + " tag is missing the second tag");
//                    break;
//                }
//                else
                    if ( next == "<" ||next ==" "){
                    save += s;
                    break;

                }
                else{

                save += s;
                i++;
                }

               }
               closing = false;
               next = xml[i+1];
               if ((next =="<"|| next==" ")&& s!=">"){ui -> output_text->append((QString::fromStdString(save)) + " tag is incorrect");}
               else{
               saveO = save;
               saveO.erase(remove(saveO.begin() ,saveO.end(), '<'), saveO.end());
               saveO.erase(remove(saveO.begin() ,saveO.end(), '>'), saveO.end());
               d.push(saveO);
                }
            }
            else if(sb =="/"){

                while(s!=">"){
                    s = xml[i];
                    next = xml[i+1];
//                    if (s ==" "){
//                        save +=">";
//                        ui -> output_text->append((QString::fromStdString(save)) + " tag is missing the second tag");
//                        break;
//                    }
//                    else
                        if ( next == "<"||next ==" "){
                        save += s;
                        break;

                    }
                    else{

                    save += s;
                    i++;
                    }

                    //w hena
                  //  close_tag_name = close_tag_name + s;
//                    save += s;
//                    i++;
                }
                closing = true;
                next = xml[i+1];
                if ((next =="<"|| next==" ")&& s!=">"){ui -> output_text->append((QString::fromStdString(save)) + " tag is incorrect");}

                saveC = save;
                saveC.erase(remove(saveC.begin() ,saveC.end(), '<'), saveC.end());
                saveC.erase(remove(saveC.begin() ,saveC.end(), '/'), saveC.end());
                saveC.erase(remove(saveC.begin() ,saveC.end(), '>'), saveC.end());
                c.push(saveC);
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
                                 ui -> output_text->append((QString::fromStdString(u.top())) + " tag isn't closed ");
                                u.pop();
                            }
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
                while (!u.empty())
                {
                    d.push(u.top());
                    u.pop();
                }
                if (!c.empty()) {
                   ui -> output_text->append((QString::fromStdString(c.top())) + " tag isn't opened ");
                    c.pop();
                }
            }
            else
            {
                //ui -> output_text->append((QString::fromStdString(d.top())) + " tag is true ");
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
        ui -> output_text->append((QString::fromStdString(d.top())) + " tag isn't closed ");
        d.pop();
    }
    while (!c.empty())
    {
        ui -> output_text->append((QString::fromStdString(c.top())) + " tag isn't opened ");
        c.pop();
    }

}

void MainWindow::on_Correct_btn_clicked()
{
    ui->output_text->clear();
    int i = 0;
        std::string temp, temp1, temp2, Tag, open_tag_name, closed_tag_name, correct;
        std::stack<std::string> open_st, closed_st, temp_st;
        std::vector<std::string> xml;
        QString qstr = ui->input_text->toPlainText();
        std:: string XML=qstr.toStdString();
        //XML = RemoveSpace(XML);
        xml = split(XML," ");
        std::string corrected = correct_XML(xml);
        ui->output_text->insertPlainText(QString::fromStdString(corrected));
//        //XML.erase(std::remove_if(XML.begin(), XML.end(), ::isspace));
//        //XML.replace(XML.size()-1,2,"");
//       //qDebug()<< QString::fromStdString(XML);
//        while(i < XML.size()){
//            temp1 = XML[i];
//            if(temp1 == "<"){
//                temp2 = XML[i+1];
//                if(temp2 != "/"){
//                    temp1 = XML[i];
//                    while(temp1 != ">"){
//                        temp1 = XML[i];
//                        Tag += temp1;
//                        i++;
//                    }
//                    open_tag_name = Tag;
//                    open_tag_name.erase(remove(open_tag_name.begin(), open_tag_name.end(),'<'), open_tag_name.end());
//                    open_tag_name.erase(remove(open_tag_name.begin(), open_tag_name.end(),'>'), open_tag_name.end());
//                    open_st.push(open_tag_name);
//                    if(!open_st.empty()&& !closed_st.empty()){
//                        if(closed_st.top() == open_st.top()){
//                            correct += Tag;
//                            temp = closed_st.top();
//                            temp.insert(0, "<");
//                            temp.insert(1, "/");
//                            int x = temp.length();
//                            temp.insert(x, ">");
//                            open_st.pop();
//                            closed_st.pop();
//                            correct += temp;
//                            //qDebug() << QString::fromStdString(correct);
//                        }
//                        else{correct += Tag;}
//                    }
//                    else{correct += Tag;}
//                }
//                else if(temp2 == "/"){
//                    while(temp1 != ">"){
//                        temp1 = XML[i];
//                        Tag += temp1;
//                        i++;
//                    }
//                    closed_tag_name = Tag;
//                    closed_tag_name.erase(remove(closed_tag_name.begin(), closed_tag_name.end(),'<'), closed_tag_name.end());
//                    closed_tag_name.erase(remove(closed_tag_name.begin(), closed_tag_name.end(),'>'), closed_tag_name.end());
//                    closed_tag_name.erase(remove(closed_tag_name.begin(), closed_tag_name.end(),'/'), closed_tag_name.end());
//                    closed_st.push(closed_tag_name);
//                    if(!open_st.empty()&& !closed_st.empty()){
//                        if(closed_st.top() != open_st.top()){
//                            while(!closed_st.empty()){
//                                temp_st.push(closed_st.top());
//                                closed_st.pop();
//                            }
//                        }
//                        else if(closed_st.top() == open_st.top()){
//                            while(!open_st.empty()&& !closed_st.empty()){
//                                temp = closed_st.top();
//                                temp.insert(0, "<");
//                                temp.insert(1, "/");
//                                int x = temp.length();
//                                temp.insert(x, ">");
//                                closed_st.pop();
//                                open_st.pop();
//                                correct += temp;
//                            }
//                        }
//                    }
//                }
//            }
//            else{
//                while(temp1 != "<"){
//                    Tag += temp1;
//                    i++;
//                    temp1 = XML[i];
//                }
//                correct += Tag;
//            }
//            Tag = "";
//            open_tag_name = "";
//            closed_tag_name = "";
//            temp = "";
//            while(!temp_st.empty()){
//                closed_st.push(temp_st.top());
//                temp_st.pop();
//            }
//        }
//        //ana eli mzawedaha de
//        while(!open_st.empty()&& closed_st.empty()){
//            temp = open_st.top();
//            temp.insert(0, "<");
//            temp.insert(1, "/");
//            int x = temp.length();
//            temp.insert(x, ">");
//            closed_st.push(temp);
//            closed_st.pop();
//            open_st.pop();
//            correct += temp;
//        }
//        ui->output_text->insertPlainText(QString::fromStdString(correct));
//        QMessageBox::information(this,"","Corrected");
//       // QMessageBox::warning(this,"Success","Corrected");
//        //cout << correct << endl;
}
void MainWindow::on_actionCorrect_Errors_triggered()
{
    ui->output_text->clear();
    int i = 0;
        std::string temp, temp1, temp2, Tag, open_tag_name, closed_tag_name, correct,next,last;
        std::stack<std::string> open_st, closed_st, temp_st;
        //QVector<std::string> blabla ;
        QString qstr = ui->input_text->toPlainText();
        std:: string XML=qstr.toStdString();
        //std::vector<std::string> xml;
        XML = RemoveSpace(XML);

      //  xml_corrector(XML);
        //XML.erase(std::remove_if(XML.begin(), XML.end(), ::isspace));
        //XML.replace(XML.size()-1,2,"");
       //qDebug()<< QString::fromStdString(XML);
        while(i < XML.size()){
            temp1 = XML[i];
            if(temp1 == "<"){
                temp2 = XML[i+1];
                if(temp2 != "/"){
                    temp1 = XML[i];
                    while(temp1 != ">"){
                        temp1 = XML[i];
                        next = XML[i+1];
//                        last = Tag.back();
                        if (temp1 ==" " && (next!="<")){

                            Tag +=">";
                            break;
                        }
                        else if ( next == "<"){
                            Tag += temp1;
                            break;

                        }
                        else{

                        Tag += temp1;
                        i++;
                        }
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
                            //qDebug() << QString::fromStdString(correct);
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
        //ana eli mzawedaha de
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
        ui->output_text->insertPlainText(QString::fromStdString(correct));
        QMessageBox::information(this,"","Corrected");
        //QMessageBox::warning(this,"YAY","Corrected");
        //cout << correct << endl;
}

void MainWindow::on_Minify_btn_clicked()
{
    QString qstr = ui->input_text->toPlainText();
    std:: string xml=qstr.toStdString();
    xml = RemoveSpace(xml);
    ui->output_text->setText(QString::fromStdString(xml));
}
void MainWindow::on_actionMinify_triggered()
{
    QString qstr = ui->input_text->toPlainText();
    std:: string xml=qstr.toStdString();
    xml = RemoveSpace(xml);
    ui->output_text->setText(QString::fromStdString(xml));
}

void MainWindow::on_Convert_btn_clicked()
{
    QString qstr = ui->input_text->toPlainText();
    std:: string s=qstr.toStdString();
    s = RemoveSpace(s);
    int size = s.length();
        std::string json = "{";
        std::string append = "*";
        std::string w, word = "";
        //bool save = false;
        //i for xml length, j for json length, x for repeated tags
        int i = 0, j = 1, x = 0;
        //stk for opening tags, tag for opening tags but they are poped when they are closed, brackets for({,])
        std::stack<std::string> stack_open_tags, tag, brackets;
        //it's true if opening tag,and false if closing
        std::stack<bool> opening_tag;
        //tags holds last closed tag, bracket holds last printed bracket
        std::string last_closed_tag, bracket;
        //saves value of x
        std::stack<int> ind;
        while (i < size) {
            w = s[i];
            if (w == "\r" || w == "\n") {
            }

            //checking if it's tag or data to be printed
            if (w == "<") {
                i++;
                w = s[i];
                if (w != "/") { //if opening tag
                    while (w != ">") {
                        word += w;
                        i++;
                        w = s[i];
                    }
                    //if more than one <topic> repeated in scope of <topics>, delete topic from json
                    if (word == last_closed_tag) {
                        json.erase(x - ((brackets.size() + 1)) - 2, word.length() + 6 + ((brackets.size() + 1))); //6 bec ({ \n " " : ), x->"
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
                else {  //if closing tag
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
                        std::string currentWord;
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
                        std::string back;
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
        ui->output_text->setText(QString::fromStdString(json));
    }
void MainWindow::on_actionConver_to_Json_triggered()
{
    QString qstr = ui->input_text->toPlainText();
    std:: string s=qstr.toStdString();
    s = RemoveSpace(s);
    int size = s.length();
        std::string json = "{";
        std::string append = "*";
        std::string w, word = "";
        //bool save = false;
        //i for xml length, j for json length, x for repeated tags
        int i = 0, j = 1, x = 0;
        //stk for opening tags, tag for opening tags but they are poped when they are closed, brackets for({,])
        std::stack<std::string> stack_open_tags, tag, brackets;
        //it's true if opening tag,and false if closing
        std::stack<bool> opening_tag;
        //tags holds last closed tag, bracket holds last printed bracket
        std::string last_closed_tag, bracket;
        //saves value of x
        std::stack<int> ind;
        while (i < size) {
            w = s[i];
            if (w == "\r" || w == "\n") {
            }

            //checking if it's tag or data to be printed
            if (w == "<") {
                i++;
                w = s[i];
                if (w != "/") { //if opening tag
                    while (w != ">") {
                        word += w;
                        i++;
                        w = s[i];
                    }
                    //if more than one <topic> repeated in scope of <topics>, delete topic from json
                    if (word == last_closed_tag) {
                        json.erase(x - ((brackets.size() + 1)) - 2, word.length() + 6 + ((brackets.size() + 1))); //6 bec ({ \n " " : ), x->"
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
                else {  //if closing tag
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
                        std::string currentWord;
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
                        std::string back;
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
        ui->output_text->setText(QString::fromStdString(json));
}

void MainWindow::on_Compress_btn_clicked()
{
    QString qstr = ui->input_text->toPlainText();
    std:: string str=qstr.toStdString();
    str = RemoveSpace(str);
    std::string encodedString;
        calcFreq(str, str.length());
        HuffmanCodes(str.length());
        //std::cout << "Character With there Frequencies:\n";
        //for (auto v = codes.begin(); v != codes.end(); v++)
          //  std::cout << v->first << ' ' << v->second <<"\n";

        for (auto i : str)
            encodedString += codes[i];
        ui->output_text->setPlainText(QString::fromStdString(encodedString));
        //std::cout << "\nEncoded Huffman data:\n" << encodedString ;
}
void MainWindow::on_actionCompress_triggered()
{
    QString qstr = ui->input_text->toPlainText();
    std:: string str=qstr.toStdString();
    str = RemoveSpace(str);
    std::string encodedString;
        calcFreq(str, str.length());
        HuffmanCodes(str.length());
        //std::cout << "Character With there Frequencies:\n";
       // for (auto v = codes.begin(); v != codes.end(); v++)
          //  std::cout << v->first << ' ' << v->second <<"\n";

        for (auto i : str)
            encodedString += codes[i];
        ui->output_text->setPlainText(QString::fromStdString(encodedString));
        //std::cout << "\nEncoded Huffman data:\n"<< encodedString ;
}

void MainWindow::on_decompress_btn_clicked()
{
    QString qstr = ui->input_text->toPlainText();
    std:: string str=qstr.toStdString();
    str = RemoveSpace(str);
    std::string  decodedString;
    decodedString= decode_file(minHeap.top(), str);
       //std::cout << "\nDecoded Huffman Data:\n"<< decodedString ;
       ui->output_text->setPlainText(QString::fromStdString(decodedString));

}
void MainWindow::on_actionDecompress_triggered()
{
    QString qstr = ui->input_text->toPlainText();
    std:: string str=qstr.toStdString();
    str = RemoveSpace(str);
    std::string  decodedString;
    decodedString= decode_file(minHeap.top(), str);
      // std::cout << "\nDecoded Huffman Data:\n"  << decodedString ;
       ui->output_text->setPlainText(QString::fromStdString(decodedString));
}



void MainWindow::on_Prettify_btn_clicked()
{
    QString qstr = "";
    if (ui->output_text->toPlainText() == ""){
    qstr = ui->input_text->toPlainText();}
    else{
    qstr = ui->output_text->toPlainText();}
    std:: string xml=qstr.toStdString();
    xml = RemoveSpace(xml);
    ui->output_text->clear();
   // std::string xml = "<users><user><id>1</id><name>Jumana</name></user></users>";
    std::string s;
    int ind =0;
    std:: string str="";
    int openflag = 0;
    int closeflag = 0;
    std::string save;
    std::string sb;
    for (unsigned int i = 0; i < xml.size();) {
        s = xml[i];
        sb = xml[i+1];
        if(s == "<" && sb!="/"){
            save = "";
            //If is not a closing tag!!
            while(s!=">"){
                s = xml[i];
                save +=s;
                i++;
                }
            openflag++;
            closeflag = 0;
            if (openflag > 1) {
                ind++;
                }
            for (int j = 0; j < ind; j++) {
                str += "    ";		//print tab
                }
            str += save + "\n";	//print output
        }
        else if(s == "<" && sb == "/"){
            save = "";
            //If it is a closing tag!!
            while(s!=">"){
                s = xml[i];
                save +=s;
                i++;
                }
            closeflag++;
            openflag = 0;
            if (closeflag > 1) {
                ind--;
            }
            for (int j = 0; j < ind; j++) {
                str += "    ";		//print tab
            }
            str += save + "\n";	//print output

        }
        else{
            save = "";
            sb=" ";
            while(sb!="<"){
                s = xml[i];
                sb= xml[i+1];
                save +=s;
                i++;
                }
            for (int j = 0; j < ind; j++) {
                str += "    ";		//print tab
                }
             str += save + "\n";
        }
        }
    ui->output_text->setPlainText(QString::fromStdString(str));
}


void MainWindow::on_Graph_btn_clicked()
{

}


void MainWindow::on_actionPrettify_triggered()
{
    QString qstr = "";
    if (ui->output_text->toPlainText() == ""){
    qstr = ui->input_text->toPlainText();}
    else{
    qstr = ui->output_text->toPlainText();}
    std:: string xml=qstr.toStdString();
    xml = RemoveSpace(xml);
    ui->output_text->clear();
   // std::string xml = "<users><user><id>1</id><name>Jumana</name></user></users>";
    std::string s;
    int ind =0;
    std:: string str="";
    int openflag = 0;
    int closeflag = 0;
    std::string save;
    std::string sb;
    for (unsigned int i = 0; i < xml.size();) {
        s = xml[i];
        sb = xml[i+1];
        if(s == "<" && sb!="/"){
            save = "";
            //If is not a closing tag!!
            while(s!=">"){
                s = xml[i];
                save +=s;
                i++;
                }
            openflag++;
            closeflag = 0;
            if (openflag > 1) {
                ind++;
                }
            for (int j = 0; j < ind; j++) {
                str += "    ";		//print tab
                }
            str += save + "\n";	//print output
        }
        else if(s == "<" && sb == "/"){
            save = "";
            //If it is a closing tag!!
            while(s!=">"){
                s = xml[i];
                save +=s;
                i++;
                }
            closeflag++;
            openflag = 0;
            if (closeflag > 1) {
                ind--;
            }
            for (int j = 0; j < ind; j++) {
                str += "    ";		//print tab
            }
            str += save + "\n";	//print output

        }
        else{
            save = "";
            sb=" ";
            while(sb!="<"){
                s = xml[i];
                sb= xml[i+1];
                save +=s;
                i++;
                }
            for (int j = 0; j < ind; j++) {
                str += "    ";		//print tab
                }
             str += save + "\n";
        }
        }
    ui->output_text->setPlainText(QString::fromStdString(str));
}

