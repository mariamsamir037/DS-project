#include <bits/stdc++.h>
#include "analysis.h"
using namespace Entity;

std::vector<std::string> XmlParser::splitter(std::string s, int size) {
    vector<string>chars;
    while (s.size() > 0) {
        chars.push_back(s.substr(0, size));
        s.erase(0, size);
    }
    return chars;
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

template<class T>
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
