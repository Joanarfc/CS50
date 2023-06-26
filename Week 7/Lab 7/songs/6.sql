SELECT s.name FROM songs s, artists a
WHERE s.artist_id = a.id
AND a.name like '%Malone';