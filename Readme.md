# Assembler
<p>This project was written as an academic assignment.<br>
To implement an assembler - a compiler for assembly
</p>
<h3>Who Can Use It?</h3>
<p>The was writen in Linux Ubuntu and compatible with this os.<br>
It may work on other platforms also as we didn't relied on any<br>
additional dependencies but the standard libraries. </p>

<h3>How To You Use It?</h3>

Clone the git repository and run the makefile. 
In Linux:
`
git status
`
<br>
Write in terminal
`
$ ./assembler [file-name]
`
<br>
You can specify as many files as you want.
<br>
note that only
`
.as
` files will be accepted. <br>
All of the errors free files will be compiled.<br>

<h3> Output files</h3>
After compilation of each error free file you will get 3 output files:<br>
<ol>
  <li>

`
file_name.ob
` - The data and instruction lines compiled in hexa.
</li>
  <li>

`
file_name.ext
` - Declaration of the external variables.
</li>
  <li>

`
file_name.ent
` - Declaration of the global variables.
</li>
</ol> <br><br>

For additional information - fell free to contact me 
in [Linkedin](https://www.linkedin.com/in/amit-roth/).







