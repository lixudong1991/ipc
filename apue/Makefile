cc = gcc
prom = myls
deps = $(shell find ./ -name "*.h")
src = $(shell find ./ -name "*.c")
obj = $(src:%.c=%.o)
#libpath = /home/lxd/apue/apue.3e
$(prom): $(obj)
	$(cc) -o $(prom) $(obj) -L. -lapue
%.o: %.c $(deps) 
	$(cc) -g -c $< -o $@ 
clean:
	rm -rf $(obj) $(prom)
