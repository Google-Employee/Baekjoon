import copy

class Board:
    def __init__(self, board, red_pos, blue_pos, hole_pos):
        self.content = board
        self.red_pos = red_pos
        self.blue_pos = blue_pos
        self.hole_pos = hole_pos


def getBoardInput():
    size_input = input()
    [height, width] = size_input.split(" ")

    board = Board([], None, None, None)

    for i in range(int(height)):
        row_input = input()
        if row_input.__contains__("R"):
            board.red_pos = [i, row_input.find("R")]
        if row_input.__contains__("B"):
            board.blue_pos = [i, row_input.find("B")]
        if row_input.__contains__("O"):
            board.hole_pos = [i, row_input.find("O")]
        row_list = list(row_input.replace("R", ".").replace("B", ".").replace("O", "."))
        board.content.append(row_list)

    return board


def get_elem(board, x, y):
    return board.content[x][y]


def move(board, elem, direction):
    assert direction == 'r' or \
           direction == 'l' or \
           direction == 'u' or \
           direction == 'd'

    if elem == 'R':
        pos = board.red_pos
        anti_pos = board.blue_pos
    if elem == 'B':
        pos = board.blue_pos
        anti_pos = board.red_pos

    if direction == 'd':
        adjacent_elem = get_elem(board, pos[0] + 1, pos[1])
        if adjacent_elem == '.' and [pos[0] + 1, pos[1]] != anti_pos:
            pos[0] += 1
            return 1
        else:
            return 0
    elif direction == 'u':
        adjacent_elem = get_elem(board, pos[0] - 1, pos[1])
        if adjacent_elem == '.' and [pos[0] - 1, pos[1]] != anti_pos:
            pos[0] -= 1
            return 1
        else:
            return 0
    elif direction == 'r':
        adjacent_elem = get_elem(board, pos[0], pos[1] + 1)
        if adjacent_elem == '.' and [pos[0], pos[1] + 1] != anti_pos:
            pos[1] += 1
            return 1
        else:
            return 0
    elif direction == 'l':
        adjacent_elem = get_elem(board, pos[0], pos[1] - 1)
        if adjacent_elem == '.' and [pos[0], pos[1] - 1] != anti_pos:
            pos[1] -= 1
            return 1
        else:
            return 0


def slide_ball(board, elem, direction):
    status = move(board, elem, direction)
    while status != 0:
        status = move(board, elem, direction)


def tilt(board, direction):
    if direction == 'r':
        if board.red_pos[0] > board.blue_pos[0]:
            slide_ball(board, 'R', direction)
            slide_ball(board, 'B', direction)
        else:
            slide_ball(board, 'B', direction)
            slide_ball(board, 'R', direction)
    elif direction == 'l':
        if board.red_pos[0] > board.blue_pos[0]:
            slide_ball(board, 'B', direction)
            slide_ball(board, 'R', direction)
        else:
            slide_ball(board, 'R', direction)
            slide_ball(board, 'B', direction)
    elif direction == 'd':
        if board.red_pos[1] > board.blue_pos[1]:
            slide_ball(board, 'R', direction)
            slide_ball(board, 'B', direction)
        else:
            slide_ball(board, 'B', direction)
            slide_ball(board, 'R', direction)
    elif direction == 'u':
        if board.red_pos[1] > board.blue_pos[1]:
            slide_ball(board, 'B', direction)
            slide_ball(board, 'R', direction)
        else:
            slide_ball(board, 'R', direction)
            slide_ball(board, 'B', direction)

    return board


def calc_min(a, b):
    if a is not None and b is not None:
        return min(a, b)
    else:
        return b


def calc_count(board, max_count, direction):
    if max_count < 0:
        raise RuntimeError("max count를 초과했습니다.")
    if direction != 'r':
        tilt_r = tilt(copy.deepcopy(board), 'r')
    if direction != 'l':
        tilt_l = tilt(copy.deepcopy(board), 'l')
    if direction != 'u':
        tilt_u = tilt(copy.deepcopy(board), 'u')
    if direction != 'd':
        tilt_d = tilt(copy.deepcopy(board), 'd')

    if (tilt_r.red_pos == board.hole_pos \
            or tilt_l.red_pos == board.hole_pos \
            or tilt_u.red_pos == board.hole_pos \
            or tilt_d.red_pos == board.hole_pos):
        return 1

    result = None

    r_success = True
    l_success = True
    u_success = True
    d_success = True

    try:
        if direction != 'r':
            result = calc_count(tilt_r, max_count - 1, direction) + 1
    except RuntimeError:
        r_success = False
    try:
        if direction != 'r':
            result = calc_min(result, calc_count(tilt_l, max_count - 1, direction) + 1)
    except RuntimeError:
        l_success = False
    try:
        if direction != 'r':
            result = calc_min(result, calc_count(tilt_u, max_count - 1, direction) + 1)
    except RuntimeError:
        u_success = False
    try:
        if direction != 'r':
            result = calc_min(result, calc_count(tilt_d, max_count - 1, direction) + 1)
    except RuntimeError:
        d_success = False

    if r_success or l_success or u_success or d_success:
        return result
    else:
        raise RuntimeError("max count를 초과했습니다.")


prob_input = getBoardInput()
try:
    print(calc_count(prob_input, 4, ""))
except RuntimeError as e:
    print(-1)
