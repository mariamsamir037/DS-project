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
