FROM alpine:edge as game
RUN apk add --update --no-cache build-base clang make libstdc++ libgcc docker
VOLUME /bots
WORKDIR /app
COPY . .
RUN make
ENV TIMEOUT
CMD [ "./game.exe", "docker run --rm -i mechmania.io/bot/1", "docker run --rm -i mechmania.io/bot/2", "./Map.json", "${TIMEOUT}" ]