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
	:parameters (?r - robot ?from ?to - waypoint)
	:duration ( = ?duration 60)
	:condition (
		(at start (robot_at ?r ?from)))
	:effect (and
		(at end (robot_at ?r ?to))
		(at start (not (robot_at ?r ?from))))
)

(:durative-action visits
	:parameters (?r - robot ?wp - waypoint)
	:duration ( = ?duration 3)
	:condition (over all (robot_at ?r ?wp))
	:effect (at end (visited ?wp))
)



)
