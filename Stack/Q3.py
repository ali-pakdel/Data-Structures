def check_merging(listt):
    i = 0
    while i < len(listt):
        for j in range (len(listt)):
            if listt[i][0] == listt[j][len(listt[j]) - 1] and listt[i][0] != 0:
                listt[j].pop()
                listt[i] = listt[j] + listt[i]
                del listt[j]
                i = -1
                break
            elif listt[i][len(listt[i]) - 1] == listt[j][0] and listt[j][0] != 0:
                listt[i].pop()
                listt[i] = listt[i] + listt[j]
                del listt[j]
                i = -1
                break
        i += 1
    return listt

def get_input(n, listt):
    single_server = 1
    for i in range(int(n)):
        pre, aft = input().split(" ")
        pre = int(pre)
        aft = int(aft)
        flag = 0
    
        if(single_server < aft):
            single_server = aft + 1
        if(single_server < pre):
            single_server = pre + 1
        for j in range (len(listt)):
            if listt[j][0] == aft and aft != 0:
                listt[j].insert(0, -1)
                listt[j].insert(0, pre)
                flag = 1
                break
            elif listt[j][len(listt[j]) - 1] == pre and pre != 0:
                listt[j].append(-1)
                listt[j].append(aft)
                flag = 1
                break
        if flag == 1:
            continue

        temp = [pre, -1, aft]
        listt.append(temp)
    return single_server
    

n = input()
listt = []

single_server = get_input(n, listt)
listt = check_merging(listt)

i = 0
while i < len(listt):
    if listt[i][0] == 0 and listt[i][len(listt[i]) - 1] == 0 :
        if len(listt[i]) == 3:
            listt[i][1] = single_server
            single_server += 1
            i += 1
            continue
	
        j = i + 1
        while j < len(listt):
            if listt[j][0] != 0 and listt[j][len(listt[j]) - 1] != 0 and len(listt[j]) + 2 == len(listt[i]):
                k = 0
                while k < len(listt[j]):
                    listt[i][k + 1] = listt[j][k]
                    k += 2
                del listt[j]
                break
            j += 1
            
    elif listt[i][0] != 0 and listt[i][len(listt[i]) - 1] != 0:
        j = i +1
        while j < len(listt):
            if listt[j][0] == 0 and listt[j][len(listt[j])-1] == 0 and len(listt[j]) - 2 == len(listt[i]):
                k = 0
                while k < len(listt[j]) - 3:
                    listt[i][k + 1] = listt[j][k + 2]
                    k += 2
                del listt[j]
                break
            j += 1
	    
    elif listt[i][0] == 0 and listt[i][len(listt[i]) - 1] != 0:
        j = i + 1
        while j < len(listt):
            if listt[j][0] != 0 and listt[j][len(listt[j])-1] == 0 and len(listt[j]) == len(listt[i]):
                k = 0
                while k < len(listt[j]) - 1:
                    listt[i][k + 1] = listt[j][k]
                    k += 2
                listt[i].append(0)
                del listt[j]
                break
            j += 1
	    
    elif listt[i][0] != 0 and listt[i][len(listt[i]) - 1] == 0:
        j = i + 1
        while j < len(listt):
            if listt[j][0] == 0 and listt[j][len(listt[j])-1] != 0 and len(listt[j]) == len(listt[i]):
                k = 0
                while k < len(listt[j]) - 2:
                    listt[i][k + 1] = listt[j][k + 2]
                    k += 2
                listt[i].insert(0, 0)
                del listt[j]
                break
            j += 1
	    
    i += 1

print(len(listt))
for x in range(len(listt)):
    listt[x] = [y for y in listt[x] if y != 0]
    print(' '.join(map(str, listt[x])))




