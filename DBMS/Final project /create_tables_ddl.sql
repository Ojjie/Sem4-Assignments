CREATE TABLE League
(
  league_id INT,
  league_name VARCHAR,
  country VARCHAR,
  sponsors VARCHAR,
  current_champions VARCHAR,
  top_scorer VARCHAR,
  PRIMARY KEY (league_id)
);

CREATE TABLE Stadium
(
  stadium_id INT,
  stadium_name VARCHAR,
  city VARCHAR,
  surface_type VARCHAR,
  capacity INT,
  PRIMARY KEY (stadium_id)
);

CREATE TABLE Team
(
  team_id INT,
  team_name VARCHAR,
  address VARCHAR,
  owners VARCHAR,
  trophies_won INT,
  league_id INT,
  stadium_id INT,
  PRIMARY KEY (team_id),
  FOREIGN KEY (league_id) REFERENCES League(league_id),
  FOREIGN KEY (stadium_id) REFERENCES Stadium(stadium_id)
);

CREATE TABLE Manager
(
  manager_id INT,
  manager_name_surname VARCHAR,
  nationality VARCHAR,
  manager_contract_start_date DATE,
  manager_contract_end_date DATE,
  age INT,
  team_id INT,
  PRIMARY KEY (manager_id),
  CHECK(manager_contract_end_date>manager_contract_start_date),
  FOREIGN KEY (team_id) REFERENCES Team(team_id)
);

CREATE TABLE Football_Player
(
  player_id INT,
  player_name_surname VARCHAR,
  position VARCHAR,
  nationality VARCHAR,
  player_contract_start_date DATE,
  player_contract_end_date DATE,
  age INT,
  current_market_value FLOAT,
  team_id INT,
  PRIMARY KEY (player_id),
  CHECK(player_contract_end_date>player_contract_start_date),
  FOREIGN KEY (team_id) REFERENCES Team(team_id)
);

CREATE TABLE Player_statistics
(
  goals INT,
  assists INT,
  yellow_cards INT,
  red_cards INT,
  minutes_played INT,
  player_id INT,
  PRIMARY KEY (player_id),
  FOREIGN KEY (player_id) REFERENCES Football_Player(player_id)
);

CREATE TABLE Referee
(
  license_number INT,
  referee_name_surname VARCHAR,
  classification VARCHAR,
  matches_refereed INT,
  league_id INT,
  PRIMARY KEY (license_number),
  FOREIGN KEY (league_id) REFERENCES League(league_id)
);

CREATE TABLE Match
(
  match_id INT,
  stadium VARCHAR,
  final_score VARCHAR,
  home_team VARCHAR,
  away_team VARCHAR,
  date DATE,
  license_number INT,
  league_id INT,
  PRIMARY KEY (match_id),
  FOREIGN KEY (license_number) REFERENCES Referee(license_number),
  FOREIGN KEY (league_id) REFERENCES League(league_id)
);