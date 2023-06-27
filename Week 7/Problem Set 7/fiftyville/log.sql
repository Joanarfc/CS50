-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Query used to find the crime scene for the CS50's duck theft
SELECT * FROM crime_scene_reports
WHERE day = 28 AND month = 7 AND year = 2021 AND street LIKE 'Humphrey%';

/* Result:
id   year  month  day  street           description
---  ----  -----  ---  ---------------  ------------------------------------------------------------
295  2021  7      28   Humphrey Street  Theft of the CS50 duck took place at 10:15am at the Humphrey
                                         Street bakery. Interviews were conducted today with three w
                                        itnesses who were present at the time - each of their interv
                                        iew transcripts mentions the bakery.

297  2021  7      28   Humphrey Street  Littering took place at 16:36. No known witnesses.

The crime scene report with id = 297, does not mention the theft, so it has to be the id = 295.
With this result, we now know that we have:
- the theft took place at 10:15 am 3 witnesses, at the Humphrey Street bakery
- 3 witnesses were interviewd
*/

SELECT * from interviews
WHERE transcript LIKE '%akery%'
AND year = 2021 AND month = 7 AND day = 28;

/* Result:
id   name     year  month  day  transcript
---  -------  ----  -----  ---  ------------------------------------------------------------
161  Ruth     2021  7      28   Sometime within ten minutes of the theft, I saw the thief ge
                                t into a car in the bakery parking lot and drive away. If yo
                                u have security footage from the bakery parking lot, you mig
                                ht want to look for cars that left the parking lot in that t
                                ime frame.

162  Eugene   2021  7      28   I don't know the thief's name, but it was someone I recogniz
                                ed. Earlier this morning, before I arrived at Emma's bakery,
                                 I was walking by the ATM on Leggett Street and saw the thie
                                f there withdrawing some money.

163  Raymond  2021  7      28   As the thief was leaving the bakery, they called someone who
                                 talked to them for less than a minute. In the call, I heard
                                 the thief say that they were planning to take the earliest
                                flight out of Fiftyville tomorrow. The thief then asked the
                                person on the other end of the phone to purchase the flight
                                ticket.

Things we know now with this result:
1. the thief used a car after 10 min of the theft. So, the theft occurred at 10:15am, and around 10:25am the thief used a car
-> check footages of the bakery parking lot (bakery_security_logs table)
*/
SELECT p.name FROM people p
JOIN bakery_security_logs bsl ON bsl.license_plate = p.license_plate
WHERE year = 2021 AND month = 7 AND day = 28
AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = 'exit'
ORDER BY p.name;

/* Result:
With this query we get the following suspect's names:
name
-------
Barry
Bruce
Diana
Iman
Kelsey
Luca
Sofia
Vanessa
*/

/* 2. when he left the bakery, the thief called someone to book a flight out of Fiftyville for the earliest flight tomorrow (so day 29)
-> check the phone calls and the flights
*/
-- Query to check the phone calls:
SELECT p.name FROM people p
JOIN phone_calls pc ON pc.caller= p.phone_number
WHERE pc.year = 2021 AND pc.month = 7 AND pc.day = 28 AND pc.duration < 60
ORDER BY p.name;

/* Result:
With this query we get the following suspect's names:
name
-------
Benista
Bruce
Carina
Diana
Kelsey
Kelsey
Kenny
Sofia
Taylor
*/

-- Query to check the flights:
SELECT p.name from people p
JOIN passengers pa ON pa.passport_number = p.passport_number
WHERE pa.flight_id = (
	SELECT id FROM flights f
	WHERE f.year = 2021 AND f.month = 7 AND f.day = 29
	AND f.origin_airport_id = (
	SELECT id FROM airports WHERE city = 'Fiftyville')
ORDER BY f.hour, f.minute)
ORDER BY p.name;

/* Result:
With this query we get the following suspect's names:
name
------
Bruce
Doris
Edward
Kelsey
Kenny
Luca
Sofia
Taylor
*/

/* 3. thief withdraw some money at the ATM on Leggett Street
-> check ATM records
*/
-- Query to check ATM records:
SELECT p.name FROM people p
JOIN bank_accounts ba ON ba.person_id = p.id
JOIN atm_transactions at ON at.account_number = ba.account_number
WHERE at.atm_location = 'Leggett Street'
AND at.year = 2021 AND at.month = 7 AND at.day = 28
AND at.transaction_type = 'withdraw'
ORDER BY p.name;

/* Result:
With this query we get the following suspect's names:
name
-------
Benista
Brooke
Bruce
Diana
Iman
Kenny
Luca
Taylor
*/

-- By combining the information from the 3 transcripts, we get:
SELECT p.name FROM people p
JOIN bank_accounts ba ON ba.person_id = p.id
JOIN atm_transactions at ON at.account_number = ba.account_number
JOIN phone_calls pc ON pc.caller= p.phone_number
JOIN bakery_security_logs bsl ON bsl.license_plate = p.license_plate
JOIN passengers pa ON pa.passport_number = p.passport_number
WHERE at.atm_location = 'Leggett Street'
AND at.year = 2021 AND at.month = 7 AND at.day = 28
AND at.transaction_type = 'withdraw'
AND pc.year = 2021 AND pc.month = 7 AND pc.day = 28 AND pc.duration < 60
AND bsl.year = 2021 AND bsl.month = 7 AND bsl.day = 28
AND bsl.hour = 10 AND bsl.minute >= 15 AND bsl.minute <= 25 AND bsl.activity = 'exit'
AND pa.flight_id = (
	SELECT id FROM flights f
	WHERE f.year = 2021 AND f.month = 7 AND f.day = 29
	AND f.origin_airport_id = (
	SELECT id FROM airports WHERE city = 'Fiftyville')
ORDER BY f.hour, f.minute)
ORDER BY p.name;

/* Result:
name
-----
Bruce

So, Bruce is the thief.
*/

-- Now, we need to know the destination:
SELECT p.name, origin_airport.city AS origin_city, destination_airport.city AS destination_city
FROM flights f
JOIN airports AS origin_airport ON f.origin_airport_id = origin_airport.id
JOIN airports AS destination_airport ON f.destination_airport_id = destination_airport.id
JOIN passengers pa ON f.id = pa.flight_id
JOIN people p ON pa.passport_number = p.passport_number
WHERE f.year = 2021
AND f.month = 7
AND f.day = 29
AND origin_airport.city = 'Fiftyville'
AND p.name = 'Bruce';

/* Result:
origin_city  destination_city
-----------  ----------------
Fiftyville   New York City

So, the destination of the flight is New York City
*/

-- Now we need to know who is the Bruce's accomplice (the person for which he called)
SELECT p.name AS receiver_name
FROM phone_calls pc
JOIN people p ON pc.receiver = p.phone_number
WHERE pc.year = 2021
  AND pc.month = 7
  AND pc.day = 28
  AND pc.duration < 60
  AND pc.caller = (SELECT phone_number FROM people WHERE name = 'Bruce');

/* Result:
receiver_name
-------------
Robin

So, Robin is the accomplice.
*/