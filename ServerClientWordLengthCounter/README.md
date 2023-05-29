
This project was created by Colin Hommerding, Jack Poehlmann, and Jacob Fandel.


## Goal
The goal of this project is to be able to get a count of how many words of each length that there is within multiple text input files. The server and client will interact with each other by sending specific formatted messages that each can process via TCP sockets.

## Overview
This project uses a server and client executable. The server program will use multithreading to implement a multi-threaded server. The client program will generate multiple client processes. Each client process reads a file, processes “word length statistics” and sends a message to the server through TCP connections. The server spawns a thread whenever it establishes a new TCP connection with a client. The statistics sent by clients are accumulated in a shared resource named “Result Histogram”. So the overall purpose is to use TCP sockets to communicate between a server and client to count the number of words of each length in different files. 

## Compilation and Running the Program

The server is compiled by typing make clean on the terminal within the Server directory.

The client is compiled by typing make client on the terminal within the Client directory.

The server executable must be started first. Navigate to the Server directory and 
type "./server <Server Port>". So for example ./server 7777.

When running the client sample testcases are given that are located within the TestCases directory. The location of the test files that the client should run on is what is refered to by <Folder Name> below. All test files given must be named "1.txt", "2.txt", "3.txt", and so on in ascending order for the number of test files that there is. Look at the example TestCases to see examples of this.
Then to run the client navigate to the Client directory and type "./client <Folder Name> <# of Clients> <Server IP> <Server Port>". So for example ./client Testcases/TC3 3 127.0.0.1 7777

Once the program has finished running there will be a log of connections opened/closed and messages recieved by the client created in the Client/log directory. The server will print its connections opened/closed and messages recieved information to the terminal. The GET_WSTAT message furthest to the bottom of the client log will contain the final word length counts. So for example it will look like this: "GET_WSTAT: 1 2 2 2 2 2 2 2 2 0 0 0 0 0 0 0 0 0 1 1 1".
The first 1 represents that the message was a success. Then each following integer is the count of the number of words for a particular word length starting at 1 and ending at 20. 20 is the maximum word length this program works for. So for example the second integer is a 2, which means that there were two words of length one within the input files. The next integer is also a 2 meaning there were two words of length two within the input files. So as a whole for this example there were 2 words of length one, two, three, four, five, six, seven, and eight. There was one word of length eighteen, nineteen, and twenty.

