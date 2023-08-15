SELECT m.title, r.rating
    FROM movies AS m
    INNER JOIN ratings AS r
    ON m.id = r.movie_id
    WHERE year = 2010
    ORDER BY r.rating DESC, m.title;