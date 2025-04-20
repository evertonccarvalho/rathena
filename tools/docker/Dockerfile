FROM ubuntu:22.04
WORKDIR /rathena

RUN apt-get update && apt-get install -y \
    build-essential \
    default-libmysqlclient-dev \
    libssl-dev \
    zlib1g-dev \
    cmake \
    make \
    g++ \
    screen \
    nano \
    && rm -rf /var/lib/apt/lists/*

ENTRYPOINT [  ]
