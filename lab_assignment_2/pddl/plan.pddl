Number of literals: 19
Constructing lookup tables: [10%] [20%] [30%] [40%] [50%] [60%] [70%] [80%] [90%] [100%]
Post filtering unreachable actions:  [10%] [20%] [30%] [40%] [50%] [60%] [70%] [80%] [90%] [100%]
[01;34mNo analytic limits found, not considering limit effects of goal-only operators[00m
92% of the ground temporal actions in this problem are compression-safe
Initial heuristic = 17.000
b (14.000 | 120.002)b (13.000 | 120.002)b (10.000 | 180.004)b (9.000 | 180.004)b (8.000 | 240.006)b (6.000 | 300.007)b (5.000 | 300.007)b (3.000 | 360.009)b (1.000 | 360.009);;;; Solution Found
; States evaluated: 43
; Cost: 390.010
; Time 0.02
0.000: (goto_waypoint rosbot start wp1)  [60.000]
60.001: (find_marker rosbot m11 wp1)  [60.000]
60.002: (goto_waypoint rosbot wp1 wp2)  [60.000]
120.003: (find_marker rosbot m12 wp2)  [60.000]
120.004: (goto_waypoint rosbot wp2 wp3)  [60.000]
180.005: (find_marker rosbot m13 wp3)  [60.000]
180.006: (goto_waypoint rosbot wp3 start)  [60.000]
240.007: (goto_waypoint rosbot start wp4)  [60.000]
300.008: (find_marker rosbot m15 wp4)  [60.000]
300.009: (goto_waypoint rosbot wp4 start)  [60.000]
360.010: (return_home rosbot start start)  [30.000]
