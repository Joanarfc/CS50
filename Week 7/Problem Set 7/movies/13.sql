SELECT DISTINCT(p.name) FROM people p
JOIN stars s ON p.id = s.person_id
JOIN movies m ON m.id = s.movie_id
WHERE m.id IN (
	SELECT movies.id FROM movies
	JOIN stars AS s2 ON movies.id = s2.movie_id
	JOIN people AS p2 ON p2.id = s2.person_id
	WHERE p2.name = 'Kevin Bacon' AND p2.birth = 1958
)
AND p.name != 'Kevin Bacon';