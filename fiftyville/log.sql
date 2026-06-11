-- Keep a log of any SQL queries you execute as you solve the mystery.
 -- Getting description of the crimes at Humphrey Street on 28 July 2025

SELECT description
FROM crime_scene_reports
WHERE (YEAR = 2025
       AND MONTH = 7
       AND DAY = 28
       AND street = "Humphrey Street");

-- Getting details on the people interviewed at the crime scene

SELECT name,
       transcript
FROM interviews
WHERE transcript LIKE "%bakery%";

-- Checking bakery security logs for details of cars in parking lot within 10 minutes of crime

SELECT activity,
       license_plate
FROM bakery_security_logs
WHERE (YEAR = 2025
       AND MONTH = 7
       AND DAY = 28
       AND HOUR = 10
       AND (MINUTE > 15
            AND MINUTE < 25));

-- Checking atm transactions in the morning of the crime scene at Leggett Street

SELECT account_number,
       amount
FROM atm_transactions
WHERE (YEAR = 2025
       AND MONTH = 7
       AND DAY = 28
       AND atm_location = "Leggett Street"
       AND transaction_type = "withdraw");

-- Checking person_id of the people who withdrew money that day on Leggett Street

SELECT person_id
FROM bank_accounts
WHERE account_number IN
        (SELECT account_number
         FROM atm_transactions
         WHERE (YEAR = 2025
                AND MONTH = 7
                AND DAY = 28
                AND atm_location = "Leggett Street"
                AND transaction_type = "withdraw"));

-- Checking names of people against the person_id for suspects

SELECT name
FROM people
WHERE id IN
        (SELECT person_id
         FROM bank_accounts
         WHERE account_number IN
                 (SELECT account_number
                  FROM atm_transactions
                  WHERE (YEAR = 2025
                         AND MONTH = 7
                         AND DAY = 28
                         AND atm_location = "Leggett Street"
                         AND transaction_type = "withdraw")));

-- Checking names of people who drove out of parking lot that day for suspects

SELECT name
FROM people
WHERE license_plate IN
        (SELECT license_plate
         FROM bakery_security_logs
         WHERE (YEAR = 2025
                AND MONTH = 7
                AND DAY = 28
                AND HOUR = 10
                AND (MINUTE > 15
                     AND MINUTE < 25)));

-- Getting names of final suspects who both drove out of bakery parking and withdew money at leggett street

SELECT name
FROM people
WHERE id IN
        (SELECT person_id
         FROM bank_accounts
         WHERE account_number IN
                 (SELECT account_number
                  FROM atm_transactions
                  WHERE (YEAR = 2025
                         AND MONTH = 7
                         AND DAY = 28
                         AND atm_location = "Leggett Street"
                         AND transaction_type = "withdraw"))) INTERSECT
SELECT name
FROM people
WHERE license_plate IN
        (SELECT license_plate
         FROM bakery_security_logs
         WHERE (YEAR = 2025
                AND MONTH = 7
                AND DAY = 28
                AND HOUR = 10
                AND (MINUTE > 15
                     AND MINUTE < 25)));

-- Checking receiver of phone calls made by these people that day which lasted less than a minute

SELECT caller,
       receiver
FROM phone_calls
WHERE (YEAR = 2025
       AND MONTH = 7
       AND DAY = 28
       AND duration < 60
       AND caller IN
           (SELECT phone_number
            FROM people
            WHERE name IN
                    (SELECT name
                     FROM people
                     WHERE id IN
                             (SELECT person_id
                              FROM bank_accounts
                              WHERE account_number IN
                                      (SELECT account_number
                                       FROM atm_transactions
                                       WHERE (YEAR = 2025
                                              AND MONTH = 7
                                              AND DAY = 28
                                              AND atm_location = "Leggett Street"
                                              AND transaction_type = "withdraw"))) INTERSECT SELECT name
                     FROM people
                     WHERE license_plate IN
                             (SELECT license_plate
                              FROM bakery_security_logs
                              WHERE (YEAR = 2025
                                     AND MONTH = 7
                                     AND DAY = 28
                                     AND HOUR = 10
                                     AND (MINUTE > 15
                                          AND MINUTE < 25))))));

-- Getting names of caller that matched

SELECT name
FROM people
WHERE phone_number IN
        (SELECT caller
         FROM phone_calls
         WHERE (YEAR = 2025
                AND MONTH = 7
                AND DAY = 28
                AND duration < 60
                AND caller IN
                    (SELECT phone_number
                     FROM people
                     WHERE name IN
                             (SELECT name
                              FROM people
                              WHERE id IN
                                      (SELECT person_id
                                       FROM bank_accounts
                                       WHERE account_number IN
                                               (SELECT account_number
                                                FROM atm_transactions
                                                WHERE (YEAR = 2025
                                                       AND MONTH = 7
                                                       AND DAY = 28
                                                       AND atm_location = "Leggett Street"
                                                       AND transaction_type = "withdraw"))) INTERSECT SELECT name
                              FROM people
                              WHERE license_plate IN
                                      (SELECT license_plate
                                       FROM bakery_security_logs
                                       WHERE (YEAR = 2025
                                              AND MONTH = 7
                                              AND DAY = 28
                                              AND HOUR = 10
                                              AND (MINUTE > 15
                                                   AND MINUTE < 25)))))));

-- Getting names of receiver that matched

SELECT name
FROM people
WHERE phone_number IN
        (SELECT receiver
         FROM phone_calls
         WHERE (YEAR = 2025
                AND MONTH = 7
                AND DAY = 28
                AND duration < 60
                AND caller IN
                    (SELECT phone_number
                     FROM people
                     WHERE name IN
                             (SELECT name
                              FROM people
                              WHERE id IN
                                      (SELECT person_id
                                       FROM bank_accounts
                                       WHERE account_number IN
                                               (SELECT account_number
                                                FROM atm_transactions
                                                WHERE (YEAR = 2025
                                                       AND MONTH = 7
                                                       AND DAY = 28
                                                       AND atm_location = "Leggett Street"
                                                       AND transaction_type = "withdraw"))) INTERSECT SELECT name
                              FROM people
                              WHERE license_plate IN
                                      (SELECT license_plate
                                       FROM bakery_security_logs
                                       WHERE (YEAR = 2025
                                              AND MONTH = 7
                                              AND DAY = 28
                                              AND HOUR = 10
                                              AND (MINUTE > 15
                                                   AND MINUTE < 25)))))));

-- Final list of suspects and accomplices
-- Bruce & Robin
-- Diana % Philip
 -- Checking Flights & Airport data to finalise the criminal
 -- Finding airport ID and name of Fiftyville Airport

SELECT id,
       full_name
FROM airports
WHERE city = "Fiftyville";

-- Finding flights from Fiftyville Airport the next day

SELECT id,
       destination_airport_id,
       HOUR,
       MINUTE
FROM flights
WHERE (origin_airport_id = 8
       AND YEAR = 2025
       AND MONTH = 7
       AND DAY = 29);

-- Finding name of destination airport

SELECT city,
       full_name,
       abbreviation
FROM airports
WHERE id = 4;

-- Creating table of final suspects

CREATE TABLE final_suspects (person_id INT NOT NULL,
                                           name TEXT NOT NULL,
                                                     passport_number INT NOT NULL,
                             FOREIGN KEY(person_id) REFERENCES people(id));


INSERT INTO final_suspects (name, person_id, passport_number)
VALUES ("Bruce",(SELECT id FROM people WHERE name = "Bruce"), (SELECT passport_number FROM people WHERE name = "Bruce"));


INSERT INTO final_suspects (name, person_id, passport_number)
VALUES ("Diana",(SELECT id FROM people WHERE name = "Diana"), (SELECT passport_number FROM people WHERE name = "Diana"));

-- Creating table of final accomplices suspect

CREATE TABLE accomplice_suspects (person_id INT NOT NULL,
                                                name TEXT NOT NULL,
                                                          passport_number INT ,
                                  FOREIGN KEY(person_id) REFERENCES people(id));


INSERT INTO accomplice_suspects (name, person_id, passport_number)
VALUES ("Philip",(SELECT id FROM people WHERE name = "Philip"), (SELECT passport_number FROM people WHERE name = "Philip"));

-- Selecting passport number from passengers of identified flight which matches with an entry in final_suspects

SELECT passport_number
FROM passengers
WHERE (flight_id = 36
       AND passport_number IN
           (SELECT passport_number
            FROM final_suspects));

-- Matching the name of the criminal against the passport number

SELECT name
FROM people
WHERE passport_number =
        (SELECT passport_number
         FROM passengers
         WHERE (flight_id = 36
                AND passport_number IN
                    (SELECT passport_number
                     FROM final_suspects)));

-- Creating table with name of the criminal and details

CREATE TABLE criminal (person_id INT NOT NULL,
                                     name TEXT NOT NULL,
                                               passport_number INT NOT NULL,
                                                                   license_plate TEXT NOT NULL,
                       FOREIGN KEY(person_id) REFERENCES people(id));


INSERT INTO criminal (name, person_id, passport_number, license_plate)
VALUES ("Bruce", (SELECT id FROM people WHERE name = "Bruce"), (SELECT passport_number FROM people WHERE name = "Bruce"), (SELECT license_plate FROM people WHERE name = "Bruce"));
