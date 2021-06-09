#Minishell
It's serious training project on C language. This is my first team projects. The goal of this project is code own Unix "shell" program like bash. We split our project for 6 parts, my comrade code lexer and parser, my parts is 3-6. More information about parts: 
1) Lexer - this is lexical analyzer, that check correctness of string command like in bash.
2) Parser - in this part, we parse lexered string command to our main structure.
3) Environment variables handler - in this part we search matches with environment variables names in the string, if we found this, we replace this with environment variable value.
4) Executor - in this part we execute our commands, if command is not builtin we call execve().
5) Signal part - in this part we code signals from keyboard (ctrl-C, ctrl-D and ctrl-\).
6) Error handler - simple error handler part, error must be line in bash.
