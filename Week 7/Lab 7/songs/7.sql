SELECT AVG(s.energy) as Energy FROM songs s, artists a
WHERE s.artist_id = a.id
AND a.name like '%Drake';