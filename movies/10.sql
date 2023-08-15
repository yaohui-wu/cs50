SELECT DISTINCT p.name
    FROM people AS p
        INNER JOIN directors AS d
        ON p.id = d.person_id
        INNER JOIN ratings AS r
        USING (movie_id)
        WHERE r.rating >= 9.0;