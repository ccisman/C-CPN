# PDNet
an aotumatic tool for modeling and slicing

This project is a tool for building a PDNet model of c program, and alleviate the state space with slicing.
The c program must satisfy ANSI-C grammar.

## Environment
- Windows 10
- Visual Studio 2017


## INPUT&OUTPUT

- There is some static variables in tree.h, which describe the input and output file.
* origin_dirname : indicate the direction of the input files
* newfile_dirname : indicate the direction of those files after preprocessing.
* rg_sliceOnly_dirname : indicate the direction of the output reachable graph.

- During the running of our project, it will read the files in the direction indicated by 'origin_dirname', and do preprocessing, putting those files after preprocessing in the direction indicated by newfile_dirname. After creating the RG(reachable graph), it will output the RG in the direction indicated by rg_sliceOnly_dirname and calculate the time using to build CPN and RG.
- In our project, we use Graphviz to show the picture of CPN. So you should install Graphviz first.

## Tips

- The program might use a lot of stack memory, so make sure your stack memory enough. Otherwise, it will report stackoverflow.
