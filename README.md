# C_Crude_Browser

This is a Project/Homework we had at PCLP (Computer Programming and Programming Languages) in the first semester of Computer Science.

We had 4 tasks, each of them implements a function for the final task, where a GUI was made using Ncurses Library, each of them with it's personal .C file.

## Task1
```
- I implemented a "DataBase" with a struct and dynamically allocated arrays for the HTML code (each HTML site contains the number 
    of bytes that is read from each HTML site.
- For the sake of "clean code" in Task1.C I only have calls to functions that are in a Defines.C file that is called from every
    task for the database construction
```

## Task2
```
- After Database is read again with calls to Defines.h, some words are read from stdin and on the screen are shown the sites that
    contain these words
```

## Task3
```
- Same as Task2, but it's a more complex "search" withing the Database.
- Now the programm reads words that should not appear in sites and full sentences that should appear in the sites that are shown
    in the end
```

## Task4
```
- Task4 calculates the checksum of the sites and verifies if the site it's safe to acces or not
- The checksum is calculated with bits operations( shifts, rotations and XOR)
```

## Task5 (browser)
```
- The last task uses the Ncurses library to build a GUI and all the information that is read or shown appears in the application 
    (like a real browser would do)
```
![menubar](/screenshots/menubar.png)
![searchbar](/screenshots/searchbar.png)
