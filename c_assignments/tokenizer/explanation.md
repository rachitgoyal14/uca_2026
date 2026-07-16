```c
#include<stdio.h>
#include<string.h>

int main() {

	char str[] = "C++,C,Java,Python,Rust";
	char *token;

	token = strtok(str, ",");
	
	while (token != NULL) {
		printf("%s\n", token);
		token = strtok(NULL, ",");
	
	}

	return 0;
}
```


1. Header Files

```c
#include<stdio.h>
```
this gives us the access to printf statements which allows us to print the values

```c
#include<string.h>
```
this gives us the access to the strtok(), which is actually a pointer in string