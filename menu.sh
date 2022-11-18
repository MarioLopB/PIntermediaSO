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
            es_numero="^-?[0-9]+([.][0-9]+)?$"
            
            if test -e $ejecutable && test -x $ejecutable
            then
                echo "El archivo se va a ejecutar."
                echo "Introduzca el número de asistentes."
                read nasistentes
                
                if [[ -z $nasistentes ]] 
                then
                    echo "ERROR: Debe indicar el número de asistentes."
                elif [[ ! $nasistentes =~ $es_numero ]]
                then
                   echo "ERROR: De introducir un número entero sin caracteres."
                elif [[ $nasistentes == 0 ]] 
                then
                    echo "ERROR: El número de asistentes debe ser mayor que 0."
                else
                    ./ejecu.ex $nasistentes
                fi
            else
                echo "ERROR: El ejecutable no existe o no tiene permisos de ejecución"
            fi
        ;;
        4)exit 0;;
        *)echo "ERROR: Opción no existe, pruebe de nuevo";;
    esac
done
