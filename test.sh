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


################ TESTS ################

echo -e "$ORANGE################################################"
echo -e "#############    TEST ARGUMENTS    #############"
echo -e "################################################$RESET\n"

result=$(echo "hello world" | ./ft_ssl md5)
echo "Pipe input: $result"

result=$(echo "hello world" | ./ft_ssl md5 -p)
echo "Pipe input with -p option: $result"

result=$(echo "hello world" | ./ft_ssl md5 -q)
echo "Pipe input with -q option: $result"

result=$(echo "hello world" | ./ft_ssl md5 -r)
echo "Pipe input with -r option: $result"

result=$(echo "hello world" | ./ft_ssl md5 -p -r)
echo "Pipe input with -p/-r option: $result"

result=$(echo "hello world" | ./ft_ssl md5 -p -q)
echo "Pipe input with -p/-q option: $result"

result=$(echo "hello world" | ./ft_ssl md5 -q -r)
echo "Pipe input with -q/-r option: $result"

result=$(echo "hello world" | ./ft_ssl md5 -p -q -r)
echo "Pipe input with -p/-q/-r option: $result"

echo -e "$ORANGE################################################"
echo -e "##########    TEST MULTIPLE INPUTS    ##########"
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
    OPENSSL_RESULT=$(cat file | openssl md5 | awk '{print $2}')
    CUSTOM_SSL_RESULT=$(cat file | ./ft_ssl md5 -q)
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
