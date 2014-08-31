#!/bin/bash
for f in $(find ./EjemplosESO/* -name '*.txt' -print); do
	echo $f $(./build/so-ensamblador -o ${f%.txt}.bc $f)
done
