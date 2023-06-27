SELECT DISTINCT(p.name) FROM movies m, people p, ratings r, directors d
WHERE p.id = d.person_id
AND m.id = d.movie_id
AND m.id = r.movie_id
AND r.rating >= 9.0;