# DS-project
* This project is about developing a complete XML **GUI (Graphical User Interface)** based program to
parse and visualize an XML file project:

* For starters, **XML (Extensible Markup Language)** is one of the most famous formats for storing and sharing
information among different devices. Some text editors such as Sublime Text are able to parse
such files and do some basic operations.

* In our system the XML file will represent users in a social network where:
* * Each user has id (unique), name, list of posts, list of followers.
* * Each post has text and list of topics

<h2> The features implemented to make GUI easier to use are: </h2>

<h3> 1. Checking the XML consistency: </h3>

The input XML may have inconsistencies like missing any
of the closing and opening tags or not matching tags. It should also be able to detect and visually show any errors in consistency.
   
<h3> 2. Correcting errors found in XML </h3>

The program is also able to solve errors discussed in the previous point.

<h3> 3. Formatting (Prettifying) the XML: </h3>

The XML file should be well formatted by keeping the indentation for each level.

<h3> 4. Converting XML to JSON: </h3>

**JSON (Javascript Object Notation)** is another format that is used
to represent data. It’s helpful to convert the XML into JSON, especially when using
javascript as there’s tons of libraries and tools that use json notation.

<h3> 5. Minifying the XML file: </h3>

Since spaces and newlines (\n) are actually characters that can
increase the size of an XML document. This feature should aim at decreasing the size of
an XML file (compressing it) by deleting the whitespaces and indentations.

<h3> 6. Compressing and Decompressing the data in the XML/JSON file: </h3>

It is a way to reduce the
size of the file using a data compression technique.
The smaller the output file is, the more efficient your algorithm is.
Decompressing the compressed data makes it return to its original format.

<h3> 7. Representing the users' data: </h3>

the XML file will represent the
users data in a social network (their posts, followers, ...etc). 
The user data is his id (unique across the network), name, list of his posts and followers.

<h3> 8. Network Analysis: </h3>

We use this analysis to extract important data like:
* who is the most influencer user (has the most followers)
* who is the most active user (connected to lots of users)
* the mutual followers between 2 users
* for each user, suggest a list of users to follow (the followers of his followers)

<h3> 9. Post Search: </h3>

given a specific word or topic, we can get the posts where this word or topic was
mentioned.

<h2> How to use the executable file: </h2>

    1. Click on the "Clear" button to clear input and output.
    2. Click on the "Browse" button to open an existing XML file.
    3. Click on the "Save As" button to save changes in a new file.
    4. Click on the "Exit" button to exit the application.
    5. Click on the "Convert to JSON" button to convert the XML file to JSON.
    6. Click on the "Check for Errors" button to check and detect if there are any errors in the XML file.
    7. Click on the "Correct Errors" button to correct the errors in the XML file.
    8. Click on the "Minify" button to minify the XML file.
    9. Click on the "Compress" button to compress the XML file.
    10. Click on the "Decompress" button to decompress the XML file.
    11. Click on the "Prettify" button to prettify the XML file and show it in its correct format.
    12. Click on the "Post Search" button to search the XML file for a specefic word or topic.
    13. Click on the "Most Followed" button to show user that has largest number of followers.
    14. Click on the "Most Active" button to show user with highest number of posts and that with most following.
    15. Click on the "Mutual Friends" button to show mutual followers between 2 users.
    16. Click on the "Recommend Friends" button to suggest users to follow.

<h2> Check Drive Link for Full Report, EXE file and Short Illustration Video: </h2>

https://drive.google.com/drive/folders/19jAyBznOou4bqQW50L21J2xYEm1AMePQ

<h2> Contributors: </h2>

The following individuals have contributed to this project:

<a href="https://github.com/mariamsamir037/DS-project/graphs/contributors">   
  <img src="https://contrib.rocks/image?repo=mariamsamir037/DS-project" />
</a>
