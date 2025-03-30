-- write a SQL query to list the names and their counts of all people
-- who have directed a movie that received a rating of at least 9.0.
SELECT DISTINCT name
FROM people
WHERE id IN
(
    SELECT person_id
    FROM directors
    WHERE movie_id IN (
        SELECT movie_id
        FROM ratings
        WHERE rating >= 9.0
    )
);

/*
SELECT COUNT(name)
FROM people
WHERE id IN
(
    SELECT person_id
    FROM stars
    WHERE movie_id IN (
        SELECT movie_id
        FROM ratings
        WHERE rating >= 9.0
    )
);
*/
