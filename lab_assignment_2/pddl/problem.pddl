(define (problem task)
(:domain rosbot)
(:objects
    wp0 wp1 wp2 wp3 wp4 - waypoint
    rosbot - robot
    m11 m12 m13 m15 - marker
)
(:init
    (rosbot_at rosbot wp0)

    (marker_at m11 wp1)
    (marker_at m12 wp2)
    (marker_at m13 wp3)
    (marker_at m15 wp4)

)
(:goal (and
    (marker_found m11)
    (marker_found m12)
    (marker_found m13)
    (marker_found m15)
    (completed)
))
)
