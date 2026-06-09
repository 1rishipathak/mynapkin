text = input("Text: ")

n = len(text)

# Calculating total number of letters
letters = 0
for i in range(n):
    if text[i].isalpha():
        letters += 1

# Calculating total number of words
words = 1
for i in range(n):
    if text[i].isspace():
        words += 1

# Calculating total number of sentences
sentences = 0
for i in range(n):
    if text[i] in [".", "!", "?"]:
        sentences += 1

# Calculating averages
l = (letters / words) * 100
s = (sentences / words) * 100

# Calculating grade
index = 0.0588 * l - 0.296 * s - 15.8

grade = round(index)

if grade in range(15, 0, -1):
    print(f"Grade {grade}")
elif grade >= 16:
    print("Grade 16+")
elif grade < 1:
    print("Before Grade 1")
