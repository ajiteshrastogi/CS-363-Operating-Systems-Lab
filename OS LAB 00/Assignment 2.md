# Assignment 2: Understanding Linux Navigation and File Commands

## Objective

To practice basic Linux navigation and file manipulation commands.

## Steps & Commands

> Step 1: Show current directory

``` bash
pwd
```

> Step 2: List files in current directory
``` bash
ls
```

> Step 3: Detailed listing
``` bash
ls -l
```
> Step 4: Show hidden files
``` bash
ls -a
```

> Step 5: Navigate into a directory (example: Documents)
``` bash
cd Documents
```

> Step 6: Move to parent directory
``` bash
cd ..
```

> Step 7: Go to home directory
``` bash
cd ~
```

> Step 8: Create a new directory
``` bash
mkdir test_dir
```

> Step 9: Remove empty directory
``` bash
rmdir test_dir
```

> Step 10: Create directory with content
``` bash
mkdir mydata
cd mydata
touch file1.txt file2.txt
cd ..
```

> Step 11: Remove directory with content
``` bash
rm -r mydata
```

> Step 12: Create a new file
``` bash
touch newfile.txt
```

> Step 13: Delete a file
``` bash
rm newfile.txt
```

> Step 14: Copy a file
``` bash
echo "Linux Assignment" > original.txt
cp original.txt copy.txt
```

> Step 15: Move or rename a file
``` bash
mv copy.txt renamed.txt
```