-- write a SQL query to list the titles of all movies in IMDb with a release date on or after 2018,
-- in alphabetical order.
SELECT title
FROM movies
WHERE (year = '2018' OR year > '2018')
ORDER BY title ASC;

/*
SELECT COUNT(title)
FROM movies
WHERE (year = '2018' OR year > '2018');
*/
