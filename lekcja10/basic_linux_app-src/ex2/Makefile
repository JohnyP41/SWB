CC:=g++
CFLAGS:=
SRCS:=main.cpp
OBJS:=$(subst .cpp,.o, $(SRCS))

looper: $(OBJS)
	@$(CC) $(CFLAGS) -o looper $(OBJS)

%.o: %.cpp
	@$(CC) $(CFLAGS) -c $<

.PHONY:clean

clean:
	rm -f looper $(OBJS)
