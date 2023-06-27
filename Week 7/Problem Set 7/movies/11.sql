SELECT DISTINCT(m.title) FROM movies m, stars s, ratings r, people p
WHERE m.id = s.movie_id
AND m.id = r.movie_id
AND p.name = 'Chadwick Boseman'
AND s.person_id = p.id
ORDER BY r.rating DESC
LIMIT 5;