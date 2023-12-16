## Parse and order FILL blocks in a .def file

the program will take a .def file and parse it to:
- get the FILL blocks
- order the FILL blocks by their layer and number them
- write the new .def file with the ordered FILL blocks

Make sure the .def file has the following ending:
```
END COMPONENTS
END DESIGN
```

### How to install the program
run the following command:
```
./install
```
This will add the program to your PATH so you can run it from anywhere

### How to run the program

test the program with the following command:
```
fillparsing <input_file>
```
where <input_file> is the .def file you want to parse
The program will create a new file called "ordered_\<inputfile\>" with the ordered FILL blocks

You can also run the program with the following command:
```
fillparsing -r <input_file>
```
The **-r** flag will perform the parsing and save the result in the same file

