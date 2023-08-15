SELECT DISTINCT p.name
    FROM people AS p
        INNER JOIN stars AS s
        ON p.id = s.person_id
        INNER JOIN movies AS m
        ON s.movie_id = m.id
        WHERE m.title IN
            (
                SELECT DISTINCT m.title
                    FROM movies AS m
                        INNER JOIN stars AS s
                        ON m.id = s.movie_id
                        INNER JOIN people as p
                        ON s.person_id = p.id
                        WHERE p.name = 'Kevin Bacon' AND p.birth = 1958
            )
            AND p.name <> 'Kevin Bacon';