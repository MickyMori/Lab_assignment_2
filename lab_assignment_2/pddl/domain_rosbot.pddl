(define (domain rosbot)
(:requirements :strips :typing :fluents :disjunctive-preconditions :durative-actions)
(:types
	 waypoint 
	 robot
	 marker
)

(:predicates
 (robot_at ?r - robot ?wp - waypoint)
 (visited ?wp - waypoint)
 (marker_found ?m - marker)
 (marker_at ?m - marker ?wp - waypoint)
 (return ?wp - waypoint)
)

(:functions
    (found)
)

;; Move to any waypoint, avoiding terrain
(:durative-action goto_waypoint
 :parameters (?r - robot ?from ?to - waypoint)
 :duration ( = ?duration 60)
 :condition (and
  (at start (robot_at ?r ?from)))
 :effect (and
  (at end (visited ?to))
  (at end (robot_at ?r ?to))
  (at start (not (robot_at ?r ?from))))
)

;; Find Aruco Markers
(:durative-action find_marker
 :parameters (?r - robot ?m - marker ?wp - waypoint)
 :duration ( = ?duration 60)
 :condition (and 
   (at start (robot_at ?v ?wp))
   (at start (maarker_at ?m ? wp)))
 :effect (and
   (at end (increase (found) 1))
   (at end (marker_found ?m)))
)

;; Return to start position
(:durative-action return_home
 :parameters (?r - robot ?from ?to - waypoint)
 :duration ( = ?duration 30)
 :condition (and
  (at start (= (found) 4))
  (at start (robot_at ?r ?from)))
 :effect (and
  (at start (not (robot_at ?r ?from)))
  (at end (return ?to))
  (at end (robot_at ?r ?to)))
)
)
