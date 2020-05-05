/*
Name - Tejas Srinivasan
SRN - PES1201800110
Section - 4 'A'
Assignment #3
----------------------------------------------------------------------------------------------------------
*/



/* Important points to note -
Schema used - LIBRARY 
(Keeps track of books,borrowers,loans etc.)

R.I constraints enforced (indicated by directed arcs)

Choose the appropriate action (reject, cascade, set to NULL, set to default) for each referential integrity constraint, both for the deletion of a referenced tuple and for the update of a primary key attribute value in a referenced tuple

Get one row output for queries in Assignment #4 ? (What is this for ?)

Add your name and details for BORROWER table and BOOK_LOANS table 
Card number - SRN 

Figure out how to write DDL statements and also understand how R.I constraints work 
*/


CREATE 	DATABASE LIBRARY;
USE LIBRARY;

CREATE TABLE PUBLISHER (
    Publisher_name VARCHAR(500) PRIMARY KEY,
    Address VARCHAR(1000),
    Phone DECIMAL(10)
);

CREATE TABLE BOOK (
    Book_id INT PRIMARY KEY,
    Title VARCHAR(500),
    Publisher_name VARCHAR(500),
    FOREIGN KEY (Publisher_name) REFERENCES PUBLISHER(Publisher_name)
    ON DELETE SET NULL
    	 ON UPDATE CASCADE
);

CREATE TABLE BOOK_AUTHORS (
    Book_id INT,
    Author_name VARCHAR(500),
    PRIMARY KEY (Book_id,Author_name),
    FOREIGN KEY (Book_id) REFERENCES BOOK(Book_id)
    ON DELETE CASCADE
    	 ON UPDATE CASCADE
);

CREATE TABLE LIBRARY_BRANCH (
    Branch_id CHAR(8) PRIMARY KEY,
    Branch_name VARCHAR(500) NOT NULL,
    Address VARCHAR(1000)
);

CREATE TABLE BOOK_COPIES (
    Book_id INT NOT NULL,
    Branch_id CHAR(8) NOT NULL,
    No_copies INT DEFAULT 1,
    PRIMARY KEY (Book_id, Branch_id),
    FOREIGN KEY (Book_id) REFERENCES BOOK(Book_id)
    ON DELETE CASCADE 
        ON UPDATE CASCADE,
    FOREIGN KEY(Branch_id) REFERENCES LIBRARY_BRANCH(Branch_id)
    ON DELETE CASCADE
    	 ON UPDATE CASCADE
);

CREATE TABLE BORROWER (
    Card_no INT PRIMARY KEY,
    Borrower_name VARCHAR(500) NOT NULL,
    Address Varchar(1000),
    SRN CHAR(15),
    Phone Decimal(10)
);

CREATE TABLE BOOK_LOANS (
    Book_id INT NOT NULL,
    Branch_id CHAR(8) NOT NULL,
    Card_no INT NOT NULL,
    Date_out DATE,
    Due_date DATE,
    PRIMARY KEY (Book_id, Branch_id, Card_no),
    FOREIGN KEY (Book_id) REFERENCES BOOK(Book_id)
    ON DELETE RESTRICT
    	 ON UPDATE CASCADE,
    FOREIGN KEY (Branch_id) REFERENCES LIBRARY_BRANCH(Branch_id)
    ON DELETE RESTRICT
    	 ON UPDATE CASCADE,
    FOREIGN KEY (Card_no) REFERENCES BORROWER(Card_no)
    ON DELETE RESTRICT	 
        ON UPDATE CASCADE
);

INSERT INTO PUBLISHER 
VALUES
    ('HarperCollins','New York',4087859933),
    ('Penguin Random House','Las Vegas',4087859959),
    ('WP BOOKS','Paris',4087859962),
    ('Macmillan Publishers','Massachusets',4087859971),
    ('Avery Publishing','Banashankari',694206907);

INSERT INTO BOOK
VALUES
    (1,'Harry Potter','Penguin Random House'),
    (2,'The Holdout','HarperCollins'),
    (3,'War and Peace','WP BOOKS'),
    (4,'Vendetta Road','Macmillan Publishers'),
    (5,'How Starbucks Saved My Life','Avery Publishing');

INSERT INTO BOOK_AUTHORS 
VALUES
    (1,'J.K. Rowling'),
    (2,'Mia Sosa'),
    (3,'Leo Tolstoy'),
    (4,'Jay Aaseng'),
    (5,'Michael Gates Gill');
INSERT INTO BORROWER
VALUES
    (1,'Tejas','New York','PES1201800110',3076583368),
    (2,'Joseph','Utah','PES1201800112',3076583366),
    (3,'Sid','California','PES1201800113',3076583370),
    (4,'Sam','California','PES1201800114',3076583399);

INSERT INTO LIBRARY_BRANCH
VALUES
    (1,'Central','Bangalore 560001'),
    (2,'Vijayanagar','Bangalore 560040'),
    (3,'Banashankari','Bangalore 560085');

INSERT INTO BOOK_COPIES
VALUES
    (1,1,5),
    (1,2,10),
    (1,3,12),
    (2,2,11),
    (2,3,25),
    (3,2,35),
    (3,3,40),
    (4,2,54),
    (4,1,12),
    (5,1,20),
    (5,2,7),
    (5,3,3);
    
INSERT INTO BOOK_LOANS
VALUES
    (2,2,1,'2020-02-15','2020-04-26'),
    (1,2,2,'2020-01-19','2020-02-01'),
    (3,3,3,'2020-03-05','2020-05-30'),
    (4,2,4,'2020-02-11','2020-04-28'),
    (1,2,3,'2020-03-01','2020-03-30'),
    (5,3,4,'2020-01-23','2020-04-26'),
    (2,3,1,'2020-02-02','2020-03-16');