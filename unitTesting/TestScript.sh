#!/bin/bash

#assuming make has already been called, & from current dir, all the input lays in a dir called input
for file in ./input/*
do
    ./P2.out "$file" 

done
