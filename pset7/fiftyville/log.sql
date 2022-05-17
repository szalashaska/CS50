-- Keep a log of any SQL queries you execute as you solve the mystery.
--Theft took place at Chaberlin Street, 28-07-2020

SELECT street, description FROM crime_scene_reports WHERE year = 2020 AND month = 7 AND day = 28;
--Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
--Interviews were conducted today with three witnesses, each of their interview transcripts mentions the courthouse.

SELECT name, transcript FROM interviews WHERE year = 2020 AND month = 7 AND day = 28;
--Ruth: ~10 min of theft, thief got into car in the courthause parking lot and left
--Eugene: Recognizes the thief. She saw him withdraw money by ATM on Fifer Street earlier this morning.
--Reymond: Thief leving the courthouse called for < 1 min. In call he said they're taking earliest flight out of Fiftyville next day. Thief asked the person to buy ticket.

--Lincense plate number:
SELECT hour, minute, activity, license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 10 AND 25;

--ATM withdrawal at Fifier Street:
SELECT transaction_type, amount, account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" and transaction_type = "withdraw";

--Phone call:
SELECT caller, receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60;

--Airport - Fiftyville
SELECT abbreviation, full_name FROM airports WHERE city = "Fiftyville";

--CSF | Fiftyville Regional Airport, look for earliest flight
SELECT hour, minute, id FROM flights WHERE year = 2020 AND month = 7 AND day = 29
AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") ORDER BY hour;
--First flight occured at 8:20 , ID = 36.

--Find out destination:
SELECT city FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE id = 36);
--Destenation is London.
-----------------------------------------------------------------------------------------------------------------------------------------
--List of passengers of flight 36 by PASSPORT NUMBER:
SELECT passport_number FROM passengers WHERE flight_id = 36;

--LICENSE PLATE at crime scene:
SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 10 AND 25;

--ACCOUNT NUMBER at C.S. - THIEF
SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" and transaction_type = "withdraw";

--PHONE NUMBER - caller - THIEF
SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60;

--PHONE NUMBER - reciver - ACCOMPLICE
SELECT receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60;

--Looking for suspects:

-- Thief and Accomplice
SELECT name FROM people
WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);

-- Thief or Accomplice
SELECT name FROM people
WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs
WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25);

--Thief
SELECT name FROM people
WHERE phone_number IN (SELECT caller FROM phone_calls
WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60);

--Accomplice
SELECT name FROM people
WHERE phone_number IN (SELECT receiver FROM phone_calls
WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60);

--Thief
SELECT people.name FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.year = 2020 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = "Fifer Street"
AND atm_transactions.transaction_type = "withdraw";

--Now its time to choose our criminals:

--Thief:
SELECT name FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36)
AND
phone_number IN (SELECT caller FROM phone_calls
WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60)
AND
atm_transactions.year = 2020 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = "Fifer Street"
AND atm_transactions.transaction_type = "withdraw"
AND
license_plate IN (SELECT license_plate FROM courthouse_security_logs
WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 10 AND 25);

--Accomplice:

SELECT name FROM people
WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE caller = (SELECT phone_number FROM people WHERE name = "Ernest")
AND year = 2020 AND month = 7 AND day = 28 AND duration <= 60);
