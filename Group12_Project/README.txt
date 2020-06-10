- In order for this program to work properly, a folder named TextFiles must be in the same directory as the *.sln file or *.exe file.
- The TextFiles folder must have at least the Staffs.txt file on first run of this program.
- User password in text files are hashed using SHA256.
- All dates data must be in the format YYYY-MM-DD.
- Default password of Staff and Lecturer is username_HCMUS; Default password of Student is their birthdate YYYYMMDD.
- Contents of Staffs.txt:
	+ 1st line: Number of staffs
	+ N-staffs = blocks of lines, each line in a block holds the following information of a staff: username, password (hashed), fullname, email, gender (M or F).
	+ A blank line after each block (Last block must have 2 blank lines after it).
- Contents of the *.csv file containing student list of a class, following columns in exact order: No.; ID; first name; last name; gender (Male/Female); date of birth
- Contents of the *.csv file containing course schedules and infos, following columns in exact order:
	No.;  Course ID; Course name; Class; Lecturer Username; Lecturer Name; Lecturer Email; Lecturer Degree; Lecturer Gender; Start Date; End Date; Day Of Week; Start Time; End Time; Room
- Contents of the *.csv file containing course scoreboard, following columns in exact order: No.; ID; First Name; Last Name; Midterm; Final; Bonus; Total
- It is recommended to export the scoreboard of a course from the system, edit the scores in that exported file then import that file back into the system.
- It is recommended to create the *.csv file from a text file, using MS Excel to make the csv may cause the program to not import the file properly (for some reason...).
- All *.csv files must use the character ';' as delimiter for the columns, or else the program will not work properly.
- Except for Staffs.txt and the *.csv files, DON'T DO ANYTHING WITH THE OTHER *.TXT FILES IN THE TEXTFILES FOLDER.