PROGRAM RecordTest;

TYPE
    String = ARRAY [1..16] OF char;
    Person = RECORD
                 id   : integer;
                 name : String;
             END;
             
VAR
    john, bill : Person;
    i : integer;
    s, t : String;

PROCEDURE print(p : Person);
    BEGIN
        writeln('id = ', p.id, ', name = ', p.name);
    END;
    
BEGIN
    s := 'foo';
    t := s;
    writeln('s = ', s, ', t = ', t);

    john.id   := 1234;
    john.name := 'John';
    i := john.id;
    s := john.name;
    writeln('i = ', i, ', s = ', s);
    write('John: ');
    print(john);
    
    bill.id   := 9876;
    bill.name := 'Bill';
    write('Bill: ');
    print(bill);
    
    bill := john;
    write('Bill: ');
    print(bill);
    
    john.id   := 1357;
    john.name := 'Jack';
    write('John: ');
    print(john);
    write('Bill: ');
    print(bill);
    
    bill.id   := 2468;
    bill.name := 'Will';
    
    write('John: ');
    print(john);
    write('Bill: ');
    print(bill);
END.