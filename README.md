# SUMMARY :

This program has been developed as part of an internship programm screening task.  
The source program is written in C++11.  
The FGSM (Fast Gradient Sign Method) is used to attack an images classifier adding small noise to the input images.   
![FGSM](fgsmExample.png.PNG)  

# HOW TO BUILD :  
  
You can use the Makefile to build the program.  
The Makefile rules are :  
make : build the program (rebuild the object files only if necessary).  
make clean : remove only the object files.  
make fclean : remove all (the object files and the executable).  
make re :  remove all and rebuild the program.  
  
To build the program for the first time, simply use the command 'make'.  
  
# HOW TO USE :  
  
The Makefile build a program named 'attack'.  
This programm allows you to test the efficiency of different types of attacks.  
The attacks can be tested on all the images, on one specific image or on one random image.  
The image modified by the attack can be saved.  
It can be used as follows :  
  
## usage :  
./attack [-a <type>] [-t <target>] [-s <save to>] [-e <epsilon>] [-r <ratio>] [-uh]  
  
### -a <type>   
fgsm            : (DEFAULT) generate noise with the Fast Gradient Sign Method  
random          : generate random noise  
random-binarize : reverse (0 to 1 or 1 to 0) randomly a small proportion of the inputs  
fgsm-binarize   : use backpropagation to get inputs gradients then reverse the steepest inputs  
none            : No attack, print only original accuracy or prediction  
  
### -t <target>  
all        : (DEFAULT) check all the images in the 'pgm' directory  
random     : pick a random image file in the 'pgm' directory  
<filename> : select a specific file (example: '-t 12.pgm')  
  
### -s <save to>  
If target is 'all', indicate the repertory where to save all the modified images.  
Else, indicate the file name used to save the target image.  
If not present, by default, the modified image(s) are not saved.  
  
### -e <epsilon>  
Used by fgsm and random methods.  
Set the epsilon value that define the noise intensity.  
Default is 0.1.  
  
### -r <ratio>  
Used by fgsm-binarize and random-binarize methods.  
Set the ratio of pixels that will be reverse.  
Default is 0.01 (corresponds to a proportion of 1%).  
  
### -h  
Display help.  
  
### -u  
Conduct unitest on vector/matrix operations (sum, product, transpose, relu, softmax...)  
