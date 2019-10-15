program P2;
type
  a = array[1..20] of integer;
  b = integer;
var
  a1: array [1..20] of integer; 					// Array for first array values
  a2: array [1..20] of integer;						// Array for second array values
  a3: array [1..20] of integer;						// Array for merged values
  input: integer;							// variable for user input
  size1: integer;							// size variable of the first array
  size2: integer;							// size variable of the second array
  size3: integer;							// size variable of the third array
  i: integer;
  j: integer;
  k: integer;





Procedure Store(var arr: a;var size:b);					// Store Routine to place values into an array
  BEGIN
	i := 1;
	while not eoln do						// Repeats task until end line
		begin
		read(input);						// Takes input from user
		arr[i] := input;					// store value into array
		i := i + 1;						// increment array size
		end;
	readln();							// used to go to the next line
	size := i;							// store size value into a size variable
		
        
  end;
Procedure Print(var arr: a; var size:b);				// Print Routine to print out the array
  Begin

	write('Printing Array: ');
	For i := 1 to size-1 do						// For loop to increment through the array
		begin
		write(arr[i], ' ');					// Print array values
		end;
		writeln(' ');
  end;

Procedure Merge(var arr1, arr2, arr3 :a; var size1,size2,size3: b);     // Merge Routine to merge two arrays into one array
BEGIN
        i := 1;
        j := 1;
        k := 1;
	size3 := size1 + size2 - 1;					// Size of the third array will equal the combination of the two arrays	
        repeat                                                          // Repeat until the array is equal to the size
       
	if (arr1[i] >= arr2[j]) then                                    // Checks if the first array has a larger value than the second array
        begin
        
	if j >= size2 then                                              // Checks if the array is not at the end of the array 
	begin
	arr3[k] := arr1[i];                                             // If the array is at the end then store the other value 
	k := k+1;                                                       // increment the index of the merged array
	i := i+1;                                                       // increment the index of the first array
	end
	
	else                                                    
	begin
        arr3[k] := arr2[j];                                             // else store lower value into the merged array
        k := k + 1;                                                     // increment index of the merged array
        j := j + 1;                                                     // increment index of the second array
        end
        
	end
        
        else if (arr1[i] < arr2[j]) then                                // else if the value is less than the second array
        begin
	if i >= size1 then                                              // checks if the first array index is past the size
	begin
	arr3[k] := arr2[j];                                             // store the value from second array if the first array is passed size index
	k := k + 1;                                                     // increment the index of the merged array
	j := j + 1;                                                     // increment the index of the second array
	end
	else 
	begin
        arr3[k] := arr1[i];                                             // else store the lower value into the merged array
        k := k + 1;                                                     // increment the index of the merged array
        i := i + 1;                                                     // increment the index of the first array
    	end
        end
        until k = size3;                

End;
begin
 
	Store(a1,size1);                                                
	Print(a1,size1);
	Store(a2,size2);
	Print(a2,size2);
        Merge(a1,a2,a3, size1, size2, size3);
   	Print(a3, size3);

end.

//Inputs
//1 5 9 12 16 21 25 
//3 7 12 13 14 15 16 19 20 26
//Outputs
//Printing Array: 1 5 9 12 16 21 25  
//Printing Array: 3 7 12 13 14 15 16 19 20 26  
//Printing Array: 1 3 5 7 9 12 12 13 14 15 16 16 19 20 21 25 26 
//
