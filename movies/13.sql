-- List the names of all people who starred in a movie in which Kevin Bacon also starred
/*
SELECT name
FROM people
WHERE id IN
(
    SELECT person_id
    FROM stars
    WHERE movie_id IN
    (
        SELECT id
        FROM people
        WHERE name = 'Kevin Bacon'
    )
)


-- Find the ID of Kevin Bacon (the one born in 1958!)
SELECT id
FROM people
WHERE name = 'Kevin Bacon'

-- Find the IDs of movies associated with Kevin Bacon’s ID
SELECT movie_id
FROM stars
WHERE person_id = (
    SELECT id
    FROM people
    WHERE name = 'Kevin Bacon'
)

-- Find the IDs of people associated with those movie IDs
SELECT id
FROM people
WHERE id IN (
    SELECT person_id
    FROM stars
    WHERE movie_id =
        SELECT movie_id
        FROM stars
        WHERE person_id = (
            SELECT id
            FROM people
            WHERE name = 'Kevin Bacon'
    )
)
*/
-- Find the names of people with those people IDs
SELECT name
FROM people
WHERE id IN
(
    SELECT id
    FROM people
    WHERE id IN (
        SELECT person_id
        FROM stars
        WHERE movie_id IN (
            SELECT movie_id
            FROM stars
            WHERE person_id = (
                SELECT id
                FROM people
                WHERE name = 'Kevin Bacon'
    )
)
)
)
AND name != 'Kevin Bacon';
