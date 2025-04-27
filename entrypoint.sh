#!/bin/bash

# Run the original MySQL entrypoint
/usr/local/bin/docker-entrypoint.sh mysqld &

# Wait for MySQL to start
while ! mysqladmin ping -hlocalhost --silent; do
    sleep 1
done

# Executa APENAS os scripts que você quer
mysql -u root -p"${MYSQL_ROOT_PASSWORD}" ragnarok < /docker-entrypoint-initdb.d/main.sql
mysql -u root -p"${MYSQL_ROOT_PASSWORD}" ragnarok < /docker-entrypoint-initdb.d/web.sql
mysql -u root -p"${MYSQL_ROOT_PASSWORD}" ragnarok < /docker-entrypoint-initdb.d/logs.sql
# Keep container running
wait
