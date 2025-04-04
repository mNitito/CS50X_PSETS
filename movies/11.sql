-- write a SQL query to list the titles of the five highest rated movies (in order) ..
-- .. that Chadwick Boseman starred in, starting with the highest rated.
/*
SELECT title
FROM movies m
JOIN stars s ON s.movie_id = m.id
JOIN ratings r ON r.movie_id = m.id
JOIN people p ON p.id = person_id
WHERE p.name = 'Chadwick Boseman'
ORDER BY r.rating DESC
LIMIT 5;
*/
SELECT title
FROM movies
JOIN ratings ON ratings.movie_id = movies.id
WHERE id IN
(
    SELECT movie_id
    FROM stars
    WHERE person_id IN
    (
        SELECT id
        FROM people
        WHERE name = 'Chadwick Boseman'
    )
)
ORDER BY rating DESC
LIMIT 5;
