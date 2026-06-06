The following program checks any file containing text against a given dictionary (which can be loaded) for spelling errors, and returns the number of words mis-spelled.
It also returns the time taken by the program to complete and also the times taken by various helper-functions to pop-off the stack.

Usage: speller [dictionary] text
-> Where dictionary is assumed to be a file containing a list of lowercase words, one per line, and text is a file to be spell-checked.
-> As the brackets suggest, provision of dictionary is optional; if this argument is omitted, speller will use dictionaries/large by default.

The folder already contains sample text files and dictionaries.
