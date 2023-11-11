def calculate_possibilities(first_num, second_num):
    result = 0
    index1 = find_first_unknown_digit(second_num)
    index2 = find_second_unknown_digit(second_num[index1 + 1:]) + index1 + 1
    if index1 >= 0:
        if index2 >= 0:
            result += first_case(first_num[index1:], second_num[index1:])
            
            if compare(first_num[index1 + 1:index2], second_num[index1 + 1:index2]) == 2:
                return bigger_num(second_num[index1:]) + result
            elif compare(first_num[index1 + 1:index2], second_num[index1 + 1:index2]) == 0:
                return result
            return result + int(calculate_possibilities(first_num[index2:], second_num[index2:]))
        else:
            return first_case(first_num[index1:], second_num[index1:])
        return 0


def bigger_num(second_num):
    return 10 ** ((len(list(filter(lambda x : x == '?', second_num)))) - 1)

def compare(first_num, second_num):
    if first_num > second_num:
        return 2
    elif first_num == second_num:
        return 1
    return 0

def find_first_unknown_digit(second_num):
    for x in second_num:
        if x == '?':
            return second_num.index('?')
    return -100

def find_second_unknown_digit(second_num):
    for x in second_num:
        if x == '?':
            return second_num.index('?')
    return -100
        
        
def first_case(first_num, second_num):
    if int(first_num[0]) > 0:
        return int(first_num[0]) * (10 ** (len(list(filter(lambda x : x == '?', second_num))) - 1))
    else:
        return 0

    
first_num = input()
second_num = input()

index = find_first_unknown_digit(second_num)
if compare(first_num[:index], second_num[:index]) == 2:
    print(bigger_num(second_num[index + 1:]) % 100000007)
elif compare(first_num[:index], second_num[:index]) == 1:
    print(calculate_possibilities(first_num[index:], second_num[index:]) % 100000007)
else:
    print("0")


