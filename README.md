# xincrol
URNG Xincrol! algorithm provides random numbers which appear only once.

Xincrol - unique and random number generation algorithm.

The challenge.


Every serious programmer writing serious code at least once in his life has been stuck with this problem.
How to generate random numbers, but in a way so each number will appear only once.
Regular Random Number Generators (RNG) don't guaranty any uniqueness of provided numbers.
Programmers were using large random numbers like UUID(MD5) to hope that the same number will not appear twice in their life . But this does happen, I have seen it many times with large and dynamically changing databases, where object IDs were collided and this caused applications to crash, reports to fail, data lost etc.
The other common practice is to create huge array, fill it with serial numbers and shuffle this array for long time to have more-less acceptable level of randomness.
Those solutions are very CPU and memory consuming.
At the same time there are millions of SW applications which are seriously require URNGs.
Some examples of such applications:
Video and Image Effects
Encryption 
Steganography
All kinds of unique but secure (not serial) IDs (ex. any website with big DB)
Random serial numbers for money bills, car license plates, airplane part numbers etc. 
MP3 player playlist shuffling
Playing Cards shuffling for Casinos
Absolutely every Computer game needs unique randomization
ASCII to ASCII encryption/decryption 
Random memory or disk space addressing
more...
We all needed a function which will do the job.
I discovered it!


The Discovery.


If your input is serial numbers stream (like 0,1,2,3...) and you will perform cycling and directional bitwise operations in some predefined order you will get the same set of numbers but placed in different positions.
Magical operations are XOR, INC and ROL (the name of algorithm).

There are also DEC and ROR operations which could be used instead of INC and ROL.
There are 4 possible groups of operations:

XOR, INC, ROL 
XOR, DEC, ROL
XOR, INC, ROR
XOR, DEC, ROR

where...
XOR - exclusive disjunction,
INC - cyclic incrementation,
DEC - cycling decrementation,
ROL - rotation left,
ROR - rotation right.

Why is this happening? Well, because those operations are cyclic and directional. When you increment a variable, it grows up to biggest number in the range and then drops to 0. So, regardless on how many times you will perform this operation, but if you will always repeat it the same number of times, you will get the unique numbers output if your input is unique. One such operation doesn't really shuffle the input stream but if combined with other two, shuffling and randomness becomes really strong.

Important: Don't use INC and DEC  in the same cycle, don't use ROR and ROL in the same cycle!

Here I am publishing simple Java code of one of my Xincrol implementations.
This implementation also has ability to set a different range for generated unique numbers.
There is main() method below that demonstrates how it works. 
Have it! Enjoy it! 
Stop working with huge arrays, hashcodes and UUIDs!
