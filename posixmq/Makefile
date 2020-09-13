cc = gcc
prom = mqcreate
deps = $(shell find ./ -name "*.h")
src = $(shell find ./ -name "*.c")
obj = $(src:%.c=%.o)

$(prom): $(obj)
	$(cc) -o $(prom) $(obj) -L../ -lunpipc -lrt -lpthread
%.o: %.c $(deps) 
	$(cc) -g -c $< -o $@
.PHONY:clean
clean:
	rm -rf $(obj) $(prom)
