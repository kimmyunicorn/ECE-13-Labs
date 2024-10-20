LAB 2 README
Contributor: Ian Leung (ipleung@ucsc.edu), Kimberly Camanero (kcamaner@ucsc.edu)

Kimberly Camanero:
The parts coded by me were the math functions as well as the main programs that went with every function. Such as the addition, subtraction, multiplication, division, F -> C, C->F, absolute value, tangent/degree value, and the round function. Main programs were not in their designated areas, but they were coded for these functions. 

Ian leung:
I programmed the input loop as well as making modifications to the code to make it function in the linux terminal. I made a couple of separate helper functions (OperandInputTwo and OperandInput) that help simplify the code. I also made some modifications to the functions to make the code both more readable and function correctly with my main input loop.

What happens if the line “scanf(" ");” executes? Why?
The ``scanf()`` is one of the c methods to get a user input. When scanf(“ ”) is run, the scanf waits for user input until there is both another character other than a space and return character “\n” is inputted. This is because the scanf will “consume” the spaces or discard any of the inputted white space from the I/O stream until it sees a non space character. 
In this lab, we forbid you from using printf() or scanf() inside of certain functions. Explain why a rule like this is useful.
It is helpful to not use printf() or scanf() inside functions because it defines a clear separation between your main loop function and the rest of your code. If you have every function taking user input then it is harder to tell whether or not your code breaks at accepting user input or if it’s an issue with a separate function. For this small of a program, I felt it was a hindrance since it reduced the amount of code I could obviate into another function and repeat over my program however I see it’s applications. 
How long did this lab take you? Was it harder or easier than you expected? What challenges did you encounter?
The lab took ~6 hours cumulatively to complete. The biggest challenge was formatting my code in a readable manner. I found it difficult to write the code in a neat manner without putting print into functions. In addition the scanf() function was hard to use because of how much validation and the number of steps I had to take in addition to scanning the input. 

Kimberly:
The math functions tooth me about 4 days to complete as well as the main program. I spent around two days learning how exactly to use the scanf command and seeing their relationship with strings such as %f, %lf, %d, and %s and learning about pointers and what “&” does, and where it stores it. Doing the actual math functions and putting everything together (the new topics to make the math functions) in itself took another two days. 

The math functions were a bit easier than from what I expected after studying all the concepts in order to run the program.

More of formatting and where to put specific things, for example I knew the math functions had to be there as well as the main code, but I didn’t know how to set it up in a way in which the calculator would be functional. If i got one math function and one main programs that corresponded with that function then it’ll work, but once I had everything and multiple main programs I didn't really know how to format it. 

