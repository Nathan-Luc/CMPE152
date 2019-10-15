PROGRAM OrdChr;

VAR
    ch : char;
    i  : integer;
    
BEGIN
    ch := 'Q';
    writeln('ch: ', ch);
    
    i := ord('a');
    writeln('ord(''a''): ', i);
        
    i := ord('A');
    writeln('ord(''A''): ', i);
        
    i := ord(ch);
    writeln('ord(ch): ', i);
    
    i := ord(ch) + (ord('a') - ord('A'));
    writeln('ord(ch) + (ord(''a'') - ord(''A'')): ', i);
    
    ch := chr(i);
    writeln('ch: ', ch);   
    
    ch := 'Q';
    ch := chr(ord(ch) + (ord('a') - ord('A')));
    writeln('ch: ', ch);
END.