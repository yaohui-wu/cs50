SELECT COUNT(movies.title) AS number_of_movies
FROM movies
INNER JOIN ratings
ON movies.id = ratings.movie_id
WHERE rating = 10.0;