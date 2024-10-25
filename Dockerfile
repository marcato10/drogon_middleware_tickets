FROM ubuntu:noble
LABEL authors="marcato"

RUN apt-get update && apt-get install -y \
    git \
    gcc \
    g++ \
    cmake \
    libjsoncpp-dev \
    uuid-dev \
    zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /drogon
RUN git clone https://github.com/drogonframework/drogon . && \
    git submodule update --init && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && \
    make && make install
WORKDIR /app

COPY cmake-build-release/ /app/

# Permissão de execução
RUN chmod +x /app/middleware

EXPOSE 8000
EXPOSE 3000

CMD ["./middleware"]

