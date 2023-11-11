def make_number(text):
    number = 0
    i = 0
    while i < len(text):
        if text[i] == '(':
            number -= int(text[i - 1])
            repeat = int(text[i - 1])
            del text[0:i + 1]
            list1 = make_number(text)
            number += repeat * list1
            i = -1
        elif text[i] == ')':
            del text[0:i + 1]
            return number
        else:
            number += int(text[i])
        i += 1
    return number
            
inp = input()
text = []
text[:0] = inp
sum = 0
print(make_number(text))
