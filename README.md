# Address-Book
Using classes, design an online address book as a unordered linked list with  the nodes dynamically allocated. The address book keeps the track of the names (first and last), addresses, phone numbers.

The menu-driven program should perform the following operations:

Avoid redundant code
Load the data into the address book from a file
Write the data in the address book to a file
Search for a person by last name or phone number (one function to do both)
Add a new entry to the address book
Delete an entry from the address book based on a phone number or last name
The input file is well-formed
might have improper capitalization 
no error checking of the data in the input file needed 
all records are unique, no duplicates
one record per line, items separated by a blank space or a tab
first and last names are one word each
building number: one word ( 6202)
street  name : one word, no str. blvd. etc ( Victory)
city: one word ( Reseda )
phone:  10 digits, no formatting characters ( 8187196458)
all records are well--formed, no missing or extra pieces of data, no bad records
Make sure each function has a description, post/pre-conditions
No vectors
must use classes
Address Book should  be a class
Address should be a class
Record  should be a class
Node should be a class
Sample of a record in the input file

John doe 6202 WinneTka Canoga ca 91336 9193457896

Sample of the output ( formatted) - do not store formatting characters, either all upper case or  proper capitalization

John Doe        6202 Winnetka Canoga,  Ca 91336            (919) 345 7896
