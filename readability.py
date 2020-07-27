from cs50 import get_string

# main function runs program
def main():
   t = get_string("Text: ")
   text = t.lower()
   l = countLetters(text)
   w = countWords(text)
   s = countSentences(text)
   p = colemanLiauIndex(l, w, s)
   i = round(p)
   grade(i)

# determines number of letter in text
def countLetters(text):
    l = 0
    for i in range(len(text)):
        if (text[i] >= "a" and text[i] <= "z"):
            l += 1
    return l

# determines number of words in text
def countWords(text):
    w = 1
    for i in range(len(text)):
        if (text[i] == ' '):
            w += 1
    return w

# determines number of sentences in text
def countSentences(text):
    s = 0
    for i in range(len(text)):
        if (text[i] == "." or text[i] == '?' or text[i] == '!'):
            s += 1
    return s

# determines the coleman liau index
def colemanLiauIndex(l, w, s):
    let = ((l * 100) / w);
    sen = ((s * 100) / w);
    p = ((0.0588 * let) - (0.296 * sen)) - 15.8;
    return p

# prints out the grade level appropriate for the text.
def grade(i):
    if i < 1:
        print("Before Grade 1")
    elif i > 16:
        print("Grade 16+")
    else:
        print(f"Grade {i}")
    return

main()