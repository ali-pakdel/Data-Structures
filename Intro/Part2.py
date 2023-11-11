def full_row(table, j):
    for x in range (len(table)):
        if table[x][j] == 0:
            return False
    return True

def full_column(table, i):
    for y in range (len(table)):
        if table[i][y] == 0:
            return False
    return True


def empty_row(table, empty_rows):
    for x in empty_rows:
        for y in range (len(table)):
            if table[x][y] == 1:
                break
            return True
    return False

def empty_column(table, empty_columns):
    for y in empty_columns:
        for x in range (len(table)):
            if table[x][y] == 1:
                break
            return True
    return False

        
    
def is_full_row_column(table, i, j):
    if full_row(table, j) == True or full_column(table, i) == True:
        return True
    else:
        return False

def is_empty_row_column(table, empty_rows, empty_columns):
    if empty_row(table, empty_rows) == True or empty_column(table, empty_columns) == True:
        return True
    else:
        return False
    
def delete_rows_columns(empty_rows, empty_columns, i, j):
    for k in range (len(empty_rows)):
        if empty_rows[k] == j:
            empty_rows.remove(j)
            break
    for t in range (len(empty_columns)):
        if empty_columns[t] == i:
            empty_columns.remove(i)
            break
            
n = int(input())

table = [[0]*n for i in range (n)]
empty_rows = [i for i in range(n)]
empty_columns = [i for i in range(n)]

full_row_column = False
counter = 0

while counter < n * n:
    row, column=list(map(int,input().split()))

    table[row - 1][column - 1] = 1
    delete_rows_columns(empty_rows, empty_columns, row - 1, column - 1)
    
    if full_row_column == False:
        if is_full_row_column(table, row - 1, column - 1) == True:
            full_row_column = True

    if full_row_column == True:
        print("HIDEOUS")
    elif len(empty_rows) == 0 and len(empty_columns) == 0:
        print("LOVELY")
    else:
        print("HIDEOUS")
    
    counter += 1

