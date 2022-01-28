make:
	pio run --target upload --upload-port /dev/ttyACM1
	pio run --target upload --upload-port /dev/ttyACM0
