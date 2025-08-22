# Assignment 3: Exploring Linux Manual and Help System
## Objective

To learn how to use the Linux manual (man) pages, --help option, and other utilities (whatis, which) to get information about commands and their usage.


## Steps & Commands
> Step 1: Open manual pages for common commands
```bash
man ls
man cp
man mkdir
```

> Step 2: View quick help options for commands
```bash
ls --help
cp --help
```

> Step 3: Search for keywords inside a man page (example: search for 'sort')
```bash
/sort
```

> Step 4: Test ls options
```bash
ls -r      # Reverse order
ls -a      # Show all files including hidden ones
ls -l      # Detailed listing
```

> Step 5: Explore whatis and which
```bash
whatis chmod
which nano
```

# Explanation 
The man command is used to open the manual pages in Linux. It gives detailed information about a command, including its description, options, syntax, and related commands. The --help flag, on the other hand, provides a short summary of the command along with the most commonly used options, making it quicker but less detailed than man. Inside a manual page, you can press / followed by a keyword (for example /sort) to search for specific terms, which helps in navigating long documentation.

When exploring options of the ls command:

- ls -r lists files in reverse order.

- ls -a shows all files, including hidden files (those starting with .).

- ls -l displays a long, detailed listing with file permissions, ownership, size, and modification time.

The whatis command gives a one-line description of what a command does (e.g., chmod – change file modes), while the which command shows the exact location of the command’s executable on the system (e.g., /usr/bin/nano). These tools are very useful for quickly understanding Linux commands directly from the terminal.