#!/bin/bash

function init {
    pad=$(printf '%.1s' "."{1..70})
    padlength=71

    mkdir -p outputs

    make
    valgrind --leak-check=full --error-exitcode=1 ./AVLRun
    valgrind_error=$?

    printf "\n"
}

function print_result {
    green='\e[32m'
    blue='\e[34m'
    orange='\e[33m'
    red='\e[31m'
    reset='\e[0m'

    if [ "$2" == "passed" ]; then
        result="${green}$2${reset}"
    elif [ "$2" == "failed" ]; then
        result="${red}$2${reset}"
    else
        result="$2"
    fi

    printf "${orange}Test ${blue}$1${reset}"  # Test label in orange, test name in blue
    printf "%*.*s" 0 $((padlength - ${#1} - ${#2} )) "$pad"
    printf "$result\n"
}

function check_test {
    begin_test='outputs/output_'
    begin_result='reference/result_'
    termination='.out'


    tests=("init" "search" "minmax" "succ_pred" "rotations" "insert" "delete" "list_insert" "list_delete")

    for i in ${!tests[@]}
    do
        element=${tests[$i]}
        testFileName=$begin_test$element$termination
        resultFileName=$begin_result$element$termination
        result=$(diff $testFileName $resultFileName | wc -l)

        if [ -f $testFileName ] && [ -f $resultFileName ] && [ "$result" -eq "0" ]; then
            print_result "${tests[$i]}" "passed"
        else
            print_result "${tests[$i]}" "failed"
        fi
    done

    printf "\n"

    result_build_tree_simple=$(diff reference/simple_key_tree.dot outputs/simple_key_tree.dot | wc -l)
    result_build_tree=$(diff reference/key_tree.dot outputs/key_tree.dot | wc -l)
    result=$(($result_build_tree_simple + $result_build_tree))

    if [ "$result" -eq "0" ]; then
        print_result "build_tree" "passed"
    else
        print_result "build_tree" "failed"
    fi


    tests=("inorder_key" "level_key" "range_key")

    for i in ${!tests[@]}
    do
        element=${tests[$i]}
        testFileName=$begin_test$element$termination
        resultFileName=$begin_result$element$termination
        result=$(diff $testFileName $resultFileName | wc -l)

        if [ -f $testFileName ] && [ -f $resultFileName ] && [ "$result" -eq "0" ]; then
            print_result "${tests[$i]}" "passed"
        else
            print_result "${tests[$i]}" "failed"
        fi
    done

    printf "\n"

    if [[ ${valgrind_error} -eq 0 ]]; then
        print_result "Valgrind errors" "passed"
    else
        print_result "Valgrind errors" "failed"
    fi

    printf "\n"
}

init
check_test
make clean_all &> /dev/null
