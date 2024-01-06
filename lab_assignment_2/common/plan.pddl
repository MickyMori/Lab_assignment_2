Number of literals: 14
Constructing lookup tables:
Post filtering unreachable actions: 
[01;34mNo analytic limits found, not considering limit effects of goal-only operators[00m
All the ground actions in this problem are compression-safe
Initial heuristic = 8.000
b (7.000 | 120.001)b (6.000 | 120.002)b (5.000 | 180.003)b (4.000 | 180.004)b (3.000 | 240.005)b (2.000 | 240.006)b (1.000 | 300.007);;;; Solution Found
; States evaluated: 14
; Cost: 300.008
; Time 0.01
0.000: (goto_waypoint rosbot start wp1)  [60.000]
60.001: (find_marker rosbot m11 wp1)  [60.000]
60.002: (goto_waypoint rosbot wp1 wp2)  [60.000]
120.003: (find_marker rosbot m12 wp2)  [60.000]
120.004: (goto_waypoint rosbot wp2 wp3)  [60.000]
180.005: (find_marker rosbot m13 wp3)  [60.000]
180.006: (goto_waypoint rosbot wp3 wp4)  [60.000]
240.007: (find_marker rosbot m15 wp4)  [60.000]
240.008: (goto_waypoint rosbot wp4 start)  [60.000]
