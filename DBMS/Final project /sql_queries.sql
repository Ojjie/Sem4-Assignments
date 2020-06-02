/*1. Find the total number of teams playing in the Premier league and their details. */

SELECT *
FROM team,league
WHERE team.league_id = league.league_id AND league.league_name = 'Premier League'

/*2. Find the names of the players playing for the team Borussia Dortmund in the Bundesliga.*/

SELECT player_name_surname 
FROM football_player,league,team
WHERE football_player.team_id = team.team_id AND team.league_id = league.league_id
AND league.league_name = 'Bundesliga' AND team.team_name = 'Borussia Dortmund'  

/*3. Find the number of matches played on each date, and return details like the teams that played, the final score of the game etc.*/

SELECT Date,home_team,away_team,final_score,count(*) as No_of_matches 
FROM Match 
GROUP BY Date,home_team,away_team,final_score;

/*4. Find the total number of matches refereed by all referees from each country. List the classification for each group of referees and sort them by their league_ids.*/

SELECT classification,league_id,SUM(matches_refereed) 
FROM referee 
GROUP BY league_id,classification
ORDER BY league_id, classification ASC;

/*5. Find the total number of red cards received by a player named “Andre Gomes” in the Premier League. */

SELECT red_cards
FROM player_statistics,football_player
WHERE player_statistics.player_id = football_player.player_id AND football_player.player_name_surname = 'Andre Gomes';

/*6. Find the player_ids of the players who have played for more average minutes amongst the players that have the same number of red cards. */

SELECT player_id,red_cards,minutes_played 
FROM player_statistics as s1 
WHERE s1.minutes_played > (SELECT AVG(minutes_played) FROM player_statistics as s2 WHERE s2.red_cards = s1.red_cards);

/*7. Find the names of the teams that have won the third highest number of trophies in their respective leagues. */

SELECT league_id,team_name 
FROM team as t1
WHERE 3 = (SELECT COUNT(distinct t2.team_id) FROM team as t2 WHERE t1.league_id = t2.league_id AND t2.trophies_won >= t1.trophies_won);

/*8. Find all the players and team names.*/

SELECT fp.player_name_surname,team.team_name
FROM football_player as fp
FULL OUTER JOIN team on team.team_id = fp.team_id;

/*9. Find all the matches with league names.*/

SELECT match_id,league_name
FROM match 
FULL OUTER JOIN league ON match.league_id = league.league_id;


