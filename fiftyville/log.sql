-- Keep a log of any SQL queries you execute as you solve the mystery.

-- GET THE REPORTS
SELECT description
FROM crime_scene_reports
WHERE day = 28 AND street = 'Humphrey Street' AND month = 7;

-- GET THE TRANSCRIPTS FROM THE INTERVIEW
SELECT transcript
FROM interviews
WHERE day = 28 AND year = 2023 AND month = 7;

-- getting the license_plate
SELECT activity , license_plate FROM bakery_security_logs WHERE month = 7 AND year = 2023
AND day = 28  AND hour = 10;


-- GETTING THE PERSON_ID
SELECT  person_id
FROM  bank_accounts
WHERE account_number IN
   ( SELECT account_number
    FROM atm_transactions
    WHERE year = 2023 AND day = 28 AND month = 7 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
    );

--GETTING THE PASSPORT NUMBER
SELECT passport_number
FROM passengers
WHERE flight_id IN
(
    SELECT id
    FROM flights
    WHERE year = 2023 AND month = 7 AND day = 29 AND hour = 8 AND minute = 20 AND origin_airport_id = 8
);


-- INTEGRATING THE TWO SUB QURIES
SELECT person_id
FROM bank_accounts
WHERE account_number IN (
    SELECT account_number
    FROM atm_transactions
    WHERE year = 2023
    AND day = 28
    AND month = 7
    AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw'
)
AND person_id IN (
    SELECT person_id
    FROM passengers
    WHERE flight_id IN (
        SELECT id
        FROM flights
        WHERE year = 2023
        AND month = 7
        AND day = 29
        AND hour = 8
        AND minute = 20
        AND origin_airport_id = 8
    )
);


-- AMANDA = 632023  AND BROIS = 686048

-- trying to get the name of the person by a relationship between person_id (from the bank_accounts)...
-- ... and the people table
SELECT name
FROM people
WHERE id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE person_id = (
        SELECT person_id
FROM bank_accounts
WHERE account_number IN (
    SELECT account_number
    FROM atm_transactions
    WHERE year = 2023
    AND day = 28
    AND month = 7
    AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw'
)
AND person_id IN (
    SELECT person_id
    FROM passengers
    WHERE flight_id IN (
        SELECT id
        FROM flights
        WHERE year = 2023
        AND month = 7
        AND day = 29
        AND hour = 8
        AND minute = 20
        AND origin_airport_id = 8
    )
)

    )
    AND license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND hour = 10
)
);


-- the full name of the airport
SELECT abbreviation , full_name FROM airports WHERE city = 'Fiftyville';
-- Fiftyville Regional Airport

-- AND THE ID OF IT
SELECT id , full_name FROM airports WHERE full_name = 'Fiftyville Regional Airport';

-- trying get the time of the filght of the theif
SELECT hour , minute
FROM flights
WHERE day = 29 AND month = 7 AND year = 2023
ORDER BY hour ASC;

-- detrmine the destination_airport of the theif
SELECT full_name
FROM airports
WHERE id =
(
    SELECT destination_airport_id
    FROM flights
    WHERE year = 2023 AND month = 7 AND day = 29 AND hour = 8 AND minute = 20 AND origin_airport_id = 8
);
-- destination AIRPORT IS LaGuardia Airport

-- finding the name of the city which theif escaped into
SELECT city
FROM airports
WHERE full_name = 'LaGuardia Airport';

-- detrmine the theif number
SELECT phone_number
FROM people
WHERE name = 'Bruce'
AND license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND hour = 10
);
--  (821) 555-5262 caller

-- detect the receiver from phone_calls
SELECT receiver
FROM phone_calls
WHERE caller = '(367) 555-5533' AND duration < 60 AND year = 2023 AND month = 7 AND day = 28;


-- detect name
SELECT name
FROM people
WHERE phone_number = '(375) 555-8161';

