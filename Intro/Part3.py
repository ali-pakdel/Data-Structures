import sys
sys.setrecursionlimit(100000)

def find_island(table, cur_row, cur_col, n, m, row_moves, col_moves):
    for i in range (4):
        new_row = cur_row + row_moves[i]
        new_col = cur_col + col_moves[i]
        if new_row < 0 or new_row >= n or new_col < 0 or new_col >= m:
            continue

        if table[new_row][new_col] == -1 or table[new_row][new_col] == 0:
            continue
        
        table[new_row][new_col] = -1
        find_island(table, new_row, new_col, n, m, row_moves, col_moves)
    
        
            
    
row, column=list(map(int,input().split()))

table = []
row_moves = [0, 1, 0, -1]
col_moves = [1, 0, -1, 0]
islands = 0

for i in range (row):
    temp = list(map(int, input().split()))
    table.append(temp)
    
for i in range (row):
    for j in range (column):
        if table[i][j] == 1:
            find_island(table, i, j, row, column, row_moves, col_moves)
            islands += 1
print(islands)
            
