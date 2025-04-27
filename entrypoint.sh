#!/bin/bash

# Run the original MySQL entrypoint
/usr/local/bin/docker-entrypoint.sh mysqld &

# Wait for MySQL to start
while ! mysqladmin ping -hlocalhost --silent; do
    sleep 1
done

# Alterar a autenticação do usuário 'ragnarok' para 'mysql_native_password'
echo "Alterando autenticação do usuário ragnarok para mysql_native_password..."
mysql -u root -p"${MYSQL_ROOT_PASSWORD}" -e "ALTER USER 'ragnarok'@'%' IDENTIFIED WITH mysql_native_password BY '${MYSQL_ROOT_PASSWORD}';"

# Verificar as permissões do usuário 'ragnarok'
echo "Verificando permissões do usuário ragnarok..."
mysql -u root -p"${MYSQL_ROOT_PASSWORD}" -e "SHOW GRANTS FOR 'ragnarok'@'%';"

# Conceder todas as permissões ao usuário 'ragnarok'
echo "Concedendo todas as permissões ao usuário ragnarok..."
mysql -u root -p"${MYSQL_ROOT_PASSWORD}" -e "GRANT ALL PRIVILEGES ON ragnarok.* TO 'ragnarok'@'%';"
mysql -u root -p"${MYSQL_ROOT_PASSWORD}" -e "FLUSH PRIVILEGES;"

# Executa APENAS os scripts que você quer
mysql -u root -p"${MYSQL_ROOT_PASSWORD}" ragnarok < /docker-entrypoint-initdb.d/main.sql
mysql -u root -p"${MYSQL_ROOT_PASSWORD}" ragnarok < /docker-entrypoint-initdb.d/web.sql
mysql -u root -p"${MYSQL_ROOT_PASSWORD}" ragnarok < /docker-entrypoint-initdb.d/logs.sql
# Keep container running
wait
