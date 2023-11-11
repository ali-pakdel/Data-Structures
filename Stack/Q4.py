def find_code(lines):
    code = [0] * lines
    stack_str = []
    stack_index = []

    index = 0
    for i in range (int(lines)):
        string = input()
        if string == "Endfor":
            if "For" in stack_str:
                x = stack_str.pop()
                if x == "For":
                    code[index] = 2
                    code[stack_index.pop()] = 2
                else:
                    stack_str.clear()
                    stack_index.clear()
            else:
                stack_str.clear()
                stack_index.clear()
            index = i + 1
            
        
        elif string == "Endwhile":
            if "While" in stack_str:
                temp = stack_str[::-1]
                if "For" in stack_str:
                    x = stack_str.pop()
                    if x == "While":
                        code[index] = 1
                        code[stack_index.pop()] = 1
                    else:
                        stack_str.clear()
                        stack_index.clear()
            else:
                stack_str.clear()
                stack_index.clear()
            index = i + 1
        else:
            if string != "For" and string != "While":
                code[index] = 1
            else:
                stack_str.append(string)
                stack_index.append(index)
            index += 1
    return code


def check_code(codee):
    s = 0
    t_s = -1
    e = 0
    t_e = -1
    f = 0
    t_f = 0
    counter = 0
    flag = 0
    code = [idx for idx, val in enumerate(codee) if val != 0]
    if len(code) == 0:
        print(0, 0, 0)
        return
    
    num = []
    for i in range (len(code)):
        if codee[code[i]] == 2:
            t_f += 1
        t_s = code[i]
        t_e = code[i]
        for j in range (i + 1, len(code)):
            if code[j] - 1 == code[j - 1]:
                if codee[code[j]] == 2:
                    t_f += 1
                continue
            t_e = code[j - 1]
            temp = [t_f, t_s, t_e]
            t_f = 0
            num.append(temp)
            flag = 1
            break
        if flag != 1:
            t_e = code[j]
            temp = [t_f, t_s, t_e]
            t_f = 0
            num.append(temp)
        
    num.sort(key = lambda x: x[0])
    print(int(num[len(num) - 1][0] / 2), num[len(num) - 1][1], num[len(num) - 1][2] + 1)

lines = input()
code = find_code(int(lines))
check_code(code)

