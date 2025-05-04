#!/bin/bash

cd "$(dirname "$0")" # vai pra pasta onde o script está (rathena)

# Finaliza sessões antigas com o mesmo nome
for srv in login char map; do
  screens=$(screen -ls | grep -w "$srv" | awk '{print $1}')
  if [ -n "$screens" ]; then
    echo "Finalizando sessões antigas de $srv..."
    for s in $screens; do
      screen -S "$s" -X quit
    done
  fi
done

echo "Iniciando login-server..."
screen -dmS login ./login-server

echo "Iniciando char-server..."
screen -dmS char ./char-server

echo "Iniciando map-server..."
screen -dmS map ./map-server

echo "Todos os servidores foram iniciados em screen!"
