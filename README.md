# PROJECT BLEATCODE
By Michael Hu (Period 10) 
## About Bleat
A very primitive project attempting to simulate a live coding environment like Coding Bat. Each user has an ID linked to a problem set that will keep track of problem-solving progression.
A user can choose a problem from a problem set and read what it's about (description, examples, etc.) and then edit the a solutioni file using nano. After, the user can submit the file for testing with a few cases.
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
   - `make`
2. First, run the server and then run the client
   - `make runserver`
   - `make run`
3. The prompt will ask you a series of introductory questions!
   - What is your name?
   - Have you been on Bleetcode before? If so, enter your ID to return to your problem set progression.
4. After, you will be directed to your problem set! From here, you can choose a problem from Problem 0 to Problem 19.
