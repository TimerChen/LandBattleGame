#!/usr/bin/env python3

import sys
import time
import json
import chess
import threading
import locale
from queue import Empty
from pprint import pprint
from stdio_ipc import ChildProcess

# meaning of op
# 翻面 -1
# 上下左右 0 1 2 3
# 炮上下左右 4 5 6 7

def action(ai):
    try:
        ai.send('action\n')
        message = ai.recv(timeout=1)
        posx, posy, tox, toy = map(int, message.strip().split(' '))
    except Empty as e:
        return { 'err': 'timeout' }
    except :
        return { 'err': 'wrong format. your output: %s' % repr(message) }
    return { 'posx': posx, 'posy': posy, 'tox': tox, 'toy': toy }

def message(ai, id, res):
    x = res['posx']
    y = res['posy']
    xx = res['tox']
    yy = res['toy']
    if board.col[xx][yy] != -1:
        ai.send('message\n%d %d %d %d %d %d\n' % (x, y, xx, yy, board.col[xx][yy], board.kind[xx][yy]))
    else:
        ai.send('message\n%d %d %d %d %d %d\n' % (x, y, xx, yy, 0, -2))
def get_init(ai):
    try:
        ai.send('init\n')
        message = ai.recv(timeout=2)
        list = [int(i) for i in message.strip().split(' ')]
        #print(list)
    except Empty as e:
        return { 'err': 'timeout' }
    except Exception as e:
        print(e)
        return { 'err' : str(e) }
    if len(list) != 25:
        return { 'err' : 'invalid init board' }
    if list[1] != 11 and list[3] != 11:
        return { 'err' : 'the flag should be placed in the stronghold' }
    count = [0 for i in range(12)]
    for i in range(10):
        count[list[i]] += 1
    if count[9] != 3:
        return { 'err' : 'the landmine can only be placed in the lowest two lines of your map.' }
    for i in range(10, 25):
        count[list[i]] += 1
    if count[0] != 1 or count[1] != 1 or count[2] != 2 or count[3] != 2 or count[4] != 2 or count[5] != 2 or count[6] != 3 or count[7] != 3 or count[8] != 3 or count[9] != 3 or count[10] != 2 or count[11] != 1:
        return { 'err' : 'invalid init board, some kind(s) is/are overused.' }
    for i in range(20, 25):
        if list[i] == 10:
            return { 'err' : 'you cannot set a bomb in the front line of your base.' }
    return list

def show_init(ai):
    global init0, init1;
    ai.send('refresh\n')
    for i in range(len(init0)):
        ai.send('%d ' % init0[i])
    ai.send('\n')
    for i in range(len(init1)):
        ai.send('%d ' % init1[i])
    ai.send('\n')
        
def send_id(ai, id):
    try:
        ai.send('id\n%d\n' % id)
        name = ai.recv(timeout=1).strip()
    except Empty as e:
        return { 'err': 'timeout' }
    except Exception as e:
        print(e)
        return { 'err' : str(e) }
    return name

def finish(winner, err0, err1):
    global running, name0, name1, first_sit, steps

     # kill ai and write stdio log
    if type(ai0) is not dict:
        ai0.exit()
    if type(ai1) is not dict:
        ai1.exit()

    # write result
    try:
        result = {
            'user': [name0, name1],
            'err': [err0, err1],
            'id': [0, 1],
            'first' : first_sit,
            'total': steps,
            'result': winner,
            'init-board' : init_board,
            'step' : Record
        }
    except :
        result = {
            'user': [name0, name1],
            'err': [err0, err1],
            'id': [0, 1],
            'first' : 0,
            'total': steps,
            'result': winner,
            'init-board' : [],
            'step' : []
        }

    if not is_p2dv:
        pprint(result)
    with open('result.json', 'w') as f:
        f.write(json.dumps(result))

    # exit
    running = False
    sys.exit(0)

def work(color, res):
    ret, error, war = board.check(color, res)
    if ret == 'right':
        return war
    elif ret == 'wrong':
        if color == 0:
            res['err'] = error
            finish(color_ai[1], '', '')
            return False
        else:
            res['err'] = error
            finish(color_ai[0], '', '')
            return False
    elif ret == 'end':
        finish(color_ai[color], '', '')
        return True

def check_both(ai0_success, ai1_success, res1, res2):
    if not ai0_success and not ai1_success:
        finish(2, res1['err'], res2['err'])
    elif not ai0_success and ai1_success:
        finish(1, res1['err'], '')
    elif not ai1_success and ai0_success:
        finish(0, '', res2['err'])

def spawnAI(args, save_stdin_path, save_stdout_path, save_stderr_path):
    try:
        ai = ChildProcess(args, save_stdin_path, save_stdout_path, save_stderr_path)
        return ai
    except:
        return { 'err': 'fail to spawn the program.' + str(sys.exc_info()[1]) }

def Record_Chess():
    for i in range(17):
        ret = []
        for j in range(5):
            ret.append({
                'kind' : board.kind[i][j],
                'color' : board.col[i][j]
            })
        init_board.append(ret)

def judge():
    global board, id0, id1, ai0, ai1, name0, name1, color_ai, steps, empty_steps, init_board, init0, init1, Record, first_sit



    # spawn AI
    seed_base = int(time.time() * 1e3) % 10000000000
    id0 = 0
    id1 = 1 - id0
    color_ai = [0, 0]
    color_ai[0] = 0
    color_ai[1] = 1
    ai0 = spawnAI([sys.argv[1], '%.0f' % (seed_base+0)], 'ai0_stdin.log', 'ai0_stdout.log', 'ai0_stderr.log')
    ai1 = spawnAI([sys.argv[2], '%.0f' % (seed_base+1)], 'ai1_stdin.log', 'ai1_stdout.log', 'ai1_stderr.log')
    check_both(type(ai0) is not dict, type(ai1) is not dict, ai0, ai1)
    # send ID and get name
    res0 = send_id(ai0, 0)
    res1 = send_id(ai1, 1)
    name0 = res0 if type(res0) is not dict else '[Unknown]'
    name1 = res1 if type(res1) is not dict else '[Unknown]'
    check_both(type(res0) is not dict, type(res1) is not dict, res0, res1)
    # start working
    steps = 0
    empty_steps = 0
    first_sit = seed_base % 2;
    now_sit = seed_base % 2
    Record = []
    init_board = []
    init0 = get_init(ai0)
    init1 = get_init(ai1)
    check_both(type(init0) is not dict, type(init1) is not dict, init0, init1)
    
    board = chess.chess(init0, init1)
    show_init(ai0)
    show_init(ai1)
    
    # record chess
    Record_Chess()
    
    eat_occurs = False
    while empty_steps < 50:
        steps += 1
        eat_occurs = False
        print("now it's the %d-th step" % steps)
        if now_sit == 0:
            res1 = action(ai0)
            Record.append(res1)
            check_both('err' not in res1, True, res1,'')
            eat_occurs = work(id0, res1)
            message(ai0, id0, res1)
            message(ai1, id0, res1)
            if eat_occurs:
                empty_steps = 0
            else:
                empty_steps += 1
            now_sit = now_sit^1
        else:
            res2 = action(ai1)
            Record.append(res2)
            check_both(True, 'err' not in res2, '', res2)
            eat_occurs = work(id1, res2)
            message(ai0, id1, res2)
            message(ai1, id1, res2)
            if eat_occurs:
                empty_steps = 0
            else:
                empty_steps += 1
            now_sit = now_sit^1

    # steps exceeded
    finish(2, 'steps exceeded', 'steps exceeded')

def p2dv():
    t = threading.Thread(target=judge)
    t.start()

    while True:
        line = sys.stdin.readline()
        if not running:
            sys.stderr.write('finished\n')
            sys.stderr.flush()
            break

        if line == 'get steps\n':
            sys.stderr.write('%d\n'%steps)

        sys.stderr.flush()

def main():
    global running, is_p2dv

    if not (len(sys.argv) in [3, 4]):
        print('usage:   ./main.py ai0Path ai1Path')
        print('example: ./main.py ./sample_ai ./sample_ai')
        print('')
        sys.exit(1)

    running = True

    if len(sys.argv) == 4 and sys.argv[3] == 'p2dv':
        is_p2dv = True
        p2dv()
    else:
        is_p2dv = False
        judge()


locale.setlocale(locale.LC_ALL, 'en_US.UTF-8')
steps = 0
name0 = 'Unknown'
name1 = 'Unknown'
main()
