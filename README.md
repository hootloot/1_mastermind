# 1_mastermind
Project 1 for Fundamentals of Algorithms EECE2560

- jan 20: first meeting

- part a due jan 27
- part b due feb 3


pseudocode:

- program starts
- codebreaker (program) asks user to input two integers, $n$ and $m$
    - create code (vector) object (int length, int range)
- codemaker randomly generates code
    - for (int i = 0; i < n; i++) {
        content[i] = rand() % m;
    }
- prompts user to enter a guess
    - within main function

- codemaker responds by printing two values that indicate how close the guess is to the code
- the first response value is the number of digits that are the right digit in the right location. 
- the second response is the number of digits that are the right digit in the wrong location. 
