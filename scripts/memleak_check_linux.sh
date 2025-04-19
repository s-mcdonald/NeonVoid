#!/bin/bash

cd ../build/

valgrind \
    --suppressions=../suppressions.supp \
    --leak-check=full \
    --show-leak-kinds=all \
    --track-origins=yes \
    --num-callers=30 \
    --vgdb=no \
    --trace-children=yes \
    --trace-children-skip=/bin/cat,/bin/rm \
    --track-fds=yes \
    ./NeonVoid