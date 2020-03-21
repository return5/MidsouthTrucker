#!/bin/bash
#compile script for midsouth trucker
#compiles midsouth trucker and creates executable named 'trucker'
#defaults to using gcc, but uses clang if user supplies '-c' or '--clang' as argument to script. 
#use argumnet --help to bring up help info

#prints the help message to terminal.
printHelp() {
	printf "compile script for mid south trucker\n"
	printf "compiles midsouth trucker and creates executable names 'trucker'\n"
	printf "defaults to using gcc, but uses clang if user supplies '-c' to script.\n\n"
	printf "options:\n"
	printf " -c   --clang 	use clang instead of gcc\n"
	printf "-help  --help 	prints this page then exits\n"
}

#checks if GCC is installed, and if so it compiles the game with given flags.  if not installed then gives error message and exits.
useGCC() {
	(gcc -v >/dev/null 2>&1 && 
	printf "using GCC\n" &&
	gcc @src_files  -orogueclone -Wall -Wextra -O2 -Iheaders -finline-functions -Wswitch-enum -lm -lncurses -std=gnu11 -otrucker ) ||
	printf "error, gcc seems to not be installed.\n"
}

#compiles game using Clang
useClang() {
	printf "using Clang\n"
	clang @src_files -Iheaders -Wall -Wextra -O2 -lncurses -finline-functions -Wswitch-enum -lm -std=gnu11 -otrucker   
}

main() {
	case "$1" in
		-help | --help)
			printHelp && exit
			;;
		-c | --clang)
			(clang -v >/dev/null 2>&1 && useClang) || (printf "falling back to GCC.\n" && useGCC)
			;;
		*)
			useGCC
			;;
	esac
}

#make list of all .c files to include. file paths are writtent to file 'src_files'
find  "${PWD}/src" -type f > "${PWD}/src_files"

main "$1"
rm src_files
