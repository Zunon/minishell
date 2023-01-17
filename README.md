# minishell

## Tokens:
### Variables - `/\$[A-z_?]\w*/`
### Words - Anything that isn't any of the other tokens
### Whitespace - `/\s+/`
### Redirection - `/(<<?)|(>>?)/`
### Pipe - `/\|/`
### Single Quote - `/'/`
### Double Quote - `/"/`

## Grammar:

```
<PIPELINE> 	::=	<SIMPLE-COMMAND>
			|	<SIMPLE-COMMAND> '|' <PIPELINE>
			|   ε

<SIMPLE-COMMAND> ::=  <SIMPLE-COMMAND-ELEMENT>
                   |  <SIMPLE-COMMAND-ELEMENT> <SIMPLE-COMMAND>

<SIMPLE-COMMAND-ELEMENT> ::= <WORD>
                          |  <REDIRECTION-LIST>

<REDIRECTION>   ::= <DIRECTION> <WORD>

<REDIRECTION-LIST> ::= <REDIRECTION>
                    | <REDIRECTION> <REDIRECTION-LIST>
```