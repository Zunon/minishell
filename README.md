# minishell

## Tokens:
### Variables - `/\$[^\d]\w+/`
### Words - `/[A-z]\w+/`
### Redirectors - `/(<<?)|(>>?)/`
### Pipes - `/\|/`
### Quotations - `/'|"/`

## Grammar:

```
<PIPELINE> 	::=	<SIMPLE-COMMAND>
			|	<SIMPLE-COMMAND> '|' <PIPELINE>

<SIMPLE-COMMAND> ::=  <SIMPLE-COMMAND-ELEMENT>
                   |  <SIMPLE-COMMAND-ELEMENT> <SIMPLE-COMMAND>

<SIMPLE-COMMAND-ELEMENT> ::= <WORD>
                          |  <REDIRECTION-LIST>

<REDIRECTION>   ::= <DIRECTION> <WORD>

<REDIRECTION-LIST> ::= <REDIRECTION>
                    | <REDIRECTION> <REDIRECTION-LIST>
```