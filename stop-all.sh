#!/bin/bash

for srv in login char map; do
  if screen -list | grep -q "$srv"; then
    echo "Parando $srv..."
    screen -S "$srv" -X quit
  else
    echo "$srv já está parado ou não existe."
  fi
done

echo "Todos os servidores foram parados (se estavam rodando)."
