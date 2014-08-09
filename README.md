# WordNet # 

[Programming Assignment 7](http://coursera.cs.princeton.edu/algs4/assignments/wordnet.html)

[Checklist](http://coursera.cs.princeton.edu/algs4/checklists/wordnet.html)

### To Do List ###
* Make destructor, copy constructor, and assignment operator for breadthdirectedfirstpaths

### Things I've learned ###
* Remember to initialize arrays to a default value, otherwise there will be screwy behavior. Default zero initialization is done with () after the declaration.
* Can't use `INFINITY' for maximum integer value. Need to use `<limits>` and call `std::numeric_limits<int>::max()`