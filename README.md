# MyShell ⌨️
## **Subject**
A project task was to make small Bash-like command-line interpreter capable of starting binaries, including piped and sequenced execution.\
It reads line entered by user, parse it and execute command in a same way as your favorite shell like Zsh, Bash etc.\
MyShell also capable of doing redirections with '>' and '<' symblols, allowing to redirect program data into file or file into program. Like "cat < some.txt".\
It also include history (use UP and DOWN arrows to navigate previously entered commands), it handles multiple commands execution, either separetad by ';' symblos, or with '|' symbol, which is piped execution (allowing one program transfer data to another) as such as "ls -la | grep somethingsomething".\
It was made in a team of me and my pertner.\
He made a parser part and I did all the back-end logic, including piped execution, evironment variables handling.\
I also programmed command line behaviour with using of Termcap library. It includes replacing currently entered text with another when moving through History with UP and DOWN arrows.
## **Usage**
This is a Makefile project\
In your Terminal, clone it\
$ git clone https://github.com/BuddhaCola/MyShell.git \
cd into it\
$ cd MyShell
and enter\
$ make\
and then lauch by entering\
$ ./myshell

![Screen-Recording-2021-09-23-at-1 46 44-PM](https://user-images.githubusercontent.com/63592194/134494785-01369347-cd15-4b9a-a1a5-c04d80e59371.gif)
