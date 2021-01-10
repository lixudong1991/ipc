#libpath = /home/lxd/apue/apue.3e
prom=$1
echo "gcc $prom.c -o $prom -L. -lapue"
gcc -D_XOPEN_SOURCE=700 $prom.c -o build/$prom -L. -lapue -std=c99
