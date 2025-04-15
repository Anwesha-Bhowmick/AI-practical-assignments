import heapq
import copy

def display_puzzle(state):
    for i in state:
        print(" ".join(map(str, i)))
    print()

def find_blank_tile(state):
    for i in range(3):
        for j in range(3):
            if state[i][j]==0:
                return i, j
                
def is_valid_move(x,y):
    return 0<=x<3 and 0<=y<3

def generate_neighbours(state):
    neighbours=[]
    x,y = find_blank_tile(state)
    dx=[1, -1, 0, 0]
    dy=[0, 0, -1, 1]
    for i in range(4):
        new_x = x+dx[i]
        new_y = y+dy[i]
        if is_valid_move(new_x, new_y):
            new_state = copy.deepcopy(state)
            new_state[x][y] , new_state[new_x][new_y] = new_state[new_x][new_y] , new_state[x][y] #swap the tiles
            neighbours.append((new_state, (new_x,new_y)))
    return neighbours

def misplaced_tiles(state, goal):
    sum=0
    for i in range(3):
        for j in range(3):
            if state[i][j]!=0 and state[i][j]!=goal[i][j]:
                sum+=1
    return sum;

def manhattan_distance(state, goal):
    distance =0
    for i in range(3):
        for j in range(3):
            if state[i][j]!=0:
                value = state[i][j]
                goal_x, goal_y = [(x,y) for x in range(3) for y in range(3) if goal[x][y]==value][0]
                distance += abs(goal_x - i) + abs(goal_y - j)
    return distance

def astar(start, goal, heuristic):
    open_set = []
    closed_set = set()
    nodes_expanded = 0

    heapq.heappush(open_set, (0, start, []))#cost current path

    while open_set:
        cost, current, path = heapq.heappop(open_set)

        if tuple(map(tuple, current)) in closed_set:
            continue

        closed_set.add(tuple(map(tuple, current)))
        if current==goal:
            return path, nodes_expanded

        nodes_expanded+=1
        for neighbour, moves in generate_neighbours(current):
            if tuple(map(tuple, neighbour)) not in closed_set:
                new_cost = cost + 1 + heuristic(neighbour, goal)
                heapq.heappush(open_set,(new_cost, neighbour, path + [neighbour]))

    return None, nodes_expanded
                
        
        

def solve():
  start = [
    [2, 8, 3],
    [1, 6, 4],
    [7, 0, 5]
  ]
  goal = [
    [1, 2, 3],
    [8, 0, 4],
    [7, 6, 5]
  ]
  
  print("start state: ")
  display_puzzle(start)
  print("goal state: ")
  display_puzzle(goal)

  print("solution using misplaced tiles: ")
  solution1, nodes1 = astar(start, goal, misplaced_tiles)
  if solution1:
    print("path : ")
    for step in solution1:
      display_puzzle(step)
    print(f"no of nodes expanded = {nodes1}")
  else: 
    print("could not find solution")

  print("solution using manhattan distance: ")
  solution2, nodes2 = astar(start, goal, manhattan_distance)
  if solution2:
    print("path : ")
    for step in solution2:
      display_puzzle(step)
    print(f"no of nodes expanded = {nodes2}")
  else: 
    print("could not find solution")

if __name__=="__main__":
  solve()
