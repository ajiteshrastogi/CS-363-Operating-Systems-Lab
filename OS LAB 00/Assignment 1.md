# Assignment 1: Linux File Permissions and Ownership

## Objective
To explore how file permissions and ownership work in Linux by experimenting with different permission settings.

## Steps & Commands

> Step 1: Create a sample file

``` bash
touch sample.txt
```

> Step 2: Check default permissions of the file

``` bash
ls -l sample.txt
```

> Step 3: Change permissions to 777 (read, write, execute for all)

``` bash
chmod 777 sample.txt
ls -l sample.txt
````


> Step 4: Change permissions to 644 (read/write for owner, read-only for group & others)

``` bash
chmod 644 sample.txt
ls -l sample.txt
```

> Step 5: Change permissions to 600 (read/write for owner only)

``` bash
chmod 600 sample.txt
ls -l sample.txt
```

> Step 6: Create a sample script file

``` bash
echo -e '#!/bin/bash\necho "Hello, World!"' > hello.sh
```

> Step 7: Give execute permission and run
``` bash
chmod +x hello.sh
./hello.sh
```


### Explanation

- 777 → Everyone has full access (read, write, execute).

- 644 → Owner can read/write, others can only read.

- 600 → Only owner can read/write, others have no access.

- Ownership defines who controls the file, while permissions control what actions are allowed.

- During experimentation, we see that without execute permission, scripts cannot run; without read/write, files cannot be accessed or modified.