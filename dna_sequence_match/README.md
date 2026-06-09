Usage: python3 dna.py [path to database csv file] [path to dna sequence txt file]

The program looks for repeating STRs (short tandem repeats) which are basically a specific sequence of the bases (A- adnenine, G- guanine, C- cytosine, T- thymine) repeating consecutively.
The program calculates the longest consecutive repeating sequence of a given STR from the dna sequence and it is used to match and profile the DNA.
The number of times a specific STR repeats can be used to profile the DNA. More number of STRs used leads to better accuracy.

In the program, if all the STR repeat values of the sequence match with all of the STR repeat values of any person in the database, it is considered as a match and the program outputs the name of the person.
If no match is found, it outputs "No Match".
