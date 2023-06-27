SELECT AVG(r.rating) FROM movies m, ratings r
WHERE m.id = r.movie_id
AND m.year = 2012;