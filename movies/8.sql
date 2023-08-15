SELECT p.name
    FROM people AS p
    INNER JOIN stars AS s
    ON p.id = s.person_id
    INNER JOIN movies AS m
    ON s.movie_id = m.id
    WHERE m.title = 'Toy Story';