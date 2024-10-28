FROM drogonframework/drogon
LABEL authors="marcato"

RUN apt-get update && apt-get install -y \
    curl \
    && rm -rf /var/lib/apt/lists/*

# Cria os diretórios
RUN mkdir -p /drogon/install/middleware/build

# Copia os arquivos para o diretório do projeto
COPY . /drogon/install/middleware/

# Move para o diretório de build
WORKDIR /drogon/install/middleware/build

ENV PROXY_URL="http://localhost:8000"

# Executa o CMake a partir do diretório build
RUN cmake -DCMAKE_BUILD_TYPE=Release .. && \
    cmake --build .

EXPOSE 8000

CMD ["./middleware"]