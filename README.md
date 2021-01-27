# PROJECT BLEATCODE
By Michael Hu (Period 10) 
## About Bleat
A very primitive project attempting to simulate a live coding environment like Coding Bat. Each user has an ID linked to a problem set that will keep track of problem-solving progression.
A user can choose a problem from a set of 20 problems (adapted from [w3resources](https://www.w3resource.com/c-programming-exercises/)) and read about each (description, examples, etc.). Then, the user can edit a solution file using nano and submit the file after for testing with a few test cases.
## Required Libraries
- fcntl.h
- unistd.h
- signal.h
- stdlib.h
- stdio.h
- string.h
- sys/stat.h
- sys/types.h
- sys/wait.h
- time.h
## Instructions
1. Get everything ready by using make!
   - `$ make`
   
2. First, run the server and then run the client
   - `$ make runserver`
   - `$ make run`
   
3. The prompt will ask you a series of introductory questions!
   - What is your name?
   - Have you been on Bleetcode before?
     - If so, enter your ID to return to your problem set.
     - If not, you will receive a new ID and a new problem set. 
     
4. After, you will be directed to your problem set! From here, you can choose a problem from Problem 0 to Problem 19.
   - "+" signifies a completed problem, while "-" signfies a non-completed problem.
   - The user prompt should guide you through the program.
   - You may choose to try and solve a problem using nano. The file will not disappear in your session, so you may return to it even after you try another problem.
     - You will be directed to a pre-formatted file, and a designated area for you to write your code. Don't touch the parts of the file you're not supposed to touch!
   - If you succeed, this problem will be marked as complete on your problem set. You don't get any congratulations for finishing your set. Maybe bragging rights?
   - You have the option to look at solutions (the only solution that is available currently is the solution for Problem 0);
   
5. To exit, the prompt will guide you to an exit after you attempt one problem. Your progress will be saved to your ID.
   - To exit abruptly, either `Ctrl Z,` `Ctrl X,` or `Ctrl C`. Unfortunately, your progress will not be saved to your ID when you exit.
   - If the client exits either naturally or abruptly (not due to a bug), the server will wait with a handshake for a new client.
