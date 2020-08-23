cc = gcc
prom = ftok
deps = $(shell find ./ -name "*.h")
src = $(shell find ./ -name "*.c")
obj = $(src:%.c=%.o)

$(prom): $(obj)
	$(cc) -o $(prom) $(obj) -L/home/lxd/project/unix/unpv22e -lunpipc -lrt -lpthread
%.o: %.c $(deps) 
	$(cc) -g -c $< -o $@ 
clean:
	rm -rf $(obj) $(prom)
