# Usa a imagem oficial do MySQL 8.0
FROM mysql:8.0

# Cria o diretório de inicialização
RUN mkdir -p /docker-entrypoint-initdb.d

# Copia APENAS os 3 arquivos desejados
COPY ./sql-files/main.sql /docker-entrypoint-initdb.d/
COPY ./sql-files/web.sql /docker-entrypoint-initdb.d/
COPY ./sql-files/logs.sql /docker-entrypoint-initdb.d/

COPY ./init-user.sh /docker-entrypoint-initdb.d/
RUN chmod +x /docker-entrypoint-initdb.d/init-user.sh
# Porta padrão do MySQL
EXPOSE 3306

# SELECT user, host, plugin FROM mysql.user WHERE user = 'ragnarok';

# ALTER USER 'ragnarok'@'%' IDENTIFIED WITH mysql_native_password BY 'ragnarok';
# FLUSH PRIVILEGES;
