(define (domain rosbot)

(:requirements :typing :durative-actions :numeric-fluents :negative-preconditions :action-costs :conditional-effects :equality :fluents)

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
	 (connect ?wpx -waypoint ?wpy - waypoint)
)

;; Move to any waypoint, avoiding terrain
(:durative-action goto_waypoint
	 :parameters (?r - robot ?from ?to - waypoint)
	 :duration ( = ?duration 60)
	 :condition (and
	  		(at start (robot_at ?r ?from))
	  		(at start (connect ?from ?to)))
	 :effect (and
			(at start (not (robot_at ?r ?from)))
			(at end (visited ?to))
			(at end (robot_at ?r ?to)))
)

;; Find Aruco Markers
(:durative-action find_marker
	 :parameters (?r - robot ?m - marker ?wp - waypoint)
	 :duration ( = ?duration 60)
	 :condition (and 
		   	(at start (robot_at ?r ?wp))
		   	(at start (marker_at ?m ? wp)))
	 :effect (and
	   		(at end (marker_found ?m)))
)

)
