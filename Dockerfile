FROM debian:trixie

RUN apt-get update && apt-get upgrade -y && apt-get install -y clang clang-format gcc git libogg-dev libvorbis-dev make
