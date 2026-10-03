SELECT m.title
    FROM movies AS m
        INNER JOIN stars AS s
        ON m.id = s.movie_id
        INNER JOIN people AS p
        ON s.person_id = p.id
        WHERE p.name = 'Bradley Cooper'
        AND m.title IN
            (
                SELECT m.title
                    FROM movies AS m
                        INNER JOIN stars AS s
                        ON m.id = s.movie_id
                        INNER JOIN people AS p
                        ON s.person_id = p.id
                        WHERE p.name = 'Jennifer Lawrence'
            );