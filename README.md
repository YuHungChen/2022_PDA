# 2022_PDA

## Lab1
* This is an exercise lab to review corner stitching data structure.
* Organize the space tiles as maximal horizontal stripes.
* No space tile has other space tiles immediately to its right or left and every space tile
must be as wide as possible

* The input example
![image](https://github.com/YuHungChen/2022_PDA/assets/120573862/c7dba8d6-9c49-4e24-a3da-aa1e98eec579)
* The output results
![image](https://github.com/YuHungChen/2022_PDA/assets/120573862/f4c0886c-d889-42db-a5e8-cb0d7eb47c53)

## Lab2
* This programming assignment asks us to write a fixed-outline floorplanner that can handle hard macros
* The primary objective is to place all blocks into the fixed outline successfully and to minimize the cost
* Input file (block)
  ![image](https://github.com/YuHungChen/2022_PDA/assets/120573862/15ee183b-ff90-44d6-a81f-5477d66f2463)

* Input file (nets)
  ![image](https://github.com/YuHungChen/2022_PDA/assets/120573862/9304a910-2a78-4ead-af23-2aca5ed54f45)

* Output file 
  ![image](https://github.com/YuHungChen/2022_PDA/assets/120573862/c5d04d72-c07c-4b02-9a28-ccc600da76d8)


## Lab3
* You would get a chip design and cell information with a global placement result.
* You need to align all standard cells to feasible rows and legalize all standard cells without overlap
* Using abacus
* Initial block locations:
![image](https://github.com/YuHungChen/2022_PDA/assets/120573862/6b909531-b7cd-488d-ae70-be9c2bddfdbc)

* Final results (The yellow square are obstacles)
   * (Top die)
![image](https://github.com/YuHungChen/2022_PDA/assets/120573862/e564f451-053e-4f4b-a5d8-78f8a095a3a8)


   * (Bottom die)
![image](https://github.com/YuHungChen/2022_PDA/assets/120573862/6de295e8-ad79-4fca-af1d-5a402f34fe14)


## compile
make

## Execute
Lab1 : ./Lab1 [input] [output] <br />
Lab2 : ./Lab2 [α value] [input.block name] [input.net name] [output name] <br />
Lab3 : ./Lab3 [INPUT] [OUTPUT] <br />
