
Intelligence uses an FSM state machine 

The next state table and output table is found below
>> The output table is handeled as a 1d array since each state corresponds to a single output

>> The first line in the FSM file denotes the number of rows, second line denotes number of columns
>> S is used to denote a state, the value after it is the value 

CLO = Check left open returns true
CRO = Check right open returns true
CUO = Check up open returns true
CDO = Check down open returns true

NEXT STATE TABLE 
-------------------------------
Current State   CLO CRO CUO CDO

        SN      S1  S2  S3  SN
        S1      S1  S2  S3  S5
        S2      S1  S2  S3  S5
        S3      S1  S2  S3  S5
        S4      S1  S2  S3  S5
        S5      S1  S2  S3  S5
-------------------------------

OUTPUT TABLE (hard coded in code so we can link the function pointers)

 i = 0    i = 1      i = 2       i = 3    i = 4      i = 5 
[NOTHING, MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, BACKTRACK]

IMPORTANT : This maze solving FSM prioritizes left, meaning if left, right, and up are open
            then Micheal will move left. However this functionality is implemented in code 
            so in terms of the FSM only one direction can be open at a time to avoid conflicting
            inputs
