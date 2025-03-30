-- write a SQL query to list the titles and release years of all Harry Potter movies,
-- in chronological order
SELECT title , year
FROM movies
WHERE title LIKE 'Harry Potter%'
ORDER BY year;

/*
SELECT title , year
FROM movies
WHERE title LIKE '%Batman%'
ORDER BY year;
*/

/*
SELECT COUNT(title)
FROM movies
WHERE title LIKE '%Batman%'
*/
