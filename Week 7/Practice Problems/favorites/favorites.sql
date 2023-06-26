UPDATE shows SET title ='Adventure Time' WHERE title like 'adventure time';
UPDATE shows SET title ='Arrow' WHERE title like 'arrow';
UPDATE shows SET title ='Avatar The Last Airbender' WHERE title like 'Avatar%';
UPDATE shows SET title ='Brooklyn 99' WHERE title like '%99';
UPDATE shows SET title ='Billions' WHERE title like '%billions';
UPDATE shows SET title ='Brooklyn Nine-Nine' WHERE title like '%99';
UPDATE shows SET title ='Community' WHERE title like '%ommunity';
UPDATE shows SET title ='Criminal Minds' WHERE title like '%minds';
UPDATE shows SET title ='Family Guy' WHERE title like '%guy';
UPDATE shows SET title ='Friends' WHERE title like '%riends%';
UPDATE shows SET title ='Game Of Thrones' WHERE title like '%Thrones';
UPDATE shows SET title ='Gilmore Girls' WHERE title like 'Gilmore%';
UPDATE shows SET title ='Game Of Thrones' WHERE title like '%GoT';
UPDATE shows SET title ='Grace And Frankie' WHERE title like '%Grace and Frankie';
UPDATE shows SET title ='Grey''s Anatomy' WHERE title like 'Grey%';
UPDATE shows SET title ='How I Met Your Mother' WHERE title like 'How i%';
UPDATE shows SET title ='Its Always Sunny In Philidelphia' WHERE title like '%Philidelphia';
UPDATE shows SET title ='Last Week Tonight With John Oliver' WHERE title like 'Last Week Tonight%';
UPDATE shows SET title ='Law And Order' WHERE title like 'Law and%';
UPDATE shows SET title ='Avatar The Last Airbender' WHERE title like '%Office%' OR title like '%office';
UPDATE shows SET title ='Parks And Recreation' WHERE title like 'Parks%';
UPDATE shows SET title ='Sherlock Homes' WHERE title like 'Sherlock%' OR title like 'sherlock%';
UPDATE shows SET title ='Squid Game' WHERE title like 'squid%';
UPDATE shows SET title ='The Bachelorette' WHERE title like '%bachelorette';
UPDATE shows SET title ='The Crown' WHERE title like '%CROWN';
UPDATE shows SET title ='The Untamed' WHERE title like '%Untamed';

-- Confirmation
SELECT * FROM shows GROUP BY title;