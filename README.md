# minishell

## Tokens:
### Builtins - `/(echo)|(pwd)|(cd)|(env)|(exit)|(export)|(unset)/`
### Variables - `/\$[^\d]\w+/`
### Words - `/[A-z]\w+/`
### Redirectors - `/(<<?)|(>>?)/`
### Pipes - `/\|/`

## Grammar:
```bnf
<input>  ::= <command> '|' <command>
            |   <command>

<word-list>      ::= <word> 
            |   <word-list> <word>
            | '"' <word-list> '"' | '\'' <word-list> '\''
<assignment-word>    ::= <word> '=' <word>
<redirection>   ::= '>' <word>
                |   '<' <word>
                |   '>>' <word>
                |   '<<' <word>
<command-part>   ::= <word-list> | <assignment-word> | <redirection>
<redirection-list>      ::= <redirection>
                        |   <redirection-list> <redirection>
<command>   ::= <command-part>
            |   <command> <command-part>
```