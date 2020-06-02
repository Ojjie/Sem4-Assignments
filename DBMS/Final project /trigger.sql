/*The referee, home and away teams must be from the same leagues only, else the trigger is violated.*/

CREATE OR REPLACE FUNCTION check_league() RETURNS trigger AS $check_league$ 

DECLARE 
ref int;

BEGIN 

SELECT r.league_id INTO ref FROM "referee" as r where r.license_number = NEW.license_number;

IF ref <> NEW.league_id THEN 
RAISE EXCEPTION 'Referee must be from the same league!';
END IF; 

RETURN NEW;
END; 

$check_league$ LANGUAGE plpgsql; 

CREATE TRIGGER DIFFERENT_LEAGUE
BEFORE INSERT OR UPDATE 
ON "match" 
FOR EACH ROW EXECUTE PROCEDURE check_league(); 

/*Case when the trigger is violated.*/

/* To be tested after the trigger runs successfully

INSERT INTO "match" VALUES 
('0011','Santiago Bernabeu' , '2-0','Real Madrid','Atletico Madrid','2014-04-02','002','2'),
('0012','Allianz Arena' , '2-1','Bayern Munich','Dortmund','2017-05-01','003','3'),
('0013','Emirates Stadium' , '3-3','Arsenal','Everton','2011-12-18','003','1');

*/