#!/bin/bash
set -e

echo "Waiting for MySQL to be ready..."
while ! mysqladmin ping -h"localhost" -u"root" -p"$MYSQL_ROOT_PASSWORD" --silent; do
    sleep 1
done

echo "Configuring ragnarok user..."
mysql -u root -p"$MYSQL_ROOT_PASSWORD" <<-EOSQL
    ALTER USER '$MYSQL_USER'@'%' IDENTIFIED WITH mysql_native_password BY '$MYSQL_PASSWORD';
    FLUSH PRIVILEGES;
EOSQL

echo "Configuration completed!"
