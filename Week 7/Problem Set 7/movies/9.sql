SELECT p.name FROM movies m, people p, stars s
WHERE m.id = s.movie_id
AND p.id = s.person_id
AND m.year = 2004
ORDER BY p.birth;