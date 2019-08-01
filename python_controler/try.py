#!/usr/bin/env python
import serial
import keyboard, click


serial_port = serial.Serial("/dev/rfcomm2", baudrate = 115200)

while True:
 key = click.getchar()
 archivo = open("prueba.txt","w")
 if keyboard.is_pressed('down') == True or keyboard.is_pressed('up') == True or keyboard.is_pressed('left') == True or keyboard.is_pressed('right') == True or keyboard.is_pressed('+') == True or keyboard.is_pressed('p') == True or keyboard.is_pressed('w') == True or keyboard.is_pressed('s') == True or keyboard.is_pressed('e') == True:

	#if keyboard.is_pressed('up'):
	if key =='\x1b[A':
		print('Arriba')
		estandar = 'aa'
		serial_port.write(estandar)
	
	#elif keyboard.is_pressed('down'):
	elif key =='\x1b[B':
		print('Abajo')
		estandar = 'bb'
		serial_port.write(estandar) 
		
	#elif keyboard.is_pressed('right'):
	elif key =='\x1b[C':
		print('Derecha')
		estandar = 'cc'
		serial_port.write(estandar)
		
	#elif keyboard.is_pressed('left'):
	elif key =='\x1b[D':
		print('Izquierda')
		estandar = 'dd'
		serial_port.write(estandar)

	elif keyboard.is_pressed('+'):
		print('PWM +')
		estandar = '++'
		serial_port.write(estandar)

	elif keyboard.is_pressed('p'):
		print('PWM -')
		estandar = '--'
		serial_port.write(estandar)

	elif keyboard.is_pressed('w'):
		print('manual')
		estandar = 'ww'
		serial_port.write(estandar)

	elif keyboard.is_pressed('e'):
		print('automatico')
		estandar = 'ee'
		serial_port.write(estandar)

	elif keyboard.is_pressed('s'):
		print('stop')
		estandar = 'ss'
		serial_port.write(estandar)

	else:
		print('Uknonwn command')
		estandar = 'Uknonwn command'
		serial_port.write(estandar)	


	archivo.write(str((estandar)))
 	print(estandar)
 	
 else :
	print('Stop')
	estandar = '$psoc1,00,00,00,00#'
	print(estandar)
	archivo.write(str((estandar)))



