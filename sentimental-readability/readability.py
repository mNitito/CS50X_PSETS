from cs50 import get_string

# prompt the user for input
text = get_string("Enter the text:")

# claculate how many sentences
sentences = 0
for c in text:
    if (c == '?' or c == '!' or c == '.'):
        sentences = sentences + 1

# claculate how many words
words = 1
for c in text:
    if (c == ' ' and c != 0):
        words = words + 1

# claculate how many letters
letters = 0
for c in text:
    if (c.isalpha()):
        letters = letters + 1

# average number of letrers per (100) words
L = letters / words * 100

# average number of sentences per (100) words
S = sentences / words * 100

# calculate the index
index = round(0.0588 * L - 0.296 * S - 15.8)


# print the grade
if (index > 1 and index < 16):
    print(f"Grade {index}")

elif (index > 16):
    print("Grade 16+")

else:
    print("Before Grade 1")
