#!/bin/bash
for value in {1..50}
do
    ./cli -n lior$value 'is gay'
done

echo All done    