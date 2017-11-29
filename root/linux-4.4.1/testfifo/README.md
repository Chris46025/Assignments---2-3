Run steps in testfifo folder in order to install the fifo pipe module
	
	1. make
		
	2. sudo insmod testfifo.ko buffer_size=N device_name=fifo string_char_count=N

	3. sudo rmmod testfifo
