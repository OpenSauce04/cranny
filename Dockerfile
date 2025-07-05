FROM debian:trixie

RUN apt-get update && apt-get upgrade -y && apt-get install -y clang clang-format gcc git libvorbis-dev make
