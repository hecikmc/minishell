# Minishell


<table align="center">
  <td>
     
![ezgif com-video-to-gif](https://github.com/hecikmc/minishell/assets/121127625/d85043d9-02c2-49a0-adca-1034e506cf96)

  </td>
</table>

## Description 

Program that replicates the behavior of a **simple bash**

<img width="1475" alt="Screen Shot 2023-09-18 at 5 32 11 PM" src="https://github.com/hecikmc/minishell/assets/121127625/a0c98b26-a90c-4a4f-9520-44499b4b7d42">

* Project developed in 'C' language.
* The project compiles with the 'norma' (Norminette).
* The makefile compiles the program (and the libft needed) with the name: **minishell**

## Mandatory part

Minishell works as follows:
* Displays a **prompt while waiting for a new command**.
* Has functional command **history**.
* Searches and executes the correct executable (based on the PATH variable or using relative or absolute paths).
* Does not use global variables.
* Does **not interpret unclosed quotes** or special characters like \ (backslash) or ; (semicolon).
* **Handles ' (single quote)** to interpret metacharacters in the quoted sequence.
* **Handles " (double quote)** to interpret metacharacters in the quoted sequence except for $ (dollar sign), whose value will be expanded to its assigned value in Minishell's environment variables.
* Handles **redirections**:
    * < redirects input.
    * \> redirects output.
    * "<<" expects a delimiter, then reads from input until a line contains only the entered delimiter.
    * ">>" redirects output in append mode.
* Handles **pipes** (| character). The output of each command in the pipeline is connected via a pipe to the input of the next command. If we leave a pipe open, Minishell waits to receive the next command.
* Manages **environment variables** ($ followed by characters) that are expanded to their values.
* Manages **$?**, which expands to the exit status of the most recently executed command in the pipeline.
* Manages **ctrl-C ctrl-D ctrl-\\**, which should function as in bash.
* When in interactive mode:
    * ctrl-C prints a new prompt on a new line.
    * ctrl-D terminates the shell.
    * ctrl-\ does nothing.
* Implements **built-ins**:
    * **echo** with the -n option.
    * **cd** only with a relative or absolute path.
    * **pwd** without options.
    * **export** without options.
    * **unset** without options.
    * **env** without options or arguments.
    * **exit** without options.

## Usage

The program can be ran with the following instruction (withouth arguments):

```shell
$> ./minishell
```
