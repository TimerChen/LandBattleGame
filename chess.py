# cover 0: covered 1: clear -1: no chess here but we actually don't need a cover for the 2016 army chess system for all the chesses are already revealed
# col 0(id1) 1(id2) -1(no chess)
# kind 
# 0 司令 * 1
# 1 军长 * 1
# 2 师长 * 2
# 3 旅长 * 2
# 4 团长 * 2
# 5 营长 * 2
# 6 连长 * 3
# 7 排长 * 3
# 8 工兵 * 3
# 9 地雷 * 3
# 10炸弹 * 2
# 11军旗 * 1 
# move
# 地图禁区 -1
# 上下左右 0 1 2 3


import random

def showlist(x):
    for i in x:
        print(unpack(i))

def pack(x, y):
    return x * 5 + y
def unpack(x):
    return [int(x / 5), x % 5]

upward = set()
downward = set()
linsubway = set()
colsubway = set()
strongholds = set()
littleholds = set()
upward.update([pack(1, 0), pack(1, 2), pack(1, 4), pack(2, 1), pack(2, 3)])
upward.update([pack(3, 0), pack(3, 2), pack(3, 4), pack(4, 1), pack(4, 3)])
upward.update([pack(11, 0), pack(11, 2), pack(11, 4), pack(12, 1), pack(12, 3)])
upward.update([pack(13, 0), pack(13, 2), pack(13, 4), pack(14, 1), pack(14, 3)])
downward.update([pack(15, 0), pack(15, 2), pack(15, 4), pack(14, 1), pack(14, 3)])
downward.update([pack(13, 0), pack(13, 2), pack(13, 4), pack(12, 1), pack(12, 3)])
downward.update([pack(5, 0), pack(5, 2), pack(5, 4), pack(4, 1), pack(4, 3)])
downward.update([pack(3, 0), pack(3, 2), pack(3, 4), pack(2, 1), pack(2, 3)])
strongholds.update([pack(0, 1), pack(0, 3), pack(16, 1), pack(16, 3)])
littleholds.update([pack(2, 1), pack(2, 3), pack(3, 2), pack(4, 1), pack(4, 3)])
littleholds.update([pack(12, 1), pack(12, 3), pack(13, 2), pack(14, 1), pack(14, 3)])

for j in [1, 5, 6, 8, 10, 11, 15]:
    linsubway.update([pack(j, i) for i in range(5)])

for i in range(1, 16):
    colsubway.update([pack(i, j) for j in [0, 4]])
colsubway.update([pack(i, 2) for i in range(5, 12)])

class chess:
    def output(self):
        for i in range(4):
            for j in range(8):
                print(' ',self.kind[i][j],end=' ')
            print()
        print("---")
        for i in range(4):
            for j in range(8):
                print(' ',self.col[i][j],end=' ')
            print()
        print("----")
        for i in range(4):
            for j in range(8):
                print(' ',self.cover[i][j],end=' ')
            print()
            
    def __init__(self, arr0, arr1):
        #initialization defined by users
        #self.log = log
        #for a system that all chesses are already revealed, we actually don't need the cover list
        #self.cover = [[0 for i in range(5)] for i in range(17)]
        self.col = [[-1 for i in range(5)] for i in range(17)]
        self.kind = [[-1 for i in range(5)] for i in range(17)]
        self.cnt = []
        self.cnt.append(25) 
        self.cnt.append(25)
        cnt1 = cnt2 = 0
        
        # fill the color box with correct colors

        for i in range(6):
            for j in range(5):
                self.col[i][j] = 0
        self.col[2][1] = -1
        self.col[2][3] = -1
        self.col[3][2] = -1
        self.col[4][1] = -1
        self.col[4][3] = -1
        for i in range(11, 17):
            for j in range(5):
                self.col[i][j] = 1
        self.col[12][1] = -1
        self.col[12][3] = -1
        self.col[13][2] = -1
        self.col[14][1] = -1
        self.col[14][3] = -1

        self.kind[0][0] = arr0[0]
        self.kind[0][1] = arr0[1]
        self.kind[0][2] = arr0[2]
        self.kind[0][3] = arr0[3]
        self.kind[0][4] = arr0[4]
        self.kind[1][0] = arr0[5]
        self.kind[1][1] = arr0[6]
        self.kind[1][2] = arr0[7]
        self.kind[1][3] = arr0[8]
        self.kind[1][4] = arr0[9]
        self.kind[2][0] = arr0[10]
        self.kind[2][2] = arr0[11]
        self.kind[2][4] = arr0[12]
        self.kind[3][0] = arr0[13]
        self.kind[3][1] = arr0[14]
        self.kind[3][3] = arr0[15]
        self.kind[3][4] = arr0[16]
        self.kind[4][0] = arr0[17]
        self.kind[4][2] = arr0[18]
        self.kind[4][4] = arr0[19]
        self.kind[5][0] = arr0[20]
        self.kind[5][1] = arr0[21]
        self.kind[5][2] = arr0[22]
        self.kind[5][3] = arr0[23]
        self.kind[5][4] = arr0[24]
        
        self.kind[16][0] = arr1[4]
        self.kind[16][1] = arr1[3]
        self.kind[16][2] = arr1[2]
        self.kind[16][3] = arr1[1]
        self.kind[16][4] = arr1[0]
        self.kind[15][0] = arr1[9]
        self.kind[15][1] = arr1[8]
        self.kind[15][2] = arr1[7]
        self.kind[15][3] = arr1[6]
        self.kind[15][4] = arr1[5]
        self.kind[14][0] = arr1[12]
        self.kind[14][2] = arr1[11]
        self.kind[14][4] = arr1[10]
        self.kind[13][0] = arr1[16]
        self.kind[13][1] = arr1[15]
        self.kind[13][3] = arr1[14]
        self.kind[13][4] = arr1[13]
        self.kind[12][0] = arr1[19]
        self.kind[12][2] = arr1[18]
        self.kind[12][4] = arr1[17]
        self.kind[11][0] = arr1[24]
        self.kind[11][1] = arr1[23]
        self.kind[11][2] = arr1[22]
        self.kind[11][3] = arr1[21]
        self.kind[11][4] = arr1[20]
        
    def __inBoard__(self, x, y):
        return (0 <= x and x <= 5 and 0 <= y and y < 5) or (11 <= x and x <= 16 and 0 <= y and y < 5) or ((x == 6 or x == 8 or x == 10) and (y == 0 or y == 2 or y == 4))

    def __swap__(self, x, y, xx, yy):
        #self.cover[x][y], self.cover[xx][yy] = self.cover[xx][yy], self.cover[x][y]
        self.col[x][y], self.col[xx][yy] = self.col[xx][yy], self.col[x][y]
        self.kind[xx][yy] = self.kind[x][y]
        #self.kind[x][y], self.kind[xx][yy] = self.kind[xx][yy], self.kind[x][y]
    def __suicide__(self, attack, defend):
        if defend == -1:
            return False
        if attack == 10 or defend == 10:
            return True
        if attack == defend:
            return True
        if defend == 9:
            if attack == 8:
                return False
            else:    
                return True
        if attack >= defend:
            return True
        else: 
            return False
    def __eat__(self, attack, defend):
        if defend == -1:
            return False
        if attack == 10 or defend == 10:
            return True
        if attack != 8 and defend == 9:
            return False
        if attack == 8 and defend == 9:
            return True
        if attack <= defend:
            return True
        else: 
            return False
        
    def lin_closure(self, x, y):
        if x in [1, 5, 6, 8, 10, 11, 15]:
            l = max(0, y - 1)
            r = min(4, y + 1)
            while (l > 0):
                if self.col[x][l] != -1:
                    break
                l -= 1
            while (r < 4):
                if self.col[x][r] != -1:
                    break
                r += 1
            return set([pack(x, i) for i in range(l, r + 1)])
        else:
            return set([pack(x, y)])
        
    def col_closure(self, x, y):
        if y == 2:
            l = max(5, x - 1)
            r = min(11, x + 1)
            while (l > 5):
                if self.col[l][y] != -1:
                    break
                l -= 1
            while (r < 11):
                if self.col[r][y] != -1:
                    break
                r += 1
            return set([pack(i, y) for i in range(l, r + 1)])
        elif y == 0 or y == 4:
            l = max(1, x - 1)
            r = min(15, x + 1)
            while (l > 1):
                if self.col[l][y] != -1:
                    break
                l -= 1
            while (r < 15):
                if self.col[r][y] != -1:
                    break
                r += 1
            return set([pack(i, y) for i in range(l, r + 1)])
        else:
            return set([pack(x, y)])
    def total_closure(self, x, y):
        all = set()
        last = {i for i in self.lin_closure(x, y)}
        last.update({i for i in self.col_closure(x, y)})
        new = set()
        while True:
            for i in last:
                if self.kind[unpack(i)[0]][unpack(i)[1]] == -1:
                    new.update(self.lin_closure(unpack(i)[0], unpack(i)[1]))
                    new.update(self.col_closure(unpack(i)[0], unpack(i)[1]))
            last = last.difference(all)
            if len(last) == 0:
                break
            all.update(last)
            last = new
            new = set()
        return all
    def __move__(self, x, y, xx, yy):
        global flag, flag_suicide, upward, downward, linsubway, colsubway
        ret = False
        src = pack(x, y)
        flag = False;
        flag_suicide = False;
        if not self.__inBoard__(xx, yy):
            return ret
        else:
            if x == xx:
                if y == yy - 1 or y == yy + 1:
                    ret = True
            if y == yy:
                if x == xx - 1 or x == xx + 1:
                    ret = True
            if src in upward:
                if xx == x + 1 and (y == yy + 1 or y == yy - 1):
                    ret = True
            if src in downward:
                if xx == x - 1 and (y == yy + 1 or y == yy - 1):
                    ret = True
            if src in linsubway:
                if pack(xx, yy) in self.lin_closure(x, y):
                    ret = True
            if src in colsubway:
                if pack(xx, yy) in self.col_closure(x, y):
                    ret = True
            if self.kind[x][y] == 8 and src in self.lin_closure(x, y).union(self.col_closure(x,y)):
                if pack(xx, yy) in self.total_closure(x, y):
                    ret = True
        flag = self.__eat__(self.kind[x][y], self.kind[xx][yy])
        flag_suicide = self.__suicide__(self.kind[x][y], self.kind[xx][yy])
        return ret
            
        
    def check(self, color, res):
        #x, y, xx, yy = map(int, res.split(' '))
        x = res['posx']
        y = res['posy']
        xx = res['tox']
        yy = res['toy']
        #print(color,' ',res['posx'],' ',res['posy'],' ',res['tox'],' ',res['toy'])

        #print("-------------------------------")
        #self.output()
        if (not self.__inBoard__(x, y)) or (not self.__inBoard__(xx, yy)):
                        return 'wrong', 'Invalid Move', False
        if x == xx and y == yy:
            ret = 'wrong'
            error = 'Don\'t stay!'
            return ret, error, False
        if (self.col[x][y] == self.col[xx][yy]):
            ret = 'wrong'
            error = 'Don\'t make a civil war'
            return ret, error, False
        if pack(x, y) in strongholds:
            ret = 'wrong'
            error = 'Don\'t move a chess in a stronghold'
            return ret, error, False
        global flag, flag_suicide
        flag = False
        flag_suicide = False
        if self.__move__(x, y, xx, yy):
            if self.col[x][y] == color:
                if (self.kind[x][y] in {9, 11}):
                    ret = 'wrong'
                    error = 'You cannot move a static chess'
                    return ret, error, False
                if (flag or flag_suicide) and (pack(xx, yy) in littleholds):
                    ret = 'wrong'
                    error = 'You cannot attack a littlehold'
                    return ret, error, False
                flag_over = (self.kind[xx][yy] == 11)
                if flag:
                    self.cnt[color ^ 1] -= 1
                    self.kind[xx][yy] = -1
                    self.col[xx][yy] = -1
                if flag_suicide:
                    self.cnt[color] -= 1
                    self.kind[x][y] = self.kind[xx][yy]
                    self.col[x][y] = self.col[xx][yy]
                if flag and flag_over:
                    return 'end', 'good', True
                self.kind[xx][yy] = self.kind[x][y]
                self.col[xx][yy] = self.col[x][y]
                self.kind[x][y] = -1
                self.col[x][y] = -1
                ret = 'right'
                error = 'good'
                war = flag_suicide or flag
            else:
                ret = 'wrong'
                error = 'Not Your Chess'
                war = False
        else:
            ret = 'wrong'
            error = 'Out of the Board or Invalid Move'
            war = False
        
        if self.cnt[0] == 0 or self.cnt[1] == 0:
            ret = 'end'
            error = 'good'

        return ret, error, war

# map = chess([9,11,9,9,2,2,10,10,4,4,5,5,6,6,6,7,7,7,8,8,8,1,0,3,3], [9,11,9,9,2,2,10,10,4,4,5,5,6,6,6,7,7,7,8,8,8,1,0,3,3])

# def showall():
    # name = ['司令','军长','师长','旅长','团长','营长','连长','排长','工兵','地雷','炸弹','军旗']
    # print("void correct_move(int & x, int & y, int & xx, int & yy)")
    # print("{")
    # print("\tint p1 = map[x][y], p2 = map[xx][yy];")
    # print("\tif (p1 % TOTALKIND == p2 % TOTALKIND) throw -1;")
    # print("\tp2 %= TOTALKIND;")
    # for i in range(12):
        # for f in range(12):
            # # if i in {9, 11}:
                # # print(name[i]+'不能动')
                # # continue
            # # if map.__eat__(i, f) and map.__suicide__(i, f):
                # # print(name[i]+'和'+name[f]+'同归于尽')
                # # continue
            # # if (not map.__eat__(i, f)) and map.__suicide__(i, f):
                # # print(name[i]+'在'+name[f]+'那里送死了')
                # # continue
            # # if (not map.__suicide__(i, f)) and map.__eat__(i, f):
                # # print(name[i]+'击败了'+name[f])
                # # continue
            # # print('未知')
            # print("\tif (p1 == ", i, " && p2 == ", f, ")")
            # if map.__eat__(i, f) and map.__suicide__(i, f):
                # print("\t\tmap[x][y] = map[xx][yy] = -1;")
