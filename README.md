# Google_Search_Engine
The way this program functions is as follows:
when you first run the code it immediately reads the input websites file, after that it prompts you to pick one of 4 options. Either to update the stored information via the update file, search by inputting keywords, output all the stored information for you to see on screen , or exit.

Note: In this repository there are sample files for everything that is need, i.e. you could run the code without adding anything.

For more details regarding how the program functions keep reading...



Input: The input is based on two files, one for websites and another for keywords. The websites file must be written in comma separated list format. First, the website name then followed by a list of hyperlinks which this website links to. As for the keywords file, it is also in a comma separate list format with the keyword written first followed by a list of websites which have this keyword

Update: this option opens the update file, reads the information there and updates according to that. The update file has to be written in a certain format. Each line must start with either A (add), R (remove), or U (update). For the A, it must be followed by a comma then a website. The same format is applied for R. But for U you need to first add a comma then the website name then another comma followed by the number of impressions, then another comma and the number of clicks, and finally another comma then a space separated list in which you can add or remove hyperlinks.

Search: In this option you are prompted to enter keywords in one of two formats, either between quotations, which indicates that all the keywords must be present in the website for it to be in the results, or without quotations in which case any website which has this keyword will appear in you search result. After inputting the query, the program calculates the pagerank of all the websites (in case they were not already calculated and then sorts the relevant websites according to their pagerank and outputs them to the user

Output: In this option all stored data will be outputted and the format of the output is discussed below

Exit: In this option the runtime and the number of comparisons are outputted to the screen and the program exits causing all the stored data to be deleted

Main Data Structures Used:
1st data structure is hash tables where I used it to hash the websites and the keywords.
2nd data structure is vectors where I used to store any form of information which I did not know its size prior to storing it.

Design Tradeoffs:
Hash tables
Benefits:
Using the hash table rather than a graph since the hash function almost always guarantees O(1) search complexity except in the rare cases where collisions occur. So overall, the search function in the hash table is faster than the graph search. In the best case of the hash table, only 1 comparison would be done per search which is extremely quick.
Disadvantages:
In the worst-case space complexity for the hash table, there could be a lot of wasted space. I will give an example which is extremely rare, but if occurred would make the hash table very inefficient. If all inputted unique websites have ascii values which lead to the same index then the hash table would be basically an empty array with one cell which points to linked list containing all the websites. But this is not a lot worse than the graphs since in this case the extra space (compared to the graph) would only be the 19 extra cells which are empty which is not a lot.

Extra details
At any time you could output all the stored information in the keyword hash table and the websites hash table. The websites are outputted in the following format
Website (num starting from 0)
Website name
Number of incoming links
List of incoming links
Number of outgoing links
List of outgoing links
Number of impressions
Number of clicks

Website collisions are outputted in this format:
Collision
Website name
Number of incoming links
List of incoming links
Number of outgoing links
List of outgoing links
Number of impressions
Number of clicks


Keywords in the following format

Keyword
List of websites

Keyword collisions in the following format
Collision
List of websites
