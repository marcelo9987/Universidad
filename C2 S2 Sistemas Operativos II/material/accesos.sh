#!/usr/bin/env bash
filename="access.log"
if [[ ! (($1 == "-c") || ($1 == "GET/POST")) ]]
then
  #Hacer algo
fi

if [[ $1 == "-c" ]]
then
    cut -d " " -f 9 log/access.log | sort | uniq
fi
