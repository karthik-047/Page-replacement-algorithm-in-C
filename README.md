

								CSCE_611 Exam 1: 15) Implementation of paging system in C

		
Overiew:

	There are several page replacement policies adopted by the Operating System to fetch the necessary pages required to complete the current instruction or process. Here, I have implemented three of the existing replacement algorithms:
	
	1) FIFO  - As the name suggests, the page that had entered the cache the earliest is replaced with the page called.
		Implementation:  An array is used to track the age of the pages. The age of the pages in the cache is incremented every iteration. During replacement, the page with maximum age is replaced and it's age is set to 0.
	
	2) LRU   - In Least Recently Used, the page that was called the earliest is replaced with the page called.
		Implementation: The called page is moved to the top of the memory array. By doing so, the least referenced page is in bottom of the cache and is chosen for replacement.
	
	3) Second Chance  - It is similar to FIFO, but it has an extra field called reference bit. If a page in cache is called again, i.e., cache hit, the reference bit of the bit is made one. During replacement, if the reference bit of the oldest page is 1, it is made to 0 and given a second chance. The next oldest page with reference bit 0 is chosen as the replacement candidate.
		Implementation: In addition to the age[] array, an array is used to store the ref bit of the pages. It is made 0 when the page is first called. In case of a hit, its ref bit is made 1. During replacement, the ref bit of the pages in cache is also checked along with their age. The oldest page with reference bit 0 is chosen for replacement.
		

		###In all the 3 cases, the page fault is represented with 0 and page hit is represented with 1###
		

Files:

	paging_sys.h  - Header files and function, global variable declaration.
	paging_sys.c  - Main source code with the replacement algorithms.
	helper_fn.c   - Source code containing helper functions for the main functions.
	makefile  -  The recipe for the compilation of source code with appropriate dependencies.
	krishnamoorthynatarajanke_exam1.exe - Executable generated after compilation.


Compilation:

	- make/make all: Generate the executable file.
	- make clean: Delete the executable file.
	
Usage:

	- ./krishnamoorthynatarajanke_exam1.exe
	- Choose the options:
		1 for FIFO
		2 for LRU
		3 for Second Chance
		4 for Exit
