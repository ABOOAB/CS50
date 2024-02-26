-- Keep a log of any SQL queries you execute as you solve the mystery.

-- let's find descriptions of crimes happend in the day of theft maybe we can find a hint
SELECT description
FROM crime_scene_reports
WHERE year = 2021 AND
day = 28 and month = 7;

-- THE DESCRIPTION STATE THAT THERE ARE 3 INTERVIEW DONE WITH WITNESSES. WE HAVE TO FIND WHAT TEHY SAID
SELECT transcript
FROM interviews
WHERE year = 2021 AND
day = 28 AND
month = 7;

-- find the suspect people using information provided from three witnesses about license_plates
-- account number and phone number

select name
from people
join bakery_security_logs as bak
on people.license_plate = bak.license_plate
join bank_accounts as bnk
on people.id = bnk.person_id
join atm_transactions as atm
on bnk.account_number = atm.account_number
join phone_calls as ph
on people.phone_number = ph.caller
where bak.year = 2021 and bak.day = 28 and bak.month = 7 and bak.hour = 10 and bak.minute between 15 and 25
and atm.year = 2021 and atm.day = 28 and atm.month = 7 and ph.year = 2021 and ph.day = 28 and ph.month = 7 and ph.duration < 60;

-- find the suspect to be accomplice

select name from people where phone_number in (select ph.receiver
from people
join bakery_security_logs as bak
on people.license_plate = bak.license_plate
join bank_accounts as bnk
on people.id = bnk.person_id
join atm_transactions as atm
on bnk.account_number = atm.account_number
join phone_calls as ph
on people.phone_number = ph.caller
where bak.year = 2021 and bak.day = 28 and bak.month = 7 and bak.hour = 10 and bak.minute between 15 and 25
and atm.year = 2021 and atm.day = 28 and atm.month = 7 and ph.year = 2021 and ph.day = 28 and ph.month = 7 and ph.duration < 60
);

-- we suspect now in Bruce and Diana as a criminal
-- also maybe Philip or Robin as a accomplice

-- find the earliest flight on the day after the theft which is most probably the criminal flight as 3rd witness mentioned
select * from flights where year = 2021 and day = 29 and month = 7 and origin_airport_id = (
    select id from airports where city = 'Fiftyville'
) order by hour limit 1;


-- find the criminal knowing their flight information
select name from people
join passengers
on passengers.passport_number = people.passport_number
where passengers.flight_id = (select id from flights where year = 2021 and day = 29 and month = 7 and origin_airport_id = (
    select id from airports where city = 'Fiftyville'
) order by hour limit 1
) and passengers.passport_number in (select people.passport_number
from people
join bakery_security_logs as bak
on people.license_plate = bak.license_plate
join bank_accounts as bnk
on people.id = bnk.person_id
join atm_transactions as atm
on bnk.account_number = atm.account_number
join phone_calls as ph
on people.phone_number = ph.caller
where bak.year = 2021 and bak.day = 28 and bak.month = 7 and bak.hour = 10 and bak.minute between 15 and 25
and atm.year = 2021 and atm.day = 28 and atm.month = 7 and ph.year = 2021 and ph.day = 28 and ph.month = 7 and ph.duration < 60);

-- find the distination of the criminal

select city from airports where id = (select destination_airport_id from flights where year = 2021 and day = 29 and month = 7 and origin_airport_id = (
    select id from airports where city = 'Fiftyville'
) order by hour limit 1);

-- find the accomplice knowing all information about criminal
select name from people where phone_number in (select ph.receiver
from people
join bakery_security_logs as bak
on people.license_plate = bak.license_plate
join bank_accounts as bnk
on people.id = bnk.person_id
join atm_transactions as atm
on bnk.account_number = atm.account_number
join phone_calls as ph
on people.phone_number = ph.caller
where bak.year = 2021 and bak.day = 28 and bak.month = 7 and bak.hour = 10 and bak.minute between 15 and 25
and atm.year = 2021 and atm.day = 28 and atm.month = 7 and ph.year = 2021 and ph.day = 28 and ph.month = 7 and ph.duration < 60
and ph.caller = (select phone_number from people where name = (select name from people
join passengers
on passengers.passport_number = people.passport_number
where passengers.flight_id = (select id from flights where year = 2021 and day = 29 and month = 7 and origin_airport_id = (
    select id from airports where city = 'Fiftyville'
) order by hour limit 1
) and passengers.passport_number in (select people.passport_number
from people
join bakery_security_logs as bak
on people.license_plate = bak.license_plate
join bank_accounts as bnk
on people.id = bnk.person_id
join atm_transactions as atm
on bnk.account_number = atm.account_number
join phone_calls as ph
on people.phone_number = ph.caller
where bak.year = 2021 and bak.day = 28 and bak.month = 7 and bak.hour = 10 and bak.minute between 15 and 25
and atm.year = 2021 and atm.day = 28 and atm.month = 7 and ph.year = 2021 and ph.day = 28 and ph.month = 7 and ph.duration < 60)
)));
