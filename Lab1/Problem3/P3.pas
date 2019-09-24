program P3;
const
filename = 'presidents.txt';								//Const of file name
MAX_LENGTH = 12;									//Character limit for name
space = ' ';									
type
	namestring = PACKED ARRAY [1..MAX_LENGTH] of char;
	PresidentInfo = record								// President Info Record that has Start & End Year F and L name and Middle Initials
		StartYear	 : integer;
		EndYear  	 : integer;
		FirstName 	 : namestring;
		LastName  	 : namestring;
		MiddleInitials   : namestring;
		
	end;
	Records = array [1..12] of PresidentInfo;					//Array of Records of President Info
	
var
	
	PR : Records;									// Variable for Records
	myfile: text;									// Text File object

Function readYear : integer;								//Function that reads Start and End Year		
var
	year	:integer;							
	ch	:char;
begin
	
	read(myfile,year);								// Reads the integer value
	readYear := year;								// Returns the integer value
	read(myfile,ch);								// Safety read for white space
	
end;

Function FindSeperation: integer;							//Function used for stopping at the end of the list of presidents
var 
	i: integer;
	Countfile : text;
	data : string;
begin
	assign(Countfile, filename);							//File object assigned 
	reset(Countfile);								// Resets the pointer to the start of the file
	i := 0;
	repeat
	readln(Countfile, data);							//Will parse throught the data until the value is -1 and will have an incrementer
	i := i+1;
	until data = '-1';
	FindSeperation := i;
	close(Countfile);								//close file 
end;

Procedure readName(var name : namestring);						//reads the first name, middle initials, and last name
var
	ch: char;
	i : integer;
begin
	
	i := 1;
	repeat		
	read(myfile,ch);								// reads the character
	if(ch <> space) and (i <= MAX_LENGTH) then					// if not a space or at max length then will store into the name array
		begin
		name[i] := ch;
		i := i + 1;
		end;
	until (ch = space) or (i = MAX_LENGTH) or eoln(myfile);				//will repeat until a space, end of file, or hits max character limit
	
end;

Procedure ReadFile;									// Stores all President information in President Records array
var
	i:integer;
begin

	i:=1;
	repeat
	PR[i].StartYear := readYear;				
	PR[i].EndYear   := readYear;
	readName(PR[i].FirstName);
	readName(PR[i].LastName);
	if not eoln(myfile) then							//Checks if end of line in the file
	begin										// IF it is true then Middle initial will take Last Name value and will read once 												more
	PR[i].MiddleInitials := PR[i].LastName;
	readName(PR[i].LastName);
	end;
	i := i+1;
	until i = FindSeperation;							//Will repeat until it i is the same value of find seperation
end;
Procedure PrintFile;									//Print Start and End years and the Names of President 
var
	i:integer;
begin
	for i:=1 to FindSeperation -1 do
	begin
	write(PR[i].StartYear, ' ', PR[i].EndYear, ' ', PR[i].FirstName, ' ', PR[i].MiddleInitials, ' ', PR[i].LastName );
	writeln();
	end;
end;	
Procedure Search;									// Search the years that a president was active in
var 
	i: integer;
	j: integer;
	k: integer;
	marker : integer;								// Used to mark if a president was found in a year
	SearchYear : array [1..10] of integer;						//Array to store all the search year 
begin
	j:=1;
	read(myfile,i);									// Gets past -1
	
	repeat											
	SearchYear[j] := readYear;							//Will use readYear function to fill array
											//Line 113 - 118 is printing the search years
	if eoln(myfile) then								//Checks for the end of the file so that it does not print -1
	begin
	write(' ');
	end
	else 
	write(SearchYear[j], ' ');
	
	j := j+1;				
	until eoln(myfile);
	
	writeln();									//used new line for aesthetics
	writeln();									//used new line for aesthetics
	
	i := 1;
	k := 1;
	marker := 0;

	repeat 
	for k :=1 to FindSeperation - 1 do						// For loop that checks the years and president and prints the one that matches
	begin
	if ( SearchYear[i] >= PR[k].StartYear ) AND (SearchYear[i] <= PR[k].EndYear) then
	begin
	writeln(SearchYear[i], ' ', PR[k].FirstName, ' ', PR[k].MiddleInitials, ' ', PR[k].LastName);
	marker := 1;									// Sets marker to 1 to show that a match has been found
	end
	end;
	if (marker = 0) then								// If the marker is not 1 then will display the year and the message
	begin
	writeln( SearchYear[i], ' No Match Found'); 
	end;
	i := i +1;									// increment the year
	marker := 0;
	until i = j-1;									// Repeats until matches the entries in the array
end;
begin

	assign(myfile,filename);
	reset(myfile);	
	ReadFile;
	PrintFile;
	writeln();
	writeln('Search Year');
	Search;
end.
