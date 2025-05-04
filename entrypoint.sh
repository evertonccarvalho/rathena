#!/bin/bash

# Inicia o MySQL em segundo plano
/usr/local/bin/docker-entrypoint.sh mysqld &

# Aguarda o MySQL estar pronto para conexões
until mysqladmin ping -hlocalhost --silent; do
    sleep 1
done

# Cria o usuário 'ragnarok' se ainda não existir e altera a autenticação para 'mysql_native_password'
echo "Configurando o usuário 'ragnarok'..."
mysql -u root -p"${MYSQL_ROOT_PASSWORD}" <<-EOSQL
    CREATE USER IF NOT EXISTS 'ragnarok'@'%' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
    ALTER USER 'ragnarok'@'%' IDENTIFIED WITH mysql_native_password BY '${MYSQL_ROOT_PASSWORD}';
    GRANT ALL PRIVILEGES ON ragnarok.* TO 'ragnarok'@'%';
    FLUSH PRIVILEGES;
EOSQL

# Executa os scripts SQL no banco de dados 'ragnarok'
echo "Executando scripts SQL..."
mysql -u root -p"${MYSQL_ROOT_PASSWORD}" ragnarok < /docker-entrypoint-initdb.d/main.sql
mysql -u root -p"${MYSQL_ROOT_PASSWORD}" ragnarok < /docker-entrypoint-initdb.d/web.sql
mysql -u root -p"${MYSQL_ROOT_PASSWORD}" ragnarok < /docker-entrypoint-initdb.d/logs.sql

# Mantém o container ativo
wait
