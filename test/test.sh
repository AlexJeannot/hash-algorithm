#!/bin/bash

################ VARIABLES GLOBALES ################

GREEN="\033[38;5;113m"
RED="\033[38;5;160m"
GREY="\033[38;5;109m"
ORANGE="\033[38;5;208m"
WHITE="\033[38;5;15m"
CYAN="\033[38;5;51m"
PURPLE="\033[38;5;135m"
RESET="\033[0m"

################ MAKE ################

cd ..
make 

################ FUNCTIONS ################

make_tests ()
{
    echo -e "$RED################################################"
    if [[ "$1" == "md5" ]]
    then
        echo -e "##############    MD5 ALGORITHM    #############"
    elif [[ "$1" == "sha256" ]]
    then
        echo -e "############    SHA256 ALGORITHM    ############"
    fi
    echo -e "################################################$RESET\n"

    ################ TESTS ################

    echo -e "$ORANGE################################################"
    echo -e "#############    TEST ARGUMENTS    #############"
    echo -e "################################################$RESET"

    ################ PIPE ################

    result=$(echo "hello world" | ./ft_ssl $1)
    echo -e "$PURPLE"
    echo -e "Pipe input:$RESET\n$result"

    result=$(echo "hello world" | ./ft_ssl $1 -p)
    echo -e "$PURPLE"
    echo -e "Pipe input with -p option:$RESET\n$result"

    result=$(echo "hello world" | ./ft_ssl $1 -q)
    echo -e "$PURPLE"
    echo -e "Pipe input with -q option:$RESET\n$result"

    result=$(echo "hello world" | ./ft_ssl $1 -r)
    echo -e "$PURPLE"
    echo -e "Pipe input with -r option:$RESET\n$result"

    result=$(echo "hello world" | ./ft_ssl $1 -p -r)
    echo -e "$PURPLE"
    echo -e "Pipe input with -p/-r option:$RESET\n$result"

    result=$(echo "hello world" | ./ft_ssl $1 -p -q)
    echo -e "$PURPLE"
    echo -e "Pipe input with -p/-q option:$RESET\n$result"

    result=$(echo "hello world" | ./ft_ssl $1 -q -r)
    echo -e "$PURPLE"
    echo -e "Pipe input with -q/-r option:$RESET\n$result"

    result=$(echo "hello world" | ./ft_ssl $1 -p -q -r)
    echo -e "$PURPLE"
    echo -e "Pipe input with -p/-q/-r option:$RESET\n$result"
    echo ""

    ################ FILE ################

    result=$(./ft_ssl $1 test_file.txt)
    echo -e "$CYAN"
    echo -e "File input:$RESET\n$result"

    result=$(./ft_ssl $1 -q test_file.txt)
    echo -e "$CYAN"
    echo -e "File input with -q option:$RESET\n$result"

    result=$(./ft_ssl $1 -r test_file.txt)
    echo -e "$CYAN"
    echo -e "File input with -r option:$RESET\n$result"

    result=$(./ft_ssl $1 -q -r test_file.txt)
    echo -e "$CYAN"
    echo -e "File input with -q/-r option:$RESET\n$result"
    echo ""

    ################ STRING ################

    result=$(./ft_ssl $1 -s "hello world")
    echo -e "$GREY"
    echo -e "String input:$RESET\n$result"

    result=$(./ft_ssl $1 -q -s "hello world")
    echo -e "$GREY"
    echo -e "String input with -q option:$RESET\n$result"

    result=$(./ft_ssl $1 -r -s "hello world")
    echo -e "$GREY"
    echo -e "String input with -r option:$RESET\n$result"

    result=$(./ft_ssl $1 -q -r -s "hello world")
    echo -e "$GREY"
    echo -e "String input with -q/-r option:$RESET\n$result"
    echo ""

    ################ MIX ################

    result=$(echo "stdin input" | ./ft_ssl $1 -p -s "hello world" test_file.txt)
    echo -e "$GREEN"
    echo -e "Mix input:$RESET\n$result"

    result=$(echo "stdin input" | ./ft_ssl $1 -p -q -s "hello world" test_file.txt)
    echo -e "$GREEN"
    echo -e "Mix input with -q option:$RESET\n$result"

    result=$(echo "stdin input" | ./ft_ssl $1 -p -r -s "hello world" test_file.txt)
    echo -e "$GREEN"
    echo -e "Mix input with -r option$RESET\n$result"

    result=$(echo "stdin input" | ./ft_ssl $1 -p -q -r -s "hello world" test_file.txt)
    echo -e "$GREEN"
    echo -e "Mix input with -q/-r option:$RESET\n$result"
    echo ""

    echo -e "$ORANGE################################################"
    echo -e "#######    TEST MULTIPLE STDIN INPUTS    #######"
    echo -e "################################################$RESET\n"
    for nb_bytes in {0..2048}
    do
        let "step = $nb_bytes % 100"
        # echo "$step"
        if [ $step == "0" ]
        then
            echo "$nb_bytes / 2048"
        fi
        openssl rand $nb_bytes > file
        OPENSSL_RESULT=$(cat file | openssl $1 | awk '{print $2}')
        CUSTOM_SSL_RESULT=$(cat file | ./ft_ssl $1 -q)
        if [[ "$OPENSSL_RESULT" != "$CUSTOM_SSL_RESULT" ]];
        then
            echo -e "$RED"
            echo -e "INCORRECT RESULT ON TEST $nb_bytes"
            echo -e "$RESET"
            echo "INPUT IN FILE"
            break
        fi
    done
    echo "2048 / 2048"
    echo ""

    echo -e "$ORANGE################################################"
    echo -e "########    TEST MULTIPLE FILE INPUTS    #######"
    echo -e "################################################$RESET\n"

    for nb_bytes in {0..512}
    do
        let "step = $nb_bytes % 100"
        # echo "$step"
        if [ $step == "0" ]
        then
            echo "$nb_bytes / 512"
        fi
        openssl rand $nb_bytes > file
        OPENSSL_RESULT=$(openssl $1 file | awk '{print $2}')
        CUSTOM_SSL_RESULT=$(./ft_ssl $1 -q file)
        if [[ "$OPENSSL_RESULT" != "$CUSTOM_SSL_RESULT" ]];
        then
            echo -e "$RED"
            echo -e "INCORRECT RESULT ON TEST $nb_bytes"
            echo -e "$RESET"
            echo "INPUT IN FILE"
            break
        fi
    done
    echo "512 / 512"
}

make_tests "md5"
make_tests "sha256"

################ CLEAN ################

echo ""
make fclean
rm file