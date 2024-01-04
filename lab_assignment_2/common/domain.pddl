(define (domain assignment_2)
(:requirements :strips :typing :fluents :disjunctive-preconditions :durative-actions)
(:types
	waypoint
	robot
)
(:predicates
	(robot_at ?r - robot ?wp - waypoint)
	(visited ?wp - waypoint)
)
(:durative-action goto_waypoint
	:parameters (?v - robot ?from ?to - waypoint)
	:duration ( = ?duration 60)
	:condition (and
		(at start (robot_at ?v ?from)))
	:effect (and
		(at end (visited ?to))
		(at end (robot_at ?v ?to))
		(at start (not (robot_at ?v ?from))))
)


)