/*
Name - Tejas Srinivasan
SRN - PES1201800110
Section - 4 'A'
Assignment #4
----------------------------------------------------------------------------------------------------------
*/

/*1 List all books sorting by authors and title */
SELECT BOOK.Title,BOOK_AUTHORS.Author_name
FROM BOOK,BOOK_AUTHORS
WHERE BOOK.Book_id = BOOK_AUTHORS.Book_id
ORDER BY BOOK.Title ASC,BOOK_AUTHORS.Author_name ASC;

/*2 List all the books in the library by publisher and title */
SELECT BOOK.Publisher_name,BOOK.Title
FROM BOOK

/*3 For each branch print the number of copies of each book. Sort by branch id, publisher then book title */
SELECT LIBRARY_BRANCH.Branch_name,BOOK.Title,BOOK_COPIES.No_copies
FROM LIBRARY_BRANCH,BOOK,BOOK_COPIES
WHERE LIBRARY_BRANCH.Branch_id = BOOK_COPIES.Branch_id AND BOOK.Book_id = BOOK_COPIES.Book_id
ORDER BY LIBRARY_BRANCH.Branch_id ASC , BOOK.Publisher_name;

SELECT LIBRARY_BRANCH.Branch_name,BOOK.Title,BOOK_COPIES.No_copies
FROM LIBRARY_BRANCH,BOOK,BOOK_COPIES
WHERE LIBRARY_BRANCH.Branch_id = BOOK_COPIES.Branch_id AND BOOK.Book_id = BOOK_COPIES.Book_id
ORDER BY BOOK.Title;

/*4 How many copies of the book titled Harry Potter are owned by the library branch whose name is ‘Vijayanagar’? */

/* UPDATING and setting is necessary here ? */

SELECT BOOK_COPIES.No_copies,BOOK.Title,LIBRARY_BRANCH.Branch_name
FROM BOOK_COPIES,BOOK,LIBRARY_BRANCH
WHERE BOOK.Title = 'Harry Potter' AND LIBRARY_BRANCH.Branch_name = 'Vijayanagar' AND LIBRARY_BRANCH.Branch_id = BOOK_COPIES.Branch_id 
AND BOOK.Book_id = BOOK_COPIES.Book_id;

/*5 How many copies of the book titled War and Peace are owned by each library branch? */

/* UPDATING and setting is necessary here ? */

SELECT LIBRARY_BRANCH.Branch_name,BOOK.Title,BOOK_COPIES.No_copies
FROM LIBRARY_BRANCH,BOOK,BOOK_COPIES
WHERE BOOK.Title = 'War And Peace' AND BOOK.Book_id = BOOK_COPIES.Book_id AND LIBRARY_BRANCH.Branch_id = BOOK_COPIES.Branch_id;

/*6 For each book authored (or co-authored) by J. K. Rowling, retrieve the title and the number of copies owned by the library branch whose name is Central */

/* UPDATING and setting is necessary here ? */

SELECT BOOK.Title,BOOK_AUTHORS.Author_name,BOOK_COPIES.No_copies,LIBRARY_BRANCH.Branch_name
FROM BOOK,BOOK_AUTHORS,BOOK_COPIES,LIBRARY_BRANCH
WHERE BOOK_AUTHORS.Author_name = 'J.K.Rowling' AND LIBRARY_BRANCH.Branch_name = 'Central' AND LIBRARY_BRANCH.Branch_id = BOOK_COPIES.Branch_id
AND BOOK.Book_id = BOOK_AUTHORS.Book_id AND BOOK.Book_id = BOOK_COPIES.Book_id;

/*7 For each library branch, retrieve the branch name and the total number of books loaned out from that branch. Sort it in descending order of total number of books and branch name */
SELECT LIBRARY_BRANCH.Branch_name,COUNT(BOOK_LOANS.Branch_id) AS Books_Lend
FROM LIBRARY_BRANCH,BOOK_LOANS
WHERE LIBRARY_BRANCH.Branch_id = BOOK_LOANS.Branch_id
GROUP BY BOOK_LOANS.Branch_id
ORDER BY Books_Lend DESC;

/*8 Retrieve the names, addresses, and number of books checked out for all borrowers who have more than five books checked out. Sort the output */
SELECT BORROWER.Borrower_name,BORROWER.Address,COUNT(BOOK_LOANS.Card_no) AS Borrowed_books
FROM BORROWER,BOOK_LOANS
WHERE BOOK_LOANS.Card_no = BORROWER.Card_no
GROUP BY BORROWER.Card_no
HAVING Borrowed_books >5;

/*9 For each book that is loaned out from the Vijayanagar branch and whose Due_date is today, retrieve the book title, the borrower’s name, and the borrower’s address */
SELECT BOOK.Title,BORROWER.Borrower_name,Borrower.Address,BOOK_LOANS.Due_date
FROM BOOK,BORROWER,BOOK_LOANS
WHERE LIBRARY_BRANCH.Branch_name = 'Vijayanagar' AND BOOK_LOANS.Due_date = CURDATE() AND BOOK.Book_id = BOOK_LOANS.Book_id AND BOOK_LOANS.Card_no = BORROWER.Card_no;

/*10 Retrieve the names of all borrowers who do not have any books checked out */
SELECT BORROWER.Borrower_name
FROM BORROWER,BOOK_LOANS
WHERE BORROWER.Card_no NOT IN 
    (SELECT BOOK_LOANS.Card_no
     FROM BOOK_LOANS
     GROUP BY BORROWER.Card_no)
GROUP BY BORROWER.Borrower_name;