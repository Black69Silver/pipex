### Goal of the project  
This project aims to show the use of `pipe`s, `fork`s. This is the use of one command's output as an input for another command. Furthermore, the commands are executed in parallel.  

### User interaction  
* Clone the repository  
* If you run in command line: `make` and then  
	* `./pipex file1 cmd1 cmd2 file2`, where  
	* `file1`, `cmd1`, `cmd2`, and `file2` should be appropriate commands and files of your choice,  
	* the result should be the same as `< file1 cmd1 | cmd2 > file2` run in the command line.  
* If you run in command line: `make bonus` and then  
	* `./pipex_bonus file1 cmd1 cmd2 cmd3 ... cmdn file2`,  
	* the result should be the same as `< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2` run in the command line.  

### Overall Execution Flow  
1. `< file1`: Input Redirection: It redirects `stdin` standard input of `cmd1` command to the content of `file1`.  
	* i.e., `cmd1` will get its input from the content of `file1`.  
2. `cmd1`: Command 1: This is the first command in the pipeline. It processes the input received from `file1`.  
3. `|`: Pipe: It connects `stdout` standard output of `cmd1` to `stdin` standard input of `cmd2`.  
	*  It creates a data pipeline, allowing the output of `cmd1` to serve as the input for `cmd2`.  
4. `cmd2`: Command 2: This is the second command in the pipeline. It processes the input received from `cmd1`.  
5. `> file2`: Output Redirection: It redirects `stdout` standard output of `cmd2` to `file2`.  
	*  In other words, the output produced by `cmd2` is written to `file2`.  

<https://en.wikipedia.org/wiki/Pipeline_(Unix)>
