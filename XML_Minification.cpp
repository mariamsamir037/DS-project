
void minify_XML(string xml) {
    string minifiedString = "", temp1, temp2;
    int i = 0;

    while (i < xml.length()) {
        temp1 = xml[i];
        temp2 = xml[i+1];
        if (temp1 == "\r" || temp1 == "\n" || temp1 == "\t") {
            i++;
        }
        else if (temp1 == " " && temp2 == " "){
            i += 2;
        }
        else {
            minifiedString += temp1;
            i++;
        }
    }
    cout << minifiedString << endl;
}
