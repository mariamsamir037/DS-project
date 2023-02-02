#include <bits/stdc++.h>

#define MAXASCII 256

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

        vector<User> users;
        int xmlcompressedsize;
        string xmlCommpressed;
        template<class T, class U>
        static myPair<T, U> createPair(T first, U second);
        template<class T>
        static void setField(myPair<int, T>& target, vector< myPair<int, T> >& list);
        bool isStartTag(string tag);
        string getData(string& xml, int& counter);
        string getTagFrame(string& xml, int& pointer);
        void extractData();
        static string getTagName(string tag);
        vector<string> splitter(string s, int size);
        myPair<int, string> BiToHex(string s);
        string HexToBi(myPair<int, string>encoded);
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

