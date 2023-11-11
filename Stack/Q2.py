def post_pre(text, method):
    stack = []
    for char in text:
        if char.isdigit() == True:
    	    stack.append(int(char))
        else:
            num1 = stack.pop() 
            num2 = stack.pop()
            if method == "Postorder":
                num1, num2 = num2, num1   
 
            stack.append(calculate(num1, num2, char))
        
    return stack.pop()

def calculate(num1, num2, char):
    if char == '+': 
        return num1 + num2
    elif char == '-':
        return num1 - num2
    elif char == '*':
        return num1 * num2
    
method = input()
text = input()

if method == "Preorder":
    text = text[::-1]
print(post_pre(text, method))
