#!/bin/bash

function menu()
{
	echo 1\) " Codigo del programa."
	echo 2\) " Compilación del archivo."
	echo 3\) " Ejecutar programa."
	echo 4\) " Salir."
}

while true
do
	menu

	read option

	case $option in
		1)cat *.c;;
		2)gcc *.c -o ejecu.ex;;
		3)	
			ejecutable="ejecu.ex"

			echo $ejecutable

			if test -e $ejecutable && test -x $ejecutable
			then
				echo "El archivo se va a ejecutar."

				read nasistentes
				
				if $nasistentes -le 0
				then
					echo "El numero de asistentes debe ser mayor que 0."
				else
					./ejecu.ex $*
				fi
			else
				echo "El ejecutable no existe o no tiene permisos de ejecución"
			fi
			;;
		4)exit 0;;
		*)echo "Opcion no existe, pruebe de nuevo";;
	esac
done
