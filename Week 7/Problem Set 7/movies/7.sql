SELECT m.title, r.rating FROM movies m, ratings r
WHERE m.id = r.movie_id
AND m.year = 2010
ORDER by r.rating desc, m.title;