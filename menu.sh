#!/bin/bash

function menu()
{
    echo 1\) " Codigo del programa."
    echo 2\) " Compilación del archivo."
    echo 3\) " Ejecutar programa."
    echo 4\) " Salir."
}

function logo()
{
    echo '

 ______   __         __     ______     ______   __  __        ______     __     __    __     __  __     __         ______     ______   ______     ______    
/\  ___\ /\ \       /\ \   /\  ___\   /\__  _\ /\ \_\ \      /\  ___\   /\ \   /\ "-./  \   /\ \/\ \   /\ \       /\  __ \   /\__  _\ /\  __ \   /\  == \   
\ \  __\ \ \ \____  \ \ \  \ \ \__ \  \/_/\ \/ \ \  __ \     \ \___  \  \ \ \  \ \ \-./\ \  \ \ \_\ \  \ \ \____  \ \  __ \  \/_/\ \/ \ \ \/\ \  \ \  __<   
 \ \_\    \ \_____\  \ \_\  \ \_____\    \ \_\  \ \_\ \_\     \/\_____\  \ \_\  \ \_\ \ \_\  \ \_____\  \ \_____\  \ \_\ \_\    \ \_\  \ \_____\  \ \_\ \_\ 
  \/_/     \/_____/   \/_/   \/_____/     \/_/   \/_/\/_/      \/_____/   \/_/   \/_/  \/_/   \/_____/   \/_____/   \/_/\/_/     \/_/   \/_____/   \/_/ /_/ 
                                                                                                                                                            

'
}

function avion()
{
    echo '        ______
            _\ _~-\___
    =  = ==(____AA____D
                \_____\___________________,-~~~~~~~`-.._
                /     o O o o o o O O o o o o o o O o  |\_
                `~-.__        ___..----..                  )
                      `---~~\___________/------------`````
                      =  ===(_________D
                      
                      '
}

logo

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
                   echo "ERROR: Debe introducir un número entero sin caracteres."
                elif [[ $nasistentes -le 0 ]] 
                then
                    echo "ERROR: El número de asistentes debe ser mayor que 0."
                else
                    if [[ $nasistentes -ge 10000 ]]
                    then
                        echo "ERROR: Demasiados asistentes"
                    elif [[ $nasistentes -ge 55 ]]
                    then 
                        echo "       !        "
                        sleep 0.1
                        echo "       ^        "
                        sleep 0.1
                        echo "      / \       "
                        sleep 0.1
                        echo "     /___\      "
                        sleep 0.1
                        echo "    |=   =|     "
                        sleep 0.1
                        for (( i=1; i<=10 ; i++ ))
                        do
                            echo "    |     |     "
                            sleep 0.1
                        done
                        echo "   /|##!##|\     "
                        sleep 0.1
                        echo "  / |##!##| \        "
                        sleep 0.1
                        echo " /  |##!##|  \       "
                        sleep 0.1
                        echo "|  / ^ | ^ \  |      "
                        sleep 0.1
                        echo "| /  ( | )  \ |      "
                        sleep 0.1
                        echo "|/   ( | )   \|      "
                        sleep 0.1
                        echo "    ((   ))          "
                        sleep 0.1
                        echo "   ((  :  ))         "
                        sleep 0.1
                        echo "   ((  :  ))         "
                        sleep 0.1
                        echo "    ((   ))          "
                        sleep 0.1
                        echo "     (( ))           "
                        sleep 0.1
                        echo "      ( )            "

                        for ((i=1; i<50; i++))
                        do
                            echo ""
                            sleep 0.1
                        done
                        ./ejecu.ex $nasistentes
                    else
                        avion
                        ./ejecu.ex $nasistentes
                    fi
                        
                    
                fi
            else
                echo "ERROR: El ejecutable no existe o no tiene permisos de ejecución"
            fi
        ;;
        4)exit 0;;
        *)echo "ERROR: Opción no existe, pruebe de nuevo";;
    esac
done
