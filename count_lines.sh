
#!/bin/sh
cpp=`find . -type f -name "*.cpp" | xargs cat | wc -l`          
hpp=`find . -type f -name "*.hpp" | xargs cat | wc -l`
cc=`find . -type f -name "*.c" | xargs cat | wc -l`   
hh=`find . -type f -name "*.h" | xargs cat | wc -l`
sh=`find . -type f -name "*.sh" | xargs cat | wc -l`

echo "cpp lines is $cpp "
echo "hpp lines is $hpp "
echo "c   lines is $cc  "
echo "h   lines is $hh  "
echo "sh  lines is $sh  "

((all=$cpp+$hpp+$hpp+$hh))

echo "All code lines without *.sh is $all ! "
