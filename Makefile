all:
	arm-none-linux-gnueabi-gcc recv.c -o recv_arm
	arm-none-linux-gnueabi-gcc send.c -o send_arm
	gcc recv.c -o recv_pc
	gcc send.c -o send_pc
	cp send_arm recv_arm recv_pc send_pc /nfs
clean:
	rm send_* recv_*
