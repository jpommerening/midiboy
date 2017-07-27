FROM alpine:3.6

MAINTAINER Jonas Pommerening <jonas.pommerening@gmail.com>

RUN apk update \
 && apk add make gcc-avr avr-libc

RUN apk add openssl ca-certificates gcc libc-dev libelf libelf-dev git bash \
 && update-ca-certificates \
 && wget -O simavr-1.5.tar.gz https://github.com/buserror/simavr/archive/v1.5.tar.gz \
 && tar xzf simavr-1.5.tar.gz \
 && make -C simavr-1.5 install RELEASE=1 SHELL=bash \
 && apk del gcc libelf-dev libc-dev bash \
 && rm -r simavr-1.5

RUN mkdir /build
WORKDIR /build
VOLUME /build

ENTRYPOINT [ "make" ]
