from colorama import init
init(autoreset=True)
from os import system as s

full_board = [['b车', 'b马','b象', 'b士','b将', 'b士','b象', 'b马','b车'],
['  ', '  ','  ', '  ','  ', '  ','  ', '  ','  '],
['  ', 'b炮','  ', '  ','  ', '  ','  ', 'b炮','  '],
['b卒', '  ','b卒', '  ','b卒', '  ','b卒', '  ','b卒'],
['  ', '  ','  ', '  ','  ', '  ','  ', '  ','  '],
['  ', '  ','  ', '  ','  ', '  ','  ', '  ','  '],
['r兵', '  ','r兵', '  ','r兵', '  ','r兵', '  ','r兵'],
['  ', 'r炮','  ', '  ','  ', '  ','  ', 'r炮','  '],
['  ', '  ','  ', '  ','  ', '  ','  ', '  ','  '],
['r车', 'r马','r相', 'r仕','r帅', 'r仕','r相', 'r马','r车']
]
chinese_piece = tuple('车马炮仕相士象兵卒将帅')
num_piece = {"9":"车","5":"炮","4":"马","3":{'.':'相','@':'象'},"2":{'.':'仕','@':'士'},"1":{'.':'兵','@':'卒'},"0":{'.':'帅','@':'将'}}
let_color = {".":"r","@":"b"}
fen_piece = {"r":"车","R":"车","c":"炮","C":"炮","n":"马","N":"马",'B':'相','b':'象','A':'仕','a':'士','P':'兵','p':'卒','K':'帅','k':'将'}
board = []


def print_board():
    empty_board = [list('┏┳┳┳┳┳┳┳┓'),
list('┣╋╋╋╋╋╋╋┫'),list('┣╋╋╋╋╋╋╋┫'),
list('┣╋╋╋╋╋╋╋┫'),list('┣┻┻┻┻┻┻┻┫'),
list('┣┳┳┳┳┳┳┳┫'),list('┣╋╋╋╋╋╋╋┫'),
list('┣╋╋╋╋╋╋╋┫'),list('┣╋╋╋╋╋╋╋┫'),
list('┗┻┻┻┻┻┻┻┛')]
    
    for i in range(len(board)):
        for j in range(len(board[i])):
            if board[i][j] != "  ":
                if board[i][j][0] == "r":
                    print(f'\033[0;31;43m{board[i][j][1]}\033[0m', end="")
                else:
                    print(f'\033[0;30;43m{board[i][j][1]}\033[0m', end="")
            else:
                print(empty_board[i][j], end="")
            if j == len(board[i]) - 1:
                print('',end='')
            else:
                if board[i][j] != "  ":
                    print('--',end="")
                else:
                    print('---', end="")
        print('' if board[i][j] != "  " else ' ', i)
        if i == 0 or i == 7:
            print('|   |   |   | \ | / |   |   |   |   ')
        elif i == 1 or i == 8:
            print('|   |   |   | / | \ |   |   |   |   ')
        elif i == len(board)-1:
            print('')
        elif i == 4:
            print('|                               |   ')
        else:
            print('|   |   |   |   |   |   |   |   |   ')
    print('0   1   2   3   4   5   6   7   8   ')
    print()

def v_k(v, d):
    for i in d:
        if d[i] == v:
            return i
    raise ValueError


def format(name):
    chars = list(name)
    if chars[0] in ['r', 'b']:
        if chars[1] not in chinese_piece:
            raise ValueError
        return name
    else:
        color = let_color[chars[0]]
        if type(num_piece[chars[1]])==str:
            piece = num_piece[chars[1]]
        else:
            piece = num_piece[chars[1]][chars[0]]
        return color + piece
    
def fen_to_board(ord):
    fen = ord[0].split('/')
    for line in range(10):
        row = 0
        for item in fen[line]:
            if item.isdigit():
                for i in range(int(item)):
                    board[line][row] = "  "
                    row += 1
            elif item in fen_piece.keys():
                piece = fen_piece[item]
                color = 'r' if item.isupper() else 'b'
                board[line][row] = color + piece
                row += 1
            else:
                print('输入错误，请重新输入')
                return
    
def board_to_fen():
    fenstr = ""
    for line in board:
        empty = 0
        for item in line:
            if item == '  ':
                empty += 1
            else:
                if empty:
                    fenstr += str(empty)
                    empty = 0
                is_upper = item[0] == "r"
                let = v_k(item[1], fen_piece)
                if is_upper:
                    let = let.upper()
                else:
                    let = let.lower()
                fenstr += let
        if empty:
            fenstr += str(empty)
            empty = 0
        fenstr +=  "/"  
    fenstr = fenstr[:-1]    
    return fenstr
        
def change():
    
    print_board()
    print('''输入规则：每项间均用空格隔开
1.添加棋子：有四项，分别为'+'、棋子、添加到的位置的行、添加到的位置的列；
2.删除棋子：有三项，分别为'-'、删除的位置的行、删除的位置的列；
3.移动棋子：有四项，分别为原位置行、原位置列、新位置行、新位置列；
棋子表示方法：
1.两个字符，第一个字符为英文字母，b代表黑棋，r代表红棋，第二个字符为汉字，为棋子名称
2.两个字符，第一个字符以.代表红棋，以@代表黑棋，第二个字符为棋子价值（车9、炮5、马4、相3、仕2、兵1、帅0）
局面也可以用fen格式输入（仅输入中间最长的部分）
输入fen得到当前局面fen表示法。\n''')
    while True:
        ord = input('请输入操作').split()
        error = 0
        
        try:
            if ord[0] == '+':
                board[int(ord[2])][int(ord[3])] = format(ord[1])
            elif ord[0] == "-":
                board[int(ord[1])][int(ord[2])] = '  '
            elif ord[0].isdigit():
                board[int(ord[2])][int(ord[3])] = board[int(ord[0])][int(ord[1])]
                board[int(ord[0])][int(ord[1])] = "  "
            elif ord[0] == '退出':
                exit()    
            elif len(ord[0].split('/')) == 10:
                fen_to_board(ord)
            elif ord[0] == "fen":
                print(board_to_fen())
                error = 1
            else:
                print('输入错误，请重新输入')
                error=1
        except Exception:
            print('输入错误，请重新输入')
            error=1
        
        if not error:
            s('cls')
            print_board()


def main():
    global board
    a = input('从空白摆棋输入1，从原始局面摆棋输入2，其他任意键退出')
    if a == "1":
        board = []
        for i in range(10):
            board.append(['  '] * 9)
        change()
    elif a == "2":
        board = full_board[:]
        change()
    
    
if __name__ == "__main__":
    main()
