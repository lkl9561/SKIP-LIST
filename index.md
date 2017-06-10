<p>Skip lists are data structures which are used in place of balanced trees. It uses probabilistic balancing rather than enforced strict balancing like in BST,AVL etc hence as a result its algorithms are simpler and significantly faster than algorithms in case of BST , AVL etc.</p>
 
<h1>ABSTRACT</h1> 
<p>Binary trees are used for representing abstract data types such as dictionaries and ordered lists. It works better when elements are inserted in random order , when elements are inserted in order it gives poor performance. If it is possible to randomly permute the input it works well with high probability . But in information retrieval queries must be answered on-line so randomly permuting the input is impractical. In binary tree we satisfy certain balance conditions and assure good performance.</p>
 
<p>SKIP-LISTS are probabilistic alternative to balanced trees. They are balanced by consulting a random number generator. Skip lists have bad worst-case performance,but no input sequence consistently produce worst case.( like random Quick sort  ) . It is very unlikely a skip list data structure will be significantly unbalanced. Skip lists have balanced properties similar to search trees built by random insertions , yet do not require insertions to be random. Skip lists do not require input sequence to be random , it consults random number generator for balancing. </p>
 
<p>TAG-LINE : BALANCING A DATA STRUCTURE PROBABILISTICALLY IS EASIER THAN EXPLICITLY MAINTAINING THE BALANCE.</p>
 
<p>Skip lists are also very space efficient. They can be configured to require an average of 1.33 pointers per element (or even less) and do not require balance or priority information to be stored with each node.</p>
 
SKIP-LIST
