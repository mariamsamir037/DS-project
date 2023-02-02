#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QInputDialog>
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

#define MAXASCII 256
#define XML_FORMAT 0
#define JSON_FORMAT 1
#define PRIMITIVE 2
#define ARRAY 3
#define OBJECT 4
#define  ILLUSION -1


typedef unsigned long long ull;
#define USER_ID 0
#define FOLLOWER_ID 1
#define NAME 2
#define BODY 3
#define TOPICS 4
#define FOLLOWERS 5
#define POSTS 6
#define MAXASCII 256
// for color coding
#define ID_COLOR 0
#define USER_COLOR 1
#define USERS_COLOR 2
#define FOLLOWER_COLOR 3
#define FOLLOWERS_COLOR 4
#define POST_COLOR 5
#define POSTS_COLOR 6
#define NAME_COLOR 7
#define TOPIC_COLOR 8
#define TOPICS_COLOR 9
#define BODY_COLOR 10
namespace Entity
{
    using namespace std;
    typedef unsigned long long ull;
    //the xml handling class
    class XmlParser {
    public:
        class Follower {
        public:
            string id;
            vector<string> idVector;
            void clear();
            void setFollower();
        };
        template<class T, class U>
        class myPair {
        public:
            T first;
            U second;
            myPair(T first, U second);
            myPair();
            void setPairValues(T first, U second);
        };
        class Post {
        public:
            vector<int>postOrder;
            string s = "";
            myPair<int, string> body = createPair(-1, s);
            myPair<int, vector<string>> topics = createPair(-1, vector<string>{});
            vector<myPair<int, string>> bodyVector;
            vector<myPair<int, vector<string>>> topicsVector;
            void clear();
            void setPost();
        };
        class User {
        public:
            vector<int> userOrder;
            string s = "";
            myPair<int, string> id = createPair(-1, s);
            myPair<int, string> name = createPair(-1, s);
            myPair<int, vector<Post>> posts = createPair(-1, vector<Post>{});
            myPair<int, vector<Follower>> followers = createPair(-1, vector<Follower>{});
            vector<myPair<int, string>>idVector;
            vector<myPair<int, string>>nameVector;
            vector<myPair<int, vector<Post>>> postsVector;
            vector<myPair<int, vector<Follower>>> followersVector;
            int following;
            void clear();
            void setUser();
        };
        vector<myPair<int, int>>errors;
        stack<myPair<myPair<string, int>, myPair< int, int>>> tagStack;  //{tag name, line index} and {start index,end index}
        vector<vector<myPair<int, int>>> colors;
        vector<User> users;
        string json;
        string xml;
        int xmlcompressedsize;
        string xmlCommpressed;
        string xmlFormatted;
        vector<string>lines;
        string reformatted;
        string temp;
        int freq[MAXASCII] = { 0 };
        vector<myPair<string, string>> pairs;
        template<class T, class U>
        static myPair<T, U> createPair(T first, U second);
        template<class T>
        static void setField(myPair<int, T>& target, vector< myPair<int, T> >& list);
        bool isStartTag(string tag);
        string getData(string& xml, int& counter);
        void checkStack();
        string trimLine(string input);
        string getTagFrame(string& xml, int& pointer);
        void deleteNewLines();
        void extractData();
        void toLines();
        void fillColors();
        void getXmlFormatted();
        static string getTagName(string tag);
        static string getSpace(int numOfSpaces);
        vector<string> splitter(string s, int size);
        myPair<int, string> BiToHex(string s);
        string HexToBi(myPair<int, string>encoded);
        static bool compareByLength(const myPair<string, string>& a, const myPair<string, string>& b);
        void sortingTree();
        string EncryptData(int freq[], string data);
        string encode(string data);
        string decode(string data);
        static bool isSubString(string target, string base);
        static bool isNumber(string number);
        static int isItemFound(int item, vector<int>& itemVec);
        static bool compareUsers(User user1, User user2);
        string searchPosts(string keyWord);
        string getMutualFollowers(string ID1, string ID2);
        string recommendPeople(string id);
        string doNetworkAnalysis();
        string MostActive();
    };
}

using namespace Entity;
std::vector<std::string> XmlParser::splitter(std::string s, int size) {
    vector<string>chars;
    while (s.size() > 0) {
        chars.push_back(s.substr(0, size));
        s.erase(0, size);
    }
    return chars;
}
std::string XmlParser::getSpace(int numOfSpaces) {
    string spaces;
    for (int i = 0; i < numOfSpaces; ++i)
        spaces.push_back(' ');
    return spaces;
}
std::string XmlParser::getTagName(string tag) {
    string name;
    for (int i = 0; i < tag.size(); ++i)
        if (tag[i] != '<' && tag[i] != '>' && tag[i] != '/')
            name.push_back(tag[i]);
    return name;
}

XmlParser::myPair<int,string> XmlParser::BiToHex(std::string s) {
    int i =0;
    while(s.size()%5 !=0){
        s.append("0");
        i++;

    }

    std::vector<std::string>chars = splitter(s, 5);
    std::string hex = "";
    for (std::string i : chars) {
        if (i == "00000") {
            hex += '0';
        }
        else if (i == "00001") {
            hex += '1';
        }
        else if (i == "00010") {
            hex += '2';
        }
        else if (i == "00011") {
            hex += '3';
        }
        else if (i == "00100") {
            hex += '4';
        }
        else if (i == "00101") {
            hex += '5';
        }
        else if (i == "00110") {
            hex += '6';
        }
        else if (i == "00111") {
            hex += '7';
        }
        else if (i == "01000") {
            hex += '8';
        }
        else if (i == "01001") {
            hex += '9';
        }
        else if (i == "01010") {
            hex += 'A';
        }
        else if (i == "01011") {
            hex += 'B';
        }
        else if (i == "01100") {
            hex += 'C';
        }
        else if (i == "01101") {
            hex += 'D';
        }
        else if (i == "01110") {
            hex += 'E';
        }
        else if (i == "01111") {
            hex += 'F';
        }
        else if (i == "10000") {
            hex += 'G';
        }
        else if (i == "10001") {
            hex += 'H';
        }
        else if (i == "10010") {
            hex += 'I';
        }
        else if (i == "10011") {
            hex += 'J';
        }
        else if (i == "10100") {
            hex += 'K';
        }
        else if (i == "10101") {
            hex += 'L';
        }
        else if (i == "10110") {
            hex += 'M';
        }
        else if (i == "10111") {
            hex += 'N';
        }
        else if (i == "11000") {
            hex += 'O';
        }
        else if (i == "11001") {
            hex += 'P';
        }
        else if (i == "11010") {
            hex += 'Q';
        }
        else if (i == "11011") {
            hex += 'R';
        }
        else if (i == "11100") {
            hex += 'S';
        }
        else if (i == "11101") {
            hex += 'T';
        }
        else if (i == "11110") {
            hex += 'U';
        }
        else if (i == "11111") {
            hex += 'V';
        }
    }
    myPair<int, string> encoded = createPair(i, hex);
    return encoded;
}
std::string XmlParser::HexToBi(XmlParser::myPair<int,string> encoded){
    string s= encoded.second;
    int i = encoded.first;

    string bi = "";
    for (char i : s) {
        if (i == '0') {
            bi += "00000";
        }
        else if (i == '1') {
            bi += "00001";
        }
        else if (i == '2') {
            bi += "00010";
        }
        else if (i == '3') {
            bi += "00011";
        }
        else if (i == '4') {
            bi += "00100";
        }
        else if (i == '5') {
            bi += "00101";
        }
        else if (i == '6') {
            bi += "00110";
        }
        else if (i == '7') {
            bi += "00111";
        }
        else if (i == '8') {
            bi += "01000";
        }
        else if (i == '9') {
            bi += "01001";
        }
        else if (i == 'A') {
            bi += "01010";
        }
        else if (i == 'B') {
            bi += "01011";
        }
        else if (i == 'C') {
            bi += "01100";
        }
        else if (i == 'D') {
            bi += "01101";
        }
        else if (i == 'E') {
            bi += "01110";
        }
        else if (i == 'F') {
            bi += "01111";
        }
        else if (i == 'G') {
            bi += "10000";
        }
        else if (i == 'H') {
            bi += "10001";
        }
        else if (i == 'I') {
            bi += "10010";
        }
        else if (i == 'J') {
            bi += "10011";
        }
        else if (i == 'K') {
            bi += "10100";
        }
        else if (i == 'L') {
            bi += "10101";
        }
        else if (i == 'M') {
            bi += "10110";
        }
        else if (i == 'N') {
            bi += "10111";
        }
        else if (i == 'O') {
            bi += "11000";
        }
        else if (i == 'P') {
            bi += "11001";
        }
        else if (i == 'Q') {
            bi += "11010";
        }
        else if (i == 'R') {
            bi += "11011";
        }
        else if (i == 'S') {
            bi += "11100";
        }
        else if (i == 'T') {
            bi += "11101";
        }
        else if (i == 'U') {
            bi += "11110";
        }
        else if (i == 'V') {
            bi += "11111";
        }
    }
    while (i!=0){
        bi= bi.substr(0,bi.size()-1);
        i--;
    }
    return bi;
}

bool XmlParser::compareByLength(const myPair<string, string>& a, const myPair<string, string>& b) {
    return a.second.size() < b.second.size();
}

bool XmlParser::isSubString(string target, string base)
{
    int targetIndex = 0;
    if (target.size() > base.size())
        return 0;
    for (int i = 0; i < base.size() - target.size() + 1; ++i) {
        if (base[i] == target[targetIndex]) {
            for (int j = i; targetIndex < target.size(); ++j) {
                if (base[j] != target[targetIndex]) {
                    targetIndex = 0;
                    i = j;
                    break;
                }
                if (base[j] == target[targetIndex] && targetIndex == target.size() - 1)
                    return 1;
                ++targetIndex;
            }
        }
    }
    return 0;
}
bool XmlParser::isNumber(string number)
{
    for (auto c : number)
        if (!(c - '0' >= 0 && c - '0' <= 9))
            return 0;
    return 1;
}
int XmlParser::isItemFound(int item, vector<int>& itemVec)
{
    int start = 0, end = itemVec.size() - 1;
    while (start <= end) {
        int mid = (end - start) / 2 + start;
        if (itemVec[mid] == item)
            return mid;
        else if (itemVec[mid] > item)
            end = mid - 1;
        else
            start = mid + 1;
    }
    return -1;
}

bool XmlParser::compareUsers(User user1, User user2)
{
    return stoi(user1.id.second) <= stoi(user2.id.second);
}
string XmlParser::searchPosts(string keyWord)
{
    int postNumber = 1;
    string postList;
    for (auto user : users) {
        for (auto post : user.posts.second) { //looping through the body of all posts of a user
            if (isSubString(keyWord, post.body.second)) {
                postList.append("Post #" + to_string(postNumber++) + ":\n" + "BY: " + user.name.second + " (" + user.id.second + ")" + "\n" + post.body.second + "\n_________\n");
                break;
            }
            for (auto topic : post.topics.second)
                if (isSubString(keyWord, topic)) {
                    postList.append("Post #" + to_string(postNumber++) + ":\n" + "BY: " + user.name.second + " (" + user.id.second + ")" + "\n" + post.body.second + "\n_________\n");
                    break;
                }
        }
    }
    if (postList.empty())
        postList = "NO POSTS FOUND :(";
    return postList;
}

string XmlParser::getMutualFollowers(string ID1, string ID2)
{
    if (!isNumber(ID1) && !isNumber(ID2))
        return "INVALID ID FOR USER 1 AND USER 2";
    else if (!isNumber(ID1) && isNumber(ID2))
        return "INVALID ID FOR USER 1";
    else if (isNumber(ID1) && !isNumber(ID2))
        return "INVALID ID FOR USER 2";
    else { //work starts here
        if (ID1 == ID2)
            return "PLEASE ENTER DIFFERENT USERS' IDS";
        string usersList;
        vector<int> followers1, followers2;
        bool firstUserFound = 0, secondUserFound = 0;
        for (auto user : users) { //filling the vectors
            if (user.id.second == ID1) {
                firstUserFound = 1;
                for (auto follower : user.followers.second)
                    followers1.push_back(stoi(follower.id));
            }
            else if (user.id.second == ID2) {
                secondUserFound = 1;
                for (auto follower : user.followers.second)
                    followers2.push_back(stoi(follower.id));
            }
        }
        if (!firstUserFound && secondUserFound)
            return "USER 1 DOES NOT EXIST ON THE NETWORK";
        else if (firstUserFound && !secondUserFound)
            return "USER 2 DOES NOT EXIST ON THE NETWORK";
        else if (!firstUserFound && !secondUserFound)
            return "USER 1 AND USER 2 DON'T EXIST ON THE NETWORK";
        sort(followers1.begin(), followers1.end());
        sort(followers2.begin(), followers2.end());
        for (auto follower : followers1)
            if (isItemFound(follower, followers2) != -1)
                usersList.append(to_string(follower) + " ");
        return usersList.empty() ? "NO MUTUAL FOLLOWERS FOUND :(" : "Mutual users' IDs: \n" + usersList;
    }
}
string XmlParser::recommendPeople(string id)
{
    if (!isNumber(id))
        return "INVALID USER ID";
    vector<int>usersIds, toFollowIds;
    string toFollow;
    for (auto user : users)
        usersIds.push_back(stoi(user.id.second));
    int userIndex = isItemFound(stoi(id), usersIds);
    if (userIndex == -1)
        return "USER DOES NOT EXIST ON THE NETWORK";
    //getting the followers of followers
    for (auto follower : users[userIndex].followers.second) {
        int followerId = stoi(follower.id);
        int followerIndex = isItemFound(followerId, usersIds);
        for (auto followerOfFollower : users[followerIndex].followers.second)
            if (followerOfFollower.id != id)
                toFollowIds.push_back(stoi(followerOfFollower.id));
    }
    sort(toFollowIds.begin(), toFollowIds.end());
    toFollowIds.push_back(-1);
    for (int i = 0; i < toFollowIds.size() - 1; ++i)
        if (toFollowIds[i] != toFollowIds[i + 1])
            toFollow.append(to_string(toFollowIds[i]) + " ");
    return toFollow.empty() ? "No recommendations found :(" : "The list of recommended to follow: \n" + toFollow;
}

string XmlParser::doNetworkAnalysis()
{
    string influencerString;
    int influncerFollowers = -1;
    for (auto user : users) {
        influncerFollowers = max(influncerFollowers, (int)user.followers.second.size());
    }
    for (auto user : users) {
        if (user.followers.second.size() == influncerFollowers)
            influencerString.append("User Name: " + user.name.second + " - User ID: " + user.id.second + "\n");
        }
    influencerString = (influncerFollowers == -1) ? "NO ONE IS FOLLOWING ANYONE" : "The List of most followed people with "
        + to_string(influncerFollowers) + " follower/s :\n" + influencerString;
    return influencerString ;
}
string XmlParser::MostActive()
{
    string Following_string;
    string writerString;
    int writerPosts = -1;
    int Following = -1;
    for (int i = 0; i < users.size(); i++) {
        for (int j = 0; j < users.size(); j++){
            if (stoi(users[i].id.second) != stoi(users[j].id.second)){
                for(auto follower : users[j].followers.second){
                    if (stoi(follower.id) == stoi(users[i].id.second))
                            users[i].following++;
                }
            }
        }
        writerPosts = max(writerPosts, (int)users[i].posts.second.size());
        Following = max(Following, users[i].following);

    }
    for(auto user: users){
        if (user.following == Following)
            Following_string.append("User Name: " + user.name.second + " - User ID: " + user.id.second + "\n");
       if (user.posts.second.size() == writerPosts)
           writerString.append("User Name: " + user.name.second + " - User ID: " + user.id.second + "\n");
    }
    writerString = (writerPosts == -1) ? "NO ONE WROTE POSTS" : "The List of people with the highest number of posts with "
        + to_string(writerPosts) + " post/s :\n" + writerString;
    Following_string = (Following == -1) ? "NO ONE IS FOLLOWING ANYONE" : "The List of most following people with " + to_string(Following) + " following/s :\n" + Following_string;
    return  writerString + "____\n" + Following_string ;
}

void XmlParser::extractData() {
    users.clear();
    vector<Post> posts;
    vector<Follower> followers;
    vector<string> topics;
    int order = 0;
    int innerOrder = 0;
    int followersOder = -1;
    int postsOrder = -1;
    int topicsOrder = -1;
    bool followerHasId = 0;
    User user;
    Post post;
    Follower follower;
    bool inFollower = 0;
    bool inPost = 0;
    bool inPosts = 0;
    bool inFollowers = 0;
    bool inTopics = 0;
    bool inUser = 0;
    user.following=0;
    xmlcompressedsize = xmlCommpressed.size();
    for (int i = 0; i < xmlCommpressed.size(); ++i) {
        if ((xmlCommpressed[i] == '<' && (i == 0 || xmlCommpressed[i - 1] != '\\' || (i >= 2 && xmlCommpressed[i - 1] == '\\' && xmlCommpressed[i - 2] == '\\')))) {
            string tagFrame = getTagFrame(xmlCommpressed, i);
            string tagName = getTagName(tagFrame);
            if (isStartTag(tagFrame)) {
                if (tagName == "name" || tagName == "body" || tagName == "topic" || tagName == "id") {
                    ++i;
                    string data = getData(xmlCommpressed, i);
                    getTagFrame(xmlCommpressed, i);
                    if (inUser && !inPosts && !inFollowers) {
                        if (tagName == "name") {
                            user.nameVector.push_back(createPair(order, data));
                            ++order;
                        }
                        else if (tagName == "id") {
                            user.idVector.push_back(createPair(order, data));
                            ++order;
                        }
                    }
                    else if (inUser && inFollower) {
                        if (tagName == "id") {
                            follower.idVector.push_back(data);
                            followerHasId = 1;
                        }
                    }
                    else if (inUser && inPost && !inTopics) {
                        if (tagName == "body") {
                            post.bodyVector.push_back(createPair(innerOrder, data));
                            ++innerOrder;
                        }
                    }
                    else if (inTopics) {
                        if (tagName == "topic") {
                            topics.push_back(data);
                        }
                    }
                }
                else if (tagName == "user") {
                    if (!inUser) {
                        order = 0;
                        followersOder = -1;
                        postsOrder = -1;
                        user.clear();
                        inUser = 1;
                    }
                }
                else if (tagName == "followers") {
                    if (!inFollowers) {
                        followersOder = order;
                        ++order;
                        inFollowers = 1;
                        followers.clear();
                    }
                }
                else if (tagName == "topics") {
                    if (!inTopics) {
                        inTopics = 1;
                        topicsOrder = innerOrder;
                        ++innerOrder;
                        topics.clear();
                    }
                }
                else if (tagName == "posts") {
                    if (!inPosts) {
                        inPosts = 1;
                        postsOrder = order;
                        posts.clear();
                        ++order;
                    }
                }
                else if (tagName == "follower") {
                    if (!inFollower) {
                        follower.clear();
                        inFollower = 1;
                    }
                }
                else if (tagName == "post") {
                    if (!inPost) {
                        innerOrder = 0;
                        post.clear();
                        inPost = 1;
                        topicsOrder = -1;
                    }
                }
            }
            else {
                if (tagName == "user") {
                    if (inUser) {
                        inUser = 0;
                        users.push_back(user);
                    }
                }
                else if (tagName == "followers") {
                    if (inFollowers) {
                        inFollowers = 0;
                        user.followersVector.push_back(createPair(followersOder, followers));
                    }
                }
                else if (tagName == "topics") {
                    if (inTopics) {
                        inTopics = 0;
                        post.topicsVector.push_back(createPair(topicsOrder, topics));
                    }
                }
                else if (tagName == "posts") {
                    if (inPosts) {
                        inPosts = 0;
                        user.postsVector.push_back(createPair(postsOrder, posts));
                    }
                }
                else if (tagName == "follower") {
                    if (inFollower) {
                        inFollower = 0;
                        if (followerHasId) {
                            followers.push_back(follower);
                            followerHasId = 0;
                        }
                    }
                }
                else if (tagName == "post") {
                    if (inPost) {
                        inPost = 0;
                        posts.push_back(post);
                    }
                }
            }
        }
    }
    for (int i = 0; i < users.size(); ++i) {
        users[i].setUser();
        for (int j = 0; j < users[i].posts.second.size(); ++j)
            users[i].posts.second[j].setPost();
        for (int j = 0; j < users[i].followers.second.size(); ++j)
            users[i].followers.second[j].setFollower();
    }
    sort(users.begin(), users.end(), compareUsers);
}
void XmlParser::fillColors() {
    colors.clear();
    colors.resize(11);
    for (int i = 0; i < xmlFormatted.size(); ++i) {
        if (xmlFormatted[i] == '<' && (i == 0 || xmlFormatted[i - 1] != '\\' || (i >= 2 && xmlFormatted[i - 1] == '\\' && xmlFormatted[i - 2] == '\\'))) { //markd the start of a tag
            int start = i;
            string tagFrame = getTagFrame(xmlFormatted, i);
            int end = i;
            string tagName = getTagName(tagFrame);
            int target = -1;
            if (tagName == "users")
                target = USERS_COLOR;
            else if (tagName == "user")
                target = USER_COLOR;
            else if (tagName == "id")
                target = ID_COLOR;
            else if (tagName == "name")
                target = NAME_COLOR;
            else if (tagName == "posts")
                target = POSTS_COLOR;
            else if (tagName == "post")
                target = POST_COLOR;
            else if (tagName == "body")
                target = BODY_COLOR;
            else if (tagName == "topic")
                target = TOPIC_COLOR;
            else if (tagName == "topics")
                target = TOPICS_COLOR;
            else if (tagName == "follower")
                target = FOLLOWER_COLOR;
            else if (tagName == "followers")
                target = FOLLOWERS_COLOR;
            else
                break;
            colors[target].push_back(createPair(start, end));
        }
    }
}

string XmlParser::getTagFrame(string& xml, int& pointer) {
    string tagFrame;
    tagFrame.push_back('<');
    ++pointer;
    for (pointer; !(xml[pointer] == '>' && (pointer == 0 || xml[pointer - 1] != '\\' || (pointer >= 2 && xml[pointer - 1] == '\\' && xml[pointer - 2] == '\\'))); ++pointer)
        tagFrame.push_back(xml[pointer]);
    tagFrame.push_back('>');
    return tagFrame;
}
string XmlParser::getData(string& xml, int& counter) {
    string data;
    while (!(xml[counter] == '<' && (counter == 0 || xml[counter - 1] != '\\' || (counter >= 2 && xml[counter - 1] == '\\' && xml[counter - 2] == '\\')))
        ) {
        data.push_back(xml[counter]);
        ++counter;
    }
    return data;
}

string XmlParser::trimLine(string input) {
    for (int i = 0; i < input.size() && input[i] == ' ';)
        input.erase(i, 1);
    for (int i = input.size() - 1; i >= 0 && input[i] == ' '; --i)
    {
        input.erase(i, 1);
    }
    return input;
}

template<class T>
//static ana eli sheltaha
 void XmlParser::setField(myPair<int, T>& target, vector< myPair<int, T> >& list) {
    if (!list.empty()) {
        if (list.size() == 1) {
            target = list[0];
        }
        else if (list.size() > 1) {
            bool nonEmptyFound = 0;
            for (int i = 0; i < list.size(); ++i) {
                if (!list[i].second.empty()) {
                    nonEmptyFound = 1;
                    target = list[i];
                    break;
                }
            }
            if (!nonEmptyFound)
                target = list[0];
        }
    }
}
template<class T, class U>
XmlParser::myPair<T, U> XmlParser::createPair(T first, U second)
{
    myPair<T, U> mypair(first, second);
    return mypair;
}
void XmlParser::Follower::clear()
{
    id = "";
    idVector.clear();
}
void XmlParser::Follower::setFollower() {
    bool nonEmptyIdFound = 0;
    if (!idVector.empty()) {
        if (idVector.size() == 1) {
            id = idVector[0];
        }
        else {
            for (int i = 0; i < idVector.size(); ++i) {
                if (!idVector[i].empty()) {
                    id = idVector[i];
                    nonEmptyIdFound = 1;
                    break;
                }
                if (!nonEmptyIdFound) {
                    id = "";
                }
            }
        }
    }
}

template<class T, class U>
void XmlParser::myPair<T, U>::setPairValues(T first, U second)
{
    this->first = first;
    this->second = second;
}
template<class T, class U>
XmlParser::myPair<T, U>::myPair(T first, U second)
{
    this->first = first;
    this->second = second;
}
template<class T, class U>
XmlParser::myPair<T, U>::myPair()
{}

void XmlParser::Post::clear()
{
    postOrder.clear();
    body.first = -1;
    body.second = "";
    topics.first = -1;
    topics.second.clear();
    bodyVector.clear();
    topicsVector.clear();
}
void XmlParser::Post::setPost() {
    //setting the body
    setField(body, bodyVector);
    //setting the topics
    setField(topics, topicsVector);
}

void XmlParser::User::clear()
{
    userOrder.clear();

    id.first = -1, name.first = -1;
    id.second = "", name.second = "";

    posts.second.clear();
    posts.first = -1;

    followers.second.clear();
    followers.first = -1;


    idVector.clear();
    nameVector.clear();
    postsVector.clear();
    followersVector.clear();
}
void XmlParser::User::setUser()
{
    setField(name, nameVector);
    setField(id, idVector);
    setField(posts, postsVector);
    setField(followers, followersVector);
}

bool XmlParser::isStartTag(string tag) {
    if (tag[1] != '/' && tag[0] == '<')
        return true;
    return false;
}

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
std::vector<int> compress(std::string str)
{
    std::unordered_map<std::string, int> code_table;
    for (int i = 0; i <= 255; i++) {
        std::string single_char = "";
        single_char += char(i);
        code_table[single_char] = i;
    }

    std::string p = "", c = "";
    p += str[0];
    int sequ = 256;
    std::vector<int> out_sequ;
    for (unsigned int i = 0; i < str.length(); i++) {
        if (i != str.length() - 1)
            c += str[i + 1];
        if (code_table.find(p + c) != code_table.end()) {
            p = p + c;
        }
        else {
            out_sequ.push_back(code_table[p]);
            code_table[p + c] = sequ;
            sequ++;
            p = c;
        }
        c = "";
    }
    out_sequ.push_back(code_table[p]);
    return out_sequ;
}

std::map<char, std::string> codes;
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
struct compare {
    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        return (l->freq > r->freq);
    }
};

void storeCodes(struct MinHeapNode* root, std::string str)
{
    if (root == NULL)
        return;
    if (root->data != '$')
        codes[root->data] = str;
    storeCodes(root->left, str + "0");
    storeCodes(root->right, str + "1");
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

std::priority_queue<MinHeapNode*, std::vector<MinHeapNode*>, compare>minHeap;

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
void calcFreq(std::string str, int n)
{
    for (int i = 0; i < str.size(); i++)
        freq[str[i]]++;
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
std::string decompress(std::vector<int> o_code)
{
    std::string out = "";
    std::unordered_map<int, std::string> code_table;
    for (int i = 0; i <= 255; i++) {
        std::string single_char = "";
        single_char += char(i);
        code_table[i] = single_char;
    }
    int old_sequ = o_code[0], n;
    std::string s = code_table[old_sequ];
    std::string c = "";
    c += s[0];
    std::cout << s;
    int no_seq = 256;
    for (unsigned int i = 0; i < o_code.size() - 1; i++) {
        n = o_code[i + 1];
        if (code_table.find(n) == code_table.end()) {
            s = code_table[old_sequ];
            s = s + c;
        }
        else {
            s = code_table[n];
        }
        out += s;
        c = "";
        c += s[0];
        code_table[no_seq] = code_table[old_sequ] + c;
        no_seq++;
        old_sequ = n;
    }
    return out;
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
void MainWindow::on_Exit_Button_clicked()
{
    close();
}

void MainWindow::on_Browse_btn_clicked()
{
    ui->output_text->clear();
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
    ui->output_text->clear();
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
        std::vector<std::string> xml;
        QString qstr = ui->input_text->toPlainText();
        std:: string XML=qstr.toStdString();
        //XML = RemoveSpace(XML);
        xml = split(XML," ");
        std::string corrected = correct_XML(xml);
        ui->output_text->insertPlainText(QString::fromStdString(corrected));

}
void MainWindow::on_actionCorrect_Errors_triggered()
{
    ui->output_text->clear();
    int i = 0;
        std::vector<std::string> xml;
        QString qstr = ui->input_text->toPlainText();
        std:: string XML=qstr.toStdString();
        //XML = RemoveSpace(XML);
        xml = split(XML," ");
        std::string corrected = correct_XML(xml);
        ui->output_text->insertPlainText(QString::fromStdString(corrected));
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
    if (qstr!= ""){
    std:: string str=qstr.toStdString();
    str = RemoveSpace(str);
    std::string encodedString;
        calcFreq(str, str.length());
        HuffmanCodes(str.length());
        for (auto i : str)
            encodedString += codes[i];
        XmlParser xmlparser;
        XmlParser::myPair<int,string> encoded = xmlparser.BiToHex(encodedString);
        encodedString = encoded.second;
        ui->output_text->setPlainText(QString::fromStdString(encodedString));
    }
}
void MainWindow::on_actionCompress_triggered()
{
    QString qstr = ui->input_text->toPlainText();
    if (qstr!= ""){
    std:: string str=qstr.toStdString();
    str = RemoveSpace(str);
    std::string encodedString;
        calcFreq(str, str.length());
        HuffmanCodes(str.length());
        for (auto i : str)
            encodedString += codes[i];
        XmlParser xmlparser;
        XmlParser::myPair<int,string> encoded = xmlparser.BiToHex(encodedString);
        encodedString = encoded.second;

    ui->output_text->setPlainText(QString::fromStdString(encodedString));

    }
}

void MainWindow::on_decompress_btn_clicked()
{
    QString qstr = ui->input_text->toPlainText();
    if (qstr!= ""){
    std:: string str=qstr.toStdString();
    XmlParser xmlparser ;
    xmlparser.extractData();
    int i = xmlparser.xmlcompressedsize % 5;
    str= xmlparser.HexToBi(XmlParser::myPair(i,str));
    str = RemoveSpace(str);
    std::string  decodedString;
    decodedString= decode_file(minHeap.top(), str);
    ui->output_text->setPlainText(QString::fromStdString(decodedString));
    }

}
void MainWindow::on_actionDecompress_triggered()
{
    QString qstr = ui->input_text->toPlainText();
    if (qstr!= ""){
    std:: string str=qstr.toStdString();
    XmlParser xmlparser ;
    xmlparser.extractData();
    int i = xmlparser.xmlcompressedsize % 5;
    str= xmlparser.HexToBi(XmlParser::myPair(i,str));
    str = RemoveSpace(str);
    std::string  decodedString;
    decodedString= decode_file(minHeap.top(), str);
    ui->output_text->setPlainText(QString::fromStdString(decodedString));
}
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
                if (i >= xml.size()){break;}
                i++;
                }
            for (int j = 0; j < ind; j++) {
                if(i>=xml.size()){break;}
                str += "    ";		//print tab
                }
             str += save + "\n";
        }
        }
    ui->output_text->setPlainText(QString::fromStdString(str));
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
                if (i >= xml.size()){break;}
                i++;
                }
            for (int j = 0; j < ind; j++) {
                if(i>=xml.size()){break;}
                str += "    ";		//print tab
                }
             str += save + "\n";
        }
        }
    ui->output_text->setPlainText(QString::fromStdString(str));
}

void MainWindow::on_Search_btn_clicked()
{
    ui->output_text->clear();
    QString qstr = ui->input_text->toPlainText();
    std:: string xml=qstr.toStdString();
    xml = RemoveSpace(xml);
    XmlParser xmlparser;
    xmlparser.xmlCommpressed = xml;
    xmlparser.extractData();
    QString userinput = QInputDialog::getText(0 , "Search Post","Please enter Keyword");
    if(userinput.isEmpty()){

    }
    else{

    ui->output_text->setPlainText(QString::fromStdString(xmlparser.searchPosts(userinput.toStdString())));
}

}
void MainWindow::on_actionPost_Search_triggered()
{
    ui->output_text->clear();
    QString qstr = ui->input_text->toPlainText();
    std:: string xml=qstr.toStdString();
    xml = RemoveSpace(xml);
    XmlParser xmlparser;
    xmlparser.xmlCommpressed = xml;
    xmlparser.extractData();
    QString userinput = QInputDialog::getText(0 , "Search Post","Please enter Keyword");
    if(userinput.isEmpty()){

    }
    else{

    ui->output_text->setPlainText(QString::fromStdString(xmlparser.searchPosts(userinput.toStdString())));
}
}

void MainWindow::on_Most_followed_clicked()
{
    ui->output_text->clear();
    QString qstr = ui->input_text->toPlainText();
    std:: string xml=qstr.toStdString();
    xml = RemoveSpace(xml);
    XmlParser xmlparser;
    xmlparser.xmlCommpressed = xml;
    xmlparser.extractData();
    ui->output_text->setPlainText(QString::fromStdString(xmlparser.doNetworkAnalysis()));
}
void MainWindow::on_actionMost_Followed_triggered()
{
    ui->output_text->clear();
    QString qstr = ui->input_text->toPlainText();
    std:: string xml=qstr.toStdString();
    xml = RemoveSpace(xml);
    XmlParser xmlparser;
    xmlparser.xmlCommpressed = xml;
    xmlparser.extractData();
    ui->output_text->setPlainText(QString::fromStdString(xmlparser.doNetworkAnalysis()));
}

void MainWindow::on_Most_Active_clicked()
{
    ui->output_text->clear();
    QString qstr = ui->input_text->toPlainText();
    std:: string xml=qstr.toStdString();
    xml = RemoveSpace(xml);
    XmlParser xmlparser;
    xmlparser.xmlCommpressed = xml;
    xmlparser.extractData();
    ui->output_text->setPlainText(QString::fromStdString(xmlparser.MostActive()));
}
void MainWindow::on_actionMost_Active_triggered()
{
    ui->output_text->clear();
    QString qstr = ui->input_text->toPlainText();
    std:: string xml=qstr.toStdString();
    xml = RemoveSpace(xml);
    XmlParser xmlparser;
    xmlparser.xmlCommpressed = xml;
    xmlparser.extractData();
    ui->output_text->setPlainText(QString::fromStdString(xmlparser.MostActive()));
}

void MainWindow::on_Mutual_friends_clicked()
{
    ui->output_text->clear();
    QString qstr = ui->input_text->toPlainText();
    std:: string xml=qstr.toStdString();
    xml = RemoveSpace(xml);
    XmlParser xmlparser;
    xmlparser.xmlCommpressed = xml;
    xmlparser.extractData();
    QString userinput = QInputDialog::getText(0 , "Enter users ids","Please enter your 2 users ids separated by a comma");
    if(userinput.isEmpty()){

    }
    else{
    QStringList splitted = userinput.split(",");
    string x = splitted[0].toStdString();
    string y = splitted[1].toStdString();
    ui->output_text->setPlainText(QString::fromStdString(xmlparser.getMutualFollowers(x,y)));
    }

}
void MainWindow::on_actionMutual_Friends_triggered()
{
    ui->output_text->clear();
    QString qstr = ui->input_text->toPlainText();
    std:: string xml=qstr.toStdString();
    xml = RemoveSpace(xml);
    XmlParser xmlparser;
    xmlparser.xmlCommpressed = xml;
    xmlparser.extractData();
    QString userinput = QInputDialog::getText(0 , "Enter users ids","Please enter your 2 users ids separated by a comma");
    if(userinput.isEmpty()){

    }
    else{
    QStringList splitted = userinput.split(",");
    string x = splitted[0].toStdString();
    string y = splitted[1].toStdString();
    ui->output_text->setPlainText(QString::fromStdString(xmlparser.getMutualFollowers(x,y)));
    }
}

void MainWindow::on_Recommend_friends_clicked()
{
    ui->output_text->clear();
    QString qstr = ui->input_text->toPlainText();
    std:: string xml=qstr.toStdString();
    xml = RemoveSpace(xml);
    XmlParser xmlparser;
    xmlparser.xmlCommpressed = xml;
    xmlparser.extractData();
    QString userinput = QInputDialog::getText(0 , "","Please enter User ID");
    if(userinput.isEmpty()){

    }
    else{
    ui->output_text->setPlainText(QString::fromStdString(xmlparser.recommendPeople(userinput.toStdString())));
    }

}
void MainWindow::on_actionSuggest_Friends_triggered()
{

    ui->output_text->clear();
    QString qstr = ui->input_text->toPlainText();
    std:: string xml=qstr.toStdString();
    xml = RemoveSpace(xml);
    XmlParser xmlparser;
    xmlparser.xmlCommpressed = xml;
    xmlparser.extractData();
    QString userinput = QInputDialog::getText(0 , "","Please enter User ID");
    if(userinput.isEmpty()){

    }
    else{
    ui->output_text->setPlainText(QString::fromStdString(xmlparser.recommendPeople(userinput.toStdString())));
    }
}
