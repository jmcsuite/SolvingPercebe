## Compilation and testing ###
function gc {
    if g++ $1.cpp -o $1.exe -Wall -Werror --std=c++20 2> log.txt; then
        echo "Compiled Succesfully!"
    else
        less log.txt;
    fi
}

function tn {
    for (( i=1; i<=$2; i++))
    do
        if ./$1.exe < $i.in > $i.out; then echo "Ran Test $i"
        else
            echo "Exploded Test $i"
        fi
    done
}

function dn {
    for (( i=1; i<=$1; i++))
    do
        if cmp $i.out $i.ans -s; then
            echo "Passed test $i"
        else
            echo "Failed test $i"
        fi
    done
}

export -f gc
export -f tn
export -f dn
