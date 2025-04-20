#!/bin/bash

cd "$(dirname "$0")" # vai pra pasta onde o script está (rathena)

echo "Iniciando login-server..."
screen -dmS login ./login-server

echo "Iniciando char-server..."
screen -dmS char ./char-server

echo "Iniciando map-server..."
screen -dmS map ./map-server

echo "Todos os servidores foram iniciados em screen!"
