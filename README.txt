Welcome to the Connect 4 README.

The object of the game is to place 4 pieces in a row, before your
opponent!  Place pieces into the board by pressing number keys
between one and seven.  Your pieces are represented by an "o" while the computer 
player's pieces are "x"s.

Compilation Instructions:

1.  Navigate to the directory containing the game files using
your favourite terminal client.  

2.  Type "make".  This will compile the source files and create the executable.

3.  To run the executable type "./Connect4".  

4.  To delete object files and executable, type "make clean"

Comments?  Feedback?  Want to get involved?  Email me at s0905852@sms.ed.ac.uk or
check out the project source code at https://github.com/duncand0nuts/SD 

Note for developers:  There are several memory leaks within the program.
There are some functions included to free the memory allocated to point or board types
after use in Board.c.
