SELECT COUNT(*) FROM movies m, ratings r
WHERE m.id = r.movie_id
AND r.rating = 10.0;